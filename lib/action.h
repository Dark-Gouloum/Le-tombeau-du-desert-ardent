#ifndef _ACTION_H_
#define _ACTION_H_

/**
	* \file lib/action.h
	* \brief Définition de l'objet action.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Ven. 03 Mars 2023 11:52:38
	*
	* L'objet action sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "err.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure action_t.
	* \author Dylan GRAMMONT
	*
	* La structure action_t sert à FaitQuelqueChose.
	*
	*/
typedef struct action_s {
#include "attributs_objet.h"
	int var; //!< Une simple variable.
} action_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Dylan GRAMMONT
	*
	* La fonction 'afficherSurvivant_action' est prévue pour fonctionner dans le fichier 'projet/test/action.c'.
	* Cette fonction affiche le nombre de action non-détruit, ainsi que le nombre d'objet inclut dans action qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_action();

/**\brief La fonction créant un objet action_t.
	* \author Dylan GRAMMONT
	* \param[in,out] utilite
	* \return un pointeur sur un action_t.
	*
	* La fonction 'creer_action' crée un objet action.
	*
	*/
extern action_t * creer_action();

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
