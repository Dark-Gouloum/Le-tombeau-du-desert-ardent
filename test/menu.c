/**
	* \file test/menu.c
	* \brief Test de l'objet menu.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 01:17:05
	*
	* L'objet menu sert à créer et gérer le menu du jeu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/menu.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet menu. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	err_t statut = E_AUTRE;
	menu_t *menu = creer_menu();
	SDL_Event event;

	// INSTRUCTION(S)
	if( !menu ){ // Pas d'objet menu de créer :
		printf("Erreur à la création de menu.\n");
		return(statut);
	}

	statut = E_AUTRE;
	while( statut ){
		while( SDL_PollEvent(&event) ){
		}
	}

	// FIN DU PROGRAMME
	statut = menu->detruire( &menu );
	if( statut != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de menu.\n");
		return(statut);
	}
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(statut);
}
	/* Programme qui test l'objet menu. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

