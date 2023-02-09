/**
	* \file src/bouton.c
	* \brief Définition de l'objet bouton.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 11:50:43
	*
	* L'objet bouton sert à creer un bouton et le dessine sur un renderer..
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/bouton.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
static void afficher_bouton( bouton_t *bouton ){
}

static err_t detruire_bouton( bouton_t **bouton ){
	free( (*bouton) );
	(*bouton) = NULL;
	return(E_OK);
}

extern bouton_t * creer_bouton(){
	bouton_t *bouton = malloc( sizeof(bouton_t) );
	if( !bouton ){ // malloc à échouer :
		printf("ERREUR : creer_bouton :\n\tmalloc à échouer, pas assez de place de place disponible en mémoire.\n");
		return (bouton_t*)NULL;
	}

	bouton->detruire = (err_t (*)(void *))detruire_bouton;
	bouton->afficher = (void (*)(void *))afficher_bouton;

	return bouton;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

