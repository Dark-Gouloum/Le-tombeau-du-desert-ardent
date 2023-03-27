#ifndef _WIDGET_H_
#define _WIDGET_H_

/**
	* \file lib/widget.h
	* \brief Définition d'un widget générique
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 04:23:47
	*
	* Définition d'un widget générique.
	* Le widget générique peut prendre la place de n'importe qu'elle widget.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun_sdl.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure widget_t.
	* \author Erwan PECHON
	*
	* La structure widget_t sert à remplacer n'importe qu'elle widget.
	*
	*/
typedef struct widget_s {
#include "attributs_widget.h"
} widget_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
extern err_t changerRendu(void *widget,SDL_Renderer *rendu);

extern SDL_Rect * obtenirSource(void *widget);
extern err_t changerSource(void *widget, SDL_Rect *src);

extern SDL_Rect * obtenirDest(void *widget);
extern err_t changerDest(void *widget, SDL_Rect *dest);
extern err_t actualiserDest(void *widget, float pL , float pH );

extern int hover(void *widget , SDL_Point *curseur);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
