/**
	* \file src/liste.c
	* \brief Définition de l'objet liste.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mer. 15 Févr. 2023 15:17:01
	*
	* L'objet liste sert à stocke des pointeurs sur des objets.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../lib/liste.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_liste = 0;
static int unsigned cmpt_nbObjetDansListe = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet liste
extern int liste_taille( liste_t *liste ){
	return liste->nb;
}

extern err_t liste_ajoute( liste_t *liste , void * obj ){
	char *nomFonction = "liste_ajoute : ";
	if( liste->nb ){
		void **new_liste = malloc( sizeof(void*) * ((liste->nb)+1) );
		if( !new_liste ){ // malloc à échouer :
			printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
			return E_MEMOIRE;
		}
		// Copie de la liste
		for( int i=0 ; i<liste->nb ; i++ ){
			new_liste[i] = liste->liste[i];
		}
		// Suppression de l'ancienne liste
		free(liste->liste);
		(liste->liste) = new_liste;
	}
	// Ajout de l'objet à la liste
	liste->liste[ liste->nb ] = obj;
	(liste->nb)++;
	cmpt_nbObjetDansListe++;
	return E_OK;
}

extern int liste_recherche( liste_t *liste, void *obj ){
	for( int i=0 ; i<liste->nb ; i++ ){
		if( liste->liste[i] == obj ){
			return i;
		}
	}
	return -1;
}
extern err_t liste_enlever_obj( liste_t *liste, void * obj ){
	int pos = liste_recherche(liste,obj);
	if( pos != -1 ){
		return liste_enlever_pos(liste,pos);
	}else{
		printf("%s%sobj : L'objet n'est pas dans la liste.\n",MSG_E,"liste_enlever_obj");
		return(E_OBTENIR);
	}	
}
extern err_t liste_enlever_pos( liste_t *liste, int pos ){
	if( pos < liste_taille(liste) ){
		printf("L'élément n°%d est hors de la liste.",pos);
		return E_ARGUMENT;
	}
	char *nomFonction = "liste_enlever : ";
	err_t err=E_OK;
	if( (pos>=0) && ((liste->nb)>1) && (pos<(liste->nb)) ){
		void **new_liste = malloc( sizeof(void*) * ((liste->nb)-1) );
		if( !new_liste ){ // malloc à échouer :
			printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
			return E_MEMOIRE;
		}
		int i,j;
		// Copie de la liste
		for( i=j=0 ; i<liste->nb ; i++ ){
			if( i != pos ){
				new_liste[j++] = liste->liste[i];
			} else {
				objet_t *obj = (objet_t*)( liste->liste[i] );
				err = obj->detruire( &obj );
			}
		}
		// Suppression de l'ancienne liste
		free(liste->liste);
		(liste->liste) = new_liste;
	}else if( (liste->nb) == 1 ){
		objet_t *obj = (objet_t*)( liste->liste[0] );
		err = obj->detruire( &obj );
	} else if( pos < 0 ){
		printf("%s%spos : Les indiçage commence à partir de 0.\n",MSG_E,nomFonction);
		return E_MEMOIRE;
	} else {
		printf("%s%spos : Il n'y à pas assez d'élément pour accéder à cette indicage.\n",MSG_E,nomFonction);
		return E_MEMOIRE;
	}
	// Ajout de l'objet à la liste
	(liste->nb)--;
	cmpt_nbObjetDansListe--;
	return err;
}

extern void * liste_lit( liste_t *liste, int pos){
	if( pos < liste_taille(liste) ){
		return (liste->liste)[pos];
	}
	return NULL;
}

	// Methode commune à tout les objets
static void afficher_liste( liste_t *liste ){
	int i=0;
	int nbObj = liste_taille( liste );
	void *obj;
	printf("liste = {\n");
	for( i=0 ; i<nbObj ; i++ ){
		printf("\t");
		obj = liste_lit( liste , i );
		( (objet_t*)obj )->afficher( obj );
		printf("\n");
	}
	printf("}( %i élément(s) )",i);
}
static err_t detruire_liste( liste_t **liste ){
	err_t err=E_OK;
	int nbObj = liste_taille( *liste );
	void * obj = NULL;
	// Suppression des attributs de l'objet liste
	for( int i=0 ; i<nbObj ; i++ ){
		obj = liste_lit( *liste , i );
		err = ( (objet_t*)obj )->detruire( &obj );
		cmpt_nbObjetDansListe--;
	}
	free( (*liste)->liste );

	// Suppression de l'objet liste
	free( (*liste) );
	(*liste) = NULL;

	// Destruction de l'objet liste réussie
	cmpt_liste--;
	return(err);
}

extern void afficherSurvivant_liste(){
	printf("Il reste %i element de liste.\n",cmpt_nbObjetDansListe);
	printf("Il reste %i liste_t.\n",cmpt_liste);
}

extern liste_t * creer_liste(){
	// Définission des variables utiles
	char *nomFonction = "creer_liste : ";

	// Créer l'objet liste
	liste_t *liste = malloc( sizeof(liste_t) );
	if( !liste ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (liste_t*)NULL;
	}

	// Affecter les attributs
	liste->nb = 0;
	liste->liste = malloc( sizeof(void*) );
	if( !liste->liste ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (liste_t*)NULL;
	}
	liste->liste[0] = NULL;

	// Affecter les methodes
	liste->detruire = (err_t (*)(void *))detruire_liste;
	liste->afficher = (void (*)(void *))afficher_liste;

	// Renvoyer le bouton
	cmpt_liste++;
	return liste;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

