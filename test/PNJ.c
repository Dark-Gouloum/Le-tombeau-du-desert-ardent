/**
	* \file test/PNJ.c
	* \brief Test de l'objet PNJ.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Jeu. 23 Mars 2023 01:36:49
	*
	* L'objet PNJ sert à gérer les Personnage Non Joueur du jeu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/PNJ.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet PNJ. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
		/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
		/* Création d'un pointeur sur l'objet à tester */
	PNJ_t *PNJ = NULL;
		/* Création des autres variables */

	// INSTRUCTION(S)
	printf("Création de l'objet PNJ...");
	if(!( PNJ=creer_PNJ() )){ // Pas d'objet PNJ de créer :
		MSG_ERR2("À la création de PNJ");
		status = E_AUTRE;
		goto Quit;
	}
	PNJ->afficher( PNJ );
	printf("OK\n");

	printf("Attribution des stats de l'objet PNJ...");
	attribuer_personnage(PNJ,2,3,4,6,7,5,"Benard de la ville aride");
	PNJ->afficher( PNJ );
	printf("OK\n");

	status = E_OK;

	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=PNJ->detruire(&PNJ)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de PNJ");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_PNJ();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet PNJ. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

