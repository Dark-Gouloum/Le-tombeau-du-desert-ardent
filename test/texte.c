/**
	* \file test/texte.c
	* \brief Test de l'objet texte.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Lun. 13 Févr. 2023 18:46:38
	*
	* L'objet texte sert à écrire du texte sur une fenêtre.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/texte.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet texte. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	err_t err = E_AUTRE;
	texte_t *texte = creer_texte();

	// INSTRUCTION(S)
	if( !texte ){ // Pas d'objet texte de créer :
		printf("Erreur à la création de texte.\n");
		return(E_AUTRE);
	}

	// FIN DU PROGRAMME
	err = texte->detruire( &texte );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de texte.\n");
		return(err);
	}
	afficherSurvivant_texte();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(E_OK);
}
	/* Programme qui test l'objet texte. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

