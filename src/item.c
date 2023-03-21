/**
	* \file src/item.c
	* \brief Définition de l'objet item.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Mar. 28 Févr. 2023 14:47:08
	*
	* L'objet item sert à FaitQuelqueChose.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/item.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_item = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet item

	// Methode commune à tout les objets
static void afficher_item( item_t *item ){
	printf("item{\nNom: %s",item->nom);
	printf("\nStatistique: %s",traduire(item->statModif));
	printf(" %d}",item->valeur);
}


static err_t detruire_item( item_t **item ){
	// Suppression des attributs de l'objet item

	// Suppression de l'objet item
	free( (*item) );
	(*item) = NULL;

	// Destruction de l'objet item réussie
	cmpt_item--;
	return(E_OK);
}

extern void afficherSurvivant_item(){
	printf("Il reste %i item_t.\n",cmpt_item);
}

extern item_t * creer_item(){
	// Créer l'objet item
	item_t *item = malloc( sizeof(item_t) );
	if( !item ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : malloc à échouer, pas assez de place de place disponible en mémoire");
		return (item_t*)NULL;
	}

	// Affecter les attributs
	item->nom = NULL;
	item->statModif = 0;
	item->valeur =0;
	// Affecter les methodes
	item->detruire = (err_t (*)(void *))detruire_item;
	item->afficher = (void (*)(void *))afficher_item;

	// Renvoyer le bouton
	cmpt_item++;
	return item;
}


extern char * traduire(stat_t stat){
	switch(stat){
		case STAT_PV:
			return "PV";
		case STAT_FORCE:
			return "Force";
		case STAT_AGILITE:
			return "Agilite";
		case STAT_ARMURE:
			return "Armure";
		case STAT_CRITIQUE:
			return "Critique";
		case STAT_INTEL:
			return "Intelligence";
		default:
			return "Stat inconnu";
	}
}
// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

