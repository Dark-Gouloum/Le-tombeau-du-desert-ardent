#ifndef _POLICE_H_
#define _POLICE_H_

/**
	* \file lib/police.h
	* \brief Définition de l'objet police.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 02:18:02
	*
	* L'objet police sert à gére les polices d'écritures du projets.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun_sdl.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure police_t.
	* \author Erwan PECHON
	*
	* La structure police_t sert à gére les polices d'écritures du projets.
	*
	*/
typedef struct police_s {
#include "attributs_objet.h"
	TTF_Font *font; //!< La police d'écriture utilisé.
	SDL_Color couleur;
} police_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Erwan PECHON
	*
	* La fonction 'afficherSurvivant_police' est prévue pour fonctionner dans le fichier 'projet/test/police.c'.
	* Cette fonction affiche le nombre de police non-détruit, ainsi que le nombre d'objet inclut dans police qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_police();

/**\brief La fonction créant un objet police_t.
	* \author Erwan PECHON
	* \param[in,out] utilite
	* \return un pointeur sur un police_t.
	*
	* La fonction 'creer_police' crée un objet police.
	*
	*/
extern police_t * creer_police(char *nomFont, int taille, SDL_Color *couleur);

/** \brief La fonction transformant un texte en image, en utilisant une police d'écriture.
	* \author Dylan GRAMMONT
	* \param[out] La surface du texte à coller dans la fenêtre
	* \param[in] La police d'écriture
	* \param[in] Le texte à écrire
	* \param[in] La limite hoorizontale d'affichage du texte, 0 si infinie
	* \return Renvoit E_OK en cas de réussite
	*
	*
	*/
extern err_t police_creerSurface_texte( SDL_Surface **surface , police_t *police , char *texte , Uint32 limLargeur );
extern err_t police_changerCouleur( police_t *police , SDL_Color c );

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
