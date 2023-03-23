/**
	* \file src/PNJ.c
	* \brief Définition de l'objet PNJ.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Jeu. 23 Mars 2023 01:36:49
	*
	* L'objet PNJ sert à gérer les Personnage Non Joueur du jeu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/PNJ.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_PNJ = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet PNJ

	// Methode commune à tout les objets
static void afficher_PNJ( PNJ_t *PNJ ){
	afficher_personnage( PNJ , "mechant");
}

static err_t detruire_PNJ( PNJ_t **PNJ ){
	// Suppression des attributs de l'objet PNJ
	free( (*PNJ)->nom );

	// Suppression de l'objet PNJ
	free( (*PNJ) );
	(*PNJ) = NULL;

	// Destruction de l'objet PNJ réussie
	cmpt_PNJ--;
	return(E_OK);
}

extern void afficherSurvivant_PNJ(){
	printf("Il reste %i PNJ_t.\n",cmpt_PNJ);
}

extern PNJ_t * creer_PNJ(){
	// Créer l'objet PNJ
	PNJ_t *PNJ = malloc( sizeof(PNJ_t) );
	if( !PNJ ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'PNJ'");
		return (PNJ_t*)NULL;
	}

	// Affecter les attributs
	PNJ->nom = NULL;
	attribuer_personnage(PNJ,0,0,0,0,0,0,NULL);

	// Affecter les methodes
	PNJ->detruire = (err_t (*)(void *))detruire_PNJ;
	PNJ->afficher = (void (*)(void *))afficher_PNJ;

	// Renvoyer le bouton
	cmpt_PNJ++;
	return PNJ;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

