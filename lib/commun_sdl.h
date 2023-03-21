#ifndef _COMMUN_SDL_H_
#define _COMMUN_SDL_H_

/**
	* \file lib/commun_sdl.h
	* \brief Définition des donnée commune à tous les fichiers comportant des fonction sdl.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 00:49:37
	*
	* Définition des donnée commune à tous les fichiers comportant des fonction sdl :
	*	+ L'inclusion de librairies commune :
	*		- commun
	*		- SDL2
	*	+ La gestion des erreurs.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

// CRÉATION(S) DE(S) CONSTANTE(S) BASIQUE(S)
#define SEP_WIDGET 10

#define NB_LIB_SDL 2

#define SDL_TTF 1<<0
#define SDL_IMG 1<<1
/*
#define SDL_MIX 1<<2
#define SDL_NET 1<<3
#define SDL_GFX 1<<4
#define SDL_GPU 1<<5
#define SDL_RTF 1<<6
*/

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)
typedef enum clique_s {
	C_UNK = 0,
	C_GAUCHE,
	C_MOLLETTE,
	C_DROIT,
} clique_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/** \brief La fonction initialisant la bibliothéque SDL.
	* \author Erwan PÉCHON
	* \param[in] La liste des bibliothèque à initialiser, en plus de la SDL.
	* \return En cas de problème, renvoit E_INIT, Sinon, renvoit E_OK.
	*
	* La fonction 'initialisation_SDL' initialise la bibliothéque SDL et ses sous-bibliothéque.
	* Cette fonction doit être au tout début de la fonction 'main' de chaque programme utilisant la bibiothéque SDL.
	*
	*/
extern err_t initialisation_SDL(Uint32 choix,...);
/** \brief La fonction initialisant la bibliothéque SDL_TTF.
	* \author Erwan PÉCHON
	*
	* La fonction 'fermer_SDL' ferme la bibliothéque SDL et ses sous-bibliothéque, qui ont était initialisé.
	* Cette fonction doit être à la fin de la fonction 'main' de chaque programme utilisant la bibiothéque SDL.
	*
	*/
extern void fermer_SDL();
extern clique_t obtenir_clique(SDL_Point *pt);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
