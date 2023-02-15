/**
	* \file src/fenetre.c
	* \brief Définition de l'objet fenetre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 13 Févr. 2023 11:20:15
	*
	* L'objet fenetre sert à creer et gerer une fenêtre basique.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/fenetre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

int unsigned cmpt_fenetre = 0;
// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet fenetre_t
extern clique_t obtenir_positionSouris( SDL_Point *point){
	Uint32 b = SDL_GetMouseState(&(point->x),&(point->y));
	if( b & SDL_BUTTON(1) )
		return CLIQUE_Gauche;
	if( b & SDL_BUTTON(2) )
		return CLIQUE_Mollette;
	if( b & SDL_BUTTON(3) )
		return CLIQUE_Droit;
	return CLIQUE_Erreur;
}

extern err_t initialisation_SDL(){
	if( SDL_Init( SDL_INIT_VIDEO ) ){
		printf( "%sSDL_Init : %s" , MSG_E , SDL_GetError() );
		return E_INIT;
	}
	return E_OK;
}

extern SDL_Renderer *getRenderer( fenetre_t *f ){
	return f->renderer;
}

extern err_t changerCouleur( fenetre_t *f , SDL_Color *c ){
	char * fonc = "changerCouleur : ";
	if( SDL_SetRenderDrawColor(f->renderer, c->r,c->g,c->b,c->a) ){
		printf("%s%sSDL_SetRenderDrawColor : %s",MSG_E,fonc, SDL_GetError());
		return E_COLOR;
	}
	return E_OK;
}

	// Methode commune à tout les objets
static void afficher_fenetre( fenetre_t *fenetre ){
	SDL_ShowWindow( fenetre->fenetre );
	SDL_RenderPresent( fenetre->renderer );
	SDL_Delay(100);
}

static err_t detruire_fenetre( fenetre_t **fenetre ){
	// Suppression des attributs de l'objet fenetre_t
	if( (*fenetre)->renderer )
		SDL_DestroyRenderer( (*fenetre)->renderer );
	if( (*fenetre)->fenetre )
		SDL_DestroyWindow( (*fenetre)->fenetre );

	// Suppression de l'objet fenetre_t
	free( (*fenetre) );
	(*fenetre) = NULL;

	// Destruction de l'objet fenetre_t réussie
	cmpt_fenetre--;
	return(E_OK);
}

extern fenetre_t * creer_fenetre(SDL_Point dim, Uint32 WindowFlags, char *titre){
	// Définission des variables utiles
	char *nomFonction = "creer_fenetre : ";
	// Créer la fenetre
	fenetre_t *fenetre = malloc( sizeof(fenetre_t) );
	if( !fenetre ){ // malloc à échouer :
		printf("%s%smalloc :\n\tmalloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (fenetre_t*)NULL;
	}

	// Affecter les attributs
	fenetre->fenetre = NULL;
	fenetre->renderer = NULL;
	if( SDL_CreateWindowAndRenderer(dim.x,dim.y, WindowFlags, &(fenetre->fenetre),&(fenetre->renderer)) ){
		printf("%s%sSDL_CreateWindowAndRenderer : %s.\n",MSG_E,nomFonction,SDL_GetError());
		return (fenetre_t*)NULL;
	}
	SDL_SetWindowTitle(fenetre->fenetre,titre);

	// Affecter les methodes
	fenetre->detruire = (err_t (*)(void *))detruire_fenetre;
	fenetre->afficher = (void (*)(void *))afficher_fenetre;

	// Renvoyer le bouton
	cmpt_fenetre++;
	return fenetre;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

