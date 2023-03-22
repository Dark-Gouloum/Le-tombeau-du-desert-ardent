/**
	* \file src/menu.c
	* \brief Définition de l'objet menu.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 14:21:44
	*
	* L'objet menu sert à créer un menu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/menu.h"
#include "../lib/police.h"
#include "../lib/img.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
extern err_t ajouterBouton_menu( fenetre_t *f, int nbB,char *nomB[],err_t (*action)(int argc,...), SDL_Point *pos,int nbCol ){
	SDL_Point dim;
	police_t *police = NULL;
	img_t *img = NULL;
	err_t err = E_OK;

	if(!( police=creer_police(NULL,25,NULL) )){ // Pas d'objet police de créer :
		MSG_ERR2("de la création de la police d'écriture des boutons de la fenetre");
		return(E_AUTRE);
	}
	SDL_GetWindowSize( (f->fenetre) , &(dim.x) , &(dim.y) );

	int maxX = pos->x;
	int ligneX[nbCol];
	for( int i=0 ; i<nbCol ; i++ ){
		ligneX[i] = (i+1) * (dim.x/(nbCol+1));
	}
	int col = 0;
	int lig = pos->y;
	int ligneY = pos->y;

	for( int i=0 ; i<nbB ; i++,col++ ){
		if( col == nbCol ){
			col = 0;
			ligneY = lig + SEP_WIDGET;
			if( maxX < pos->x ){
				maxX = pos->x;
			}
		}
		pos->x = ligneX[col];
		pos->y = ligneY;
		if(( err=placer(f,police,nomB[i],pos,&img) )){
			MSG_ERR2("de la création du texte d'un bouton de la fenetre");
			return(err);
		}
		if(( err=ajouterBouton(f,img,action) )){
			MSG_ERR2("de l'ajout du bouton à la fenetre");
			return(err);
		}
		if( lig < pos->y ){
			lig = pos->y;
		}
	}

	if(( err=police->detruire( &police ) )){
		MSG_ERR2("de la destruction de la police d'écriture des boutons de la fenetre");
		return(E_AUTRE);
	}
	pos->x = maxX + SEP_WIDGET;
	pos->y = lig + SEP_WIDGET;
	return(E_OK);
}
extern err_t ajouterImage_menu( fenetre_t *f, int nbB,char *fichierB[],err_t (*action)(int argc,...), SDL_Point *pos,int nbCol ){
	SDL_Point dim;
	img_t *img = NULL;
	err_t err = E_OK;
	SDL_GetWindowSize( (f->fenetre) , &(dim.x) , &(dim.y) );

	int maxX = pos->x;
	int ligneX[nbCol];
	for( int i=0 ; i<nbCol ; i++ ){
		ligneX[i] = (i+1) * (dim.x/(nbCol+1));
	}
	int col = 0;
	int lig = pos->y;
	int ligneY = pos->y;

	for( int i=0 ; i<nbB ; i++,col++ ){
		if( col == nbCol ){
			col = 0;
			ligneY = lig + SEP_WIDGET;
			if( maxX < pos->x ){
				maxX = pos->x;
			}
		}
		pos->x = ligneX[col];
		pos->y = ligneY;
		if(( err=placer(f,NULL,fichierB[i],pos,&img) )){
			MSG_ERR2("de la création du texte d'un bouton de la fenetre");
			return(err);
		}
		if(( err=ajouterBouton(f,img,action) )){
			MSG_ERR2("de l'ajout du bouton à la fenetre");
			return(err);
		}
		if( lig < pos->y ){
			lig = pos->y;
		}
	}

	pos->x = maxX + SEP_WIDGET;
	pos->y = lig + SEP_WIDGET;
	return(E_OK);
}

extern err_t creer_menu(Uint32 flags, char *titre,SDL_Color *c, char *fond , int nbCol , fenetre_t **fenetre , SDL_Point *pos){
	if( *fenetre ){
		MSG_ERR(E_ARGUMENT,"Il y à déjà une fenêtre, rique de fuite de mémoire.");
		return(E_ARGUMENT);
	}
	img_t * img = NULL;
	police_t *police = NULL;
	SDL_Point dim;
	SDL_Rect rect;
	err_t err = E_OK;

	printf("Création de l'objet fenetre...");
	if(!( *fenetre=creer_fenetre(NULL,flags|SDL_WINDOW_FULLSCREEN,titre) )){
		MSG_ERR2("À la création de fenetre");
		return(E_AUTRE);
	}
	printf("OK\n");

	if( fond ){
		printf("Ajout de l'arrière plan de la fenêtre...");
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
	SDL_GetWindowSize( ((*fenetre)->fenetre) , &(dim.x) , &(dim.y) );

	if(!( police=creer_police(NULL,52,c) )){ // Pas d'objet police de créer :
		MSG_ERR2("de la création de la police d'écriture du titre de la fenetre");
		return(E_AUTRE);
	}
	pos->x = dim.x / 2;
	pos->y = 2 * (dim.y/10);
	if( titre ){
		if(( err=placer(*fenetre,police,titre,pos,&img) )){
			MSG_ERR2("de la création de la police d'écriture du titre de la fenetre");
			return(err);
		}
	} else {
		if(( err=placer(*fenetre,police,"MENU",pos,&img) )){
			MSG_ERR2("de la création de la police d'écriture du titre de la fenetre");
			return(err);
		}
	}
	if(( err=ajouterWidget(*fenetre,img) )){
		MSG_ERR2("de l'ajout du titre à la fenetre");
		return(err);
	}
	if(( err=police->detruire( &police ) )){
		MSG_ERR2("de la destruction de la police d'écriture du titre de la fenetre");
		return(E_AUTRE);
	}
	pos->y+= 2 * (dim.y/10);
	return(err);
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

