#ifndef _BLOCTEXT_H_
#define _BLOCTEXT_H_

/**
	* \file lib/blocText.h
	* \brief Définition de l'objet blocText.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 27 Mars 2023 21:50:49
	*
	* L'objet blocText sert à afficher du texte dans une boite.
	* Il garde en mémoire jusqu'où le texte à était écrit.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure blocText_t.
	* \author Erwan PECHON
	*
	* La structure blocText_t sert à afficher du texte dans une boite.
	*
	*/
typedef struct blocText_s {
#include "attributs_objet.h"
	int var; //!< Une simple variable.
} blocText_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Erwan PECHON
	*
	* La fonction 'afficherSurvivant_blocText' est prévue pour fonctionner dans le fichier 'projet/test/blocText.c'.
	* Cette fonction affiche le nombre de blocText non-détruit, ainsi que le nombre d'objet inclut dans blocText qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_blocText();

/**\brief La fonction créant un objet blocText_t.
	* \author Erwan PECHON
	* \param[in,out] utilite
	* \return un pointeur sur un blocText_t.
	*
	* La fonction 'creer_blocText' crée un objet blocText.
	*
	*/
extern blocText_t * creer_blocText();

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
