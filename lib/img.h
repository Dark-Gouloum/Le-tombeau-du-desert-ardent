#ifndef _IMG_H_
#define _IMG_H_

/**
	* \file lib/img.h
	* \brief Définition de l'objet img.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 04:23:47
	*
	* L'objet img sert à gérer une image.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun_sdl.h"
#include "widget.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure img_t.
	* \author Erwan PECHON
	*
	* La structure img_t sert à gérer une image.
	*
	*/
typedef struct img_s {
#include "attributs_widget.h"
	SDL_Texture *image;
} img_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Erwan PECHON
	*
	* La fonction 'afficherSurvivant_img' est prévue pour fonctionner dans le fichier 'projet/test/img.c'.
	* Cette fonction affiche le nombre de img non-détruit, ainsi que le nombre d'objet inclut dans img qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_img();

/**\brief La fonction créant un objet img_t.
	* \author Erwan PECHON
	* \param[in,out] utilite
	* \return un pointeur sur un img_t.
	*
	* La fonction 'creer_img' crée un objet img.
	*
	*/
extern img_t * creer_img_ParTexture(SDL_Renderer *rendu, SDL_Texture **texture);
extern img_t * creer_img_ParSurface(SDL_Renderer *rendu, SDL_Surface **surface);
extern img_t * creer_img(SDL_Renderer *rendu, const char *nomFichier);
extern err_t img_demandeTaille( img_t *img , SDL_Rect *rect );
extern err_t img_fusion( img_t **imgContenant , img_t *img2 );
extern err_t img_copier( img_t **nouv , img_t *img , SDL_Point *tailleMin , SDL_Point *pos );

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
