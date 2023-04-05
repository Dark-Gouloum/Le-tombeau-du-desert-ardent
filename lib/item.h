#ifndef _item_H_
#define _item_H_

/**
	* \file lib/item.h
	* \brief Définition de l'objet item.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Mar. 28 Févr. 2023 14:47:08
	*
	* L'objet item sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun.h"
#include "liste.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)
/** \brief Enumration stat_t.
	* \author Dylan GRAMMONT
	*
	* L'enumration stat_t sert à savoir quel statistique l'objet modifie.
	*
	*/
typedef enum stat_modif_s{
	STAT_UNK =0, //!<
	STAT_FORCE, //!<
	STAT_INTEL, //!<
	STAT_PV, //!<
	STAT_ARMURE, //!<
	STAT_CRITIQUE, //!<
	STAT_AGILITE //!<
}stat_t;

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure item_t.
	* \author Dylan GRAMMONT
	*
	* La structure item_t sert à FaitQuelqueChose.
	*
	*/
typedef struct item_s {
#include "attributs_objet.h"
	char * nom;
	liste_t *lstModificateurs;
} item_t;

typedef struct modificateur_s {
#include "../lib/attributs_objet.h"
	stat_t modif;
	int valeur;
} modificateur_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Dylan GRAMMONT
	*
	* La fonction 'afficherSurvivant_item' est prévue pour fonctionner dans le fichier 'projet/test/item.c'.
	* Cette fonction affiche le nombre de item non-détruit, ainsi que le nombre d'objet inclut dans item qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_item();

/**\brief La fonction créant un objet item_t.
	* \author Dylan GRAMMONT
	* \param[in,out] utilite
	* \return un pointeur sur un item_t.
	*
	* La fonction 'creer_item' crée un objet item.
	*
	*/
extern item_t * creer_item(char *nom);

/**	* \brief La fonction traduisant une stat_t en chaine de caractère.
	* \author Dylan GRAMMONT
	* \param[in] stat
	* \return un pointeur sur une chaine de caractère.
	*/
extern char * traduire(stat_t stat);

extern err_t ajouterModificateur(item_t *item, stat_t modif, int valeur);
extern err_t sauvegarder_item(FILE *f, item_t *item);
extern err_t charger_item(FILE *f, item_t **item);
// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
