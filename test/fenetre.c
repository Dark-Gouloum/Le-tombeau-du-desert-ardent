/**
	* \file test/fenetre.c
	* \brief Test de l'objet fenetre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 13 Févr. 2023 11:20:15
	*
	* L'objet fenetre sert à creer et gerer une fenêtre basique.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>
#include <string.h>

#include "../lib/fenetre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet fenetre. */
int main(int argc, char *argv[]) {
	// INITIALISATION DE(S) VARIABLE(S)
	char nomFonction[ 3 + strlen(argv[0]) ];	sprintf(nomFonction,"%s : ",argv[0]);
	err_t status = E_AUTRE;
	if( status=initialisation_SDL() ){
		printf("%s%sInitialisation de la SDL\n",MSG_E,nomFonction);
		return(status);
	}
	printf("création de la fenêtre\n");
	fenetre_t *fenetre = creer_fenetre( (coord_t){500,500} , SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE, nomFonction);
	SDL_Event event;

	// INSTRUCTION(S)
	printf("fenêtre créer\n");
	if( !fenetre ){ // Pas d'objet fenetre de créer :
		printf("%s%screation de la fenêtre\n",MSG_E,nomFonction);
		return(E_AUTRE);
	}

	SDL_Delay(1000);
	printf("changement de couleur\n");
	SDL_Color c = {255,0,0,255};
	if( changerCouleur( fenetre , &c ) ){
		printf("%s%schangement de la couleur de la fenêtre\n",MSG_E,nomFonction);
		goto Quit;
	}
	if( SDL_RenderClear(getRenderer(fenetre)) ){
		printf("%s%sSDL_RenderClear : %s",MSG_E,nomFonction, SDL_GetError());
		goto Quit;
	}
	fenetre->afficher(fenetre);

	SDL_Delay(1000);
	printf("Gestion des évenements\n");
	status = E_AUTRE;
	while(status){ while(SDL_PollEvent(&event) ){
		switch( event.type ){
			case SDL_QUIT :	status=E_OK;	break;
		}
	} }
	// FIN DU PROGRAMME
Quit:
	status = fenetre->detruire( &fenetre );
	if( status != E_OK ){ // Echec à la destruction :
		printf("%s%sdestruction de la fenetre.\n",MSG_E,nomFonction);
		return(status);
	}
	printf("\nIl reste %i objet du type fenetre.",cmpt_fenetre);
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet fenetre. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

