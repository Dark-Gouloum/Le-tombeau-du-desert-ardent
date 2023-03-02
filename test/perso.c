/**
	* \file test/perso.c
	* \brief Test de l'objet perso.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Mar. 28 Févr. 2023 14:38:44
	*
	* L'objet perso sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/perso.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet perso. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Création des variables d'états */
	err_t err=E_AUTRE, persous=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	personage_t *perso = NULL;

	
	/* Création des autres variables */
	// INSTRUCTION(S)
	printf("Création de l'objet perso...");
	if(!( perso=creer_perso() )){ // Pas d'objet perso de créer :
		printf("Erreur à la création de perso.\n");
		persous = E_AUTRE;
		goto Quit;
	}
	perso->afficher( perso );
	printf("\nOK\n");
	persous = E_OK;


	attribuer_perso(perso,2,3,4,6,7,5);
	perso->afficher(perso);
	sauvegarder(perso);


	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	err = perso->detruire( &perso );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de perso.\n");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_perso();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(persous);
}
	/* Programme qui test l'objet perso. */
	
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

