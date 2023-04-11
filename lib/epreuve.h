#ifndef _EPREUVE_H_
#define _EPREUVE_H_

/**
	* \file lib/epreuve.h
	* \brief Définition de l'objet epreuve.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 11 Avril 2023 13:38:08
	*
	* L'objet epreuve sert à tester les compétence du joueur.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun.h"
#include "livre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
extern int epreuve_type(livre_t *livre,char *ligne,int *reussi);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
