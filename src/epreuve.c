/**
 * \file src/epreuve.c
 * \brief Définition de l'objet epreuve.
 * \author Erwan PECHON
 * \version 0.1
 * \date Mar. 11 Avril 2023 13:38:08
 *
 * L'objet epreuve sert à tester les compétence du joueur.
 *
 */

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/epreuve.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_epreuve = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
static err_t epreuve_combat( livre_t *livre , char *ligne, int *reussi){
	err_t err = E_OK;
	PNJ_t *enemi = NULL;
	if(( err=lire_PNJ(ligne,&enemi) )){
		MSG_ERR2("de la lecture de l'enemi à combattre");
		return(err);
	}
	*reussi = combat_personnage(livre->joueur,enemi,livre->fenetre->fenetre);
	return(err);
}

static err_t epreuve_agilite( livre_t *livre , char *ligne, int *reussi){
	int quit = 0;
	int difficulte = 0;
	int dist = 1000;
	SDL_Event event;
	SDL_Point pos_souris={0,0} , deb={0,0} , fin={0,0};
	SDL_Point dim;
	SDL_Window *fen = NULL;
	SDL_Renderer *rendu = NULL;

	{ // Obtenir les dimensions de l'écran
		SDL_DisplayMode current;
		if( SDL_GetCurrentDisplayMode(0,&current) !=0 ){
			MSG_ERR(E_OBTENIR,"Impossible de récupérer le mode d'affichage courant");
			MSG_ERR_COMP("SDL_GetCurrentDisplayMode",SDL_GetError());
			return(E_OBTENIR);
		}
		dim.x = current.w / 2;
		dim.y = current.h / 2;
	}
	{ // Création de la fenêtre
		fen = SDL_CreateWindow("Épreuve d'agilité", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dim.x, dim.y, SDL_WINDOW_SHOWN);
		if( !fen ){
			MSG_ERR(E_AUTRE,"Impossible de créer la fenêtre");
			MSG_ERR_COMP("SDL_CreateWindow",SDL_GetError());
			return(E_AUTRE);
		}
		rendu = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if( !rendu ){
			MSG_ERR(E_AUTRE,"Impossible de créer le rendu");
			MSG_ERR_COMP("SDL_CreateRenderer",SDL_GetError());
			return(E_AUTRE);
		}
	}
	{ // Obtention de la difficulté
		sscanf(ligne,"%d",&difficulte);
		// difficulte-= obtenir_stat(STAT_AGILITE,livre->joueur);
		difficulte+= 2;
	}
	deb.x = dim.x / 2;
	deb.y = dim.y / 2;
	dist-= difficulte*difficulte;

	*reussi = 1;
	int i = 0;
	while( i<difficulte ){
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEMOTION) {
				souris.x = event.motion.x;
				souris.x = event.motion.y;
			}
		}
		// Effacer le rendu précédent
		SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
		SDL_RenderClear(rendu);
		// Calcul de la distance à la ligne
		int dist_a_ligne = 0;
		dist_a_ligne+= ( (fin.y)-(deb.y) ) * souris.x;
		dist_a_ligne-= ( (fin.x)-(deb.x) ) * souris.y;
		dist_a_ligne+= fin.x * deb.y;
		dist_a_ligne+= fin.y * deb.x;
		dist_a_ligne = abs( dist_a_ligne ) / sqrt( pow((fin.y)-(deb.y),2) + pow((fin.x)-(deb.x),2) ) ;
		// Vérification de la distance à la ligne
		if (dist_to_line <= dist) {
			*reussi = 0;
			break;
		}
		// Dessiner la ligne
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, deb.x, deb.y, fin.x, fin.y);
		// Afficher le rendu
		SDL_RenderPresent(renderer);

		// Générer une nouvelle ligne aléatoire si la souris atteint la fin de la ligne
		if( (( (fin.x-dist)<=souris.x )&&( souris.x<=(fin.x-dist) )) || (( (fin.y-dist)<=souris.y )&&( souris.y<=(fin.y-dist) )) ){
			deb.x = fin.x;
			deb.y = fin.y;
			fin.x = rand() % dim.x;
			fin.y = rand() % dim.y;
			i++;
		}
	}

	// Libération des ressources
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return(E_OK);
}
extern err_t epreuve_type(livre_t *livre, char *ligne, int *reussi){
	switch( ligne[0] ){
		case 'A' :
			if(( err=epreuve_agilite(livre,ligne+1,reussi) )){
				MSG_ERR2("de l'épreuve d'agilité");
			}
			break;
		case 'C' :
			if(( err=epreuve_combat(livre,ligne+1,reussi) )){
				MSG_ERR2("du combat");
			}
			break;
		default :
			{
				char msg[40];
				sprintf(msg,"Le type d'épreuve '%c' est inconnue.",*(ligne-1));
				MSG_ERR(E_FICHIER,msg);
				return(E_FICHIER);
			}
	}
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

