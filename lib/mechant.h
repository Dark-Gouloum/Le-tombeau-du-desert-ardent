#ifndef _MECHANT_H_
#define _MECHANT_H_

/**
	* \file lib/mechant.h
	* \brief Définition de l'objet mechant.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Ven. 03 Mars 2023 10:21:00
	*
	* L'objet mechant sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "err.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure mechant_t.
	* \author Dylan GRAMMONT
	*
	* La structure mechant_t sert à FaitQuelqueChose.
	*
	*/
typedef struct mechant_s {
#include "attributs_objet.h"
	int force;
	int intelligence;
	int PV;
	int armure;
	int critique;
	int agilite;
	char * nom;
} mechant_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Dylan GRAMMONT
	*
	* La fonction 'afficherSurvivant_mechant' est prévue pour fonctionner dans le fichier 'projet/test/mechant.c'.
	* Cette fonction affiche le nombre de mechant non-détruit, ainsi que le nombre d'objet inclut dans mechant qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_mechant();

/**\brief La fonction créant un objet mechant_t.
	* \author Dylan GRAMMONT
	* \param[in,out] utilite
	* \return un pointeur sur un mechant_t.
	*
	* La fonction 'creer_mechant' crée un objet mechant.
	*
	*/
extern mechant_t * creer_mechant();

/**
 * \brief La fonction qui attribu les stat a un objet mechant_t.
 * \author Dylan GRAMMONT
 * \param[in,out] mechant
 * 
*/
extern void attribuer_mechant(mechant_t * mechant, int force, int intelligence, int PV, int Armure, int critique, int agilite, char * nom);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
