#ifndef _BOITE_H_
#define _BOITE_H_

/**
	* \file lib/boite.h
	* \brief Définition de l'objet boite.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 16 Mars 2023 13:15:38
	*
	* L'objet boite sert à encapsuler des widgets.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "err.h"
#include "liste.h"
#include "widget.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)


// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure boite_t.
	* \author Erwan PECHON
	*
	* La structure boite_t sert à encapsuler des widgets.
	*
	*/
typedef struct boite_s {
#include "attributs_widget.h"
	int xMax; //!< Jusqu'à qu'elle taille la boite peut-être agrandi ?
	int ecart; //!< Écart entre les widget.
	liste_t *lstWidgets; //!< la liste des widgets encapsuler.
} boite_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Erwan PECHON
	*
	* La fonction 'afficherSurvivant_boite' est prévue pour fonctionner dans le fichier 'projet/test/boite.c'.
	* Cette fonction affiche le nombre de boite non-détruit, ainsi que le nombre d'objet inclut dans boite qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_boite();

/**\brief La fonction créant un objet boite_t.
	* \author Erwan PECHON
	* \param[in,out] utilite
	* \return un pointeur sur un boite_t.
	*
	* La fonction 'creer_boite' crée un objet boite.
	*
	*/
extern boite_t * creer_boite(int xMax,int ecart);

extern err_t ajouter_widget_boite( boite_t *boite , void *widget );
	
// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
