/**
	* \file test/renderer.c
	* \brief Test de l'objet renderer.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 09:36:28
	*
	* L'objet renderer sert à Liste de fonction gérant un renderer.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>
#include <unistd.h>

#include "../lib/renderer.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t initialisationSDL(){
	if( SDL_Init( SDL_INIT_VIDEO ) ){
		printf("ERREUR :  SDL_Init : %s", SDL_GetError());
		return E_AUTRE;
	}
	return E_OK;
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet renderer. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
		// Lancement de SDL
	err_t statut = E_AUTRE;
	if( initialisationSDL() )	return statut;
		// Création des variables utiles
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event event;
	SDL_Point point;

	// INSTRUCTION(S)
		// Créer la fenêtre
	if( SDL_CreateWindowAndRenderer(500,500,SDL_WINDOW_SHOWN,&window,&renderer) ){
		printf("ERREUR : SDL_CreateWindowAndRenderer : %s", SDL_GetError());
		return 1;
	}
	SDL_SetWindowTitle(window,"Le tombeau du désert ardant");
		// Dessiner dans la fenêtre
	sleep(1);
	SDL_Color couleur1 = {255,165,0,80},
		  couleur2 = {0,165,255,80};
	statut = changerFond_couleur( renderer , &couleur1 );
	if( statut )
		goto Quit;
	SDL_RenderPresent(renderer);

	sleep(1);
	SDL_Rect rectangle = {100,200,300,400};
	statut = dessinerRectangle(renderer, &couleur2, &rectangle);
	SDL_RenderPresent(renderer);

		// Création de bouton
	clique_t boutonCliquer;
	sleep(1);
	statut = E_AUTRE;
	while(statut){
		while( SDL_PollEvent(&event) ){
			switch( event.type ){
				case SDL_QUIT :	statut=E_OK;	break;
				case SDL_MOUSEBUTTONDOWN :
					boutonCliquer = obtenir_positionSouris( &point );
					char bouton[9];
					if( boutonCliquer == CLIQUE_Gauche ){
						bouton[0] = 'G';
						bouton[1] = 'A';
						bouton[2] = 'U';
						bouton[3] = 'C';
						bouton[4] = 'H';
						bouton[5] = 'E';
						bouton[6] = '\0';
					} else if( boutonCliquer == CLIQUE_Mollette ){
						bouton[0] = 'M';
						bouton[1] = 'O';
						bouton[2] = 'L';
						bouton[3] = 'L';
						bouton[4] = 'E';
						bouton[5] = 'T';
						bouton[6] = 'T';
						bouton[7] = 'E';
						bouton[8] = '\0';
					} else if( boutonCliquer == CLIQUE_Droit ){
						bouton[0] = 'D';
						bouton[1] = 'R';
						bouton[2] = 'O';
						bouton[3] = 'I';
						bouton[4] = 'T';
						bouton[5] = 'E';
						bouton[6] = '\0';
					} else {
						bouton[0] = 'E';
						bouton[1] = 'R';
						bouton[2] = 'R';
						bouton[3] = 'E';
						bouton[4] = 'U';
						bouton[5] = 'R';
						bouton[6] = '\0';
					}
					printf("Vous avez fait un clic %s au coorodnnée (%d,%d).\n",bouton,point.x,point.y);
					break;
			}
		}
	}

	// FIN DU PROGRAMME
Quit:
	if( renderer )
		SDL_DestroyRenderer(renderer);
	if( window )
		SDL_DestroyWindow(window);
	SDL_Quit();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(statut);
}
	/* Programme qui test l'objet renderer. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

