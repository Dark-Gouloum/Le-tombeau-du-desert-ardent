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
#include "commun_perso.h"
#include "joueur.h"
#include "PNJ.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**	* \brief La fonction permettant au joueur d'attaquer un mechant.
	* \author Dylan GRAMMONT
	* \param[in,out] perso
	* \param[in,out] mechant
	*/
extern void joueur_attaque(joueur_t * perso, PNJ_t * mechant);

/**	* \brief La fonction permettant au mechant d'attaquer un joueur.
	* \author Dylan GRAMMONT
	* \param[in,out] perso
	* \param[in,out] mechant
	*/
extern void mechant_attaque(joueur_t * perso, PNJ_t * mechant);

/**	* \brief La fonction permettant au joueur de crocheté des serrure.
	* \author Dylan GRAMMONT
	* \param[in,out] perso
	*/
extern int crochetage(joueur_t * perso);

/**	*\brief La fonction permettant au joueur de lancer un dé.
	* \author Dylan GRAMMONT
	* \param[in,out] stat
	* \param[in,out] statMax
	*/
extern int lancer_de(int stat,int statMax);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
