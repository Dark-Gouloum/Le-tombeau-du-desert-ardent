/**
	* \file test/police.c
	* \brief Test de l'objet police.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 02:18:02
	*
	* L'objet police sert à gére les polices d'écritures du projets.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/police.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
#define tailleFenetre_X 500
#define tailleFenetre_Y 500

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t dessineSurface( SDL_Renderer *r, SDL_Surface **surface, int pos){
	SDL_Texture *texture;
	if( !(texture=SDL_CreateTextureFromSurface( r , *surface ))  ){
		MSG_ERR_BASE("","SDL_CreateTextureFromSurface",SDL_GetError());
		return E_COLOR;
	}
	SDL_Rect dest_rect;
	if( SDL_QueryTexture( texture , NULL,NULL, &(dest_rect.w), &(dest_rect.h) ) ){
		MSG_ERR_BASE("","SDL_QueryTexture",SDL_GetError());
		return E_COLOR;
	}
	( dest_rect.x ) = tailleFenetre_X/2 - ((dest_rect.w)/2);
	( dest_rect.y ) = (tailleFenetre_Y/(pos+1)) - ((dest_rect.w)/2);
	SDL_RenderCopy( r , texture , NULL , &dest_rect );
	SDL_FreeSurface( *surface );
	SDL_DestroyTexture( texture );
	*surface = NULL;
	return(E_OK);
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet police. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
		/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF ) )
		return E_INIT;
		/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
		/* Création d'un pointeur sur l'objet à tester */
	police_t *police = NULL;
		/* Création des autres variables */
	SDL_Window *fenetre = NULL;
	SDL_Renderer *rendu = NULL;
	SDL_Surface *surface = NULL;
	SDL_Surface *surface2 = NULL;
	SDL_Color coul = { 255 , 255 , 255 , 255 };

	// INSTRUCTION(S)
	printf("Création de l'objet police...");
	if(!( police=creer_police(NULL,0,NULL) )){ // Pas d'objet police de créer :
		printf("Erreur à la création de police.\n");
		status = E_AUTRE;
		goto Quit;
	}
	police->afficher( police );
	printf("OK\n");

	printf("Création de l'image du texte...");
	if( (err=police_creerSurface_texte(&surface,police,"TEST")) ){
		MSG_ERR2("de la création de la surface du texte.");
		status = err;
		goto Quit;
	}
	printf("OK\n");

	printf("Changer la couleur de la police...");
	if( (err=police_changerCouleur(police,coul)) ){
		MSG_ERR2("du changement de la couleur de la police.");
		status = err;
		goto Quit;
	}
	if( (err=police_creerSurface_texte(&surface2,police,"TEST")) ){
		MSG_ERR2("de la création de la surface du texte.");
		status = err;
		goto Quit;
	}
	printf("OK\n");

	printf("Création de la fenêtre...");
	if( SDL_CreateWindowAndRenderer(tailleFenetre_X,tailleFenetre_Y, SDL_WINDOW_SHOWN, &fenetre,&rendu) ){
		MSG_ERR_BASE("","SDL_CreateWindowAndRenderer",SDL_GetError());
		status = E_AUTRE;
		goto Quit;
	}
	SDL_SetWindowTitle( fenetre , "test_police" );
	printf("OK\n");
	SDL_Delay(1000);

	printf("Affichage du texte...");
	if( SDL_SetRenderDrawColor(rendu, 255,125,0,255) ){
		MSG_ERR_BASE("","SDL_SetRenderDrawColor",SDL_GetError());
		status = E_COLOR;
		goto Quit;
	}
	if( SDL_RenderClear(rendu) ){
		MSG_ERR_BASE("","SDL_RenderClear",SDL_GetError());
		status = E_AFFICHE;
		goto Quit;
	}
	if( (err=dessineSurface(rendu,&surface,1)) ){
		MSG_ERR2("du 1er dessin");
		status = err;
		goto Quit;
	}
	if( (err=dessineSurface(rendu,&surface2,2)) ){
		MSG_ERR2("du 2e dessin");
		status = err;
		goto Quit;
	}
	SDL_RenderPresent(rendu);
	printf("OK\n");
	SDL_Delay(1000);

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( rendu )
		SDL_DestroyRenderer( rendu );
	if( fenetre )
		SDL_DestroyWindow( fenetre );
	if( (err=police->detruire(&police)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de police");
		return(err);
	}
	fermer_SDL();
	/* Affichage de fin */
	afficherSurvivant_police();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet police. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

