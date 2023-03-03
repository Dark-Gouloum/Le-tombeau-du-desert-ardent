/**
	* \file test/action.c
	* \brief Test de l'objet action.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Ven. 03 Mars 2023 11:52:38
	*
	* L'objet action sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/action.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet action. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	action_t *action = NULL;

	/* Création des autres variables */
	// INSTRUCTION(S)
	printf("Création de l'objet action...");
	if(!( action=creer_action() )){ // Pas d'objet action de créer :
		printf("Erreur à la création de action.\n");
		status = E_AUTRE;
		goto Quit;
	}
	action->afficher( action );
	printf("OK\n");
	status = E_OK;

	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	err = action->detruire( &action );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de action.\n");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_action();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet action. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

