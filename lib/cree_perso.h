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
#include "commun_sdl.h"
#include "joueur.h"
#include "fenetre.h"
#include "police.h"

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

/**
 * \brief La fonction de creation de personnage via la SDL2
 * \author Dylan GRAMMONT
 * \param[in,out] perso
*/
extern int creationPersonnage(joueur_t *perso, liste_t * lst_item,int nbItemAct);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
