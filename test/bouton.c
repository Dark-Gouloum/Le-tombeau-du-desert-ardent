/**
	* \file test/bouton.c
	* \brief Test de l'objet bouton.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 11:50:43
	*
	* L'objet bouton sert à creer un bouton et le dessine sur un renderer..
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/bouton.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet bouton. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	err_t err = E_AUTRE;
	bouton_t *bouton = creer_bouton();

	// INSTRUCTION(S)
	if( !bouton ){ // Pas d'objet bouton de créer :
		printf("Erreur à la création de bouton.\n");
		return(E_AUTRE);
	}
	// FIN DU PROGRAMME
	err = bouton->detruire( &bouton );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de bouton.\n");
		return(err);
	}
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(E_OK);
}
	/* Programme qui test l'objet bouton. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

