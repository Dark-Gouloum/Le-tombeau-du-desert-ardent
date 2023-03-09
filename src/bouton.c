/**
	* \file src/bouton.c
	* \brief Définition de l'objet bouton.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 14 Févr. 2023 19:09:04
	*
	* L'objet bouton sert à créer et gérer des boutons.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/bouton.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_bouton = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)
SDL_Color contour = { 255,0,0 , 255 };
SDL_Color interieur = { 125,125,125 , 20 };

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet bouton
static int estCliquer_bouton( bouton_t *bouton , SDL_Point *coord){
	SDL_Rect rect = (bouton->bouton->rect);
	if( SDL_PointInRect(coord,&rect) == SDL_TRUE  ){
		return 1;
	} else {
		return 0;
	}
	return -1;
}
extern err_t dessiner_bouton( SDL_Point tailleFenetre, SDL_Renderer *r, bouton_t *bouton ){
	err_t err = ( bouton->bouton )->dessiner( tailleFenetre , r , bouton->bouton );
	if( err )	return err;
	if( SDL_SetRenderDrawColor(r, contour.r,contour.g,contour.b,contour.a) ){
		printf("%sSDL_SetRenderDrawColor : %s",MSG_E, SDL_GetError());
		return E_COLOR;
	}
	if( SDL_RenderDrawRect(r, &(bouton->bouton->rect)) ){
		printf("%sSDL_SetRenderDrawColor : %s",MSG_E, SDL_GetError());
		return E_COLOR;
	}
	return err;
}

	// Methode commune à tout les objets
static void afficher_bouton( bouton_t *bouton ){
	printf("bouton{%s occupe {%d,%d}}", bouton->bouton->texte, (bouton->bouton->rect).w, (bouton->bouton->rect.h) );
}
static err_t detruire_bouton( bouton_t **bouton ){
	// Suppression des attributs de l'objet bouton
	( (*bouton)->bouton )->detruire( (*bouton)->bouton );

	// Suppression de l'objet bouton
	free( (*bouton) );
	(*bouton) = NULL;

	// Destruction de l'objet bouton réussie
	cmpt_bouton--;
	return(E_OK);
}

extern void afficherSurvivant_bouton(){
	afficherSurvivant_stylo();
	printf("Il reste %i bouton_t.\n",cmpt_bouton);
}

extern bouton_t * creer_bouton(SDL_Renderer *r,stylo_t *s , char *texte,ancre_t ancre , err_t (*action)(int argc,...)){
	// Définission des variables utiles
	char *nomFonction = "creer_bouton : ";

	// Créer l'objet bouton
	bouton_t *bouton = malloc( sizeof(bouton_t) );
	if( !bouton ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (bouton_t*)NULL;
	}

	// Affecter les attributs
	bouton->bouton = creer_texte( r , s , texte , ancre );
	surligner_texte( bouton->bouton , &interieur );

	// Affecter les methodes
	bouton->action = action;
	bouton->estCliquer = (int (*)(void*,SDL_Point*))estCliquer_bouton;
	bouton->dessiner = (err_t (*)(SDL_Point,SDL_Renderer*,void *))dessiner_bouton;
	bouton->detruire = (err_t (*)(void *))detruire_bouton;
	bouton->afficher = (void (*)(void *))afficher_bouton;

	// Renvoyer le bouton
	cmpt_bouton++;
	return bouton;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

