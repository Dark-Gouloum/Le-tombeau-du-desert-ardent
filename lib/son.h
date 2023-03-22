#ifndef _SON_H_
#define _SON_H_

/**
	* \file lib/son.h
	* \brief Définition de l'objet son.
	* \author Victor FOUQUERAY
	* \version 0.1
	* \date Mer. 22 Mars 2023 21:24:01
	*
	* L'objet son sert à gérer les sons et les musiques du jeu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun_sdl.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)
typedef enum typeSon_s {
	SON_UNK = 0,
	SON_MUSIQUE,
	SON_EFFET
} typeSon_t;

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure son_t.
	* \author Victor FOUQUERAY
	*
	* La structure son_t sert à gérer les sons et les musiques du jeu.
	*
	*/
typedef struct son_s {
#include "attributs_objet.h"
	typeSon_t type;
	union {
		Mix_Chunk * eff;
		Mix_Music * mus;
	} stock;
} son_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Victor FOUQUERAY
	*
	* La fonction 'afficherSurvivant_son' est prévue pour fonctionner dans le fichier 'projet/test/son.c'.
	* Cette fonction affiche le nombre de son non-détruit, ainsi que le nombre d'objet inclut dans son qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_son();

/**\brief La fonction créant un objet son_t.
	* \author Victor FOUQUERAY
	* \param[in,out] utilite
	* \return un pointeur sur un son_t.
	*
	* La fonction 'creer_son' crée un objet son.
	*
	*/
extern son_t * creer_son(typeSon_t type, char *nomSon);

extern err_t lancer_son(son_t *son,int nbRep);
extern void startPause();
// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
