#ifndef _ERR_H_
#define _ERR_H_

/**
	* \file lib/err.h
	* \brief Définition de l'enumeration err.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 00:49:37
	*
	* L'enumeration err sert à gérer les codes erreurs.
	*
	*/
// CRÉATION(S) DE(S) CONSTANTE(S)
#define MSG_E "ERREUR : "

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)
/** \brief L'enumeration err_t.
	*
	* L'enumeration err_t sert à gérer les codes erreurs.
	*
	*/
typedef enum err_s {
	E_OK = 0, //!< La fonction à réussi.
	E_MEMOIRE, //!< La fonction à échouer à cause d'un manque d'espace mémoire.
	E_ARGUMENT, //!< Mauvais arguments passé en paramètre.
	E_COLOR, //!< Erreur lors d'un changement de couleur.
	E_AFFICHE, //!< Erreur lors d'un affichage.
	E_OBTENIR, //!< Erreur lors d'une demande de donnée
	E_AUTRE //!< La fonction à échouer pour une erreur inconnu.
} err_t;

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
