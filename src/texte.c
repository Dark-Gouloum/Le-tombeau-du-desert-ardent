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

static err_t dessiner_texte(SDL_Point *coin,SDL_Point taille, SDL_Renderer *r , texte_t *t){
	char *nomFonction = "ecrire_texte :";
	(t->rect).x = coin->x;
	(t->rect).y = coin->y;
	// Affichage du texte
	if( taille.x < (t->rect).x ){
		(t->rect).x = taille.x;
	}
	if( taille.y < (t->rect).y ){
		(t->rect).y = taille.y;
	}
	if( t->fond ){
		if( SDL_SetRenderDrawColor(r, (t->fond)->r,(t->fond)->g,(t->fond)->b,(t->fond)->a) ){
			printf("%s%sSDL_SetRenderDrawColor : %s",MSG_E, nomFonction, SDL_GetError());
			return E_COLOR;
		}
		if( SDL_RenderFillRect(r, &(t->rect)) ){
			printf("%s%sSDL_SetRenderDrawColor : %s",MSG_E, nomFonction, SDL_GetError());
			return E_COLOR;
		}
	}
	SDL_RenderCopy( r , t->texture , NULL , &(t->rect) );
	coin->x = (t->rect).x + (t->rect).w;
	coin->y = (t->rect).y + (t->rect).h;
	return E_OK;
}
extern void surligner_texte( texte_t *texte , SDL_Color *fond ){
	texte->fond = fond;
}

	// Methode commune à tout les objets
static void afficher_texte( texte_t *texte ){
	printf("texte{'%s'}",texte->texte);
}

static err_t detruire_texte( texte_t **texte ){
	// Suppression des attributs de l'objet texte
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

extern texte_t * creer_texte(SDL_Renderer *r, stylo_t *s, char *str){
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
	texte->fond = NULL;
	// Création de la texture
	err_t err = creerTexture_texte(r,s, texte->texte, &(texte->rect), &(texte->texture));
	if( err ){
		return (texte_t*)NULL;
	}

	// Affecter les methodes
	texte->changerStylo = (err_t (*)(SDL_Renderer*,stylo_t*,void* ))changerStylo_texte;
	texte->dessiner = (err_t (*)(SDL_Point*,SDL_Point,SDL_Renderer*,void *))dessiner_texte;
	texte->detruire = (err_t (*)(void *))detruire_texte;
	texte->afficher = (void (*)(void *))afficher_texte;

	// Renvoyer le bouton
	cmpt_texte++;
	return texte;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

