#ifndef _ANCRE_H_
#define _ANCRE_H_

/**
	* \file lib/ancre.h
	* \brief Définition de l'objet ancre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 14 Mars 2023 15:23:38
	*
	* L'objet ancre sert à ancrer un widget dans la fenêtre.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>

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

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure ancre_t.
	* \author Erwan PECHON
	*
	* La structure ancre_t sert à ancrer un widget dans la fenêtre.
	*
	*/
typedef struct ancre_s {
#include "attributs_objet.h"
	err_t (*changerX)(struct ancre_s*,float); //!< Methode changeant l'abscisse de l'objet.
	//!< @param in Le pointeur sur l'objet à modifier.
	//!<
	//!< pour modifier un objet, il faut appeler sa méthode de modification, et donner son pointeur en paramètre.
	//!<
	err_t (*changerY)(struct ancre_s*,float); //!< Methode changeant l'ordonnée de l'objet.
	//!< @param in Le pointeur sur l'objet à modifier.
	//!<
	//!< pour modifier un objet, il faut appeler sa méthode de modification, et donner son pointeur en paramètre.
	//!<
	err_t (*changerA)(struct ancre_s*,angle_t); //!< Methode changeant le point d'encrage de l'objet.
	//!< @param in Le pointeur sur l'objet à modifier.
	//!<
	//!< pour modifier un objet, il faut appeler sa méthode de modification, et donner son pointeur en paramètre.
	//!<


	angle_t angle; //!< Le point du rectangle qui est encré.
	int x,y; //!< Le point de la fenêtre où fixé l'ancre.
} ancre_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Erwan PECHON
	*
	* La fonction 'afficherSurvivant_ancre' est prévue pour fonctionner dans le fichier 'projet/test/fenetre.c'.
	* Cette fonction affiche le nombre de ancre non-détruit, ainsi que le nombre d'objet inclut dans fenetre qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_ancre();

/**\brief La fonction créant un objet ancre_t.
	* \author Erwan PECHON
	* \param[in] Le point de fixation de l'ancre dans le conteneur, sur l'axe des abscisses. Doit-être dans l'intervalle [0,1].
	* \param[in] Le point de fixation de l'ancre dans le conteneur, sur l'axe des ordonnées. Doit-être dans l'intervalle [0,1].
	* \param[in] Le point de fixation de l'ancre dans l'objet.
	* \return un ancre_t.
	*
	* La fonction 'creer_ancre' crée un objet ancre.
	*
	*/
extern ancre_t *creer_ancre(float x, float y, angle_t angle);

/**\brief La fonction interpretant la signification d'un angle
	* \author Erwan PECHON
	* \param[in] L'angle à interpréter.
	* \return L'angle interpréter.
	*
	*/
extern char *interprete_angle(angle_t angle);
/**\brief La fonction verifiant l'existance d'un angle
	* \author Erwan PECHON
	* \param[in] L'angle à verifier.
	* \return E_OK, si il existe.
	*
	*/
extern err_t existe_angle(angle_t angle);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
