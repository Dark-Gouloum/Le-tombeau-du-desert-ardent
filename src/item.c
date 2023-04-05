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
#include <string.h>

#include "../lib/item.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_item = 0;
static int unsigned cmpt_modificateur = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)


// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet modificateur_t
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

static void afficher_modificateur(modificateur_t *modif){
	printf("modif{");
	if( !modif ){
		printf("inexistant");
	} else {
		printf("modif{%s:%d}",traduire(modif->modif),modif->valeur);
	}
	printf("}");
}

static err_t detruire_modificateur(modificateur_t **modif){
	// Suppression de l'objet item
	free( (*modif) );
	(*modif) = NULL;

	// Destruction de l'objet item réussie
	cmpt_modificateur--;
	return(E_OK);
}

static void afficherSurvivant_modificateur(){
	printf("Il reste %i modificateur_t.\n",cmpt_modificateur);
}

static modificateur_t * creer_modificateur(stat_t modif, int valeur){
	if( modif == STAT_UNK ){
		MSG_ERR(E_ARGUMENT,"ce type de stat est inconnu");
		return (modificateur_t*)NULL;
	}
	// Créer l'objet modificateur
	modificateur_t *modificateur = malloc( sizeof(modificateur_t) );
	if( !modificateur ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : malloc à échouer, pas assez de place de place disponible en mémoire");
		return (modificateur_t*)NULL;
	}

	// Affecter les attributs
	modificateur->modif = modif;
	modificateur->valeur = valeur;

	// Affecter les methodes
	modificateur->detruire = (err_t (*)(void *))detruire_modificateur;
	modificateur->afficher = (void (*)(void *))afficher_modificateur;

	// Renvoyer le bouton
	cmpt_modificateur++;
	return modificateur;
}

	// Fonctions spéciale d'un objet item
extern err_t ajouterModificateur(item_t *item, stat_t modif, int valeur){
	err_t err;
	modificateur_t *modificateur = NULL;
	if(!( modificateur=creer_modificateur(modif,valeur) )){
		MSG_ERR2("de la création d'un modificateurs");
		return(E_AUTRE);
	}
	if(( err=liste_ajoute(item->lstModificateurs,modificateur) )){
		MSG_ERR2("de l'ajout d'un modificateurs");
		return(E_AUTRE);
	}
	return(E_OK);
}

extern err_t sauvegarder_item(FILE *f, item_t *item){
	if( !f ){
		MSG_ERR(E_ARGUMENT,"Il n'y as pas de fichier à lire");
		return(E_ARGUMENT);
	}
	modificateur_t *modif = NULL;
	err_t err = E_OK;
	int nbModif = liste_taille( item->lstModificateurs );
	fprintf(f,"%s %d\n",item->nom,nbModif);
	for( int i=0 ; i<nbModif; i++ ){
		modif = liste_recherche_obj(&err, item->lstModificateurs ,  i );
		if( err ){
			char msg[ 50 ];
			sprintf(msg,"Le modificateur N°%d n'à pas était retrouvé.",i);
			MSG_ERR2(msg);
			return(err);
		}
		fprintf(f,"\t%d %d\n",modif->modif,modif->valeur);
	}
	return(E_OK);
}
extern err_t charger_item(FILE *f, item_t **item){
	err_t err = E_OK;
	if( !f ){
		MSG_ERR(E_ARGUMENT,"Il n'y as pas de fichier à lire");
		return(E_ARGUMENT);
	}
	if( *item ){
		if(( err=((*item)->detruire(item)) )){
			MSG_ERR2("de la destruction de l'ancien item");
			return(err);
		}
	}
	char nom[255];
	int nbModif;
	int modif,valeur;

	if( fscanf(f,"%s %d",nom,&nbModif) != 2 ){
		MSG_ERR(E_OBTENIR,"Une erreur c'est produite lors de la lecture du nom de l'item");
		return(E_OBTENIR);
	}
	if(!( *item = creer_item(nom) )){
			MSG_ERR2("de la création de l'item");
			return(E_AUTRE);
	}
	for( int i=0 ; i<nbModif; i++ ){
		if( fscanf(f,"\t%d %d\n",&modif,&valeur) != 2 ){
			char msg[ 60 ];
			sprintf(msg,"Le modificateur N°%d n'à pas était entièrement lu.",i);
			MSG_ERR(E_OBTENIR,msg);
			return(E_OBTENIR);
		}
		if(( err=ajouterModificateur(*item,modif,valeur) )){
			char msg[ 60 ];
			sprintf(msg,"Le modificateur N°%d n'à pas correctement chargé.",i);
			MSG_ERR2(msg);
			return(err);
		}
	}
	return(E_OK);
}

	// Methode commune à tout les objets
static void afficher_item( item_t *item ){
	printf("item{ ");
	if( !item ){
		printf("inexistant");
	} else {
		printf("Nom='%s'\n modificateurs_",item->nom,"\n");
		( item->lstModificateurs )->afficher( item->lstModificateurs );
	}
	printf(" }");
}


static err_t detruire_item( item_t **item ){
	if( !(*item) ){
		MSG_ERR(E_ARGUMENT,"Il n'y as pas d'item à detruire.");
		return(E_ARGUMENT);
	}
	// Suppression des attributs de l'objet item
	err_t err;
	liste_t *liste = (*item)->lstModificateurs;
	if(( err=liste->detruire(&liste) )){
		MSG_ERR2("de la destruction de la liste de modificateurs");
		return(err);
	}
	(*item)->lstModificateurs = liste;

	// Suppression de l'objet item
	free( (*item) );
	(*item) = NULL;

	// Destruction de l'objet item réussie
	cmpt_item--;
	return(E_OK);
}

extern void afficherSurvivant_item(){
	printf("Il reste %i item_t.\n",cmpt_item);
	afficherSurvivant_modificateur();
	afficherSurvivant_liste();
}

extern item_t * creer_item(char *nom){
	// Créer l'objet item
	item_t *item = malloc( sizeof(item_t) );
	if( !item ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : malloc à échouer, pas assez de place de place disponible en mémoire");
		return (item_t*)NULL;
	}

	// Affecter les attributs
	item->nom = malloc( sizeof(char) * (strlen(nom)+1) );
	if( !(item->nom) ){ // malloc à échouer :
		MSG_ERR2("de la création du nom");
		return (item_t*)NULL;
	}
	strcpy( item->nom , nom );
	item->lstModificateurs = creer_liste();
	if( !(item->lstModificateurs) ){ // malloc à échouer :
		MSG_ERR2("de la création de la liste de modificateurs");
		return (item_t*)NULL;
	}

	// Affecter les methodes
	item->detruire = (err_t (*)(void *))detruire_item;
	item->afficher = (void (*)(void *))afficher_item;

	// Renvoyer le bouton
	cmpt_item++;
	return item;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

