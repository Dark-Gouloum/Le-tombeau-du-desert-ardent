#ifndef _MENU_H_
#define _MENU_H_

/**
	* \file lib/menu.h
	* \brief Définition de l'objet menu.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 14:21:44
	*
	* L'objet menu sert à créer un menu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "fenetre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
extern err_t ajouterBouton_menu( fenetre_t *f, int nbB,char *nomB[],err_t (*action)(int argc,...), SDL_Point *pos,int nbCol );
extern err_t creer_menu(Uint32 flags, char *titre,SDL_Color *c, char *fond , int nbCol , fenetre_t **fenetre , SDL_Point *pos);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
