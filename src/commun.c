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
#include "../lib/commun.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
extern char * analyse_err( err_t err ){
	switch( err ){
		case E_OK :	return "Tout c'est bien passé.";
		case E_INIT :	return "Erreur lors d'une initialisation de ";
		case E_MEMOIRE :	return "Débordement mémoire : ";
		case E_ARGUMENT :	return "Un argument est non-valide : ";
		case E_OBTENIR :	return "La donné n'est pas initialisé : ";
		case E_COLOR :	return "Les pinceaux se sont mélangé.";
		case E_AFFICHE :	return "Erreur à l'affichage.";
		case E_AUTRE :	return "Erreur sans précision.";
		default :	return "Code erreur inconnu, veuillez l'ajouter.";
	}
	return "";
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

