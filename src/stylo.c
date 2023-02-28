/**
	* \file src/stylo.c
	* \brief Définition de l'objet stylo.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Mar. 14 Févr. 2023 15:14:19
	*
	* L'objet stylo sert à écrire du texte sur la fenêtre.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/stylo.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_stylo = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet stylo
extern err_t initialisation_SDL_TTF(){
	if( TTF_Init() ){
		printf( "%sTTF_Init : %s" , MSG_E , SDL_GetError() );
		return E_INIT;
	}
	return E_OK;
}

extern err_t ecrire(SDL_Renderer *r,stylo_t *s, char *texte,ancre_t ancre , SDL_Rect *dest_rect){
	SDL_Point pt = ancre.point;
	angle_t angle = ancre.angle;
	int retour=1;
	if( !dest_rect ){
		retour = 0;
		dest_rect = malloc( sizeof(SDL_Rect) );
	}
	char *nomFonction = "ecrire : ";
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;
	if( !(surface=TTF_RenderText_Solid( s->font , texte , s->couleur ))  ){
		printf("%s%sTTF : Création de la surface de texte.\n",MSG_E,nomFonction);
		return E_COLOR;
	}
	if( !(texture=SDL_CreateTextureFromSurface( r , surface ))  ){
		printf("%s%sSDL_CreateTextureFromSurface : %s.\n",MSG_E,nomFonction,SDL_GetError());
		return E_COLOR;
	}
	if( SDL_QueryTexture( texture , NULL,NULL, &(dest_rect->w), &(dest_rect->h) ) ){
		printf("%s%sSDL_QueryTexture : %s.\n",MSG_E,nomFonction,SDL_GetError());
		return E_COLOR;
	}
	if( angle == ANGLE_MILLIEU ){
		dest_rect->x = pt.x - ((dest_rect->w)/2);
		dest_rect->y = pt.y - ((dest_rect->h)/2);
	} else if( angle == ANGLE_GAUCHE_SUP ){
		dest_rect->x = pt.x;
		dest_rect->y = pt.y;
	} else if( angle == ANGLE_GAUCHE_INF ){
		dest_rect->x = pt.x;
		dest_rect->y = pt.y - (dest_rect->h);
	} else if( angle == ANGLE_DROIT_SUP ){
		dest_rect->x = pt.x - (dest_rect->w);
		dest_rect->y = pt.y;
	} else if( angle == ANGLE_DROIT_INF ){
		dest_rect->x = pt.x - (dest_rect->w);
		dest_rect->y = pt.y - (dest_rect->h);
	} else {
		printf("%s%sangle : veuillez indiquer de qu'elle parie du réctangle vous avez donnée les coordonnée(x,y). L'angle est donnée par l'énumération angle_t.\n",MSG_E,nomFonction);
		return E_COLOR;
	}
	SDL_RenderCopy( r , texture , NULL , dest_rect );
	SDL_FreeSurface( surface );
	SDL_DestroyTexture( texture );
	if( !retour ){
		free( dest_rect );
		dest_rect = NULL;
	}
	return E_OK;
}

static err_t changerCouleur_stylo( stylo_t *stylo , SDL_Color c ){
	(stylo->couleur).r = c.r;
	(stylo->couleur).g = c.g;
	(stylo->couleur).b = c.b;
	(stylo->couleur).a = c.a;
	return E_OK;
}

	// Methode commune à tout les objets
static void afficher_stylo( stylo_t *stylo ){
	printf("stylo{r=%d;g=%d;b=%d;a=%d}",stylo->couleur.r,stylo->couleur.g,stylo->couleur.b,stylo->couleur.a);
}
static err_t detruire_stylo( stylo_t **stylo ){
	// Suppression des attributs de l'objet stylo
	TTF_CloseFont( (*stylo)->font );

	// Suppression de l'objet stylo
	free( (*stylo) );
	(*stylo) = NULL;

	// Destruction de l'objet stylo réussie
	cmpt_stylo--;
	return(E_OK);
}

extern void afficherSurvivant_stylo(){
	printf("Il reste %i stylo_t.\n",cmpt_stylo);
}

extern stylo_t * creer_stylo(char *nomFont, int taille, SDL_Color c){
	// Définission des variables utiles
	char *nomFonction = "creer_stylo : ";
	char font[ 12 + strlen(nomFont) ];
	if( !sprintf(font,"Annexe/font/%s",nomFont) ){
		printf("%s%sVeuillez indiquer une police au format \"nomPolice/variante.ttf\".\n",MSG_E,nomFonction);
		return (stylo_t*)NULL;
	}

	// Créer l'objet stylo
	stylo_t *stylo = malloc( sizeof(stylo_t) );
	if( !stylo ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (stylo_t*)NULL;
	}

	// Affecter les attributs
	if( !(stylo->font=TTF_OpenFont( font , taille ))  ){
		printf("%s%sTTF_OpenFont : police inconnue.\n",MSG_E,nomFonction);
		return (stylo_t*)NULL;
	}
	stylo->couleur = (SDL_Color){ c.r , c.g , c.b , c.a };

	// Affecter les methodes
	stylo->detruire = (err_t (*)(void *))detruire_stylo;
	stylo->afficher = (void (*)(void *))afficher_stylo;
	stylo->changerCouleur = (err_t (*)(void *,SDL_Color))changerCouleur_stylo;

	// Renvoyer le bouton
	cmpt_stylo++;
	return stylo;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

