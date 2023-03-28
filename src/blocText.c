/**
	* \file src/blocText.c
	* \brief Définition de l'objet blocText.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 27 Mars 2023 21:50:49
	*
	* L'objet blocText sert à afficher du texte dans une boite.
	* Il garde en mémoire jusqu'où le texte à était écrit.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/blocText.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_blocText = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet blocText

	// Methode commune à tout les objets
static void afficher_blocText( blocText_t *blocText ){
	printf("blocText{}");
}

static err_t detruire_blocText( blocText_t **blocText ){
	// Suppression des attributs de l'objet blocText

	// Suppression de l'objet blocText
	free( (*blocText) );
	(*blocText) = NULL;

	// Destruction de l'objet blocText réussie
	cmpt_blocText--;
	return(E_OK);
}

extern void afficherSurvivant_blocText(){
	printf("Il reste %i blocText_t.\n",cmpt_blocText);
}

extern blocText_t * creer_blocText(){
	// Tests des paramètre


	// Créer l'objet blocText
	blocText_t *blocText = malloc( sizeof(blocText_t) );
	if( !blocText ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'blocText'");
		return (blocText_t*)NULL;
	}

	// Affecter les attributs

	// Affecter les methodes
	blocText->detruire = (err_t (*)(void *))detruire_blocText;
	blocText->afficher = (void (*)(void *))afficher_blocText;

	// Renvoyer le bouton
	cmpt_blocText++;
	return blocText;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

