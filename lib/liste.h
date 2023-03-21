#ifndef _LISTE_H_
#define _LISTE_H_

/**
	* \file lib/liste.h
	* \brief Définition de l'objet liste.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 20 Mars 2023 16:47:26
	*
	* L'objet liste sert à stocké des objets..
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun.h"
#include "objet.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure liste_t.
	* \author Erwan PECHON
	*
	* La structure liste_t sert à stocké des objets..
	*
	*/
typedef struct liste_s {
#include "attributs_objet.h"
	int nb; //!< Le nombre d'element dans la liste
	void **liste; //!< La liste de pointeur
} liste_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/*	Gestion des listes	*/
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
	* \param[in,out] utilite
	* \return un pointeur sur un liste_t.
	*
	* La fonction 'creer_liste' crée un objet liste.
	*
	*/
extern liste_t * creer_liste();

/*	tests sur les listes	*/
/**\brief Fonction interrogeant une liste.
	* \author Erwan PECHON
	* \param[in] la liste à tester
	* \return 0 si elle est vide, sinon, renvoit le nombre d'élément qu'elle contient.
	*
	* La fonction demandant combien d'élément à une liste.
	*
	*/
extern int liste_taille( liste_t *liste );

/*	Gestion du contenu d'une liste	*/
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
	* La fonction supprime l'élément indiqué.
	*
	*/
extern err_t liste_enlever_pos( liste_t *liste, int pos );
/**\brief Fonction de gestion du contenu d'une liste.
	* \author Erwan PECHON
	* \param[in] la liste à modifier
	* \param[in] un pointeur sur l'objet à supprimer
	* \param[in] un pointeur sur la fonction de comparaison de l'objet (0=>objet identique)
	* \return E_OK en cas de réussite.
	*
	* La fonction supprime l'élément indiqué.
	*
	*/
extern err_t liste_enlever_obj( liste_t *liste, void * obj );

/*	Utilisation du contenu d'une liste	*/
/**\brief Fonction de demande d'un élément d'une liste.
	* \author Erwan PECHON
	* \param[out] E_OK en cas de réussite, sinon, le code erreur
	* \param[in] la liste à lire
	* \param[in] l'emplacement de l'objet demandé (0 <= pos < liste->nb)
	* \return La position où se trouve l'objet recherché.
	*
	* La fonction recherche la position de l'élément demandé dans la liste.
	*
	*/
extern int liste_recherche_pos( err_t *err , liste_t *liste , void *obj );
/**\brief Fonction de demande d'un élément d'une liste.
	* \author Erwan PECHON
	* \param[out] E_OK en cas de réussite, sinon, le code erreur
	* \param[in] la liste à lire
	* \param[in] un pointeur sur l'objet à cherché dans la liste
	* \return Un pointeur sur l'objet à la position demandé.
	*
	* La fonction recherche l'élément demandé dans la liste.
	*
	*/
extern void * liste_recherche_obj( err_t *err , liste_t *liste , int pos );

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
