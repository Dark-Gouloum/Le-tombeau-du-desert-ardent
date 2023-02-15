/**
	* \file src/renderer.c
	* \brief Définition de l'objet renderer.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 09:36:28
	*
	* L'objet renderer sert à Liste de fonction gérant un renderer.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/renderer.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
extern err_t changerFond_couleur(SDL_Renderer *renderer, SDL_Color *c){
	char * fonc = "changerFond : ";
	if( SDL_SetRenderDrawColor(renderer, c->r,c->g,c->b,c->a) ){
		printf("%s%sSDL_SetRenderDrawColor : %s",MSG_E,fonc, SDL_GetError());
		return E_COLOR;
	}
	if( SDL_RenderClear(renderer) ){
		printf("%s%sSDL_RenderClear : %s",MSG_E,fonc, SDL_GetError());
		return E_AFFICHE;
	}
	return E_OK;
}

//extern clique_t obtenir_positionSouris( SDL_Point *point){
//	Uint32 b = SDL_GetMouseState(&(point->x),&(point->y));
//	if( b & SDL_BUTTON(1) )
//		return CLIQUE_Gauche;
//	if( b & SDL_BUTTON(2) )
//		return CLIQUE_Mollette;
//	if( b & SDL_BUTTON(3) )
//		return CLIQUE_Droit;
//	return CLIQUE_Erreur;
//}

extern err_t dessinerRectangle(SDL_Renderer *renderer, SDL_Color *c, SDL_Rect *rectangle){
	char * fonc = "dessinerRectangle : ";
	if( SDL_SetRenderDrawColor(renderer, c->r,c->g,c->b,c->a) ){
		printf("%s%sSDL_SetRenderDrawColor : %s",MSG_E,fonc, SDL_GetError());
		return E_COLOR;
	}
	if( SDL_RenderFillRect(renderer, rectangle) ){
		printf("%s%sSDL_RenderFillRect : %s",MSG_E,fonc, SDL_GetError());
		return E_COLOR;
	}
	return E_OK;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

