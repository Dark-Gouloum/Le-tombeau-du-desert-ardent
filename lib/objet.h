#ifndef _OBJET_H_
#define _OBJET_H_

/**
	* \file lib/objet.h
	* \brief Définition de l'objet objet.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 20 Mars 2023 16:47:26
	*
	* L'objet objet sert à remplacer la plupart des objets.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure objet_t.
	* \author Erwan PECHON
	*
	* L'objet objet sert à remplacer la plupart des objets.
	*
	*/
typedef struct objet_s {
#include "attributs_objet.h"
} objet_t;

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
