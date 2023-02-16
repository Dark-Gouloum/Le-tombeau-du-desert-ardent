/**
	* \file test/liste.c
	* \brief Test de l'objet liste.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mer. 15 Févr. 2023 15:17:01
	*
	* L'objet liste sert à stocke des pointeurs sur des objets.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../lib/liste.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_pers = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
typedef struct pers_s {
#include "../lib/attributs_objet.h"
	void (*afficher)(void*);
	char *nom, *prenom;
} pers_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
void afficher_pers( pers_t *p ){
	printf("{%s %s}",p->nom, p->prenom);
}

err_t detruire_pers( pers_t **p ){
	free( (*p)->nom );
	free( (*p)->prenom );
	free( (*p) );
	p = NULL;
	cmpt_pers--;
	return E_OK;
}

pers_t *creer_pers(char *nom, char *prenom){
	pers_t *p = malloc( sizeof(pers_t) );
	p->nom = malloc( sizeof(char) * (strlen(nom)+1) );
	p->prenom = malloc( sizeof(char) * (strlen(prenom)+1) );
	strcpy( p->nom , nom );
	strcpy( p->prenom , prenom );

	p->detruire = (err_t (*)(void*))detruire_pers;
	p->afficher = (void (*)(void*))afficher_pers;
	cmpt_pers++;
	return p;
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet liste. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	char *nom[] = {
		"aaaa",
		"bbbb",
		"cccc",
		"dddd",
		"eeee",
		"ffff",
		"gggg",
		"hhhh"
	};
	/* Création d'un pointeur sur l'objet à tester */
	liste_t *liste = NULL;
	pers_t *pers = NULL;

	/* Création des autres variables */
	// INSTRUCTION(S)
	printf("Création d'une liste d'objet...");
	if(!( liste=creer_liste() )){ // Pas d'objet liste de créer :
		printf("Erreur à la création de liste.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK.\n");

	printf("Il y à %i/%i élément dans la liste.\n\n", liste_taille(liste), cmpt_pers);

	printf("Ajout des objets...");
	for( int i=0 ; i<7 ; i++ ){
		pers = creer_pers( nom[i] , nom[i+1] );
		liste_ajoute( liste , pers );
	}
	pers = NULL;
	printf("OK.\n");

	printf("Il y à %i/%i élément dans la liste.\n\n", liste_taille(liste), cmpt_pers);

	printf("Affichage du 2e élément de la liste la liste :\n");
	liste_lit( liste, 1 , (void **)&pers );
	pers->afficher( pers );
	printf("Affichage de la liste :\n");
	afficher_liste( liste , pers->afficher );

	printf("Suppression d'éléments...");
	liste_enlever( liste , -4 );
	liste_enlever( liste , liste_taille(liste) );
	liste_enlever( liste , liste_taille(liste)-1 );
	liste_enlever( liste , 0 );
	printf("OK.\n");
	printf("Affichage de la liste :\n");
	afficher_liste( liste , pers->afficher );

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	err = liste->detruire( &liste );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de liste.\n");
		return(err);
	}
	/* Affichage de fin */
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	printf("Il reste %i pers_t.\n",cmpt_pers);
	afficherSurvivant_liste();
	return(status);
}
	/* Programme qui test l'objet liste. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

