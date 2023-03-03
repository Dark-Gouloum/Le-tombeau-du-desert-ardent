/**
	* \file src/mechant.c
	* \brief Définition de l'objet mechant.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Ven. 03 Mars 2023 10:21:00
	*
	* L'objet mechant sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/mechant.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_mechant = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet mechant

	// Methode commune à tout les objets
static void afficher_mechant( mechant_t *mechant,char * nom ){
	printf("%s : \n{ PV: %d, \nForce: %d, \nAgilite: %d, \nArmure: %d, \nCritique: %d, \nintelligence: %d}",nom,mechant->PV,mechant->force,mechant->agilite,mechant->Armure,mechant->critique,mechant->intelligence);
}

static err_t detruire_mechant( mechant_t **mechant ){
	// Suppression des attributs de l'objet mechant

	// Suppression de l'objet mechant
	free( (*mechant) );
	(*mechant) = NULL;

	// Destruction de l'objet mechant réussie
	cmpt_mechant--;
	return(E_OK);
}

extern void afficherSurvivant_mechant(){
	printf("Il reste %i mechant_t.\n",cmpt_mechant);
}

extern mechant_t * creer_mechant(){
	// Définission des variables utiles
	char *nomFonction = "creer_mechant : ";

	// Créer l'objet mechant
	mechant_t *mechant = malloc( sizeof(mechant_t) );
	if( !mechant ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (mechant_t*)NULL;
	}

	// Affecter les attributs
	mechant->PV = mechant->force = mechant->agilite = mechant->Armure = mechant->critique = mechant->intelligence = 0;
	mechant->nom = "méchant";
	// Affecter les methodes
	mechant->detruire = (err_t (*)(void *))detruire_mechant;
	mechant->afficher = (void (*)(void *))afficher_mechant;

	// Renvoyer le bouton
	cmpt_mechant++;
	return mechant;
}

extern void attribuer_mechant(mechant_t * mechant, int force, int intelligence, int PV, int Armure, int critique, int agilite, char * nom){
	mechant->PV = PV;
	mechant->force = force;
	mechant->agilite = agilite;
	mechant->Armure = Armure;
	mechant->critique = critique;
	mechant->intelligence = intelligence;
	mechant->nom = nom;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

