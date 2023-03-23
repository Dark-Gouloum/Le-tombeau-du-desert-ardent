/**
	* \file test/item.c
	* \brief Test de l'objet item.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Mar. 28 Févr. 2023 14:47:08
	*
	* L'objet item sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/item.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
void aff(item_t *item){
	printf("\tAffichage de l'item :\n");
	if( item ){
		item->afficher( item );
	} else {
		printf("Rien à afficher");
	}
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet item. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	item_t *item = NULL;
	/* Création des autres variables */
	FILE *f = NULL;
	char *nomFSave = ".save.txt";

	// INSTRUCTION(S)
	printf("Création de l'objet item...");
	if(!( item=creer_item("test") )){ // Pas d'objet item de créer :
		MSG_ERR2("Erreur à la création de item.\n");
		status = E_AUTRE;
		goto Quit;
	}
	aff(item);
	printf("OK\n");

	printf("Ajout de modificateur à l'item...");
	if(( status=ajouterModificateur(item,STAT_FORCE,5) )){
		MSG_ERR2("de l'ajout du premier modificateur d'item.\n");
		goto Quit;
	}
	if(( status=ajouterModificateur(item,STAT_INTEL,10) )){
		MSG_ERR2("de l'ajout du deuxième modificateur d'item.\n");
		goto Quit;
	}
	if(( status=ajouterModificateur(item,STAT_CRITIQUE,2) )){
		MSG_ERR2("de l'ajout du troisième modificateur d'item.\n");
		goto Quit;
	}
	aff(item);
	printf("OK\n");

	printf("sauvegarde de l'item...");
	if(!( f=fopen(nomFSave,"w") )){ // Pas d'objet item de créer :
		MSG_ERR(E_AUTRE,"impossible d'ouvrir le fichier de sauvegarde.\n");
		status = E_AUTRE;
		goto Quit;
	}
	if(( status=sauvegarder_item(f,item) )){
		MSG_ERR2("Erreur à la sauvegarde de item.\n");
		goto Quit;
	}
	if( f ){
		fclose(f);
		f = NULL;
	}
	printf("OK\n");

	printf("destruction de l'item...");
	if(( err = item->detruire(&item) )){ // Echec à la destruction :
		printf("Erreur à la destruction de item.\n");
		status = err;
		goto Quit;
	}
	aff(item);
	printf("OK\n");

	printf("chargement de l'item...");
	if(!( f=fopen(nomFSave,"r") )){ // Pas d'objet item de créer :
		MSG_ERR(E_AUTRE,"impossible d'ouvrir le fichier de sauvegarde.\n");
		status = E_AUTRE;
		goto Quit;
	}
	if(( err=charger_item(f,&item) )){ // Pas d'objet item de créer :
		MSG_ERR2("du chargement de l'item.\n");
		status = E_AUTRE;
		goto Quit;
	}
	if( f ){
		fclose(f);
		f = NULL;
	}
	aff(item);
	printf("OK\n");

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( f ){
		fclose(f);
		f = NULL;
	}
	err = item->detruire( &item );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de item.\n");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_item();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet item. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

