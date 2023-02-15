/**
	* \file src/listeObjet.c
	* \brief Définition de l'objet listeObjet.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mer. 15 Févr. 2023 15:17:01
	*
	* L'objet listeObjet sert à stocke de nombreux objet.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/listeObjet.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_listeObjet = 0;
static int unsigned cmpt_elemObjet = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet listeObjet
extern int liste_estVide( listeObjet_t *liste ){
	return (liste->drapeau) == (liste->drapeau)->suivant;
}
extern int liste_dansListe( listeObjet_t *liste ){
	return !( (liste->drapeau) == (liste->ec) );
}

extern err_t liste_suivant( listeObjet_t *liste ){
	(liste->ec) = (liste->ec)->suivant;
	return E_OK;
}
extern err_t liste_precedent( listeObjet_t *liste ){
	(liste->ec) = (liste->ec)->precedent;
	return E_OK;
}
extern err_t liste_enTete( listeObjet_t *liste ){
	liste->ec = (liste->drapeau)->suivant;
	return E_OK;
}
extern err_t liste_enQueue( listeObjet_t *liste ){
	liste->ec = (liste->drapeau)->precedent;
	return E_OK;
}

extern err_t liste_ajouteFin( listeObjet_t *liste , objet_t *objet ){
	char *nomFonction = "liste_ajouteFin : ";
	elemObjet_t *elem = malloc( sizeof(elemObjet_t) );
	if( !elem ){
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return E_MEMOIRE;
	}
	elem->objet = objet;
	elem->suivant = (liste->drapeau);
	elem->precedent = (liste->drapeau)->precedent;
	(elem->suivant)->precedent = elem;
	(elem->precedent)->suivant = elem;
	return E_OK;
}
extern err_t liste_enlever( listeObjet_t *liste ){
	elemObjet_t *elem = (liste->ec);
	(elem->suivant)->precedent = (elem->precedent);
	(elem->precedent)->suivant = (elem->suivant);
	(liste->ec) = elem->precedent;
	(elem->objet)->detruire( &(elem->objet) );
	free( elem );
	return E_OK;
}

extern err_t liste_lit( listeObjet_t *liste , objet_t *objet){
	objet = (liste->ec)->objet;
	return E_OK;
}

	// Methode commune à tout les objets
static void afficher_listeObjet( listeObjet_t *listeObjet ){
	int i=0;
	objet_t *obj = NULL;
	liste_enTete(listeObjet);
	printf("liste = {\n");
	while( liste_dansListe(listeObjet) ){
		liste_lit(listeObjet,obj);
		printf("KO : obj->afficher(obj);\n");
		liste_suivant(listeObjet);
		i++;
	}
	printf("}\nAffichage des %i élément de la liste terminer.\n",i);
}

static err_t detruire_listeObjet( listeObjet_t **listeObjet ){
	char *nomFonction = "detruire_listeObjet : ";
	// Suppression des attributs de l'objet listeObjet
	liste_enQueue(*listeObjet);
	while( liste_dansListe(*listeObjet) ){
		liste_enlever(*listeObjet);
	}
	if( !liste_estVide(*listeObjet) ){
		printf("%s%sliste_estVide : un problème est survenu, tout les éléments n'ont pas était détruits.\n",MSG_E,nomFonction);
	}
	free( (*listeObjet)->drapeau );

	// Suppression de l'objet listeObjet
	free( (*listeObjet) );
	(*listeObjet) = NULL;

	// Destruction de l'objet listeObjet réussie
	cmpt_listeObjet--;
	return(E_OK);
}

extern void afficherSurvivant_listeObjet(){
	printf("Il reste %i elemObjet_t.\n",cmpt_elemObjet);
	printf("Il reste %i listeObjet_t.\n",cmpt_listeObjet);
}

extern listeObjet_t * creer_listeObjet(){
	// Définission des variables utiles
	char *nomFonction = "creer_listeObjet : ";

	// Créer l'objet listeObjet
	listeObjet_t *listeObjet = malloc( sizeof(listeObjet_t) );
	if( !listeObjet ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (listeObjet_t*)NULL;
	}

	// Affecter les attributs
	if(!( (listeObjet->drapeau)=malloc(sizeof(elemObjet_t)) )){
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (listeObjet_t*)NULL;
	}
	(listeObjet->ec) = (listeObjet->drapeau);
	(listeObjet->drapeau)->suivant = (listeObjet->drapeau);
	(listeObjet->drapeau)->precedent = (listeObjet->drapeau);
	(listeObjet->drapeau)->objet = NULL;

	// Affecter les methodes
	listeObjet->detruire = (err_t (*)(void *))detruire_listeObjet;
	listeObjet->afficher = (void (*)(void *))afficher_listeObjet;

	// Renvoyer le bouton
	cmpt_listeObjet++;
	return listeObjet;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

