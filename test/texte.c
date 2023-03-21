/**
	* \file test/texte.c
	* \brief Test de l'objet texte.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 28 Févr. 2023 14:40:03
	*
	* L'objet texte sert à ecrire du texte sur la fenêtre.
	*
	*/
#include <assert.h>

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/texte.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet texte. */
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
	texte_t *texte = NULL;
	/* Création des autres variables */
	SDL_Window *fenetre = NULL;
	SDL_Renderer *rendu = NULL;
	stylo_t *stylo = NULL;
	char *txt="Hello World !";
	SDL_Color couleur = {255,255,255,255};
	SDL_Event event;
	SDL_Point tailleFenetre = {500,500};
	ancre_t *ancre;

	/* Création des autres variables */
	// INSTRUCTION(S)
	printf("Création de la fenêtre...");
	if( SDL_CreateWindowAndRenderer(tailleFenetre.x,tailleFenetre.y, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE , &fenetre,&rendu) ){
		printf("%sSDL_CreateWindowAndRenderer : %s.\n",MSG_E,SDL_GetError());
		status = E_AUTRE;
		goto Quit;
	}
	SDL_SetWindowTitle( fenetre , "test_stylo" );
	printf("OK\n");
	SDL_Delay(1000);

	printf("Création du stylo...");
	if( !(stylo=creer_stylo( NULL , 52 , couleur )) ){ // Pas d'objet stylo de créer :
		printf("Erreur à la création de stylo.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");

	printf("Création de l'ancre...");
	if(!( ancre=creer_ancre(1/2,1/2,ANGLE_MILLIEU) )){
		printf("Erreur à la création de fenetre.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");
	SDL_Delay(1000);

	printf("Création de l'objet texte...");
	if(!( texte=creer_texte(rendu,stylo,txt,ancre) )){ // Pas d'objet texte de créer :
		printf("Erreur à la création de texte.\n");
		status = E_AUTRE;
		goto Quit;
	}
	assert(0);
	texte->afficher( texte );
	printf("OK\n");

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
	{
		SDL_Color fond = {0,0,0,255};
		surligner_texte( texte , &fond );
	}
<<<<<<< HEAD
	pos.x=posCB.x	;	pos.y=posCB.y	;
	if(( status=texte->dessiner(&pos,tailleFenetre,rendu , texte ) ))
=======
	if(( status=texte->dessiner(tailleFenetre,rendu , texte ) ))
>>>>>>> 86c5c32686adae633507db21029db666f9184160
		goto Quit;
	surligner_texte( texte , NULL );
	SDL_RenderPresent(rendu);
	printf("OK\n");
	SDL_Delay(1000);

	printf("Changement de la couleur du stylo...");
	if(( status=stylo->changerCouleur(stylo,(SDL_Color){0,0,0,255}) ))
		goto Quit;
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
	if(( status=texte->changerStylo( rendu , stylo , texte ) ))
		goto Quit;
<<<<<<< HEAD
	pos.x=posCB.x	;	pos.y=posCB.y	;
	if(( status=texte->dessiner(&pos,tailleFenetre,rendu , texte ) ))
=======
	if(( status=texte->dessiner(tailleFenetre,rendu , texte ) ))
>>>>>>> 86c5c32686adae633507db21029db666f9184160
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
		SDL_GetWindowSize( fenetre , &(tailleFenetre.x) , &(tailleFenetre.y) );
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
<<<<<<< HEAD
		pos.x=posCB.x	;	pos.y=posCB.y	;
		if(( err=texte->dessiner(&pos,tailleFenetre,rendu , texte ) )){
=======
		if(( err=texte->dessiner(tailleFenetre,rendu , texte ) )){
>>>>>>> 86c5c32686adae633507db21029db666f9184160
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
	err = texte->detruire( &texte );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de texte.\n");
		return(err);
	}
	if(( status = ancre->detruire( &ancre ) )){ // Echec à la destruction :
		printf("Erreur à la destruction de l'ancre.\n");
		return(status);
	}
	if(( err=stylo->detruire( &stylo ) )){ // Echec à la destruction :
		printf("Erreur à la destruction de stylo.\n");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_texte();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet texte. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

