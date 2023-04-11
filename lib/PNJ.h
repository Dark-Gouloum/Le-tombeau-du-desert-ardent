#ifndef _PNJ_H_
#define _PNJ_H_

/**
	* \file lib/PNJ.h
	* \brief Définition de l'objet PNJ.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Jeu. 23 Mars 2023 01:36:49
	*
	* L'objet PNJ sert à gérer les Personnage Non Joueur du jeu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun_perso.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure PNJ_t.
	* \author Dylan GRAMMONT
	*
	* La structure PNJ_t sert à gérer les Personnage Non Joueur du jeu.
	*
	*/
typedef struct PNJ_s {
#include "attributs_perso.h"
} PNJ_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Dylan GRAMMONT
	*
	* La fonction 'afficherSurvivant_PNJ' est prévue pour fonctionner dans le fichier 'projet/test/PNJ.c'.
	* Cette fonction affiche le nombre de PNJ non-détruit, ainsi que le nombre d'objet inclut dans PNJ qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_PNJ();

/**\brief La fonction créant un objet PNJ_t.
	* \author Dylan GRAMMONT
	* \param[in,out] utilite
	* \return un pointeur sur un PNJ_t.
	*
	* La fonction 'creer_PNJ' crée un objet PNJ.
	*
	*/
extern PNJ_t * creer_PNJ(char *nomPNJ);
extern err_t lire_PNJ(char *ligne, PNJ_t **pnj);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
