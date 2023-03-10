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

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet item. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	item_t *item = NULL;

	/* Création des autres variables */
	// INSTRUCTION(S)
	printf("Création de l'objet item...");
	if(!( item=creer_item() )){ // Pas d'objet item de créer :
		printf("Erreur à la création de item.\n");
		status = E_AUTRE;
		goto Quit;
	}
	item->afficher( item );
	printf("OK");
	status = E_OK;

	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
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

