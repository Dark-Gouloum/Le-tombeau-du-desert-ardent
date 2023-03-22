#ifndef _COMMUN_H_
#define _COMMUN_H_

/**
	* \file lib/commun.h
	* \brief Définition des donnée commune à tous les fichiers.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 00:49:37
	*
	* Définition des donnée commune à tous les fichiers :
	*	+ L'inclusion de librairies commune :
	*		- stdio
	*	+ La gestion des erreurs.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>
#include <assert.h>

// CRÉATION(S) DE(S) CONSTANTE(S) BASIQUE(S)
#define MSG_ERR_BASE(pre,message1,message2) fprintf(stderr, "%sERREUR : %s(%s:%d) : %s%s.\n", pre, __func__,__FILE__,__LINE__, message1,message2);
#define MSG_ERR(codeErr,message) MSG_ERR_BASE("",analyse_err(codeErr),message);
#define MSG_ERR2(message) MSG_ERR_BASE("\t","Une erreur est survenu lors ",message);
#define MSG_ERR_COMP(message1,message2) fprintf(stderr, "\t--->%s : %s\n", message1,message2);

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)
/** \brief L'enumeration err_t.
	*
	* L'enumeration err_t sert à gérer les codes erreurs.
	*
	*/
typedef enum err_s {
	E_OK = 0,  	//!< La fonction à réussi.
	E_INIT,    	//!< Erreur lors de initialisation d'une librairie
	E_MEMOIRE, 	//!< La fonction à échouer à cause d'un manque d'espace mémoire.
	E_ARGUMENT,	//!< Mauvais arguments passé en paramètre.
	E_OBTENIR, 	//!< Erreur lors d'une demande de donnée
	E_COLOR,   	//!< Erreur lors d'un changement de couleur.
	E_SON,   	//!< Erreur lors de la gestion du son.
	E_AFFICHE, 	//!< Erreur lors d'un affichage.
	E_AUTRE    	//!< La fonction à échouer pour une erreur inconnu.
} err_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
extern char * analyse_err( err_t err );

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
