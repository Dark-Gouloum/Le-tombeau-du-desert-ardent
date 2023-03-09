#ifndef _CREE_PERSO_H_
#define _CREE_PERSO_H_

/**
	* \file lib/cree_perso.h
	* \brief Définition de l'objet cree_perso.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Jeu. 09 Mars 2023 13:59:44
	*
	* L'objet cree_perso sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "err.h"
#include "perso.h"
#include "fenetre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure cree_perso_t.
	* \author Dylan GRAMMONT
	*
	* La structure cree_perso_t sert à FaitQuelqueChose.
	*
	*/
typedef struct cree_perso_s {
#include "attributs_objet.h"
	int var; //!< Une simple variable.
} cree_perso_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Dylan GRAMMONT
	*
	* La fonction 'afficherSurvivant_cree_perso' est prévue pour fonctionner dans le fichier 'projet/test/cree_perso.c'.
	* Cette fonction affiche le nombre de cree_perso non-détruit, ainsi que le nombre d'objet inclut dans cree_perso qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_cree_perso();

/**\brief La fonction créant un objet cree_perso_t.
	* \author Dylan GRAMMONT
	* \param[in,out] utilite
	* \return un pointeur sur un cree_perso_t.
	*
	* La fonction 'creer_cree_perso' crée un objet cree_perso.
	*
	*/
extern cree_perso_t * creer_cree_perso();


/**
 * \brief La fonction de creation de personnage via la SDL2
 * \author Dylan GRAMMONT
 * \param[in,out] perso
*/
extern void creationPersonnage(personage_t * perso);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
