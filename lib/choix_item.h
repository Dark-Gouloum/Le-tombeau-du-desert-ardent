#ifndef _choix_item_H_
#define _choix_item_H_

/**
	* \file lib/choix_item.h
	* \brief Définition de l'objet choix_item.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Jeu. 09 Mars 2023 13:59:44
	*
	* L'objet choix_item sert à FaitQuelqueChose.
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

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

/**
 * \brief La fonction de choix d'item via la SDL2
 * \author Dylan GRAMMONT
 * \param[in,out] perso
*/
extern err_t choix_item(fenetre_t *fMere,joueur_t *perso, liste_t * lst_item,int nbAjout,int *retour);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
