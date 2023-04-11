/**
	* \file test/epreuve.c
	* \brief Test de l'objet epreuve.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 11 Avril 2023 13:38:08
	*
	* L'objet epreuve sert à tester les compétence du joueur.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/epreuve.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet epreuve. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
		/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
		/* Création d'un pointeur sur l'objet à tester */
	epreuve_t *epreuve = NULL;
		/* Création des autres variables */

	// INSTRUCTION(S)
	printf("Création de l'objet epreuve...");
	if(!( epreuve=creer_epreuve() )){ // Pas d'objet epreuve de créer :
		MSG_ERR2("À la création de epreuve");
		status = E_AUTRE;
		goto Quit;
	}
	epreuve->afficher( epreuve );
	printf("OK\n");
	status = E_OK;

	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=epreuve->detruire(&epreuve)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de epreuve");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_epreuve();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet epreuve. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

