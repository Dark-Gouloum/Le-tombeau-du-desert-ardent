/**
	* \file src/action.c
	* \brief Définition de l'objet action.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Ven. 03 Mars 2023 11:52:38
	*
	* L'objet action sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/action.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
// Fonctions spéciale d'un objet action

// Methode commune à tout les objets
extern void joueur_attaque(joueur_t *perso, PNJ_t *mechant){
	if (lancer_de(mechant->agilite, 6)){
		printf("Vous avez raté votre attaque.\n");
	} else {
		if (lancer_de(mechant->critique, 10)){
			printf("CRITIQUE !\n");
			perso->PV -= (mechant->force * 2) - perso->armure;
			printf("%s vous a infligé %i dégats.\n", mechant->nom, (mechant->force * 2) - perso->armure);
		} else {
			perso->PV -= mechant->force - perso->armure;
			printf("Le mechant vous a infligé %i dégats.\n", mechant->force - perso->armure);
		}
	}
}

extern void mechant_attaque(joueur_t *perso, PNJ_t *mechant){
	if (lancer_de(perso->agilite, 6)){
		printf("Le mechant a raté son attaque.\n");
	} else {
		if (lancer_de(mechant->critique, 10)){
			printf("CRITIQUE !\n");
			perso->PV -= (mechant->force * 2) - perso->armure;
			printf("%s vous a infligé %i dégats.\n", mechant->nom, (mechant->force * 2) - perso->armure);
		} else {
			perso->PV -= mechant->force - perso->armure;
			printf("Le mechant vous a infligé %i dégats.\n", mechant->force - perso->armure);
		}
	}
}

extern int crochetage(joueur_t *perso){
	if (lancer_de(perso->agilite, 6)){
		printf("Vous avez raté votre crochetage.\n");
		return 0;
	} else {
		return 1;
	}
}

extern int lancer_de(int stat, int statMax){
	int rng = rand() % statMax;
	if (rng > stat){
		return 0;
	} else {
		return 1;
	}
}
// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //
