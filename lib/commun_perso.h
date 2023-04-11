#ifndef _PERSONNAGE_H_
#define _PERSONNAGE_H_

/**
	* \file lib/commun_perso.h
	* \brief Définition de l'objet personnage.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Mer. 22 Mars 2023 23:59:23
	*
	* L'objet personnage sert à gérer les personnages du jeu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "commun_sdl.h"


// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
#define STAT_MAX_PV 30
#define STAT_MAX_ARMURE 5
#define STAT_MAX_CRITIQ STAT_MAX_ARMURE
#define STAT_MAX_FORCE 10
#define STAT_MAX_AGILI STAT_MAX_FORCE
#define STAT_MAX_INTEL STAT_MAX_FORCE

#define EPREUVE_FACILE(max) (max)
#define EPREUVE_MOYEN(max) (max*2)
#define EPREUVE_DIFF(max) (max*3)

#define MIN(a,b) ( (a<b)?(a):(b) )
#define MAX(a,b) ( (a>b)?(a):(b) )
#define STAT_NORM(stat,max) ( MIN(MAX(stat,1),max) )

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
/** \brief La structure personnage_t.
	* \author Dylan GRAMMONT
	*
	* La structure personnage_t sert à gérer les personnages du jeu.
	*
	*/
typedef struct personnage_s {
#include "attributs_perso.h"
} personnage_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
/**	* \brief La fonction qui attribu les stat a unextern void commbat_joueur{

}

extern void combat_ennemi{

}
/**	* \brief La fonction affichant un personnage.
	*  @param in Un pointeur sur le personnage à afficher.
	*  @param in Le type du personnage à afficher (par défaut = "personnage").
	*
	* La fonction affichant un personnage.
	*/
extern void afficher_personnage(void *personnage , char *type );
extern int commbat_joueur(personnage_t *perso, personnage_t *ennemi,SDL_Window *window);
extern void attribuer_personnage(void * personnage, int force, int intelligence, int PV, int armure, int critique, int agilite, char * nom);

extern int combat_personnage( void *attaquant, void *defenseur );

extern int crochetage(void *perso);

extern err_t lis_personnage( void *personnage , char *type, char **msg, int tailleLigne);
// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

#endif
