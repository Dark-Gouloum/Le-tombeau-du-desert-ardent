/**
	* \file src/widget.c
	* \brief Définition de l'objet widget.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 04:23:47
	*
	* L'objet widget sert à gérer une image.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/widget.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Methode commune à tout les widgets
/* Gestion du renderer */
static err_t changerRendu_bis(widget_t *widget, SDL_Renderer *rendu){
	if( !widget ){
		MSG_ERR(E_ARGUMENT,"Pas de widget à modifier");
		return(E_ARGUMENT);
	}
	if( !rendu ){
		MSG_ERR(E_ARGUMENT,"Pas de renderer à renseigné");
		return(E_ARGUMENT);
	}
	widget->rendu = rendu;
	return E_OK;
}
extern err_t changerRendu(void *widget, SDL_Renderer *rendu){
	return changerRendu_bis(widget,rendu);
}

/* copie d'un rectagle */
static err_t copieRect(SDL_Rect **dest, SDL_Rect *src){
	if( (*dest) ){
		free( *dest );
		*dest = NULL;
	}
	if( !src ){
		return(E_OK);
	}
	*dest = malloc( sizeof(SDL_Rect) );
	if( !(*dest) ){
		MSG_ERR(E_MEMOIRE,"Pas assez de place pour la copie du rectangle du widget");
		return(E_MEMOIRE);
	}
	(*dest)->w = src->w;
	(*dest)->h = src->h;
	(*dest)->x = src->x;
	(*dest)->y = src->y;
	return E_OK;
}

/* Gestion de la source */
static SDL_Rect * obtenirSource_bis(widget_t *widget){
	if( !widget ){
		MSG_ERR(E_ARGUMENT,"Pas de widget à modifier");
		return(NULL);
	}
	return widget->source;
}
extern SDL_Rect * obtenirSource(void *widget){
	return obtenirSource_bis(widget);
}

static err_t changerSource_bis(widget_t *widget , SDL_Rect *src){
	if( !widget ){
		MSG_ERR(E_ARGUMENT,"Pas de widget à modifier");
		return(E_ARGUMENT);
	}
	err_t err = copieRect( &(widget->source) , src );
	if( err ){
		MSG_ERR2("Erreur à la copie du rectangle de source.");
	}
	return err;
}
extern err_t changerSource(void *widget , SDL_Rect *src){
	return changerSource_bis(widget,src);
}

/* Gestion de la dest */
static SDL_Rect * obtenirDest_bis(widget_t *widget){
	if( !widget ){
		MSG_ERR(E_ARGUMENT,"Pas de widget à modifier");
		return(NULL);
	}
	return widget->dest;
}
extern SDL_Rect * obtenirDest(void *widget){
	return obtenirDest_bis(widget);
}

static err_t changerDest_bis(widget_t *widget , SDL_Rect *dest){
	if( !widget ){
		MSG_ERR(E_ARGUMENT,"Pas de widget à modifier");
		return(E_ARGUMENT);
	}
	err_t err = copieRect( &(widget->dest) , dest );
	if( err ){
		MSG_ERR2("Erreur à la copie du rectangle de destination");
	}
	return err;
}
extern err_t changerDest(void *widget , SDL_Rect *dest){
	return changerDest_bis(widget,dest);
}

static err_t actualiserDest_bis(widget_t *widget, float pL , float pH){
	if( !widget ){
		MSG_ERR(E_ARGUMENT,"Pas de widget à modifier");
		return(E_ARGUMENT);
	}
	if( !(widget->dest) ){
		MSG_ERR(E_OBTENIR, "Le widget n'à pas de zone de dessin à modifier");
		return (E_OBTENIR);
	}
	(widget->dest->h)*= pH;
	(widget->dest->w)*= pL;
	(widget->dest->x)*= pL;
	(widget->dest->y)*= pH;
	return(E_OK);
}
extern err_t actualiserDest(void *widget, float pL , float pH){
	return actualiserDest_bis( widget , pL , pH );
}

/* TEST */
static int hover_bis(widget_t *widget , SDL_Point *curseur){
	// Tests des paramètre
	if( !widget ){
		MSG_ERR(E_ARGUMENT,"Pas de widget");
		return(0);
	}
	if( !curseur ){
		MSG_ERR(E_ARGUMENT,"Pas de curseur");
		return(0);
	}
	return ( SDL_PointInRect(curseur,obtenirDest(widget)) == SDL_TRUE );
}
extern int hover(void *widget , SDL_Point *curseur){
	return hover_bis(widget , curseur );
}
	// Methode commune à tout les objets

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

