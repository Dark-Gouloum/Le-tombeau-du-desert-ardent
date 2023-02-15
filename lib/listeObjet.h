#ifndef _LISTEOBJET_H_
#define _LISTEOBJET_H_

/**
	* \file lib/listeObjet.h
	* \brief Définition de l'objet listeObjet.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mer. 15 Févr. 2023 15:17:01
	*
	* L'objet listeObjet sert à stocke de nombreux objet.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "err.h"
#include "objet.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure elemObjet_t.
	* \author Erwan PECHON
	*
	* un element d'une listeObjet_t.
	*
	*/
typedef struct elemObjet_s {
	objet_t *objet; //!< L'objet stocké
	struct elemObjet_s *suivant; //!< L'objet suivant
	struct elemObjet_s *precedent; //!< Le dernier objet
} elemObjet_t;

/** \brief La structure listeObjet_t.
	* \author Erwan PECHON
	*
	* La structure listeObjet_t sert à stocke de nombreux objet.
	*
	*/
typedef struct listeObjet_s {
#include "attributs_objet.h"
	elemObjet_t *drapeau; //!< L'élément hors de la liste.
	elemObjet_t *ec; //!< L'élément actuellement accessible.
} listeObjet_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Erwan PECHON
	*
	* La fonction 'afficherSurvivant_listeObjet' est prévue pour fonctionner dans le fichier 'projet/test/listeObjet.c'.
	* Cette fonction affiche le nombre de listeObjet non-détruit, ainsi que le nombre d'objet inclut dans listeObjet qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_listeObjet();

/**\brief La fonction créant un objet listeObjet_t.
	* \author Erwan PECHON
	* \return un pointeur sur un listeObjet_t.
	*
	* La fonction 'creer_listeObjet' crée un objet listeObjet_t vide.
	*
	*/
extern listeObjet_t * creer_listeObjet();

/**\brief Fonction interrogeant une liste.
	* \author Erwan PECHON
	* \param[in] la liste à tester
	* \return 1 si elle est vide, 0 sinon.
	*
	* La fonction demandant à une liste si elle est vide
	*
	*/
extern int liste_estVide( listeObjet_t *liste );
/**\brief Fonction interrogeant une liste.
	* \author Erwan PECHON
	* \param[in] la liste à tester
	* \return 1 si l'on est dans la liste, 0 sinon.
	*
	* La fonction demandant à une liste si l'on est encore dedans.
	*
	*/
extern int liste_dansListe( listeObjet_t *liste );

/**\brief Fonction de déplacement dans une liste.
	* \author Erwan PECHON
	* \param[in] la liste à bouger
	* \return E_OK en cas de réussite.
	*
	* La fonction déplace l'élément courant sur l'élément suivant.
	*
	*/
extern err_t liste_suivant( listeObjet_t *liste );
/**\brief Fonction de déplacement dans une liste.
	* \author Erwan PECHON
	* \param[in] la liste à bouger
	* \return E_OK en cas de réussite.
	*
	* La fonction déplace l'élément courant sur l'élément precedent.
	*
	*/
extern err_t liste_precedent( listeObjet_t *liste );
/**\brief Fonction de déplacement dans une liste.
	* \author Erwan PECHON
	* \param[in] la liste à bouger
	* \return E_OK en cas de réussite.
	*
	* La fonction déplace l'élément courant sur le premier élément de la liste.
	*
	*/
extern err_t liste_enTete( listeObjet_t *liste );
/**\brief Fonction de déplacement dans une liste.
	* \author Erwan PECHON
	* \param[in] la liste à bouger
	* \return E_OK en cas de réussite.
	*
	* La fonction déplace l'élément courant sur le dernier élément de la liste.
	*
	*/
extern err_t liste_enQueue( listeObjet_t *liste );

/**\brief Fonction de gestion du contenu d'une liste.
	* \author Erwan PECHON
	* \param[in] la liste à modifier
	* \param[in] l'élément à ajouter
	* \return E_OK en cas de réussite.
	*
	* La fonction ajoute le nouvelle élément en fin de liste
	*
	*/
extern err_t liste_ajouteFin( listeObjet_t *liste , objet_t *objet );
/**\brief Fonction de gestion du contenu d'une liste.
	* \author Erwan PECHON
	* \param[in] la liste à modifier
	* \return E_OK en cas de réussite.
	*
	* La fonction supprime l'élément courant et passe à l'élément précédent.
	*
	*/
extern err_t liste_enlever( listeObjet_t *liste );

/**\brief Fonction de gestion du contenu d'une liste.
	* \author Erwan PECHON
	* \param[in] la liste à lire
	* \param[out] l'élément lu
	* \return E_OK en cas de réussite.
	*
	* La fonction ajoute le nouvelle élément en fin de liste
	*
	*/
extern err_t liste_lit( listeObjet_t *liste , objet_t *objet);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
