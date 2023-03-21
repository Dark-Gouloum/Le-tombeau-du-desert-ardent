/**
	* \file test/img.c
	* \brief Test de l'objet img.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 04:23:47
	*
	* L'objet img sert à gérer une image.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/img.h"
#include "../lib/police.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
#define tailleFenetre_X 500
#define tailleFenetre_Y 500

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet img. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF|SDL_IMG , IMG_INIT_PNG ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	img_t *img = NULL;
	img_t *img2 = NULL;
	/* Création des autres variables */
	SDL_Window *fenetre = NULL;
	SDL_Renderer *rendu = NULL;
	police_t *police = NULL;
	SDL_Surface *surface = NULL;
	SDL_Rect rect;

	// INSTRUCTION(S)
	printf("Création de divers objet utile...");
	if(!( police=creer_police(NULL,0,NULL) )){ // Pas d'objet police de créer :
		printf("Erreur à la création de police.\n");
		status = E_AUTRE;
		goto Quit;
	}
	if( SDL_CreateWindowAndRenderer(tailleFenetre_X,tailleFenetre_Y, SDL_WINDOW_SHOWN, &fenetre,&rendu) ){
		MSG_ERR_BASE("","SDL_CreateWindowAndRenderer",SDL_GetError());
		status = E_AUTRE;
		goto Quit;
	}
	SDL_SetWindowTitle( fenetre , "test_img" );
	printf("OK\n");

	printf("Écriture d'un texte...");
	if( (status=police_creerSurface_texte(&surface,police,"TEST")) ){
		MSG_ERR2("de la création de la surface du texte.");
		goto Quit;
	}
	printf("OK\n");

	printf("Création de deux objets img...");
	if(!( img=creer_img(rendu,"fond.png") )){ // Pas d'objet img de créer :
		MSG_ERR2("de la création de img");
		status = E_AUTRE;
		goto Quit;
	}
	if(!( img2=creer_img_ParSurface(rendu,&surface) )){ // Pas d'objet img de créer :
		MSG_ERR2("de la création de img2");
		status = E_AUTRE;
		goto Quit;
	}
	if(( status=img_demandeTaille(img2,&rect) )){
		MSG_ERR2("de la modification de img2");
		goto Quit;
	}
	rect.w = rect.w * 2;
	rect.h = rect.h * 2;
	rect.x = tailleFenetre_X / 2;
	rect.y = tailleFenetre_Y / 2;
	if(( status=changerDest(img2,&rect) )){
		MSG_ERR2("de la modification de img2");
		goto Quit;
	}
	printf("OK\n");

	printf("Affichage de la fenêtre...");
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
	if(( status=img->dessiner(img) )){
		MSG_ERR2("Dessin d'img");
		goto Quit;
	}
	if(( status=img2->dessiner(img2) )){
		MSG_ERR2("Dessin d'img2");
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
	if( (status=police->detruire(&police)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de police");
		return(err);
	}
	if( (status=img->detruire(&img)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de img");
		return(err);
	}
	if( (status=img2->detruire(&img2)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de img2");
		return(err);
	}
	fermer_SDL();
	/* Affichage de fin */
	afficherSurvivant_img();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet img. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

