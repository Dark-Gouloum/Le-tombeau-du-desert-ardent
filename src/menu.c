/**
	* \file src/menu.c
	* \brief Définition de l'objet menu.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 01:17:05
	*
	* L'objet menu sert à créer et gérer le menu du jeu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/menu.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

static err_t gererEvenement_menu( menu_t *menu, SDL_Event *event ){
	switch( event->type ){
		case SDL_QUIT :
			return menu->detruire( &menu );
		default :
			return E_OK;
	}
}

static void afficher_menu( menu_t *menu ){
	SDL_RenderPresent(menu->renderer);
}

static err_t detruire_menu( menu_t **menu ){
	free( (*menu) );
	(*menu) = NULL;
	return(E_OK);
}

extern menu_t * creer_menu(){
	char *erreur = "ERREUR : CREER_MENU :\n\t";
	// Création du menu
	menu_t *menu = malloc( sizeof(menu_t) );
	if( !menu ){ // malloc à échouer :
		printf("%smalloc à échouer, pas assez de place de place disponible en mémoire.\n",erreur);
		return (menu_t*)NULL;
	}

	// Affectation des attributs
	if( SDL_CreateWindowAndRenderer(500,500,SDL_WINDOW_SHOWN,&(menu->window),&(menu->renderer)) ){
		printf("%sSDL_CreateWindowAndRenderer : %s",erreur, SDL_GetError());
		return (menu_t*)NULL;
	}
	SDL_SetWindowTitle(menu->window,"Le tombeau du désert ardant");
	SDL_Color couleur = {255,165,0,80};
	if( changerFond_couleur( menu->renderer , &couleur ) )
		return (menu_t*)NULL;
	SDL_RenderPresent(menu->renderer);

	// Affectation des Méthodes
	menu->gererEvenement = (err_t (*)(void *,SDL_Event *))gererEvenement_menu;
	menu->detruire = (err_t (*)(void *))detruire_menu;
	menu->afficher = (void (*)(void *))afficher_menu;

	return menu;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

