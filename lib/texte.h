#ifndef _TEXTE_H_
#define _TEXTE_H_

/**
	* \file lib/texte.h
	* \brief Définition de l'objet texte.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Lun. 13 Févr. 2023 18:46:38
	*
	* L'objet texte sert à écrire du texte sur une fenêtre.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "err.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure texte_t.
	* \author Dylan GRAMMONT
	*
	* La structure texte_t sert à écrire du texte sur une fenêtre.
	*
	*/
typedef struct texte_s {
#include "attributs_objet.h"
	int var; //!< Une simple variable.
} texte_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Dylan GRAMMONT
	*
	* La fonction 'afficherSurvivant_texte' est prévue pour fonctionner dans le fichier /test/texte.
	* Cette fonction affiche le nombre de texte non-détruit, ainsi que le nombre d'objet inclut dans texte qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_texte();
/**\brief La fonction renvoyant le nombre d'objet texte_t non détruit.
	* \author Dylan GRAMMONT
	*
	* La fonction 'obtenirNbSurvivant_texte' renvoit uniquement le nombre d'objet texte_t non-détruit.
	* Cette fonction ne gére pas les objet inclut dans des texte_t.
	*
	*/
extern int obtenirNbSurvivant_texte();

/**\brief La fonction créant un objet texte_t.
	* \author Dylan GRAMMONT
	* \param[in,out] utilite
	* \return un pointeur sur un texte_t.
	*
	* La fonction 'creer_texte' crée un objet texte.
	*
	*/
extern texte_t * creer_texte();

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
