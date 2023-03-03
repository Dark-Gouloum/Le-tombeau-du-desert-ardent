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
static int unsigned cmpt_frac = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
typedef struct pers_s {
#include "../lib/attributs_objet.h"
	char *nom, *prenom;
	int age;
} pers_t;

typedef struct frac_s {
#include "../lib/attributs_objet.h"
	int n,d;
} frac_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
extern void afficherSurvivant_pers();
extern pers_t * creer_pers( char *nom, char *prenom, int age );

extern void afficherSurvivant_frac();
extern frac_t * creer_frac( int n , int d );

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
	int ent[] = {1,2,3,4,5,6,7,8};
	/* Création d'un pointeur sur l'objet à tester */
	liste_t *liste = NULL;
	pers_t *pers = NULL;
	frac_t *frac = NULL;

	/* Création des autres variables */
	// INSTRUCTION(S)
	printf("Création d'une liste d'objet...");
	if(!( liste=creer_liste() )){ // Pas d'objet liste de créer :
		printf("Erreur à la création de liste.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK.\n");

	printf("Il y à %i/%i élément dans la liste.\n\n", liste_taille(liste), cmpt_pers + cmpt_frac);

	printf("Ajout des objets...");
	for( int i=0 ; i<7 ; i++ ){
		pers = creer_pers( nom[i] , nom[i+1] , (i+2)*3 );
		liste_ajoute( liste , pers );
		pers->afficher( pers );
		frac = creer_frac( ent[i] , ent[i+1] );
		liste_ajoute( liste , frac );
		frac->afficher( frac );
	}
	pers = NULL;
	frac = NULL;
	printf("OK.\n");

	printf("Il y à %i/%i élément dans la liste.\n\n", liste_taille(liste), cmpt_pers + cmpt_frac);

	printf("Affichage du 2e élément de la liste la liste :\n");
	liste_lit( liste, 1 , (void **)&pers );
	pers->afficher( pers );
	printf("Affichage de la liste :\n");
	liste->afficher( liste );

	printf("Suppression d'éléments...");
	liste_enlever_pos( liste , -4 );
	liste_enlever_pos( liste , liste_taille(liste) );
	liste_enlever_pos( liste , liste_taille(liste)-1 );
	liste_enlever_pos( liste , 0 );
	printf("OK.\n");
	printf("Affichage de la liste :\n");
	liste->afficher( liste );

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
	afficherSurvivant_pers();
	afficherSurvivant_frac();
	afficherSurvivant_liste();
	return(status);
}
	/* Programme qui test l'objet liste. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

static void afficher_pers( pers_t *pers ){
	printf("pers{%s %s à %d ans}",pers->nom,pers->prenom,pers->age);
}
static err_t detruire_pers( pers_t **pers ){
	// Suppression des attributs de l'objet pers
	free( (*pers)->nom );
	free( (*pers)->prenom );

	// Suppression de l'objet pers
	free( (*pers) );
	(*pers) = NULL;

	// Destruction de l'objet pers réussie
	cmpt_pers--;
	return(E_OK);
}

extern void afficherSurvivant_pers(){
	printf("Il reste %i pers_t.\n",cmpt_pers);
}

extern pers_t * creer_pers( char *nom , char *prenom , int age){
	// Définission des variables utiles
	char *nomFonction = "creer_pers : ";

	// Créer l'objet pers
	pers_t *pers = malloc( sizeof(pers_t) );
	if( !pers ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (pers_t*)NULL;
	}

	// Affecter les attributs
	pers->nom = malloc( sizeof(char) * (strlen(nom)+1) );
	if( !pers->nom ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		free( pers );
		return (pers_t*)NULL;
	}
	pers->prenom = malloc( sizeof(char) * (strlen(prenom)+1) );
	if( !pers->prenom ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		free( pers->nom );
		free( pers );
		return (pers_t*)NULL;
	}
	strcpy( (pers->nom) , nom );
	strcpy( (pers->prenom) , prenom );
	pers->age = age;

	// Affecter les methodes
	pers->detruire = (err_t (*)(void *))detruire_pers;
	pers->afficher = (void (*)(void *))afficher_pers;

	// Renvoyer le pers
	cmpt_pers++;
	return pers;
}

// #####-#####-#####-#####-##### FIN DEF PERS #####-#####-#####-#####-##### //

static void afficher_frac( frac_t *frac ){
	printf("frac{%d/%d}",frac->n,frac->d);
}
static err_t detruire_frac( frac_t **frac ){
	// Suppression des attributs de l'objet frac

	// Suppression de l'objet frac
	free( (*frac) );
	(*frac) = NULL;

	// Destruction de l'objet frac réussie
	cmpt_frac--;
	return(E_OK);
}

extern void afficherSurvivant_frac(){
	printf("Il reste %i frac_t.\n",cmpt_frac);
}

extern frac_t * creer_frac( int n , int d ){
	// Définission des variables utiles
	char *nomFonction = "creer_frac : ";

	// Créer l'objet frac
	frac_t *frac = malloc( sizeof(frac_t) );
	if( !frac ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (frac_t*)NULL;
	}

	// Affecter les attributs
	frac->n = n;
	frac->d = d;

	// Affecter les methodes
	frac->detruire = (err_t (*)(void *))detruire_frac;
	frac->afficher = (void (*)(void *))afficher_frac;

	// Renvoyer le pers
	cmpt_frac++;
	return frac;
}

// #####-#####-#####-#####-##### FIN DEF PERS #####-#####-#####-#####-##### //

