/**
	* \file test/joueur.c
	* \brief Test de l'objet joueur.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Jeu. 23 Mars 2023 00:31:27
	*
	* L'objet joueur sert à gére le joueur (c'est le personnage principal.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/joueur.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
void aff(joueur_t *joueur){
	printf("\tAffichage du joueur :\n");
	if( joueur ){
		joueur->afficher( joueur );
	} else {
		printf("Rien à afficher");
	}
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet joueur. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
		/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
		/* Création d'un pointeur sur l'objet à tester */
	joueur_t *joueur = NULL;
		/* Création des autres variables */

	// INSTRUCTION(S)
	printf("Création de l'objet joueur...");
	if(!( joueur=creer_joueur() )){ // Pas d'objet joueur de créer :
		MSG_ERR2("À la création de joueur");
		status = E_AUTRE;
		goto Quit;
	}
	attribuer_personnage(joueur,10,20,30,40,50,60,"moi");
	aff( joueur );
	printf("OK\n");

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
	{
		item_t *item = NULL;
		if(!( item=creer_item("Int") )){ // Pas d'objet item de créer :
			MSG_ERR2("Erreur à la création de item.\n");
			status = E_AUTRE;
			goto Quit;
		}
		if(( status=ajouterModificateur(item,STAT_INTEL,10) )){
			MSG_ERR2("de l'ajout du deuxième modificateur d'item.\n");
			goto Quit;
		}
		if(( status=ajouterItem(joueur,item) )){
			MSG_ERR2("de l'ajout du deuxième item au joueur.\n");
			goto Quit;
		}
		item = NULL;
	}
	{
		item_t *item = NULL;
		if(!( item=creer_item("crit") )){ // Pas d'objet item de créer :
			MSG_ERR2("Erreur à la création de item.\n");
			status = E_AUTRE;
			goto Quit;
		}
		if(( status=ajouterModificateur(item,STAT_CRITIQUE,2) )){
			MSG_ERR2("de l'ajout du troisième modificateur d'item.\n");
			goto Quit;
		}
		if(( status=ajouterItem(joueur,item) )){
			MSG_ERR2("de l'ajout du deuxième item au joueur.\n");
			goto Quit;
		}
		item = NULL;
	}
	aff( joueur );
	printf("OK\n");

	printf("Sauvegarde de l'objet joueur...");
	if(( status=sauvegarder_joueur(joueur,5) )){
		MSG_ERR2("de la sauvegarde du joueur");
		goto Quit;
	}
	printf("OK\n");

	printf("Retrait d'item au joueur...");
	if(( status=supprimerItem_pos(joueur,1) )){
		MSG_ERR2("de la suppression d'un item du joueur");
		goto Quit;
	}
	aff( joueur );
	printf("OK\n");

	printf("Suppression de l'objet joueur...");
	if( (err=joueur->detruire(&joueur)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de joueur");
		return(err);
	}
	aff( joueur );
	printf("OK\n");

	printf("chargement de l'objet joueur...");
	if(( status=charger_joueur(&joueur) )){ // Pas d'objet joueur de créer :
		MSG_ERR2("Au chargement du joueur");
		status = E_AUTRE;
		goto Quit;
	}
	aff( joueur );
	printf("OK\n");

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=joueur->detruire(&joueur)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de joueur");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_joueur();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet joueur. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

