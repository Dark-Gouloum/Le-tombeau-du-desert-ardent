/**
	* \file src/page.c
	* \brief Définition de l'objet page.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 23 Mars 2023 18:41:01
	*
	* L'objet page sert à afficher le contenu d'une page.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/page.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_page = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet page

	// Methode commune à tout les objets
static void afficher_page( page_t *page ){
	printf("page{}");
}

static err_t detruire_page( page_t **page ){
	// Suppression des attributs de l'objet page

	// Suppression de l'objet page
	free( (*page) );
	(*page) = NULL;

	// Destruction de l'objet page réussie
	cmpt_page--;
	return(E_OK);
}

extern void afficherSurvivant_page(){
	printf("Il reste %i page_t.\n",cmpt_page);
}

extern page_t * creer_page(){
	// Tests des paramètre


	// Créer l'objet page
	page_t *page = malloc( sizeof(page_t) );
	if( !page ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'page'");
		return (page_t*)NULL;
	}

	// Affecter les attributs

	// Affecter les methodes
	page->detruire = (err_t (*)(void *))detruire_page;
	page->afficher = (void (*)(void *))afficher_page;

	// Renvoyer le bouton
	cmpt_page++;
	return page;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

