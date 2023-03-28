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
int nouveauMot(char *mot,int i,FILE *fichier,char *action){
	char car;
	while(( car=fgetc(fichier) )){
		switch(car){
			case '\\':
				if(( car=fgetc(fichier) )){
					mot[i++] = car;
				}
				break;
			case '=':
				mot[i++] = car;
				if( i == 1 ){ // Si c'était le premier caractère du mot :
					int ret=0;
					if(( ret=nouveauMot(mot,i,fichier,action) )){
						if( strcmp(mot,"=FIN=\n") == 0 ){
							mot[0] = '\0';
							return 0;
						} else if( strcmp(mot,"===\n") == 0 ){
							mot[0] = '\0';
							return -2;
						}
					}
				}
				break;
			case '[':
				if( i == 0 ){ // Si c'est le premier caractère du mot :
					int cont=1;
					while( cont && (car=fgetc(fichier)) ){
						if( car==']' ){
							mot[i] = '\0';
							cont = 0;
						} else {
							mot[i++] = car;
						}
					}
					if(( car=fgetc(fichier) )){
						if( car=='(' ){
							int j=0;
							cont=1;
							while( cont && (car=fgetc(fichier)) ){
								if( car==')' ){
									action[j] = '\0';
									cont = 0;
								} else {
									action[j++] = car;
								}
							}
							return(-3);
						} else {
							mot[i++] = car;
							mot[i] = '\0';
							return(-1);
						}
					} else {
						mot[i] = '\0';
						return -1;
					}
				} else {
					mot[i++] = car;
				}
				break;
			case '\n':
			case '\t':
			case ' ':
				mot[i++] = car;
				mot[i] = '\0';
				return -1;
			default: mot[i++] = car;
		}
	}
	return 0;
}
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

