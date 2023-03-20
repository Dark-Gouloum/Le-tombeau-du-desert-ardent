/**
	* \file src/texte.c
	* \brief Définition de l'objet texte.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 28 Févr. 2023 14:40:03
	*
	* L'objet texte sert à ecrire du texte sur la fenêtre.
	*
	*/
#include <assert.h>

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/texte.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_texte = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet texte
static err_t changerStylo_texte( SDL_Renderer *r , stylo_t *s , texte_t *t ){
	SDL_DestroyTexture( t->texture );
	return creerTexture_texte(r,s, t->texte, &(t->rect), &(t->texture));
}

static err_t dessiner_texte(SDL_Point tailleFenetre, SDL_Renderer *r , texte_t *t){
	char *nomFonction = "ecrire_texte :";
	// Calcule du point d'ancrage de la fenêtre
	int x = tailleFenetre.x * (t->ancre).x;
	int y = tailleFenetre.y * (t->ancre).y;
	x/= 100;
	y/= 100;
	// Choix du point d'ancrage du texte
	switch( (t->ancre).angle ){
		case ANGLE_MILLIEU :
			x-= (((t->rect).w)/2);
			y-= (((t->rect).h)/2);
			break;
		case ANGLE_GAUCHE_SUP :
			break;
		case ANGLE_GAUCHE_INF :
			y-= ((t->rect).h);
			break;
		case ANGLE_DROIT_SUP :
			x-= ((t->rect).w);
			break;
		case ANGLE_DROIT_INF :
			x-= ((t->rect).w);
			y-= ((t->rect).h);
			break;
		default :
			printf("%s%sangle : veuillez indiquer de qu'elle partie du réctangle vous avez donnée les coordonnée(x,y). L'angle est donnée par l'énumération angle_t.\n",MSG_E,nomFonction);
			return E_COLOR;
	}
	(t->rect).x = x;
	(t->rect).y = y;
	// Affichage du texte
	if( t->fond ){
		if( SDL_SetRenderDrawColor(r, t->fond->r,t->fond->g,t->fond->b,t->fond->a) ){
			printf("%sSDL_SetRenderDrawColor : %s",MSG_E, SDL_GetError());
			return E_COLOR;
		}
		if( SDL_RenderFillRect(r, &(t->rect)) ){
			printf("%sSDL_SetRenderDrawColor : %s",MSG_E, SDL_GetError());
			return E_COLOR;
		}
	}
	SDL_RenderCopy( r , t->texture , NULL , &(t->rect) );
	return E_OK;
}
extern void surligner_texte( texte_t *texte , SDL_Color *fond ){
	texte->fond = fond;
}

	// Methode commune à tout les objets
static void afficher_texte( texte_t *texte ){
	printf("texte{'%s',",texte->texte);
	(texte->ancre).afficher( &(texte->ancre) );
	printf("}");
}

static err_t detruire_texte( texte_t **texte ){
	// Suppression des attributs de l'objet texte
	assert(0);
	free( (*texte)->texte );
	SDL_DestroyTexture( (void*)(*texte)->texture );

	// Suppression de l'objet texte
	free( (void*)(*texte) );
	(*texte) = NULL;

	// Destruction de l'objet texte réussie
	cmpt_texte--;
	return(E_OK);
}

extern void afficherSurvivant_texte(){
	afficherSurvivant_stylo();
	printf("Il reste %i texte_t.\n",cmpt_texte);
}

extern texte_t * creer_texte(SDL_Renderer *r, stylo_t *s, char *str, ancre_t *ancre){
	// Définission des variables utiles
	char *nomFonction = "creer_texte : ";

	// Créer l'objet texte
	texte_t *texte = malloc( sizeof(texte_t) );
	if( !texte ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (texte_t*)NULL;
	}

	// Affecter les attributs
	if(!( (texte->texte) = malloc(sizeof(char)*(strlen(str)+1)) )){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (texte_t*)NULL;
	}
	strcpy( texte->texte , str );
	(texte->ancre).x = ancre->x;
	(texte->ancre).y = ancre->y;
	(texte->ancre).angle = ancre->angle;
	// Création de la texture
	err_t err = creerTexture_texte(r,s, texte->texte, &(texte->rect), &(texte->texture));
	if( err ){
		return (texte_t*)NULL;
	}

	// Affecter les methodes
	texte->changerStylo = (err_t (*)(SDL_Renderer*,stylo_t*,void* ))changerStylo_texte;
	texte->dessiner = (err_t (*)(SDL_Point,SDL_Renderer*,void *))dessiner_texte;
	texte->detruire = (err_t (*)(void *))detruire_texte;
	texte->afficher = (void (*)(void *))afficher_texte;

	// Renvoyer le bouton
	cmpt_texte++;
	return texte;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

