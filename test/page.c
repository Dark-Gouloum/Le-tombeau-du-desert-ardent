/**
	* \file test/page.c
	* \brief Test de l'objet page.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 23 Mars 2023 18:41:01
	*
	* L'objet page sert à afficher le contenu d'une page.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/page.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
int STOP = 0;
/*
#define MARGE_X_EXT 325
#define MARGE_X_INT 25
#define MARGE_Y_SUP 125
#define MARGE_Y_INF 115
void imgG(SDL_Rect *rect , SDL_Point dim){
	rect->w = (dim.x/2) - MARGE_X_EXT - MARGE_X_INT;
	rect->h = dim.y - MARGE_Y_SUP - MARGE_Y_INF;
	rect->x = MARGE_X_EXT;
	rect->y = MARGE_Y_SUP;
}
void imgD(SDL_Rect *rect , SDL_Point dim){
	rect->w = (dim.x/2) - MARGE_X_EXT - MARGE_X_INT;
	rect->h = dim.y - MARGE_Y_SUP - MARGE_Y_INF;
	rect->x = (dim.x/2) + MARGE_X_INT - 10;
	rect->y = MARGE_Y_SUP;
}
*/
void reduireImg(SDL_Rect *rect, int r){
	( rect->h )-= r;
	( rect->w )-= r;
	( rect->x )+= r / 2;
	( rect->y )+= r / 2;
}
void imgG(SDL_Rect *rect , SDL_Point dim , int r){
	rect->h = ( (dim.y) * 765 ) / 1000;
	rect->w = ( (dim.x) * 311 ) / 1000;
	rect->x = ( (dim.x) * 171 ) / 1000;
	rect->y = ( (dim.y) * 125 ) / 1000;
	if( r )
		reduireImg(rect,r);
}
void imgD(SDL_Rect *rect , SDL_Point dim , int r){
	rect->h = ( (dim.y) * 750 ) / 1000;
	rect->w = ( (dim.x) * 301 ) / 1000;
	rect->x = ( (dim.x) * 511 ) / 1000;
	rect->y = ( (dim.y) * 127 ) / 1000;
	if( r )
		reduireImg(rect,r);
}
void imgD2(SDL_Rect *rect , SDL_Point dim , int r){
	rect->h = ( (dim.y) * 493 ) / 1000;
	rect->w = ( (dim.x) * 180 ) / 1000;
	rect->x = ( (dim.x) * 574 ) / 1000;
	rect->y = ( (dim.y) * 243 ) / 1000;
	if( r )
		reduireImg(rect,r);
}

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t quitter(int argc,...){
	printf("Quitter");
	STOP = 1;
	return E_OK;
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet page. */
int main(int argc,char *argv[]){
	// Tests sur les paramètre
	Uint32 flags = SDL_WINDOW_SHOWN;
	int centre=1;
	int reduireImg=0;
	int imgDDefaut=0;
	{
		int resize=0;
		for( int i=1 ; i<argc ; i++ ){
			if( strcmp(argv[i],"-r") == 0 ){
				resize = 1;
			} else if( strcmp(argv[i],"-v") == 0 ){
				reduireImg+= 4;
			} else if( strcmp(argv[i],"-d") == 0 ){
				imgDDefaut = 1;
			} else {
				centre*= -1;
			}
		}
		centre++;	centre= !centre;
		if( resize ){
			flags = flags|SDL_WINDOW_RESIZABLE;
		} else {
			flags = flags|SDL_WINDOW_FULLSCREEN;
		}
	}
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF|SDL_IMG , IMG_INIT_PNG ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	/* Création des autres variables */
	fenetre_t *fenetre = NULL;
	img_t *imgG = NULL , *imgD = NULL;
	police_t *police = NULL;
	SDL_Event event;
	SDL_Point curseur;
	SDL_Point pos;

	// INSTRUCTION(S)
	if(( status=creer_page(flags,argv[0],"livreOuvertPlacement.png",&fenetre,&pos) )){ // Pas d'objet fenetre de créer :
		MSG_ERR2("de la création de la fenetre");
		goto Quit;
	}
	if(( err=rafraichir(fenetre) )){
		MSG_ERR2("du rafraichissement du contenu de la fenetre");
		status = err;
		goto Quit;
	}
	SDL_RenderPresent(obtenir_Renderer(fenetre));
	SDL_Delay(1000);

	printf("Ajout du contenu de la fenêtre...");
	// Création de la police
	if(!( police=creer_police(NULL,25,NULL) )){ // Pas d'objet police de créer :
		printf("Erreur à la création de police.\n");
		status = E_AUTRE;
		goto Quit;
	}
	// Ajout des boutons
	pos.x = (fenetre->dim).x / 2;
	pos.y = (fenetre->dim).y / 2;
	if(( status=placer(fenetre,police,"Quitter",&pos,&imgG) )){
		MSG_ERR2("du placement du texte sur la fenêtre");
		goto Quit;
	}
	if(( status=ajouterBouton(fenetre,imgG,quitter,NULL) )){
		MSG_ERR2("de l'ajout du bouton");
		goto Quit;
	}
	imgG = NULL;
	// Destruction de la police
	if(( status=police->detruire(&police) )){
		printf("Erreur à la destruction de police.\n");
		goto Quit;
	}
	// Ajout des images
	/*	Image de gauche	*/
	if(!( imgG=creer_img(obtenir_Renderer(fenetre),"backPerso.jpeg") )){
		MSG_ERR2("de la création de l'image de gauche");
		status = E_AUTRE;
		goto Quit;
	}
	/*	Image de droite	*/
	if( imgDDefaut ){
		imgD = NULL;
	} else {
		if(!( imgD=creer_img(obtenir_Renderer(fenetre),"fond.png") )){
			MSG_ERR2("de la création de l'image de droite");
			status = E_AUTRE;
			goto Quit;
		}
	}
	if(( status=ajouterImages_page(fenetre,imgG,imgD,centre,reduireImg) )){
		MSG_ERR2("de l'ajout des images à la fenêtre");
		goto Quit;
	}
	// Fin placement
	imgG = NULL;
	imgD = NULL;
	printf("OK\n");

	printf("Attente du signal d'arrêt...");
	status = E_AUTRE;
	while( !STOP ){
		while( SDL_PollEvent(&event) ){
			if( event.type == SDL_QUIT )
				STOP = 1;
			else if( (event.type==SDL_MOUSEBUTTONUP) ){
				obtenir_clique(&curseur);
				bouton_t *b = obtenir_boutonCliquer(fenetre, &curseur,NULL);
				if( b ){
					if(( err=b->action(0) )){
						MSG_ERR2("L'action d'un bouton");
						status = err;
						goto Quit;
					}
				}
			}
		}
		if(( err=rafraichir(fenetre) )){
			MSG_ERR2("du rafraichissement du contenu de la fenetre");
			status = err;
			goto Quit;
		}
		SDL_RenderPresent(obtenir_Renderer(fenetre));
	}
	printf("OK\n");

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=fenetre->detruire(&fenetre)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de fenetre");
		return(err);
	}
	fermer_SDL();
	/* Affichage de fin */
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet page. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

