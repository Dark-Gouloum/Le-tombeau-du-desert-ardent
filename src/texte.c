/**
	* \file src/texte.c
	* \brief Définition de l'objet texte.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 28 Févr. 2023 14:40:03
	*
	* L'objet texte sert à ecrire du texte sur la fenêtre.
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
static err_t changerStylo_texte(texte_t *texte,stylo_t *stylo){
	(texte->stylo) = stylo;
	return E_OK;
}

extern err_t ecrire_texte(SDL_Renderer *r , texte_t *t , SDL_Rect *dest_rect){
	return ecrire(r,t->stylo,t->texte,t->ancre,dest_rect);
}

	// Methode commune à tout les objets
static void afficher_texte( texte_t *texte ){
	printf("texte{%s}",texte->texte);
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

extern void afficherSurvivant_texte(){
	printf("Il reste %i texte_t.\n",cmpt_texte);
}

extern texte_t * creer_texte(stylo_t *s, char *str, ancre_t ancre){
	// Définission des variables utiles
	char *nomFonction = "creer_texte : ";

	// Créer l'objet texte
	texte_t *texte = malloc( sizeof(texte_t) );
	if( !texte ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (texte_t*)NULL;
	}

	// Affecter les attributs
	if(!( (texte->texte) = malloc(sizeof(char)*(strlen(str)+1)) )){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (texte_t*)NULL;
	}
	strcpy( texte->texte , str );
	texte->ancre = ancre;

	// Affecter les methodes
	texte->changerStylo = (err_t (*)(void*,stylo_t*))changerStylo_texte;
	texte->detruire = (err_t (*)(void *))detruire_texte;
	texte->afficher = (void (*)(void *))afficher_texte;

	// Renvoyer le bouton
	cmpt_texte++;
	return texte;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

