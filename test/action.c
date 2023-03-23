/**
	* \file test/action.c
	* \brief Test de l'objet action.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Ven. 03 Mars 2023 11:52:38
	*
	* L'objet action sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/action.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
#define NB_TESTS 10

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet action. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création des autres variables */
	joueur_t *joueur = NULL;
	PNJ_t *PNJ = NULL;

	// INSTRUCTION(S)
	printf("Création de l'objet joueur...");
	if(!( joueur=creer_joueur() )){ // Pas d'objet joueur de créer :
		MSG_ERR2("À la création de joueur");
		status = E_AUTRE;
		goto Quit;
	}
	attribuer_personnage(joueur,10,20,30,40,50,60,"moi");
	printf("Ajout d'item au joueur...");
	{
		item_t *item = NULL;
		if(!( item=creer_item("Force") )){ // Pas d'objet item de créer :
			MSG_ERR2("Erreur à la création de item.\n");
			status = E_AUTRE;
			goto Quit;
		}
		if(( status=ajouterModificateur(item,STAT_FORCE,5) )){
			MSG_ERR2("de l'ajout du premier modificateur d'item.\n");
			goto Quit;
		}
		if(( status=ajouterItem(joueur,item) )){
			MSG_ERR2("de l'ajout du premier item au joueur.\n");
			goto Quit;
		}
		item = NULL;
	}
	joueur->afficher( joueur );
	printf("OK\n");

	printf("Création de l'objet PNJ...");
	if(!( PNJ=creer_PNJ() )){ // Pas d'objet PNJ de créer :
		MSG_ERR2("À la création de PNJ");
		status = E_AUTRE;
		goto Quit;
	}
	attribuer_personnage(PNJ,2,3,4,6,7,5,"Benard de la ville aride");
	PNJ->afficher( PNJ );
	printf("OK\n");

	printf("Début des %i tests des actions...\n",NB_TESTS);
	for( int i=0 ; i<NB_TESTS ; i++ ){
		printf("\t- tour n°%d :\n",i+1);
		joueur_attaque(joueur,PNJ);
		mechant_attaque(joueur,PNJ);
		crochetage(joueur);
	}
	printf("\nFin des tests.\n");

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if(( err=joueur->detruire(&joueur) )){
		MSG_ERR2("de la destruction du joueur");
		return(err);
	}
	if(( err=PNJ->detruire(&PNJ) )){
		MSG_ERR2("de la destruction du Personnage Non Joueur");
		return(err);
	}
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet action. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

