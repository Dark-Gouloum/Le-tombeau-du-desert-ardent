/**
	* \file src/action.c
	* \brief Définition de l'objet action.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Ven. 03 Mars 2023 11:52:38
	*
	* L'objet action sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/action.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_action = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet action

	// Methode commune à tout les objets
static void afficher_action( action_t *action ){
	printf("action{}");
}

static err_t detruire_action( action_t **action ){
	// Suppression des attributs de l'objet action

	// Suppression de l'objet action
	free( (*action) );
	(*action) = NULL;

	// Destruction de l'objet action réussie
	cmpt_action--;
	return(E_OK);
}

extern void afficherSurvivant_action(){
	printf("Il reste %i action_t.\n",cmpt_action);
}

extern action_t * creer_action(){
	// Définission des variables utiles
	char *nomFonction = "creer_action : ";

	// Créer l'objet action
	action_t *action = malloc( sizeof(action_t) );
	if( !action ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (action_t*)NULL;
	}

	// Affecter les attributs

	// Affecter les methodes
	action->detruire = (err_t (*)(void *))detruire_action;
	action->afficher = (void (*)(void *))afficher_action;

	// Renvoyer le bouton
	cmpt_action++;
	return action;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

