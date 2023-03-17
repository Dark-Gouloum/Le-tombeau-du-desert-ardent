/**
	* \file test/boite.c
	* \brief Test de l'objet boite.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 16 Mars 2023 13:15:38
	*
	* L'objet boite sert à encapsuler des widgets.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/boite.h"
#include "../lib/texte.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet boite. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de SDL */
	if( SDL_Init( SDL_INIT_VIDEO ) ){
		printf("ERREUR :  SDL_Init : %s", SDL_GetError());
		return E_INIT;
	}
	if( initialisation_SDL_TTF() )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	boite_t *boite = NULL;
	/* Création des autres variables */
	SDL_Window *fenetre = NULL;
	SDL_Renderer *rendu = NULL;
	stylo_t *stylo = NULL;
	texte_t *texte = NULL;
	char *txt[] = {
		"Hello World !"
		, "World Hello !"
		, "WrdHlo!"
		, "el ol "
	};
	SDL_Color couleur = {255,255,255,255};
	SDL_Event event;
	SDL_Point tailleFenetre = {1000,500};
	SDL_Point pos = { 10 , 10 };
	SDL_Point posCB = { pos.x , pos.y };

	// INSTRUCTION(S)
	printf("Création de la fenêtre...");
	if( SDL_CreateWindowAndRenderer(tailleFenetre.x,tailleFenetre.y, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE , &fenetre,&rendu) ){
		printf("%sSDL_CreateWindowAndRenderer : %s.\n",MSG_E,SDL_GetError());
		status = E_AUTRE;
		goto Quit;
	}
	SDL_SetWindowTitle( fenetre , "test_boite" );
	printf("OK\n");

	printf("Création du stylo...");
	if( !(stylo=creer_stylo( NULL , 52 , couleur )) ){ // Pas d'objet stylo de créer :
		printf("Erreur à la création de stylo.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");
	SDL_Delay(1000);

	printf("Création de l'objet boite...");
	if(!( boite=creer_boite(400,10) )){ // Pas d'objet boite de créer :
		printf("Erreur à la création de boite.\n");
		status = E_AUTRE;
		goto Quit;
	}
	boite->afficher( boite );
	printf("OK\n");
	SDL_Delay(1000);

	printf("Ajout des widgets à la boite...");
	for( int i=0 ; i<4 ; i++ ){
		if(!( texte=creer_texte(rendu,stylo,txt[i]) )){ // Pas d'objet texte de créer :
			printf("Erreur à la création de texte.\n");
			status = E_AUTRE;
			goto Quit;
		}
		printf("\n\t- ");
		texte->afficher( texte );
		printf("--> crée avec succés.");
		ajouter_widget_boite( boite , texte );
	}
	texte = NULL;
	printf("\n...OK\n");
	SDL_Delay(1000);

	printf("Affichage de la boite...");
	boite->afficher( boite );
	printf("\n");
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
	pos.x = posCB.x ; pos.y = posCB.x;
	if(( err=boite->dessiner(&pos,rendu , boite ) )){
		status = err;
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
				status = E_OK;
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
		pos.x = posCB.x ; pos.y = posCB.x;
		if(( err=boite->dessiner(&pos,rendu , boite ) )){
			status = err;
			goto Quit;
		}
		SDL_RenderPresent(rendu);
	}
	printf("OK\n");
	SDL_Delay(1000);

	status = E_OK;

	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if(( err=stylo->detruire( &stylo ) )){ // Echec à la destruction :
		printf("Erreur à la destruction de stylo.\n");
		return(err);
	}
	if(( err=boite->detruire( &boite ) )){ // Echec à la destruction :
		printf("Erreur à la destruction de boite.\n");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_boite();
	afficherSurvivant_texte();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet boite. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

