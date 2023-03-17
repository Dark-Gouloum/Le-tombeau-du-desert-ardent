/**
	* \file lib/attribut_widget.h
	* \brief Définition des attributs de toutes les widget.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 01:19:08
	*
	* Ce fichier contient les attributs en commun avec toutes les widgets.
	* Il faut inclure ce fichier directement dans la définition d'une structure ayant besoin de ces attributs.
	*
	*/
#include "attributs_objet.h"
err_t (*dessiner)(SDL_Point*,SDL_Renderer*,void*); //!< Methode de destruction de l'objet.
	//!< @param in La position où dessiner le centre de l'image;
	//!< @param out L'angle en bas à droite de l'image déssiner;
	//!< @param in Le rendu où il faut dessiner.
	//!< @param in Le pointeur sur l'objet à dessiner.
	//!<
	//!< La méthode dessiner est commune à tout les widgets.
	//!< pour dessiner un widget sur la fenetre, il faut appeler sa méthode de dessin, et donner l'adresse de son pointeur en paramètre.
	//!<

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

