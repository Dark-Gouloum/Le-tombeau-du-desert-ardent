/**
	* \file src/cree_perso.c
	* \brief Définition de l'objet cree_perso.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Jeu. 09 Mars 2023 13:59:44
	*
	* L'objet cree_perso sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/cree_perso.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_cree_perso = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet cree_perso

	// Methode commune à tout les objets
static void afficher_cree_perso( cree_perso_t *cree_perso ){
	printf("cree_perso{}");
}

static err_t detruire_cree_perso( cree_perso_t **cree_perso ){
	// Suppression des attributs de l'objet cree_perso

	// Suppression de l'objet cree_perso
	free( (*cree_perso) );
	(*cree_perso) = NULL;

	// Destruction de l'objet cree_perso réussie
	cmpt_cree_perso--;
	return(E_OK);
}

extern void afficherSurvivant_cree_perso(){
	printf("Il reste %i cree_perso_t.\n",cmpt_cree_perso);
}

extern cree_perso_t * creer_cree_perso(){
	// Définission des variables utiles
	char *nomFonction = "creer_cree_perso : ";

	// Créer l'objet cree_perso
	cree_perso_t *cree_perso = malloc( sizeof(cree_perso_t) );
	if( !cree_perso ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (cree_perso_t*)NULL;
	}

	// Affecter les attributs

	// Affecter les methodes
	cree_perso->detruire = (err_t (*)(void *))detruire_cree_perso;
	cree_perso->afficher = (void (*)(void *))afficher_cree_perso;

	// Renvoyer le bouton
	cmpt_cree_perso++;
	return cree_perso;
}

extern void creationPersonnage(personage_t * perso){
		
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

