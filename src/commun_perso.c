/**
	* \file src/commun_perso.c
	* \brief Définition de l'objet personnage.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Mer. 22 Mars 2023 23:59:23
	*
	* L'objet personnage sert à gérer les personnages du jeu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lib/commun_perso.h"

//STAT MAX  FORCE . AGI . INTELL  : 5 
//STAT MAX PV : 15 
//STAT MAX  ARMURE : 2
//STAT MAX  CRIT : 2


// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
static int lancer_de(int stat, int statMax){
	int rng = rand() % statMax+1;
	if (rng > stat){
		printf("\nRng echoue: %d\n", rng);
		return 0;
	} else {
		printf("\nrng pas echoue : %d\n", rng);
		return 1;
	}
}

static void attribuer_personnage_bis(personnage_t * personnage, int force, int intelligence, int PV, int armure, int critique, int agilite, char * nom){
	if( !personnage ){
		return;
	}
	personnage->force = force;
	personnage->intelligence = intelligence;
	personnage->PV = PV;
	personnage->armure = armure;
	personnage->critique = critique;
	personnage->agilite = agilite;
	if( !(personnage->nom) ){
		free( personnage->nom );
		personnage->nom = NULL;
	}
	if( nom ){
		personnage->nom = (char*)malloc( sizeof(char) * (strlen(nom)+1) );
		strcpy( personnage->nom , nom );
	}
}
extern void attribuer_personnage(void * personnage, int force, int intelligence, int PV, int armure, int critique, int agilite, char * nom){
	attribuer_personnage_bis(personnage,force,intelligence,PV,armure,critique,agilite,nom);
}

static void afficher_personnage_bis( personnage_t *personnage , char *type ){
	if( !personnage ){
		printf("Personnage inexistant.\n");
		return;
	}
	printf("Le %s %s à comme statistique :\n",( (type)?(type):("personnage") ),personnage->nom);
	printf("\t- PV   ------->   %d\n",personnage->PV);
	printf("\t- Force   ---->   %d\n",personnage->force);
	printf("\t- Agilite  ---->  %d\n",personnage->agilite);
	printf("\t- Armure  ----->  %d\n",personnage->armure);
	printf("\t- Critique  --->  %d\n",personnage->critique);
	printf("\t- intelligence -> %d\n",personnage->intelligence);
}
extern void afficher_personnage( void *personnage , char *type ){
	afficher_personnage_bis(personnage,type);
}

static void combat_personnage_bis( personnage_t *att, personnage_t *def ){
	if (lancer_de(def->agilite, 6)){
		printf("L'attaquant a raté son attaque.\n");
	} else {
		int degat = 0;
		if (lancer_de(att->critique, 10)){
			printf("CRITIQUE !\n");
			degat = ((att->force) * 2) - (def->armure);
		} else {
			degat = (att->force) - (def->armure);
		}
		if( degat < 0 ){ degat = 0; }
		def->PV-= degat;
		printf("%s a infligé %i dégats à %s.\n", att->nom, degat, def->nom);
	}
}
extern void combat_personnage( void *attaquant, void *defenseur ){
	combat_personnage_bis( attaquant , defenseur );
}

static int crochetageBis(personnage_t *perso){
	if (lancer_de(perso->agilite, 5)){
		printf("Vous avez Reussi  votre crochetage.\n");
		return 0;
	} else {
		return 1;
	}
}
extern int crochetage(void *perso){
	return crochetageBis(perso);
}
// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

