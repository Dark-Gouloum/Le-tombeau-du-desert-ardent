/**
	* \file src/commun_sdl.c
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
#include "../lib/commun_sdl.h"

// CRÉATION(S) DE(S) CONSTANTE(S) BASIQUE(S)
static Uint32 librairieInitialiser = 0;

static void (*const SDL_QUIT_FUNC[NB_LIB_SDL])(void) = {
	TTF_Quit
	, IMG_Quit
	/*
	, MIX_Quit
	, NET_Quit
	, GFX_Quit
	, GPU_Quit
	, RTF_Quit
	*/
};
static const char SDL_LIB_NOM[NB_LIB_SDL][4] = {
	"TTF"
	, "IMG"
	/*
	, "MIX"
	, "NET"
	, "GFX"
	, "GPU"
	, "RTF"
	*/
};

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
extern err_t initialisation_SDL(Uint32 choix,...){
	va_list va;	va_start(va,choix);
	err_t err = E_INIT;

	if( SDL_Init( SDL_INIT_VIDEO ) != 0 ){
		MSG_ERR(err,"la bibliothéque SDL2");
		MSG_ERR_COMP("SDL_Init",SDL_GetError());
		return(err);
	}
	printf("SDL initialisé avec succés.\n");
	printf("initialisation des sous-librairies :\n");

	if( choix & SDL_TTF ){
		if( TTF_Init() != 0 ){
			MSG_ERR(err,"la bibliothéque SDL2_TTF");
			MSG_ERR_COMP("TTF_Init",SDL_GetError());
			return(err);
		}
		librairieInitialiser+= SDL_TTF;
		printf("\t- SDL_TTF initialisé avec succés.\n");
	}
	if( choix & SDL_IMG ){
		int IMG_Flags = va_arg( va,int );
		if( IMG_Init(IMG_Flags) == 0 ){
			MSG_ERR(err,"la bibliothéque SDL2_IMG");
			MSG_ERR_COMP("IMG_Init",SDL_GetError());
			return(err);
		}
		librairieInitialiser+= SDL_IMG;
		printf("\t- SDL_IMG initialisé avec succés.\n");
	}
	/*
	if( choix & SDL_MIX ){
		if( MIX_Init() ){
			MSG_ERR(err,"la bibliothéque SDL2_MIX");
			MSG_ERR_COMP("MIX_Init",SDL_GetError());
			return(err);
		}
		librairieInitialiser+= SDL_MIX;
		printf("\t- SDL_MIX initialisé avec succés.\n");
	}
	if( choix & SDL_NET ){
		if( NET_Init() ){
			MSG_ERR(err,"la bibliothéque SDL2_NET");
			MSG_ERR_COMP("NET_Init",SDL_GetError());
			return(err);
		}
		librairieInitialiser+= SDL_NET;
		printf("\t- SDL_NET initialisé avec succés.\n");
	}
	if( choix & SDL_GFX ){
		if( GFX_Init() ){
			MSG_ERR(err,"la bibliothéque SDL2_GFX");
			MSG_ERR_COMP("GFX_Init",SDL_GetError());
			return(err);
		}
		librairieInitialiser+= SDL_GFX;
		printf("\t- SDL_GFX initialisé avec succés.\n");
	}
	if( choix & SDL_GPU ){
		if( GPU_Init() ){
			MSG_ERR(err,"la bibliothéque SDL2_GPU");
			MSG_ERR_COMP("GPU_Init",SDL_GetError());
			return(err);
		}
		librairieInitialiser+= SDL_GPU;
		printf("\t- SDL_GPU initialisé avec succés.\n");
	}
	if( choix & SDL_RTF ){
		if( RTF_Init() ){
			MSG_ERR(err,"la bibliothéque SDL2_RTF");
			MSG_ERR_COMP("RTF_Init",SDL_GetError());
			return(err);
		}
		librairieInitialiser+= SDL_RTF;
		printf("\t- SDL_RTF initialisé avec succés.\n");
	}
	*/

	va_end(va);
	return E_OK;
}
extern void fermer_SDL(){
	for( int i=NB_LIB_SDL-1 ; i+1 ; i-- ){
		if( librairieInitialiser & (1<<i) ){
			SDL_QUIT_FUNC[i]();
			printf("\t- SDL_%s quité avec succés.\n",SDL_LIB_NOM[i]);
		}
	}
	SDL_Quit();
	printf("SDL quité avec succés.\n");
}
extern clique_t obtenir_clique(SDL_Point *pt){
	Uint32 b = SDL_GetMouseState( &(pt->x) , &(pt->y) );
	if( b & SDL_BUTTON(1) ) // Si clic gauche
		return C_GAUCHE;
	else if( b & SDL_BUTTON(2) ) // Si clic mollette
		return C_MOLLETTE;
	else if( b & SDL_BUTTON(3) ) // Si clic droit
		return C_DROIT;
	// Si aucun clic
	return C_UNK;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

