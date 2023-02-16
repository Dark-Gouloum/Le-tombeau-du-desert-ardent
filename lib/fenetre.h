#ifndef _FENETRE_H_
#define _FENETRE_H_

/**
	* \file lib/fenetre.h
	* \brief Définition de l'objet fenetre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mer. 15 Févr. 2023 14:30:07
	*
	* L'objet fenetre sert à crée et gére une fenêtre.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>

#include "err.h"
#include "liste.h"
#include "bouton.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
#define SDL_TTF 1<<0
#define SDL_IMAGE 1<<1

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)
/** \brief L'enumeration clique_t.
	* \author Erwan PECHON
	*
	* L'enumeration clique_t sert à savoir qu'elle bouton de la souris à était cliqué.
	*
	*/
typedef enum clique_s {
	CLIQUE_Erreur = 0, //!< Bouton inconnnu
	CLIQUE_Gauche, //!< Bouton gauche
	CLIQUE_Mollette, //!< Bouton centrale
	CLIQUE_Droit //!< Bouton droit
} clique_t;


// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure fenetre_t.
	* \author Erwan PECHON
	*
	* La structure fenetre_t sert à crée et gére une fenêtre.
	*
	*/
typedef struct fenetre_s {
#include "attributs_fenetre.h"
	liste_t *lstBoutons; //!< la liste des boutons de la fenêtre
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
extern fenetre_t * creer_fenetre(SDL_Point dim, Uint32 flags, char *titre);

/** \brief La fonction initialisant la bibliothéque SDL.
	* \author Erwan PÉCHON
	* \param[in] La liste des bibliothèque à initialiser, en plus de la SDL.
	* \return En cas de problème, renvoit E_INIT, Sinon, renvoit 0.
	*
	* La fonction 'initialisation_SDL' initialise la bibliothéque SDL et ses sous-bibliothéque.
	* Cette fonction doit être au tout début de la fonction 'main' de chaque programme utilisant la bibiothéque SDL.
	*
	*/
extern err_t initialisation_SDL(Uint32 choix);
/** \brief La fonction initialisant la bibliothéque SDL_TTF.
	* \author Erwan PÉCHON
	*
	* La fonction 'fermer_SDL' ferme la bibliothéque SDL et ses sous-bibliothéque, qui ont était initialisé.
	* Cette fonction doit être à la fin de la fonction 'main' de chaque programme utilisant la bibiothéque SDL.
	*
	*/
extern void fermer_SDL();

/**\brief La fonction ajoutant un bouton à la fenetre_t.
	* \author Erwan PECHON
	* \param[in] Le bouton à ajouter
	* \return E_OK si tout c'est bien passé.
	*
	* La fonction ajoutant un bouton à la fenetre_t.
	*
	*/
extern err_t ajouterBouton(fenetre_t *fenetre , bouton_t *bouton);
/**\brief La fonction changeant la couleur du pinceau utilisé pour une fenetre_t.
	* \author Erwan PECHON
	* \param[in] La fenetre_t à modifier
	* \param[in] La couleur de la fenetre
	* \return E_OK si tout c'est bien passé.
	*
	* La fonction ajoutant un bouton à la fenetre_t.
	*
	*/
extern err_t changerCouleur( fenetre_t *f , SDL_Color *c );
/**\brief La fonction changeant l'arriere-plan d'une fenetre_t par une couleur uni.
	* \author Erwan PECHON
	* \param[in] La fenetre_t à modifier
	* \param[in] La couleur de la fenetre
	* \return E_OK si tout c'est bien passé.
	*
	* La fonction ajoutant un bouton à la fenetre_t.
	*
	*/
extern err_t changerFond_couleur( fenetre_t *f , SDL_Color *c );

/**\brief renvoit le renderer de la fenetre
	* \author Erwan PECHON
	* \param[in] La fenetre_t dont on veut le renderer.
	* \return un pointeur sur le renderer de la fenetre_t.
	*
	* La fonction ajoutant un bouton à la fenetre_t.
	*
	*/
extern SDL_Renderer *obtenir_Renderer( fenetre_t *f );
/**\brief obtient les coordonée (x,y) du curseur.
	* \author Erwan PECHON
	* \param[out] un pointeur sur la variable représentant les coordonnée du pointeur
	* \return un entier représentant qu'elle clique de la souris à était utilisé.
	*
	* La fonction ajoutant un bouton à la fenetre_t.
	*
	*/
extern clique_t obtenir_souris( SDL_Point *point);
/**\brief obtient un pointeur sur le bouton qui c'est fait cliquer.
	* \author Erwan PECHON
	* \param[in] un pointeur sur la fenetre_t qui c'est fait cliqué dessus.
	* \param[in] un pointeur sur la variable représentant les coordonnée du pointeur
	* \return un pointeur sur NULL si aucun bouton de la fenêtre ne c'est fait cliqué. Ou, un pointeur sur le bouton qui c'est fait cliqué dessus.
	*
	* La fonction ajoutant un bouton à la fenetre_t.
	*
	*/
extern bouton_t *obtenir_boutonCliquer( fenetre_t *f, SDL_Point *point );

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
