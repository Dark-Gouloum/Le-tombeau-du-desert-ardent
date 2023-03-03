/**
	* \file test/mechant.c
	* \brief Test de l'objet mechant.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Ven. 03 Mars 2023 10:21:00
	*
	* L'objet mechant sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/mechant.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet mechant. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	mechant_t *mechant = NULL;

	/* Création des autres variables */
	// INSTRUCTION(S)
	printf("Création de l'objet mechant...");
	if(!( mechant=creer_mechant() )){ // Pas d'objet mechant de créer :
		printf("Erreur à la création de mechant.\n");
		status = E_AUTRE;
		goto Quit;
	}
	mechant->afficher( mechant );
	attribuer_mechant(mechant,2,3,4,6,7,5,"Benard de la ville aride");
	mechant->afficher( mechant );

	printf("OK\n");
	status = E_OK;

	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	err = mechant->detruire( &mechant );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de mechant.\n");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_mechant();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet mechant. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

