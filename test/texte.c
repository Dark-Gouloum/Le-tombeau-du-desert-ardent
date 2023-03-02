/**
	* \file test/texte.c
	* \brief Test de l'objet texte.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 28 Févr. 2023 14:40:03
	*
	* L'objet texte sert à ecrire du texte sur la fenêtre.
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
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	texte_t *texte = NULL;

	/* Création des autres variables */
	// INSTRUCTION(S)
	printf("Création de l'objet texte...");
	if(!( texte=creer_texte() )){ // Pas d'objet texte de créer :
		printf("Erreur à la création de texte.\n");
		status = E_AUTRE;
		goto Quit;
	}
	texte->afficher( texte );
	printf("OK
");
	status = E_OK;

	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	err = texte->detruire( &texte );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de texte.\n");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_texte();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet texte. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

