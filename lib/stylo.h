#ifndef _STYLO_H_
#define _STYLO_H_

/**
	* \file lib/stylo.h
	* \brief Définition de l'objet stylo.
	* \author Dylan GRAMMONT, Erwan PECHON
	* \version 0.1
	* \date Mar. 14 Févr. 2023 15:14:19
	*
	* L'objet stylo sert à écrire du texte sur la fenêtre.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "err.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)
/** \brief L'enumeration angle_t.
	* \author Erwan PECHON
	*
	* L'enumeration angle_t sert à indiquer un point clé d'un rectangle.
	*
	*/
typedef enum angle_s {
	ANGLE_ERREUR = 0, //!< Un point clé inconnue
	ANGLE_MILLIEU, //!< Le millieu du rectangle de texte
	ANGLE_GAUCHE_SUP, //!< L'angle gauche supérieur du rectangle de texte
	ANGLE_GAUCHE_INF, //!< L'angle gauche inférieur du rectangle de texte
	ANGLE_DROIT_SUP, //!< L'angle gauche supérieur du rectangle de texte
	ANGLE_DROIT_INF, //!< L'angle gauche inférieur du rectangle de texte
} angle_t;

/** \brief La structure ancre_t.
	* \author Erwan PECHON
	*
	* L'enumeration ancre_t sert à indiquer un point clé d'un rectangle.
	*
	*/
typedef struct ancre_s {
	angle_t angle; //!< Le point du rectangle qui est encré.
	SDL_Point point; //!< Le point de la fenêtre où fixé l'ancre.
} ancre_t;

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure stylo_t.
	* \author Dylan GRAMMONT
	*
	* La structure stylo_t sert à écrire du texte sur la fenêtre.
	*
	*/
typedef struct stylo_s {
#include "attributs_objet.h"
	err_t (*changerCouleur)(void*,SDL_Color); //!< Methode pour changer la couleur de l'objet
		//!< @param in Le pointeur sur l'objet à modifié.
		//!< @param in La nouvelle couleur.
		//!< @param out Un entier simbolisant la réussite ou l'echec de la méthode.
		//!<
		//!< Pour changer la couleur d'un widget, il faut appeler sa méthode de modification, et donner l'adresse de son pointeur en paramètre.
		//!<
	TTF_Font *font; //!< La police d'écriture utilisé par le stylo.
	SDL_Color couleur;
} stylo_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Dylan GRAMMONT
	*
	* La fonction 'afficherSurvivant_stylo' est prévue pour fonctionner dans le fichier '/test/stylo.c'.
	* Cette fonction affiche le nombre de stylo non-détruit, ainsi que le nombre d'objet inclut dans stylo qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_stylo();

/**\brief La fonction créant un objet stylo_t.
	* \author Dylan GRAMMONT
	* \param[in] la nom de la police , en partant du dossier "Annexe/Font".
	* \param[in] La taille de la police
	* \return un pointeur sur un stylo_t.
	*
	* La fonction 'creer_stylo' crée un objet stylo.
	*
	*/
extern stylo_t * creer_stylo(char *nomFont, int taille, SDL_Color c);

/** \brief La fonction initialisant la bibliothéque SDL_TTF.
	* \author Dylan GRAMMONT
	* \return En cas de problème, renvoit E_INIT, Sinon, renvoit 0.
	*
	* La fonction 'initialisation_SDL_TTF' initialise la bibliothéque SDL_TTF.
	* Cette fonction doit être au tout début de la fonction 'main' de chaque programme utilisant la bibiothéque SDL_TTF.
	*
	*/
extern err_t initialisation_SDL_TTF();

/** \brief La fonction écrivant un texte en utilisant une police d'écriture.
	* \author Dylan GRAMMONT
	* \param[in] Le renderer où il faut afficher le texte
	* \param[in] La police d'écriture
	* \param[in] Le texte à écrire
	* \param[in] Le point où encrer le texte
	* \param[in] Le point clé du rectangle du texte à encrer
	* \param[out] Un pointeur sur uun rectangle contenant les coordonée d'affichage du texte
	* \return Renvoit E_OK en cas de réussite
	*
	*
	*/
extern err_t creerTexture_texte(SDL_Renderer *r,stylo_t *s, char *texte , SDL_Rect *dest_rect , SDL_Texture **texture);


// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
