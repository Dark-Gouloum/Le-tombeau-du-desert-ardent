/**
	* \file src/bouton.c
	* \brief Définition de l'objet bouton.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 11:50:43
	*
	* L'objet bouton sert à creer un bouton et le dessine sur un renderer..
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../lib/bouton.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
static void afficher_bouton( bouton_t *bouton ){
	char * fonc = "afficher_bouton : ";
	SDL_Color *c = &(bouton->couleur);
	if( SDL_SetRenderDrawColor(renderer, c->r,c->g,c->b,c->a) ){
		printf("%s%sSDL_SetRenderDrawColor : %s",MSG_E,fonc, SDL_GetError());
		return E_COLOR;
	}
	if( SDL_RenderFillRect(renderer, bouton->bouton) ){
		printf("%s%sSDL_RenderFillRect : %s",MSG_E,fonc, SDL_GetError());
		return E_COLOR;
	}
	return E_OK;
}

static err_t detruire_bouton( bouton_t **bouton ){
	free( (*bouton)->texte );
	free( (*bouton) );
	(*bouton) = NULL;
	return(E_OK);
}

extern bouton_t * creer_bouton(SDL_Rect rectangle, char *texte, typeBouton_t type, SDL_Color c){
	// Créer un bouton
	bouton_t *bouton = malloc( sizeof(bouton_t) );
	if( !bouton ){ // malloc à échouer :
		printf("ERREUR : creer_bouton :\n\tmalloc à échouer, pas assez de place de place disponible en mémoire.\n");
		return (bouton_t*)NULL;
	}
	bouton->texte = malloc( sizeof(char)*len(texte) );
	if( !bouton->texte ){ // malloc à échouer :
		printf("ERREUR : creer_bouton :\n\tmalloc à échouer, pas assez de place de place disponible en mémoire.\n");
		return (bouton_t*)NULL;
	}

	// Définir les attributs
	strcpy( bouton->texte , texte );
	bouton->type = type;
	bouton->bouton = rectangle;
	bouton->couleur = c;

	// Définir les méthodes
	bouton->detruire = (err_t (*)(void *))detruire_bouton;
	bouton->afficher = (void (*)(void *))afficher_bouton;

	return bouton;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

