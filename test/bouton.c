/**
	* \file test/bouton.c
	* \brief Test de l'objet bouton.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 14 Févr. 2023 19:09:04
	*
	* L'objet bouton sert à créer et gérer des boutons.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/bouton.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet bouton. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
		// Lancement de SDL
	if( SDL_Init( SDL_INIT_VIDEO ) ){
		printf("ERREUR :  SDL_Init : %s", SDL_GetError());
		return E_INIT;
	}
	if( initialisation_SDL_TTF() )
		return E_INIT;
		// Création des variables d'états
	char *nomFont="Roboto/Roboto-Thin.ttf" , *texte="Hello World !";
	err_t err=E_AUTRE , status=E_AUTRE;
	int tailleFenetre = 500;
		// Création des autres variables
	SDL_Window *fenetre = NULL;
	SDL_Renderer *rendu = NULL;
	SDL_Color couleur = {255,255,255,255};
	SDL_Event event;
		// Création de l'objet à tester
	bouton_t *bouton = NULL;

	// INSTRUCTION(S)
	printf("Création de la fenêtre...");
	if( SDL_CreateWindowAndRenderer(tailleFenetre,tailleFenetre, SDL_WINDOW_SHOWN, &fenetre,&rendu) ){
		printf("%sSDL_CreateWindowAndRenderer : %s.\n",MSG_E,SDL_GetError());
		status = E_AUTRE;
		goto Quit;
	}
	SDL_SetWindowTitle( fenetre , "test de la création d'un bouton" );
	printf("OK\n");
	SDL_Delay(1000);

	printf("Création du stylo...");
	if( !(stylo=creer_stylo( nomFont , 72 , couleur )) ){ // Pas d'objet stylo de créer :
		printf("Erreur à la création de stylo.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");
	SDL_Delay(1000);

	printf("Création du bouton...");
	if(!( bouton=creer_bouton(rendu, stylo, "quitter", {tailleFenetre/2,tailleFenetre/2}) )){ // Pas d'objet bouton de créer :
		printf("Erreur à la création de bouton.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");
	SDL_Delay(1000);

	printf("Attente du signal de fermeture...");
	status = E_AUTRE;
	while( status ){
		while( SDL_PollEvent(&event) ){
			if( event.type == SDL_QUIT )
				status = E_OK;
			else if( event.type == SDL_MOUSE_DOWN ){
			}
		}
	}
	printf("OK\n");
	SDL_Delay(1000);

	// FIN DU PROGRAMME
Quit:		// Destruction des objets
	err = bouton->detruire( &bouton );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de bouton.\n");
		return(err);
	}
		// Affichage de fin
	afficherSurvivant_bouton();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(E_OK);
}
	/* Programme qui test l'objet bouton. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

