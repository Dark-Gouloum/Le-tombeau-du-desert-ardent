/**
	* \file test/stylo.c
	* \brief Test de l'objet stylo.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Mar. 14 Févr. 2023 15:14:19
	*
	* L'objet stylo sert à écrire du texte sur la fenêtre.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/stylo.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet stylo. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
		// Lancement de SDL
	if( SDL_Init( SDL_INIT_VIDEO ) ){
		printf("ERREUR :  SDL_Init : %s", SDL_GetError());
		return E_INIT;
	}
	if( initialisation_SDL_TTF() )
		return E_INIT;
		// Création des variables dynamiques
	SDL_Window *fenetre = NULL;
	SDL_Renderer *rendu = NULL;
		// Création des variables static
	char *nomFont="Roboto/Roboto-Thin.ttf" , *texte="Hello World !";
	SDL_Color couleur = {255,255,255,255};
	err_t err=E_AUTRE , status=E_AUTRE;
	SDL_Event event;
	int tailleFenetre = 500;
	ancre_t ancre;
	ancre.point = (SDL_Point){tailleFenetre/2,tailleFenetre/3};
	ancre.angle = ANGLE_MILLIEU;
		// Création de l'objet à tester
	stylo_t *stylo = NULL;

	// INSTRUCTION(S)
	printf("Création de la fenêtre...");
	if( SDL_CreateWindowAndRenderer(tailleFenetre,tailleFenetre, SDL_WINDOW_SHOWN, &fenetre,&rendu) ){
		printf("%sSDL_CreateWindowAndRenderer : %s.\n",MSG_E,SDL_GetError());
		status = E_AUTRE;
		goto Quit;
	}
	SDL_SetWindowTitle( fenetre , nomFont );
	printf("OK\n");
	SDL_Delay(1000);

	printf("Création du stylo...");
	if( !(stylo=creer_stylo( nomFont , 52 , couleur )) ){ // Pas d'objet stylo de créer :
		printf("Erreur à la création de stylo.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");
	SDL_Delay(1000);

	printf("Affichage du texte...");
	if( SDL_SetRenderDrawColor(rendu, 255,125,0,255) ){
		printf("%sSDL_SetRenderDrawColor : %s",MSG_E, SDL_GetError());
		status = E_COLOR;
		goto Quit;
	}
	if( SDL_RenderClear(rendu) ){
		printf("%sSDL_RenderClear : %s",MSG_E, SDL_GetError());
		status = E_AFFICHE;
		goto Quit;
	}
	if(( status=ecrire(rendu,stylo , texte , ancre , NULL) ))
		goto Quit;
	SDL_RenderPresent(rendu);
	printf("OK\n");
	SDL_Delay(1000);

	printf("Changement de la couleur du stylo...");
	if(( status=stylo->changerCouleur(stylo,(SDL_Color){0,0,0,255}) ))
		goto Quit;
	printf("OK\n");
	SDL_Delay(1000);

	printf("Ajout du nouveau texte...");
	ancre.point = (SDL_Point){tailleFenetre/2,2*tailleFenetre/3};
	if(( status=ecrire(rendu,stylo , texte , ancre , NULL) ))
		goto Quit;
	SDL_RenderPresent(rendu);
	printf("OK\n");
	SDL_Delay(1000);

	printf("Attente du signal de fermeture...");
	status = E_AUTRE;
	while( status ){
		while( SDL_PollEvent(&event) ){
			if( event.type == SDL_QUIT )
				status = E_OK;
		}
	}
	printf("OK\n");
	SDL_Delay(1000);

	// FIN DU PROGRAMME
Quit:		// Destruction des objets
	printf("Destruction de la fenêtre...");
	err = stylo->detruire( &stylo );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de stylo.\n");
		return(err);
	}
	if( rendu )
		SDL_DestroyRenderer(rendu);
	if( fenetre )
		SDL_DestroyWindow(fenetre);
	TTF_Quit();
	SDL_Quit();
	printf("OK\n");
	SDL_Delay(1000);
		// Affichage de fin
	afficherSurvivant_stylo();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet stylo. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

