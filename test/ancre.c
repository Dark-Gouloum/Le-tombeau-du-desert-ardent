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
	err_t err=E_AUTRE, status=E_AUTRE;
		/* Création de l'objet à tester */
	ancre_t a;
		/* Création des autres variables */
	float x,y, test[]={-1,0,0.5,1,2 , 3};
	angle_t angle;

	// INSTRUCTION(S)
	angle = ANGLE_MILLIEU;
	for( int i=0 ; test[i]!=3 ; i++ ){
		x = test[i];
		for( int j=0 ; test[j]!=3 ; j++ ){
			y = test[j];
			a = ancre(x,y,angle);
			printf("x=%d,y=%d : ancre={%d,%d,ANGLE_MILLIEU\n",x,y,a.x,a.y);
		}
		printf("\n");
	}

	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	/* Affichage de fin */
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet ancre. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

