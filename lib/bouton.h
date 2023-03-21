#ifndef _BOUTON_H_
#define _BOUTON_H_

/**
	* \file lib/bouton.h
	* \brief Définition de l'objet bouton.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 09:56:52
	*
	* L'objet bouton sert à définir des boutons.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun_sdl.h"
#include "widget.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure bouton_t.
	* \author Erwan PECHON
	*
	* La structure bouton_t sert à définir des boutons.
	*
	*/
typedef struct bouton_s {
#include "attributs_objet.h"
	err_t (*dessiner)(void*); //!< Methode de dessin du widget sur la fenêtre.
		//!< @param in Le rendu de la fenêtre
		//!< @param in Le widget à dessiner
		//!< @return E_OK en cas de réussite, ou le code d'erreur le cas échéant.
	err_t (*action)(int argc,...);
	widget_t *widget;
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
	* \param[in,out] utilite
	* \return un pointeur sur un bouton_t.
	*
	* La fonction 'creer_bouton' crée un objet bouton.
	*
	*/
extern bouton_t * creer_bouton(SDL_Renderer *rendu, void *widget, err_t (*action)(int argc,...) );

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
