/**
	* \file src/page.c
	* \brief Définition de l'objet page.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 23 Mars 2023 18:41:01
	*
	* L'objet page sert à afficher le contenu d'une page.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/page.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
static err_t reduireImg( img_t *img , int r ){
	SDL_Rect *rect = obtenirDest(img);
	if( !rect ){
		MSG_ERR2("de l'obtention de l'espace occupé par l'image dans la fenetre");
		return(E_OBTENIR);
	}
	( rect->h )-= r;
	( rect->w )-= r;
	( rect->x )+= r / 2;
	( rect->y )+= r / 2;
	return(E_OK);
}

static err_t ajouterImageG( fenetre_t *f , img_t *img ){
	err_t err = E_OK;
	SDL_Point *dim = &( f->dim );
	SDL_Rect rect;

	rect.h = ( (dim->y) * 765 ) / 1000;
	rect.w = ( (dim->x) * 311 ) / 1000;
	rect.x = ( (dim->x) * 171 ) / 1000;
	rect.y = ( (dim->y) * 125 ) / 1000;

	if(( err=changerDest(img,&rect) )){
		MSG_ERR2("de la modification de img");
		return(err);
	}
	if(( err=ajouterWidget(f,img) )){
		MSG_ERR2("de l'ajout de l'image à la fenetre");
		return(err);
	}
	return(err);
}
static err_t ajouterImageDPlein( fenetre_t *f , img_t *img ){
	err_t err = E_OK;
	SDL_Point *dim = &( f->dim );
	SDL_Rect rect;

	rect.h = ( (dim->y) * 750 ) / 1000;
	rect.w = ( (dim->x) * 301 ) / 1000;
	rect.x = ( (dim->x) * 511 ) / 1000;
	rect.y = ( (dim->y) * 127 ) / 1000;

	if(( err=changerDest(img,&rect) )){
		MSG_ERR2("de la modification de img");
		return(err);
	}
	if(( err=ajouterWidget(f,img) )){
		MSG_ERR2("de l'ajout de l'image à la fenetre");
		return(err);
	}
	return(err);
}
static err_t ajouterImageDCentral( fenetre_t *f , img_t *img ){
	err_t err = E_OK;
	SDL_Point *dim = &( f->dim );
	SDL_Rect rect;

	rect.h = ( (dim->y) * 493 ) / 1000;
	rect.w = ( (dim->x) * 180 ) / 1000;
	rect.x = ( (dim->x) * 574 ) / 1000;
	rect.y = ( (dim->y) * 243 ) / 1000;

	if(( err=changerDest(img,&rect) )){
		MSG_ERR2("de la modification de img");
		return(err);
	}
	if(( err=ajouterWidget(f,img) )){
		MSG_ERR2("de l'ajout de l'image à la fenetre");
		return(err);
	}
	return(err);
}

extern err_t ajouterImages_page( fenetre_t *f , img_t *imgG , img_t *imgD , int central , int red ){
	err_t err = E_OK;
	if( !f ){
		err = E_ARGUMENT;
		MSG_ERR(err,"Il n'y à pas de fenêtre dans laquelle ajouter les images");
		return(err);
	}
	if( !imgG ){
		err = E_ARGUMENT;
		MSG_ERR(err,"Il n'y à pas d'image à ajouter dans la page de gauche");
		return(err);
	}
	if( !imgD ){ // Si pas d'image à droite, en créer une vide
		if(!( imgD=creer_img(f->rendu,"pageVide.png") )){ // Pas d'objet img de créer :
			MSG_ERR2("de la création de la page vide");
			return(E_AUTRE);
		}
	}
	if(( err=ajouterImageG(f,imgG) )){
		MSG_ERR2("de l'ajout de l'image de la page de gauche");
		return(err);
	}
	if( central ){
		if(( err=ajouterImageDCentral(f,imgD) )){
			MSG_ERR2("de l'ajout de l'image de la page de droite, en mode centré");
			return(err);
		}
	} else {
		if(( err=ajouterImageDPlein(f,imgD) )){
			MSG_ERR2("de l'ajout de l'image de la page de droite");
			return(err);
		}
	}
	if( red ){
		if(( err=reduireImg(imgG,red) )){
			MSG_ERR2("de la réduction de l'image de la page de gauche");
			return(err);
		}
		if(( err=reduireImg(imgD,red) )){
			MSG_ERR2("de la réduction de l'image de la page de droite");
			return(err);
		}
	}
	return(err);
}

extern err_t creer_page(Uint32 flags,char *titre, char *fond, fenetre_t **fenetre,SDL_Point *pos){
	err_t err = E_OK;
	// Tests des paramètre
	if( *fenetre ){
		MSG_ERR(E_ARGUMENT,"Il y à déjà une fenêtre, rique de fuite de mémoire.");
		return(E_ARGUMENT);
	}

	// Créer la fenêtre
	printf("Création de l'objet fenetre...");
	if(!( *fenetre=creer_fenetre(NULL,flags,titre) )){ // Pas d'objet fenetre de créer :
		MSG_ERR2("À la création de fenetre");
		return(E_AUTRE);
	}
	printf("OK\n");

	if( fond ){
		printf("Ajout de l'arrière plan de la fenêtre...");
		img_t *img = NULL;
		if(!( img=creer_img((*fenetre)->rendu,fond) )){ // Pas d'objet img de créer :
			MSG_ERR2("de la création de l'arrière plan de la fenetre");
			return(E_AUTRE);
		}
		if(( err=ajouterWidget(*fenetre,img) )){
			MSG_ERR2("de l'ajout de l'arrière plan de la fenetre");
			return(err);
		}
		printf("OK\n");
	}
	pos->x = 0;
	pos->y = 0;

	return(E_OK);
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

