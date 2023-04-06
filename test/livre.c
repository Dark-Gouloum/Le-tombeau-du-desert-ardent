/**
	* \file test/livre.c
	* \brief Test de l'objet livre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 03 Avril 2023 20:43:50
	*
	* L'objet livre sert à afficher du texte dans un livre donnée.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/livre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
#define FICHIER_TEST "test"
#define SEPX 20
#define SEPY 20
int STOP = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t quitter(int argc,...){
	printf("%s",__func__);
	STOP = 1;
	return E_OK;
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet livre. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF|SDL_IMG , IMG_INIT_PNG ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	livre_t *livre = NULL;
	/* Création des autres variables */
	police_t *police = NULL;
	SDL_Color stylo = {92,75,43,255};
	SDL_Event event;

	// INSTRUCTION(S)
	{ // Création de la police d'écriture
		police=creer_police(NULL,30,&stylo);
		if( !police ){
			MSG_ERR2("de la création de la police d'écriture");
			err = E_AUTRE;
			goto Quit;
		}
	}
	printf("Création du livre...\n");
	if(!( livre=creer_livre(SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN,"test_texte","livreOuvertPlacement.png",NULL,&police) )){
		MSG_ERR2("de la création du livre");
		err = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");

	printf("Ouverture du fichier de test...\n");
	if(( err=nouveauChapitre(livre,FICHIER_TEST) )){
		MSG_ERR2("de l'ouverture du fichier de test");
		goto Quit;
	}
	printf("OK\n");

	printf("Attente d'un signal...\n");
	err = E_AUTRE;
	while( !STOP ){
		while( SDL_PollEvent(&event) ){
			if( event.type == SDL_QUIT )
				STOP = 1;
			else if( (event.type==SDL_MOUSEBUTTONUP) ){
				if(( err=livre_cliquer(livre,&STOP) )){
					MSG_ERR2("de l'activtion du bouton");
					goto Quit;
				}
			}
		}
		if(( err=livre_rafraichir(livre) )){
			MSG_ERR2("du rafraichissement du contenu du livre");
			goto Quit;
		}
	}
	printf("OK\n");

	err = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=livre->detruire(&livre)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de livre");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_livre();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(err);
}
	/* Programme qui test l'objet livre. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

