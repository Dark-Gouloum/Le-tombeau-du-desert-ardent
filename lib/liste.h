#ifndef _LISTE_H
#define _LISTE_H

/**
	* \file lib/liste.h
	* \brief Définition de l'objet liste.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mer. 15 Févr. 2023 15:17:01
	*
	* L'objet liste sert à stocke des pointeurs sur des objets.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "err.h"
#include "objet.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure liste_t.
	* \author Erwan PECHON
	*
	* La structure liste_t sert à stocke des pointeurs sur des objets.
	*
	*/
typedef struct liste_s {
#include "attributs_objet.h"
	int nb; //!< Le nombre d'element dans la liste
	void **liste; //!< La liste de pointeur
} liste_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Erwan PECHON
	*
	* La fonction 'afficherSurvivant_liste' est prévue pour fonctionner dans le fichier 'projet/test/liste.c'.
	* Cette fonction affiche le nombre de liste non-détruit, ainsi que le nombre d'objet inclut dans liste qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_liste();

/**\brief La fonction créant un objet liste_t.
	* \author Erwan PECHON
	* \param[in] la fonction de destruction des éléments de la liste.
	* \return un pointeur sur un liste_t.
	*
	* La fonction 'creer_liste' crée un objet liste_t vide.
	*
	*/
extern liste_t * creer_liste();

/**\brief Fonction interrogeant une liste.
	* \author Erwan PECHON
	* \param[in] la liste à tester
	* \return 1 si elle est vide, 0 sinon.
	*
	* La fonction demandant combien d'élément à une liste.
	*
	*/
extern int liste_taille( liste_t *liste );

/**\brief Fonction de gestion du contenu d'une liste.
	* \author Erwan PECHON
	* \param[in] la liste à modifier
	* \param[in] l'élément à ajouter
	* \return E_OK en cas de réussite.
	*
	* La fonction ajoute le nouvelle élément en fin de liste
	*
	*/
extern err_t liste_ajoute( liste_t *liste , void *objet );
/**\brief Fonction de gestion du contenu d'une liste.
	* \author Erwan PECHON
	* \param[in] la liste à modifier
	* \param[in] l'emplacement de l'objet demandé (0 <= pos < liste->nb)
	* \return E_OK en cas de réussite.
	*
	* La fonction supprime l'élément courant et passe à l'élément précédent.
	*
	*/
extern err_t liste_enlever( liste_t *liste, int pos );

/**\brief Fonction de gestion du contenu d'une liste.
	* \author Erwan PECHON
	* \param[in] la liste à lire
	* \param[in] l'emplacement de l'objet demandé (0 <= pos < liste->nb)
	* \param[out] l'élément lu
	* \return E_OK en cas de réussite.
	*
	* La fonction ajoute le nouvelle élément en fin de liste
	*
	*/
extern err_t liste_lit( liste_t *liste , int pos , void **objet);
/**\brief Fonction de gestion du contenu d'une liste.
	* \author Erwan PECHON
	* \param[in] la liste à afficher
	*
	* La fonction affiche l'entiereté d'une liste
	*
	*/
extern void afficher_liste( liste_t *liste , void (*afficher)(void*) );

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
