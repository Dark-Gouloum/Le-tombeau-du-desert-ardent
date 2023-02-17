/**
	* \file lib/attribut_objet.h
	* \brief Définition des attributs de tout les objets.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 01:19:08
	*
	* Ce fichier contient les attributs en commun avec tout les objets.
	* Il faut inclure ce fichier directement dans la définition d'une structure ayant besoin de ces attributs.
	*
	*/

err_t (*detruire)(void*); //!< Methode de destruction de l'objet.
	//!< @param in L'addresse du pointeur sur l'objet à détruire.
	//!< @param out Un entier simbolisant la réussite ou l'echec de la méthode.
	//!<
	//!< La méthode detruire est commune à tout les objet.
	//!< pour détruire un objet, il faut appeler sa méthode de destruction, et donner l'adresse de son pointeur en paramètre.
	//!<
void (*afficher)(void*); //!< Methode d'affichage de l'objet.
	//!< @param in L'addresse du pointeur sur l'objet à afficher.
	//!<
	//!< La méthode 'affiche'r est commune à tout les objet.
	//!< pour afficher un objet, il faut appeler sa méthode d'affichage, et donner l'adresse de son pointeur en paramètre.
	//!<

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

