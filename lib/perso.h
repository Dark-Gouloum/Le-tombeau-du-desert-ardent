#ifndef _perso_H_
#define _perso_H_

/**
	* \file lib/perso.h
	* \brief Définition de l'objet perso.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Mar. 28 Févr. 2023 14:38:44
	*
	* L'objet perso sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "err.h"
#include "item.h"
#include "liste.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure perso_t.
	* \author Dylan GRAMMONT
	*
	* La structure perso_t sert à FaitQuelqueChose.
	*
	*/
typedef struct personage_s{
	#include "attributs_objet.h"
	int force;
	int intelligence;
	int PV;
	int Armure;
	int critique;
	int agilite;
	int nbObjet;
	liste_t * listItem;

} personage_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Dylan GRAMMONT
	*
	* La fonction 'afficherSurvivant_perso' est prévue pour fonctionner dans le fichier 'projet/test/perso.c'.
	* Cette fonction affiche le nombre de perso non-détruit, ainsi que le nombre d'objet inclut dans perso qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_perso();

/**\brief La fonction créant un objet perso_t.
	* \author Dylan GRAMMONT
	* \param[in,out] utilite
	* \return un pointeur sur un perso_t.
	*
	* La fonction 'creer_perso' crée un objet perso.
	*
	*/
extern personage_t * creer_perso();

extern void sauvegarder(personage_t);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
