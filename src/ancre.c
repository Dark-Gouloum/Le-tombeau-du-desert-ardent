/**
	* \file src/ancre.c
	* \brief Définition de l'objet ancre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 14 Mars 2023 15:23:38
	*
	* L'objet ancre sert à ancrer un widget dans la fenêtre..
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/ancre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_ancre = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'une enumeration angle
extern char *interprete_angle(angle_t angle){
	switch( angle ){
		case ANGLE_ERREUR :
			return "ERREUR";
		case ANGLE_MILLIEU :
			return "MILLIEU";
		case ANGLE_GAUCHE_SUP :
			return "GAUCHE SUPERIEUR";
		case ANGLE_GAUCHE_INF :
			return "GAUCHE INFERIEUR";
		case ANGLE_DROIT_SUP :
			return "DROIT SUPERIEUR";
		case ANGLE_DROIT_INF :
			return "DROIT INFERIEUR";
	}
	return "";
}
extern err_t existe_angle(angle_t angle){
	switch( angle ){
		case ANGLE_ERREUR :
			return E_AUTRE;
		case ANGLE_MILLIEU :
		case ANGLE_GAUCHE_SUP :
		case ANGLE_GAUCHE_INF :
		case ANGLE_DROIT_SUP :
		case ANGLE_DROIT_INF :
			return E_OK;
		default :
			return E_ARGUMENT;
	}
	return E_AUTRE;
}

	// Fonctions spéciale d'un objet ancre
static err_t changerX_ancre(ancre_t *ancre , float x){
	char *nomFonction = "changerX : ";
	if( x<0 ){
		printf("%s%sx est inférieur à 0. (x=%.2f)",MSG_E,nomFonction,x);
		return E_ARGUMENT;
	}
	if( x>1 ){
		printf("%s%sx est supérieur à 1. (x=%.2f)",MSG_E,nomFonction,x);
		return E_ARGUMENT;
	}
	ancre->x = 100*x;
	return E_OK;
}
static err_t changerY_ancre(ancre_t *ancre , float y){
	char *nomFonction = "changerY : ";
	if( y<0 ){
		printf("%s%sy est inférieur à 0. (y=%.2f)",MSG_E,nomFonction,y);
		return E_ARGUMENT;
	}
	if( y>1 ){
		printf("%s%sy est supérieur à 1. (y=%.2f)",MSG_E,nomFonction,y);
		return E_ARGUMENT;
	}
	ancre->y = 100*y;
	return E_OK;
}
static err_t changerA_ancre(ancre_t *ancre , angle_t a){
	err_t err;
	if(( err=existe_angle(a) )){
		printf("%schangerA : angle inconnue (angle=%d).\n",MSG_E,a);
		return err;
	}
	ancre->angle = a;
	return E_OK;
}

	// Methode commune à tout les objets
static void afficher_ancre( ancre_t *ancre ){
	printf("ancre{ {%d,%d} , %s }",ancre->x,ancre->y , interprete_angle(ancre->angle));
}
static err_t detruire_ancre( ancre_t **ancre ){
	// Suppression des attributs de l'objet ancre

	// Suppression de l'objet ancre
	free( (*ancre) );
	(*ancre) = NULL;

	// Destruction de l'objet ancre réussie
	cmpt_ancre--;
	return(E_OK);
}

extern void afficherSurvivant_ancre(){
	printf("Il reste %i ancre_t.\n",cmpt_ancre);
}

extern ancre_t * creer_ancre(float x, float y, angle_t angle){
	// Définission des variables utiles
	char *nomFonction = "creer_ancre : ";

	// Créer l'objet ancre
	ancre_t *ancre = malloc( sizeof(ancre_t) );
	if( !ancre ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (ancre_t*)NULL;
	}

	// Affecter les attributs
	if( changerX_ancre(ancre,x) ){
		return (ancre_t*)NULL;
	}
	if( changerY_ancre(ancre,y) ){
		return (ancre_t*)NULL;
	}
	if( changerA_ancre(ancre,angle) ){
		return (ancre_t*)NULL;
	}

	// Affecter les methodes
	ancre->detruire = (err_t (*)(void *))detruire_ancre;
	ancre->afficher = (void (*)(void *))afficher_ancre;

	ancre->changerX = (err_t (*)(ancre_t*,float))changerX_ancre;
	ancre->changerY = (err_t (*)(ancre_t*,float))changerY_ancre;
	ancre->changerA = (err_t (*)(ancre_t*,angle_t))changerA_ancre;

	// Renvoyer le bouton
	cmpt_ancre++;
	return ancre;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

