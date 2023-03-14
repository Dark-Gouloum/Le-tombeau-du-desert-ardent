/**
	* \file test/ancre.c
	* \brief Test de l'objet ancre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 14 Mars 2023 15:23:38
	*
	* L'objet ancre sert à ancrer un widget dans la fenêtre.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/ancre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet ancre. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
		/* Création des variables d'états */
	err_t status=E_AUTRE;
		/* Création d'un pointeur sur l'objet à tester */
	ancre_t *ancre;
		/* Création des autres variables */
	float x,y, test[]={-1,0,0.5,1,2 , 3};

	// INSTRUCTION(S)
	printf("Création de l'ancre...");
	if(!( ancre=creer_ancre(0,0,ANGLE_MILLIEU) )){
		printf("Erreur à la création de fenetre.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");

	for( int i=0 ; test[i]!=3 ; i++ ){
		x = test[i];
		if(( status=ancre->changerX( ancre , x ) )){
			printf("\n");
		} else {
			for( int j=0 ; test[j]!=3 ; j++ ){
				y = test[j];
				if(( status=ancre->changerY( ancre , y ) )){
					printf("\n");
				} else {
					printf("\tx=%f,y=%f : ",x,y);
					ancre->afficher(ancre);
					printf("\n");
				}
			}
			printf("\n");
		}
	}
	if(( status=ancre->changerA( ancre , ANGLE_ERREUR) ))
		printf("\n");
	ancre->afficher(ancre);
	if(( status=ancre->changerA( ancre , ANGLE_GAUCHE_SUP ) ))
		goto Quit;
	ancre->afficher(ancre);
	printf("\n");

	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if(( status = ancre->detruire( &ancre ) )){ // Echec à la destruction :
		printf("Erreur à la destruction de l'ancre.\n");
		return(status);
	}
	/* Affichage de fin */
	afficherSurvivant_ancre();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet ancre. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

