/**
	* \file test/joueur.c
	* \brief Test de l'objet joueur.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Jeu. 23 Mars 2023 00:31:27
	*
	* L'objet joueur sert à gére le joueur (c'est le personnage principal.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/joueur.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet joueur. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
		/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
		/* Création d'un pointeur sur l'objet à tester */
	joueur_t *joueur = NULL;
		/* Création des autres variables */

	// INSTRUCTION(S)
	printf("Création de l'objet joueur...");
	if(!( joueur=creer_joueur() )){ // Pas d'objet joueur de créer :
		MSG_ERR2("À la création de joueur");
		status = E_AUTRE;
		goto Quit;
	}
	attribuer_personnage(joueur,10,20,30,40,50,60,NULL);
	joueur->afficher( joueur );
	printf("OK\n");

	printf("Ajout d'item au joueur...");
	joueur->afficher( joueur );
	printf("OK\n");

	printf("Retrait d'item au joueur...");
	joueur->afficher( joueur );
	printf("OK\n");

	printf("Sauvegarde de l'objet joueur...");
	printf("OK\n");

	printf("Suppression de l'objet joueur...");
	if( (err=joueur->detruire(&joueur)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de joueur");
		return(err);
	}
	joueur->afficher( joueur );
	printf("OK\n");

	printf("chargement de l'objet joueur...");
	if(!( joueur=charger_joueur() )){ // Pas d'objet joueur de créer :
		MSG_ERR2("Au chargement du joueur");
		status = E_AUTRE;
		goto Quit;
	}
	joueur->afficher( joueur );
	printf("OK\n");

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=joueur->detruire(&joueur)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de joueur");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_joueur();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet joueur. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

