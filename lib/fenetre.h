#ifndef _FENETRE_H_
#define _FENETRE_H_

/**
	* \file lib/fenetre.h
	* \brief Définition de l'objet fenetre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 13 Févr. 2023 11:20:15
	*
	* L'objet fenetre sert à creer et gerer une fenêtre basique.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "err.h"
#include "coord.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

extern unsigned int cmpt_fenetre;
// CRÉATION(S) D(ES) ÉNUMÉRATION(S)
/** \brief L'enumeration clique_t.
	* \author Erwan PECHON
	*
	* L'enumeration clique_t sert à savoir qu'elle bouton de la souris à était cliqué.
	*
	*/
typedef enum clique_s {
	CLIQUE_Erreur = 0, //!< Bouton inconnnu
	CLIQUE_Gauche, //!< Bouton gauche
	CLIQUE_Mollette, //!< Bouton centrale
	CLIQUE_Droit //!< Bouton droit
} clique_t;

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure fenetre_t.
	* \author Erwan PECHON
	*
	* La structure fenetre_t sert à creer et gerer une fenêtre basique.
	*
	*/
typedef struct fenetre_s {
#include "attributs_objet.h"
#include "attributs_fenetre.h"
} fenetre_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/** \brief La fonction créant un objet fenetre_t.
	* \author Erwan PECHON
	* \param[in] La dimension de la fenêtre {largueur,hauteur}.
	* \param[in] Voir la documentation de la SDL
	* \param[in] Titre de la fenêtre
	* \return La fenêtre
	*
	* La fonction 'creer_fenetre" crée un objet fenetre_t
	*/
extern fenetre_t * creer_fenetre(coord_t dim, Uint32 WindowFlags, char *titre);

/** \brief La fonction initialisant la SDL.
	* \author Erwan PECHON
	* \return En cas de problème, renvoit E_INIT, Sinon, renvoit 0.
	*
	* La fonction 'initialisation_SDL' initialise la SDL.
	* Cette fonction doit être au tout début de la fonction 'main' de chaque programme utilisant la SDL.
	*
	*/
extern err_t initialisation_SDL();

/** \brief Obtient la position de la souris, sur la fenêtre active.
	* \author Erwan PECHON
	* \return un entier valant 0 en cas d'erreur, ou un entier symbolisant le bouton cliquer.
	*
	* La fonction 'obtenir_positionSouris' obtient le bouton cliqué, ainsi que la position du curseur dans la fenêtre active.
	*
	*/
extern clique_t obtenir_positionSouris( SDL_Point *point);

/** \brief Obtient l'adresse du renderer de la fenêtre
	* \author Erwan PECHON
	* \param[in] un objet fenetre_t
	* \return l'adresse du renderer de l'objet passé en paramètre
	*
	* La fonction obtient l'adresse du renderer d'un objet fenetre_t.
	*
	*/
extern SDL_Renderer *getRenderer( fenetre_t *f );

/** \brief Change la couleur du pinceau
	* \author Erwan PECHON
	* \param[in] un objet fenetre_t
	* \param[in] la nouvelle couleur
	* \return E_COLOR en cas d'erreur, E_OK sinon.
	*
	* La fonction change la couleur du pinceau de la fenêtre.
	*
	*/
extern err_t changerCouleur( fenetre_t *f, SDL_Color *c );

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
