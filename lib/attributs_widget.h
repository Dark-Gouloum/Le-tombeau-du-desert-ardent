/**
	* \file lib/attribut_widget.h
	* \brief Définition des attributs de tout les widgets.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 01:19:08
	*
	* Ce fichier contient les attributs en commun avec tout les widgets.
	* Il faut inclure ce fichier directement dans la définition d'une structure ayant besoin de ces attributs.
	*
	*/

#include "attributs_objet.h"

// Attributs des widgets
SDL_Renderer *rendu;
SDL_Rect *source;
SDL_Rect *dest;

// Méthodes des widgets
err_t (*dessiner)(void*); //!< Methode de dessin du widget sur la fenêtre.
	//!< @param in Le rendu de la fenêtre
	//!< @param in Le widget à dessiner
	//!< @return E_OK en cas de réussite, ou le code d'erreur le cas échéant.

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

