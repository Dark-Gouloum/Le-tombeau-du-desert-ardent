/**
	* \file src/fenetre.c
	* \brief Définition de l'objet fenetre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mer. 15 Févr. 2023 14:30:07
	*
	* L'objet fenetre sert à crée et gére une fenêtre.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/fenetre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_fenetre = 0;
static Uint32 librairieInitialiser = 0;

void (*const SDL_QUIT_FUNC[NB_LIB_SDL])(void) = {
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
const char SDL_LIB_NOM[NB_LIB_SDL][4] = {
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

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet fenetre
extern err_t initialisation_SDL(Uint32 choix,...){
	va_list va;	va_start(va,choix);
	char *nomFonction = "initialisation_SDL : ";

	if( SDL_Init( SDL_INIT_VIDEO ) ){
		printf( "%sSDL_Init : %s" , MSG_E , SDL_GetError() );
		return E_INIT;
	}
	printf("%sSDL initialisé avec succés.\n",nomFonction);

	if( choix & SDL_TTF ){
		if( TTF_Init() ){
			printf( "%s%sTTF_Init : Un problème est survenu", MSG_E, nomFonction );
			return E_INIT;
		}
		librairieInitialiser+= SDL_TTF;
		printf("%sSDL_TTF initialisé avec succés.\n",nomFonction);
	}
	if( choix & SDL_IMG ){
		int IMG_Flags = va_arg( va,int );
		if( IMG_Init(IMG_Flags) ){
			printf( "%s%sIMG_Init : Un problème est survenu", MSG_E, nomFonction );
			return E_INIT;
		}
		librairieInitialiser+= SDL_IMG;
		printf("%sSDL_IMG initialisé avec succés.\n",nomFonction);
	}
	/*
	if( choix & SDL_MIX ){
		if( MIX_Init() ){
			printf( "%s%sMIX_Init : Un problème est survenu", MSG_E, nomFonction );
			return E_INIT;
		}
		librairieInitialiser+= SDL_MIX;
		printf("%sSDL_MIX initialisé avec succés.\n",nomFonction);
	}
	if( choix & SDL_NET ){
		if( NET_Init() ){
			printf( "%s%sNET_Init : Un problème est survenu", MSG_E, nomFonction );
			return E_INIT;
		}
		librairieInitialiser+= SDL_NET;
		printf("%sSDL_NET initialisé avec succés.\n",nomFonction);
	}
	if( choix & SDL_GFX ){
		if( GFX_Init() ){
			printf( "%s%sGFX_Init : Un problème est survenu", MSG_E, nomFonction );
			return E_INIT;
		}
		librairieInitialiser+= SDL_GFX;
		printf("%sSDL_GFX initialisé avec succés.\n",nomFonction);
	}
	if( choix & SDL_GPU ){
		if( GPU_Init() ){
			printf( "%s%sGPU_Init : Un problème est survenu", MSG_E, nomFonction );
			return E_INIT;
		}
		librairieInitialiser+= SDL_GPU;
		printf("%sSDL_GPU initialisé avec succés.\n",nomFonction);
	}
	if( choix & SDL_RTF ){
		if( RTF_Init() ){
			printf( "%s%sRTF_Init : Un problème est survenu", MSG_E, nomFonction );
			return E_INIT;
		}
		librairieInitialiser+= SDL_RTF;
		printf("%sSDL_RTF initialisé avec succés.\n",nomFonction);
	}
	*/

	va_end(va);
	return E_OK;
}
extern void fermer_SDL(){
	char *nomFonction = "fermer_SDL : ";
	for( int i=NB_LIB_SDL ; i ; i-- ){
		if( librairieInitialiser & (1<<i) ){
			SDL_QUIT_FUNC[i]();
			printf("%sSDL_%s quité avec succés.\n",nomFonction,SDL_LIB_NOM[i]);
		}
	}
	if( librairieInitialiser & SDL_TTF ){
		TTF_Quit();
		printf("%sSDL_TTF quité avec succés.\n",nomFonction);
	}
	SDL_Quit();
	printf("%sSDL quité avec succés.\n",nomFonction);
}

extern SDL_Renderer *obtenir_Renderer( fenetre_t *f ){
	return f->rendu;
}
extern clique_t obtenir_souris( SDL_Point *point){
	Uint32 b = SDL_GetMouseState(&(point->x),&(point->y));
	if( b & SDL_BUTTON(1) )
		return CLIQUE_Gauche;
	if( b & SDL_BUTTON(2) )
		return CLIQUE_Mollette;
	if( b & SDL_BUTTON(3) )
		return CLIQUE_Droit;
	return CLIQUE_Erreur;
}
extern bouton_t *obtenir_boutonCliquer( fenetre_t *f, SDL_Point *point ){
	bouton_t *bouton = NULL;
	for( int i=0 ; i<liste_taille(f->lstBoutons) ; i++ ){
		bouton = liste_lit( f->lstBoutons , i );
		if( bouton->estCliquer( bouton , point ) ){
			return bouton;
		}
	}
	return NULL;
}

