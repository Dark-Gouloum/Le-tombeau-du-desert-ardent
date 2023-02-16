#ifndef _BOUTON_H_
#define _BOUTON_H_

/**
	* \file lib/bouton.h
	* \brief Définition de l'objet bouton.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 14 Févr. 2023 19:09:04
	*
	* L'objet bouton sert à créer et gérer des boutons.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <SDL2/SDL.h>

#include "err.h"
#include "stylo.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure bouton_t.
	* \author Erwan PECHON
	*
	* La structure bouton_t sert à créer et gérer des boutons.
	*
	*/
typedef struct bouton_s {
	err_t (*action)(void); //!< L'action à faire en cas de clic
	int (*estCliquer)(void *, SDL_Point *); //!< Test si le curseur est au dessus du bouton
		//!< @param in Le bouton à tester
		//!< @param in Les coordonnée (x,y) du bouton
		//!< return 1 si cliqué 0 sinon.
		//!<
		//!< Test si le curseur est au dessus du bouton
		//!<
#include "attributs_objet.h"
	SDL_Rect bouton; //!< La zone cliquable du bouton
} bouton_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Erwan PECHON
	*
	* La fonction 'afficherSurvivant_bouton' est prévue pour fonctionner dans le fichier 'projet/test/bouton.c'.
	* Cette fonction affiche le nombre de bouton non-détruit, ainsi que le nombre d'objet inclut dans bouton qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_bouton();

/**\brief La fonction créant un objet bouton_t.
	* \author Erwan PECHON
	* \param[in] Le renderer où afficher le bouton
	* \param[in] La police du texte du bouton
	* \param[in] Les coordonnées (x,y) du millieu du bouton
	* \param[in] La fonction associé à ce bouton
	* \return un pointeur sur un bouton_t.
	*
	* La fonction 'creer_bouton' crée un objet bouton.
	*
	*/
extern bouton_t * creer_bouton(SDL_Renderer *r,stylo_t *s , char *texte,SDL_Point pt,angle_t angle , err_t (*action)(void));

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
