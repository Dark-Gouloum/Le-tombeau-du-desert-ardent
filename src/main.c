/**
  * \file main.c
  * \brief Le fichier source du produit final
  * \author Clement FEFEU ; Victor FOUQUERAY ; Dylan GRAMMONT ; Erwan PECHON
  * \version 0.1
  * \date Ven. 27 Janv. 2023 14:27:35
  *
  * Le fichier source du jeu 'Le tombeau du désert ardent'.
  * Aller voir le README.md pour plus de détaille.
  *
  */

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../lib/err.h"
#include "../lib/fenetre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned STOP = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t initialisationSDL(){
	if( SDL_Init( SDL_INIT_VIDEO ) ){
		printf("ERREUR :  SDL_Init : %s", SDL_GetError());
		return E_AUTRE;
	}
	return E_OK;
}
err_t quitter1(){
	printf("bouton 1\n");
	STOP = 1;
	return E_OK;
}
err_t quitter2(){
	printf("bouton 2\n");
	STOP = 1;
	return E_OK;
}

// PROGRAMME PRINCIPALE
int main(int argc, char *argv[]){  /* Programme qui lance le tombeau du desert ardent */
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF ) )
		return E_INIT;
	/* Création des variables d'états */
	char *nomFont="Roboto/Roboto-Thin.ttf";
	err_t err=E_AUTRE, status=E_AUTRE;
		// Création des autres variables
	fenetre_t *fenetre = NULL;
	stylo_t *stylo = NULL;
	SDL_Point *curseur = malloc( sizeof(SDL_Point) );
	SDL_Point dim = {500,500};
	SDL_Color cEcriture = {255,255,255,255};
	SDL_Color cFond = {255,125,60,255};
	SDL_Event event;

	// INSTRUCTION(S)
	printf("Création de la fenêtre...");
	if(!( fenetre=creer_fenetre(dim, SDL_WINDOW_SHOWN, argv[0]) )){ // Pas d'objet fenetre de créer :
		printf("Erreur à la création de fenetre.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");
	printf("changer la couleur d'arrière plan de la fenêtre...");
	changerFond_couleur(fenetre , &cFond);
	printf("OK\n");
	printf("Création du titre...");
	if( !(stylo=creer_stylo( nomFont , 52 , cEcriture )) ){ // Pas d'objet stylo de créer :
		printf("Erreur à la création de stylo.\n");
		status = E_AUTRE;
		goto Quit;
	}
	if(( status=ecrire(obtenir_Renderer(fenetre),stylo , argv[0] , (SDL_Point){dim.x/2,dim.y/2},ANGLE_MILLIEU , NULL) ))
		goto Quit;
	if(( err=stylo->detruire(&stylo) )){ // Echec à la destruction :
		printf("Erreur à la destruction de stylo.\n");
		status = err;
		goto Quit;
	}
	printf("OK\n");
	printf("Ajout des boutons...");
	if( !(stylo=creer_stylo( nomFont , 20 , cEcriture )) ){ // Pas d'objet stylo de créer :
		printf("Erreur à la création de stylo.\n");
		status = E_AUTRE;
		goto Quit;
	}
	char *nom[] ={
		"Quitter",
		"Fermer"
	};
	err_t (*fonc[])(void) = {
		quitter1,
		quitter2,
	};
	for( int i=0 ; i<2 ; i++ ){
		SDL_Point p = { (dim.x)/2 , (i+4)*(dim.y)/6 };
		ajouterBouton( fenetre , creer_bouton(obtenir_Renderer(fenetre),stylo,nom[i],p,ANGLE_MILLIEU,fonc[i]) );
	}
	if(( err=stylo->detruire(&stylo) )){ // Echec à la destruction :
		printf("Erreur à la destruction de stylo.\n");
		status = err;
		goto Quit;
	}
	printf("OK\n");
	while( !STOP ){ while( SDL_PollEvent(&event) ){
		switch( event.type ){
			case SDL_QUIT :
				STOP = 1;
				break;
			case SDL_MOUSEBUTTONUP :
				obtenir_souris(curseur);
				bouton_t *bouton = obtenir_boutonCliquer( fenetre , curseur );
				if( bouton ){
					status = bouton->action();
				}
				break;
		}
	} }
	status = E_OK;

	// FIN DU PROGRAMME
Quit:
	free(curseur);
	err = fenetre->detruire( &fenetre );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de fenetre.\n");
		return(err);
	}
	fermer_SDL();
	/* Affichage de fin */
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU PROGRAMME\t\t\n\n");
	return(status);
} /* Programme qui lance le tombeau du desert ardent */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //
