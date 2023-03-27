#ifndef _PAGE_H_
#define _PAGE_H_

/**
	* \file lib/page.h
	* \brief Définition de l'objet page.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 23 Mars 2023 18:41:01
	*
	* L'objet page sert à afficher le contenu d'une page.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun_sdl.h"
#include "fenetre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

/**\brief La fonction créant un objet page_t.
	* \author Erwan PECHON
	* \param[in,out] utilite
	* \return un pointeur sur un page_t.
	*
	* La fonction 'creer_page' crée un objet page.
	*
	*/
extern err_t creer_page(Uint32 flags,char *titre, char *fond, fenetre_t **fenetre,SDL_Point *pos);

extern err_t ajouterImages_page( fenetre_t *f , img_t *imgG , img_t *imgD , int central , int red );

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
