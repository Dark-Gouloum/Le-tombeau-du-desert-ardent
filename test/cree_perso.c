
/**
	* \file test/cree_perso.c
	* \brief Test de l'objet cree_perso.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Jeu. 09 Mars 2023 13:59:44
	*
	* L'objet cree_perso sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/cree_perso.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet cree_perso. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	cree_perso_t *cree_perso = NULL;

	/* Création des autres variables */
	// INSTRUCTION(S)
	printf("Création de l'objet cree_perso...");
	
	cree_perso->afficher( cree_perso );
	printf("OK\n");
	status = E_OK;

	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	err = cree_perso->detruire( &cree_perso );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de cree_perso.\n");
		return(err);
	}
	/* Affichage de fin */
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet cree_perso. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //
