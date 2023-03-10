#ifndef _TEXTE_H_
#define _TEXTE_H_

/**
	* \file lib/texte.h
	* \brief Définition de l'objet texte.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 28 Févr. 2023 14:40:03
	*
	* L'objet texte sert à ecrire du texte sur la fenêtre.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "err.h"
#include "stylo.h"
#include "ancre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure texte_t.
	* \author Erwan PECHON
	*
	* La structure texte_t sert à ecrire du texte sur la fenêtre.
	*
	*/
typedef struct texte_s {
#include "attributs_widget.h"
	err_t (*changerStylo)(SDL_Renderer*,stylo_t*,void* ); //!< Methode pour changer le stylo de l'objet
		//!< @param in Le pointeur sur l'objet à modifié.
		//!< @param in Le pointeur sur le nouveau stylo.
		//!< @param out Un entier simbolisant la réussite ou l'echec de la méthode.
		//!<
		//!< Pour changer le stylo d'un label, il faut appeler sa méthode de modification, et donner l'adresse de son pointeur en paramètre.
		//!<
	char* texte; //!< Le texte à afficher.
	SDL_Texture *texture; //!< L'image du texte.
	SDL_Color *fond; //!< La couleur de surlignement du texte
	SDL_Rect rect; //!< L'espace occupé par le texte.
	ancre_t ancre; //!< Le point d'ancrage du texte.
} texte_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Erwan PECHON
	*
	* La fonction 'afficherSurvivant_texte' est prévue pour fonctionner dans le fichier 'projet/test/texte.c'.
	* Cette fonction affiche le nombre de texte non-détruit, ainsi que le nombre d'objet inclut dans texte qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_texte();

/**\brief La fonction créant un objet texte_t.
	* \author Erwan PECHON
	* \param[in] La police d'écriture
	* \param[in] Le texte à écrire
	* \param[in] Le point de fixation du texte
	* \param[out] Un pointeur sur un rectangle contenant les coordonée d'affichage du texte
	* \return un pointeur sur un texte_t.
	*
	* La fonction 'creer_texte' crée un objet texte.
	*
	*/
extern texte_t * creer_texte(SDL_Renderer *r, stylo_t *s, char *str, ancre_t *ancre);

extern void surligner_texte( texte_t *texte , SDL_Color *fond );

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
