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
	err_t err=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	img_t *img = NULL;
	img_t *img2 = NULL;
	img_t *img3 = NULL;
	/* Création des autres variables */
	SDL_Window *fenetre = NULL;
	SDL_Renderer *rendu = NULL;
	police_t *police = NULL;
	SDL_Surface *surface = NULL;
	SDL_Surface *surface2 = NULL;
	SDL_Color blanc = { 255 , 255 , 255 , 255 };
	SDL_Rect rect;

	// INSTRUCTION(S)
	printf("Création de divers objet utile...");
	if(!( police=creer_police(NULL,0,&blanc) )){ // Pas d'objet police de créer :
		printf("Erreur à la création de police.\n");
		err = E_AUTRE;
		goto Quit;
	}
	if( SDL_CreateWindowAndRenderer(tailleFenetre_X,tailleFenetre_Y, SDL_WINDOW_SHOWN, &fenetre,&rendu) ){
		MSG_ERR_BASE("","SDL_CreateWindowAndRenderer",SDL_GetError());
		err = E_AUTRE;
		goto Quit;
	}
	SDL_SetWindowTitle( fenetre , "test_img" );
	printf("OK\n");

	printf("Écriture d'un texte...");
	if( (err=police_creerSurface_texte(&surface,police,"TEST",0)) ){
		MSG_ERR2("de la création de la surface du texte.");
		goto Quit;
	}
	if( (err=police_creerSurface_texte(&surface2,police,"TEST TEST TEST TEST TEST",45)) ){
		MSG_ERR2("de la création de la surface du texte.");
		goto Quit;
	}
	printf("OK\n");

	printf("Création de deux objets img...");
	if(!( img=creer_img(rendu,"fond.png") )){ // Pas d'objet img de créer :
		MSG_ERR2("de la création de img");
		err = E_AUTRE;
		goto Quit;
	}
	if(!( img2=creer_img_ParSurface(rendu,&surface) )){ // Pas d'objet img de créer :
		MSG_ERR2("de la création de img2");
		err = E_AUTRE;
		goto Quit;
	}
	if(!( img3=creer_img_ParSurface(rendu,&surface2) )){ // Pas d'objet img de créer :
		MSG_ERR2("de la création de img2");
		err = E_AUTRE;
		goto Quit;
	}
	if(( err=img_demandeTaille(img2,&rect) )){
		MSG_ERR2("de la modification de img2");
		goto Quit;
	}
	rect.w = rect.w * 2;
	rect.h = rect.h * 2;
	rect.x = tailleFenetre_X / 4;
	rect.y = tailleFenetre_Y / 4;
	rect.x*= 3;
	rect.y*= 3;
	if(( err=changerDest(img2,&rect) )){
		MSG_ERR2("de la modification de img2");
		goto Quit;
	}
	if(( err=img_demandeTaille(img3,&rect) )){
		MSG_ERR2("de la modification de img3");
		goto Quit;
	}
	rect.w = rect.w * 2;
	rect.h = rect.h * 2;
	rect.x = tailleFenetre_X / 4;
	rect.y = tailleFenetre_Y / 4;
	if(( err=changerDest(img3,&rect) )){
		MSG_ERR2("de la modification de img3");
		goto Quit;
	}
	printf("OK\n");

	printf("Affichage de la fenêtre...");
	if( SDL_SetRenderDrawColor(rendu, 255,125,0,255) ){
		MSG_ERR_BASE("","SDL_SetRenderDrawColor",SDL_GetError());
		err = E_COLOR;
		goto Quit;
	}
	if( SDL_RenderClear(rendu) ){
		MSG_ERR_BASE("","SDL_RenderClear",SDL_GetError());
		err = E_AFFICHE;
		goto Quit;
	}
	if(( err=img->dessiner(img) )){
		MSG_ERR2("Dessin d'img");
		goto Quit;
	}
	if(( err=img2->dessiner(img2) )){
		MSG_ERR2("Dessin d'img2");
		goto Quit;
	}
	if(( err=img3->dessiner(img3) )){
		MSG_ERR2("Dessin d'img3");
		goto Quit;
	}
	SDL_RenderPresent(rendu);
	printf("OK\n");
	SDL_Delay(1000);

	printf("Nettoyage de la fenêtre...");
	if( SDL_SetRenderDrawColor(rendu, 255,125,0,255) ){
		MSG_ERR_BASE("","SDL_SetRenderDrawColor",SDL_GetError());
		err = E_COLOR;
		goto Quit;
	}
	if( SDL_RenderClear(rendu) ){
		MSG_ERR_BASE("","SDL_RenderClear",SDL_GetError());
		err = E_AFFICHE;
		goto Quit;
	}
	SDL_RenderPresent(rendu);
	printf("OK\n");
	SDL_Delay(1000);

	printf("Fusion des images...");
	if(( err=img_fusion(&img,img2) )){
		MSG_ERR2("Fusion d'img");
		goto Quit;
	}
	if(( err=img_fusion(&img2,img) )){
		MSG_ERR2("Fusion d'img");
		goto Quit;
	}
	if(( err=img_fusion(&img2,img3) )){
		MSG_ERR2("Fusion d'img");
		goto Quit;
	}
	SDL_RenderPresent(rendu);
	printf("OK\n");

	printf("Affichage de la nouvelle fenêtre...");
	if( SDL_SetRenderDrawColor(rendu, 255,125,0,255) ){
		MSG_ERR_BASE("","SDL_SetRenderDrawColor",SDL_GetError());
		err = E_COLOR;
		goto Quit;
	}
	if( SDL_RenderClear(rendu) ){
		MSG_ERR_BASE("","SDL_RenderClear",SDL_GetError());
		err = E_AFFICHE;
		goto Quit;
	}
	if(( err=img->dessiner(img) )){
		MSG_ERR2("Dessin d'img");
		goto Quit;
	}
	if(( err=img->dessiner(img2) )){
		MSG_ERR2("Dessin d'img");
		goto Quit;
	}
	SDL_RenderPresent(rendu);
	printf("OK\n");
	SDL_Delay(1000);

	err = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=police->detruire(&police)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de police");
		return(err);
	}
	if( (err=img->detruire(&img)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de img");
		return(err);
	}
	if( (err=img2->detruire(&img2)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de img2");
		return(err);
	}
	if( (err=img3->detruire(&img3)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de img3");
		return(err);
	}
	if( rendu )
		SDL_DestroyRenderer( rendu );
	if( fenetre )
		SDL_DestroyWindow( fenetre );
	fermer_SDL();
	/* Affichage de fin */
	afficherSurvivant_img();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(err);
}
	/* Programme qui test l'objet img. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

