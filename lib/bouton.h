#ifndef _BOUTON_H_
#define _BOUTON_H_

/**
	* \file lib/bouton.h
	* \brief Définition de l'objet bouton.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 11:50:43
	*
	* L'objet bouton sert à creer un bouton et le dessine sur un renderer..
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "../lib/err.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)
/** \brief L'enumeration typeBouton_t.
	*
	* L'enumeration typeBouton_t sert à donner l'action que doit faire le bouton
	*
	*/
typedef enum typeBouton_t {
	BOUTON_Autre = 0, //!< Action incconu
	BOUTON_Quit, //!< Quitte la fenêtre
	BOUTON_Parametre, //!< Lance la fenêtre de paramètre
	BOUTON_Menu, //!< Lance le menu
	BOUTON_Suivant, //!< Passe à la page suivante
	BOUTON_Precedent, //!< Passe à la page précédente
	BOUTON_Valide, //!< Valide
	BOUTON_Annule //!< Annule
} typeBouton_t;

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure bouton_t.
	*
	* La structure bouton_t sert à creer un bouton et le dessine sur un renderer..
	*
	*/
typedef struct bouton_s {
#include "attributs_objet.h"
	SDL_Rect bouton; //!< Le cadre du bouton
	char *text; //!< Le text du bouton
	typeBouton_t type; //!< Le type du bouton
} bouton_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
extern bouton_t * creer_bouton();

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
