/**
	* \file src/texte.c
	* \brief Définition de l'objet texte.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Lun. 13 Févr. 2023 18:46:38
	*
	* L'objet texte sert à écrire du texte sur une fenêtre.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/texte.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_texte = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet texte

	// Methode commune à tout les objets
static void afficher_texte( texte_t *texte ){
}

static err_t detruire_texte( texte_t **texte ){
	// Suppression des attributs de l'objet texte

	// Suppression de l'objet texte
	free( (*texte) );
	(*texte) = NULL;

	// Destruction de l'objet texte réussie
	cmpt_texte--;
	return(E_OK);
}

extern void afficherSurvivant_texte( texte_t *texte ){
	printf("Il reste %i texte_t.",cmpt_texte);
}

extern int obtenirNbSurvivant_texte( texte_t *texte ){
	return cmpt_texte;
}

extern texte_t * creer_texte(){
	// Définission des variables utiles
	char *nomFonction = "creer_texte : ";

	// Créer l'objet texte
	texte_t *texte = malloc( sizeof(texte_t) );
	if( !texte ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (texte_t*)NULL;
	}

	// Affecter les attributs

	// Affecter les methodes
	texte->detruire = (err_t (*)(void *))detruire_texte;
	texte->afficher = (void (*)(void *))afficher_texte;

	// Renvoyer le bouton
	cmpt_texte++;
	return texte;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

