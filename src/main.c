/**
  * \file main.c
  * \brief Le fichier source du produit final
  * \author Clement FEFEU ; Victor FOUQUERAY ; Dylan GRAMMONT ; Erwan PECHON
  * \version 0.1
  * \date Ven. 27 Janv. 2023 14:27:35
  *
  * Le fichier source du jeu 'Le tombeau du désert ardent'.
  * Aller voir le README.md pour plus de détaille.
  *
  */

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
int main(){  /* Programme qui lance le tombeau du desert ardent */
	// INITIALISATION DE(S) VARIABLE(S)
		// Lancement de SDL
	int statut = 1;
	if(0 != SDL_Init(SDL_INIT_VIDEO)){
		printf("Erreur SDL_Init : %s", SDL_GetError());
		return statut;
	}
		// Création des variables dynamiques
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event event;
	// INSTRUCTION(S)
		// Création de la fenêtre
	if( SDL_CreateWindowAndRenderer(500,500,SDL_WINDOW_SHOWN,&(window),&(renderer)) ){
		printf("Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
		goto Quit;
	}
	SDL_SetWindowTitle(window,"Le tombeau du désert ardant");
		// Dessiner dans la fenêtre
	sleep(1);
	if( SDL_SetRenderDrawColor(renderer, 255,165,0,80) ){	printf("Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());	goto Quit;	}
	if( SDL_RenderClear(renderer) ){	printf("Erreur SDL lors de la création d'un dessin : %s", SDL_GetError());	goto Quit;	}
	SDL_RenderPresent(renderer);
	sleep(1);
	if( SDL_SetRenderDrawColor(renderer, 0,165,255,80) ){	printf("Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());	goto Quit;	}
	if( SDL_RenderDrawLine(renderer, 0,0,1000,1000) ){	printf("Erreur SDL lors de la création d'un dessin : %s", SDL_GetError());	goto Quit;	}
	SDL_RenderPresent(renderer);
	sleep(1);
		// Création de bouton
	while(statut){
		while( SDL_PollEvent(&event) ){
			switch( event.type ){
				case SDL_QUIT :	statut = 0;	break;
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
	return statut;
} /* Programme qui lance le tombeau du desert ardent */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //
