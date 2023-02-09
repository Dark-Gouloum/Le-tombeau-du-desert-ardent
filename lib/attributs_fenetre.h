#ifndef _ATTRIBUT_FENETRE_H_
#define _ATTRIBUT_FENETRE_H_

/**
	* \file lib/attribut_fenetre.h
	* \brief Définition des attributs de toutes les fenetre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 01:19:08
	*
	* Ce fichier contient les attributs en commun avec toutes les fenetres.
	* Il faut inclure ce fichier directement dans la définition d'une structure ayant besoin de ces attributs.
	*
	*/

err_t (*gererEvenement)( void*, SDL_Event* ); ///!< Methode de gestion des événement de la fenêtre
	///!< @param in L'addresse du pointeur sur la fenetre à gérer.
	///!< @param in L'addresse de l'évenement qui vient de se dérouler.
	///!< @param out Un entier symbolisant la réussite ou l'echec de la méthode.
	///!<
	///!< La méthode gestion d'évenement est commune à tout les objet.
	///!< pour gerer les évenements d'une fenêtre, il faut appeler sa méthode de gestion, et donner son pointeur en paramètre.
	///!<
SDL_Window *window; //!< La fenêtre
SDL_Renderer *renderer; //!< Le renderer de la fenetre

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
