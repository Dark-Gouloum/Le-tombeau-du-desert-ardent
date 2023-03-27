#ifndef _PAGE_H_
#define _PAGE_H_

/**
	* \file lib/page.h
	* \brief Définition de l'objet page.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 23 Mars 2023 18:41:01
	*
	* L'objet page sert à afficher le contenu d'une page.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun_sdl.h"
#include "fenetre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure page_t.
	* \author Erwan PECHON
	*
	* La structure page_t sert à afficher le contenu d'une page.
	*
	*/
typedef struct page_s {
#include "attributs_objet.h"
	int var; //!< Une simple variable.
} page_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Erwan PECHON
	*
	* La fonction 'afficherSurvivant_page' est prévue pour fonctionner dans le fichier 'projet/test/page.c'.
	* Cette fonction affiche le nombre de page non-détruit, ainsi que le nombre d'objet inclut dans page qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_page();

/**\brief La fonction créant un objet page_t.
	* \author Erwan PECHON
	* \param[in,out] utilite
	* \return un pointeur sur un page_t.
	*
	* La fonction 'creer_page' crée un objet page.
	*
	*/
extern page_t * creer_page();

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
