#ifndef _LIVRE_H_
#define _LIVRE_H_

/**
	* \file lib/livre.h
	* \brief Définition de l'objet livre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 03 Avril 2023 20:43:50
	*
	* L'objet livre sert à afficher du texte dans un livre donnée.
	* Il garde en mémoire jusqu'où le texte à était écrit.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun.h"
#include "fenetre.h"
#include "liste.h"
#include "police.h"
#include "joueur.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure livre_t.
	* \author Erwan PECHON
	*
	* La structure livre_t sert à afficher du texte dans un livre donnée.
	*
	*/
typedef struct livre_s {
#include "attributs_objet.h"
	liste_t *lstPage; //!< La liste des images de chaque pages ayant était affiché
	int i; //!< La liste de la page actuellement affiché+1 , 0 si aucune page
	int avance; //!< État de l'avancé du fichier

	SDL_Point pos; //!< Le point en bas à droite de la derniere ligne ajouté dans l'image
	SDL_Texture *page; //!< La zone d'affichage de base du livree
	SDL_Rect zoneAff[2]; // Les deux zones d'affichage des pages

	bouton_t *prec; //!< Le bouton remontant le texte
	bouton_t *suiv; //!< Le bouton défilant le texte
	bouton_t *stat; //!< Le bouton qui affiche les stats du joueur
	bouton_t *inve; //!< Le bouton qui affiche l'inventaire du joueur
	bouton_t *stop; //!< Le bouton qui arrête le jeu

	joueur_t *joueur; //!< Le joueur qui lit le livre
	FILE *fichier; //!< Le fichier où lire le texte
	int nbChap; //!< Le nombre de chapitre parcourut
	char **lstChap; //!< La liste des chapitre parcourut
	police_t *police; //!< la police d'écriture du texte
	fenetre_t *fenetre; //!< La fenetre mére
} livre_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Erwan PECHON
	*
	* La fonction 'afficherSurvivant_livre' est prévue pour fonctionner dans le fichier 'projet/test/livre.c'.
	* Cette fonction affiche le nombre de livre non-détruit, ainsi que le nombre d'objet inclut dans livre qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_livre();

/**\brief La fonction créant un objet livre_t.
	* \author Erwan PECHON
	* \param[in,out] utilite
	* \return un pointeur sur un livre_t.
	*
	* La fonction 'creer_livre' crée un objet livre.
	*
	*/
extern livre_t * creer_livre(Uint32 flags, char *titreF, char *fondF, SDL_Color *fondB, police_t **police,joueur_t *joueur);
extern err_t nouveauChapitre(livre_t *livre, char *nomChap);
extern err_t livre_cliquer(livre_t *livre,int *stop);
extern err_t livre_rafraichir(livre_t *livre);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
