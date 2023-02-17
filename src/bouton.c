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
const SDL_Color contourBouton = { 0,0,0 , 255 };
const SDL_Color interieurBouton = { 25,25,25 , 50 };

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet bouton
static int estCliquer_bouton( bouton_t *bouton , SDL_Point *coord){
	SDL_Rect rect = (bouton->bouton);
	if( SDL_PointInRect(coord,&rect) == SDL_TRUE  ){
		return 1;
	} else {
		return 0;
	}
	return -1;
}

	// Methode commune à tout les objets
static void afficher_bouton( bouton_t *bouton ){
	printf("bouton{l=%d,h=%d}", (bouton->bouton).w, (bouton->bouton).h);
}
static err_t detruire_bouton( bouton_t **bouton ){
	// Suppression des attributs de l'objet bouton

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

extern bouton_t * creer_bouton(SDL_Renderer *r,stylo_t *s , char *texte,SDL_Point pt,angle_t angle , err_t (*action)(void)){
	// Définission des variables utiles
	char *nomFonction = "creer_bouton : ";
	SDL_Color cActu;
	SDL_GetRenderDrawColor( r, &(cActu.r),&(cActu.g),&(cActu.b),&(cActu.a) );
	SDL_BlendMode blendModeActu;
	SDL_GetRenderDrawBlendMode(r , &blendModeActu);
	SDL_SetRenderDrawBlendMode(r , SDL_BLENDMODE_BLEND);

	// Créer l'objet bouton
	bouton_t *bouton = malloc( sizeof(bouton_t) );
	if( !bouton ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (bouton_t*)NULL;
	}

	// Affecter les attributs
	ecrire( r,s , texte,pt,angle , &(bouton->bouton) );
	SDL_SetRenderDrawColor( r, contourBouton.r,contourBouton.g,contourBouton.b,contourBouton.a );
	SDL_RenderDrawRect( r , &(bouton->bouton) );
	SDL_SetRenderDrawColor( r, interieurBouton.r,interieurBouton.g,interieurBouton.b,interieurBouton.a );
	SDL_RenderFillRect( r , &(bouton->bouton) );

	// Affecter les methodes
	bouton->action = action;
	bouton->estCliquer = (int (*)(void*,SDL_Point*))estCliquer_bouton;
	bouton->detruire = (err_t (*)(void *))detruire_bouton;
	bouton->afficher = (void (*)(void *))afficher_bouton;

	// Renvoyer le bouton
	SDL_SetRenderDrawBlendMode(r , blendModeActu);
	SDL_SetRenderDrawColor( r, cActu.r,cActu.g,cActu.b,cActu.a );
	cmpt_bouton++;
	return bouton;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