extern err_t ajouterBouton(fenetre_t *fen, stylo_t *s, char *txt, ancre_t *a, err_t (*fonc)(int argc,...)){
	bouton_t *bouton;
	if(!( bouton=creer_bouton( fen->rendu , s , txt , a , fonc) )){
		return E_AUTRE;
	}
	return liste_ajoute( fen->lstBoutons , bouton );
}
extern err_t ajouterWidget(fenetre_t *fen, void* widget){
	return liste_ajoute( fen->lstBoutons , widget );
}

extern void changerFond_couleur( fenetre_t *f , SDL_Color c ){
	(f->fond).r = c.r;
	(f->fond).g = c.g;
	(f->fond).b = c.b;
	(f->fond).a = c.a;
}
extern err_t rafraichir( fenetre_t *f ){
	char * fonc = "rafraichir : ";
	if( SDL_SetRenderDrawColor(f->rendu, (f->fond).r,(f->fond).g,(f->fond).b,(f->fond).a) ){
		printf("%s%sSDL_SetRenderDrawColor : %s",MSG_E,fonc, SDL_GetError());
		return E_COLOR;
	}
	if( SDL_RenderClear(f->rendu) ){
		printf("%s%sSDL_RenderClear : %s",MSG_E,fonc, SDL_GetError());
		return E_AFFICHE;
	}
	SDL_Point taille;
	SDL_GetWindowSize( (f->fenetre) , &(taille.x) , &(taille.y) );
	for( int i=0 ; i<liste_taille( f->lstBoutons ) ; i++ ){
		widget_t *widget = liste_lit( f->lstBoutons , i);
		widget->dessiner( taille , f->rendu , widget );
	}
	for( int i=0 ; i<liste_taille( f->lstWidgets ) ; i++ ){
		widget_t *widget = liste_lit( f->lstWidgets , i);
		widget->dessiner( taille , f->rendu , widget );
	}
	return E_OK;
}

	// Methode commune à tout les objets
static void afficher_fenetre( fenetre_t *fenetre ){
	printf("fenetre.");
	(fenetre->lstBoutons)->afficher( fenetre->lstBoutons );
}
static err_t detruire_fenetre( fenetre_t **fenetre ){
	// Suppression des attributs de l'objet fenetre
	if( (*fenetre)->rendu ){
		SDL_DestroyRenderer( (*fenetre)->rendu );
	}
	if( (*fenetre)->fenetre ){
		SDL_DestroyWindow( (*fenetre)->fenetre );
	}
	( (*fenetre)->lstBoutons )->detruire( &(*fenetre)->lstBoutons );

	// Suppression de l'objet fenetre
	free( (*fenetre) );
	(*fenetre) = NULL;

	// Destruction de l'objet fenetre réussie
	cmpt_fenetre--;
	return(E_OK);
}

extern void afficherSurvivant_fenetre(){
	afficherSurvivant_bouton();
	printf("Il reste %i fenetre_t.\n",cmpt_fenetre);
}

extern fenetre_t * creer_fenetre(SDL_Point dim, Uint32 flags, char *titre){
	// Définission des variables utiles
	char *nomFonction = "creer_fenetre : ";

	// Créer l'objet fenetre
	fenetre_t *fenetre = malloc( sizeof(fenetre_t) );
	if( !fenetre ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (fenetre_t*)NULL;
	}

	// Affecter les attributs
	fenetre->fenetre = NULL;
	fenetre->rendu = NULL;
	if( SDL_CreateWindowAndRenderer(dim.x,dim.y, flags, &(fenetre->fenetre),&(fenetre->rendu)) ){
		printf("%s%sSDL_CreateWindowAndRenderer : %s.\n",MSG_E,nomFonction,SDL_GetError());
		return (fenetre_t*)NULL;
	}
	SDL_SetWindowTitle( fenetre->fenetre , titre );
	fenetre->lstBoutons = creer_liste();
	fenetre->lstWidgets = creer_liste();

	// Affecter les methodes
	fenetre->detruire = (err_t (*)(void *))detruire_fenetre;
	fenetre->afficher = (void (*)(void *))afficher_fenetre;

	// Renvoyer le bouton
	cmpt_fenetre++;
	return fenetre;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

