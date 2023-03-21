#ifndef _FENETRE_H_
#define _FENETRE_H_

/**
	* \file lib/fenetre.h
	* \brief Définition de l'objet fenetre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 12:25:01
	*
	* L'objet fenetre sert à gérer une fenêtre de base.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun_sdl.h"
#include "liste.h"
#include "bouton.h"
#include "img.h"
#include "police.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure fenetre_t.
	* \author Erwan PECHON
	*
	* La structure fenetre_t sert à gérer une fenêtre de base.
	*
	*/
typedef struct fenetre_s {
#include "attributs_objet.h"
	SDL_Window *fenetre; //!< La fenêtre
	SDL_Renderer *rendu; //!< Le renderer de la fenetre
	SDL_Color *fond; //! L'arrière plan de la fenêtre.
	liste_t *lstBoutons; //!< la liste des boutons de la fenêtre
	liste_t *lstWidgets; //!< la liste des autres widgets de la fenêtre
} fenetre_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Erwan PECHON
	*
	* La fonction 'afficherSurvivant_fenetre' est prévue pour fonctionner dans le fichier 'projet/test/fenetre.c'.
	* Cette fonction affiche le nombre de fenetre non-détruit, ainsi que le nombre d'objet inclut dans fenetre qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_fenetre();

/**\brief La fonction créant un objet fenetre_t.
	* \author Erwan PECHON
	* \param[in] les coordonnée (x,y) du coin en bas à droite de la fenêtre
	* \param[in] Les drapeaux de l'activation d'une fenêtre. Voir la doc SDL2 pour plus d'informations.
	* \param[in] Le titre de la fenêtre.
	* \return un pointeur sur un fenetre_t.
	*
	* La fonction 'creer_fenetre' crée un objet fenetre.
	*
	*/
extern fenetre_t * creer_fenetre(SDL_Point *dim, Uint32 flags, char *titre);

/**\brief La fonction ajoutant un bouton à la fenetre_t.
	* \author Erwan PECHON
	* \param[in] Un pointeur sur la fenetre à modifier.
	* \param[in] Un pointeur sur le stylo du bouton.
	* \param[in] Le texte du bouton.
	* \param[in] Comment ancrer le bouton à la fenêtre.
	* \param[in] L'action qui doit-être éxécuter lorsque le bouton est cliqué.
	* \return E_OK si tout c'est bien passé.
	*
	* La fonction ajoutant un bouton à la fenetre_t.
	*
	*/
extern err_t ajouterBouton(fenetre_t *fen, void *widget, err_t (*action)(int argc,...) );
/**\brief La fonction ajoutant un widget à la fenetre_t.
	* \author Erwan PECHON
	* \param[in] Un pointeur sur la fenetre à modifier.
	* \param[in] Un pointeur sur le widget à ajouter.
	* \return E_OK si tout c'est bien passé.
	*
	* La fonction ajoutant un widget à la fenetre_t.
	*
	*/
extern err_t ajouterWidget(fenetre_t *fen, void* widget );

/**\brief La fonction changeant l'arriere-plan d'une fenetre_t par une couleur uni.
	* \author Erwan PECHON
	* \param[in] La fenetre_t à modifier
	* \param[in] La couleur de la fenetre
	* \return E_OK si tout c'est bien passé.
	*
	* La fonction ajoutant un bouton à la fenetre_t.
	*
	*/
extern err_t changerFond( fenetre_t *f , SDL_Color *c );
/**\brief La fonction changeant l'arriere-plan d'une fenetre_t par une couleur uni.
	* \author Erwan PECHON
	* \param[in] La fenetre_t à modifier
	* \param[in] La couleur de la fenetre
	* \return E_OK si tout c'est bien passé.
	*
	* La fonction ajoutant un bouton à la fenetre_t.
	*
	*/
extern err_t clean( fenetre_t *f );
/**\brief La fonction rafraichit la fenêtre
	* \author Erwan PECHON
	* \param[in] La fenetre_t à rafraichir
	* \return E_OK si tout c'est bien passé.
	*
	* La fonction redessine tout le contenu de la fenêtre.
	*
	*/
extern err_t rafraichir( fenetre_t *fenetre );

/**\brief renvoit le renderer de la fenetre
	* \author Erwan PECHON
	* \param[in] La fenetre_t dont on veut le renderer.
	* \return un pointeur sur le renderer de la fenetre_t.
	*
	* La fonction ajoutant un bouton à la fenetre_t.
	*
	*/
extern SDL_Renderer *obtenir_Renderer( fenetre_t *f );
/**\brief obtient un pointeur sur le bouton qui c'est fait cliquer.
	* \author Erwan PECHON
	* \param[in] un pointeur sur la fenetre_t qui c'est fait cliqué dessus.
	* \param[in] un pointeur sur la variable représentant les coordonnée du pointeur
	* \return un pointeur sur NULL si aucun bouton de la fenêtre ne c'est fait cliqué. Ou, un pointeur sur le bouton qui c'est fait cliqué dessus.
	*
	* La fonction ajoutant un bouton à la fenetre_t.
	*
	*/
extern bouton_t *obtenir_boutonCliquer( fenetre_t *f , SDL_Point *curseur );

extern err_t creer_texte(fenetre_t *f, police_t *p, char *texte,SDL_Point *pos , img_t **img);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
