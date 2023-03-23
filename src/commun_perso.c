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

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
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

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

