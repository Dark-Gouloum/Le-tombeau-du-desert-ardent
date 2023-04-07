#ifndef _QSTREP_H_
#define _QSTREP_H_

/**
	* \file lib/QstRep.h
	* \brief Définition de l'objet QstRep.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 06 Avril 2023 07:47:37
	*
	* L'objet QstRep sert à proposer des choix à l'utilisateur.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun.h"
#include "menu.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**\brief La fonction affichant le nombre d'objet non détruit.
	* \author Erwan PECHON
	*
	* La fonction 'afficherSurvivant_QstRep' est prévue pour fonctionner dans le fichier 'projet/test/QstRep.c'.
	* Cette fonction affiche le nombre de QstRep non-détruit, ainsi que le nombre d'objet inclut dans QstRep qui n'ont pas était détruit.
	*
	*/
extern void afficherSurvivant_QstRep();

/**\brief La fonction créant un objet QstRep_t.
	* \author Erwan PECHON
	* \param[in,out] utilite
	* \return un pointeur sur un QstRep_t.
	*
	* La fonction 'creer_QstRep' crée un objet QstRep.
	*
	*/
extern err_t lancer_QstRep(Uint32 flags,SDL_Color *cPolice,char *ligne,fenetre_t *fMere,char *lstCodeAction, char *r_codeAction, char **r_action);

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
