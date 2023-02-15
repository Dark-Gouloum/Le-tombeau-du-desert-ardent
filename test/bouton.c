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
typedef enum clique_s {
	CLIQUE_Erreur = 0, //!< Bouton inconnnu
	CLIQUE_Gauche, //!< Bouton gauche
	CLIQUE_Mollette, //!< Bouton centrale
	CLIQUE_Droit //!< Bouton droit
} clique_t;

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t quitter(){
	printf("Quitter");
	return E_OK;
}
clique_t obtenir_posSouris( SDL_Point *point){
	Uint32 b = SDL_GetMouseState(&(point->x),&(point->y));
	if( b & SDL_BUTTON(1) )
		return CLIQUE_Gauche;
	if( b & SDL_BUTTON(2) )
		return CLIQUE_Mollette;
	if( b & SDL_BUTTON(3) )
		return CLIQUE_Droit;
	return CLIQUE_Erreur;
}

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
	char *nomFont="Roboto/Roboto-Thin.ttf" , *texte="Quitter !";
	err_t err=E_AUTRE , status=E_AUTRE;
	int tailleFenetre = 500;
		// Création des autres variables
	SDL_Window *fenetre = NULL;
	SDL_Renderer *rendu = NULL;
	stylo_t *stylo = NULL;
	SDL_Color couleur = {255,255,255,255};
	SDL_Event event;
	SDL_Point curseur;
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
	printf("OK\n");
	SDL_Delay(1000);

	printf("Création du bouton...");
	if(!( bouton=creer_bouton(rendu, stylo, texte, (SDL_Point){tailleFenetre/2,tailleFenetre/2},ANGLE_MILLIEU, quitter) )){ // Pas d'objet bouton de créer :
		printf("Erreur à la création de bouton.\n");
		status = E_AUTRE;
		goto Quit;
	}
	SDL_RenderPresent(rendu);
	printf("OK\n");
	SDL_Delay(1000);

	printf("Attente du signal de fermeture...");
	status = E_AUTRE;
	while( status ){
		while( SDL_PollEvent(&event) ){
			if( event.type == SDL_QUIT )
				status = quitter();
			else if( (event.type==SDL_MOUSEBUTTONUP) ){
				obtenir_posSouris(&curseur);
				if( bouton->estCliquer(bouton,&curseur) ){
					status = bouton->action();
				}
			}
		}
	}
	printf("OK\n");
	SDL_Delay(1000);

	// FIN DU PROGRAMME
Quit:		// Destruction des objets
	err = stylo->detruire( &stylo );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de stylo.\n");
		return(err);
	}
	if( rendu )
		SDL_DestroyRenderer(rendu);
	if( fenetre )
		SDL_DestroyWindow(fenetre);
	err = bouton->detruire( &bouton );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de bouton.\n");
		return(err);
	}
	TTF_Quit();
	SDL_Quit();
		// Affichage de fin
	afficherSurvivant_bouton();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(E_OK);
}
	/* Programme qui test l'objet bouton. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

