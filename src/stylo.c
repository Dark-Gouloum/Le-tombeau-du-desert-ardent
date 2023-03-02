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

extern err_t creerTexture_texte(SDL_Renderer *r,stylo_t *s, char *texte , SDL_Rect *dest_rect , SDL_Texture **texture){
	// Déclaration des variables
	char *nomFonction = "ecrire : ";
	SDL_Surface *surface = NULL;

	// Création du texte à aficher
	if( !(surface=TTF_RenderText_Solid( s->font , texte , s->couleur ))  ){
		printf("%s%sTTF : Création de la surface de texte.\n",MSG_E,nomFonction);
		return E_COLOR;
	}
	if( !(*texture=SDL_CreateTextureFromSurface( r , surface ))  ){
		printf("%s%sSDL_CreateTextureFromSurface : %s.\n",MSG_E,nomFonction,SDL_GetError());
		return E_COLOR;
	}
	if( SDL_QueryTexture( *texture , NULL,NULL, &(dest_rect->w), &(dest_rect->h) ) ){
		printf("%s%sSDL_QueryTexture : %s.\n",MSG_E,nomFonction,SDL_GetError());
		return E_COLOR;
	}

	// Affichage du texte
	SDL_FreeSurface( surface );
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
	if( !nomFont ){
		nomFont = "Roboto/Roboto-Thin.ttf";
	}
	if( !taille ){
		taille = 18;
	}
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

