#ifndef _RENDERER_H_
#define _RENDERER_H_

/**
	* \file lib/renderer.h
	* \brief Définition de l'objet renderer.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 09:36:28
	*
	* L'objet renderer sert à Liste de fonction gérant un renderer.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../lib/err.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)
typedef enum clique_s {
	CLIQUE_Erreur = 0,
	CLIQUE_Gauche,
	CLIQUE_Mollette,
	CLIQUE_Droit
} clique_t;

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
extern err_t changerFond_couleur(SDL_Renderer *renderer, SDL_Color *couleur);
extern clique_t obtenir_positionSouris( SDL_Point *point);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
