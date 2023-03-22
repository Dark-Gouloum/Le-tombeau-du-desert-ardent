/**
	* \file test/son.c
	* \brief Test de l'objet son.
	* \author Victor FOUQUERAY
	* \version 0.1
	* \date Mer. 22 Mars 2023 21:24:01
	*
	* L'objet son sert à gérer les sons et les musiques du jeu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/son.h"
#include "../lib/fenetre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
#define WAVES_SOUND "waves-at-baltic-sea-shore.wav"
#define CLAP_SOUND              "clap.ogg"
#define SNARE_SOUND             "snare.ogg"
#define TECHNO_CLAP_SNARE_SOUND "techno-clap-snare.ogg"
#define REVERB_SNARE_SOUND      "dubstep-reverb-snare.ogg"

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet son. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF|SDL_IMG|SDL_MIX , IMG_INIT_PNG ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	son_t *bandeSonore = NULL;
	son_t *clapnsnap1 = NULL;
	son_t *clapnsnap2 = NULL;
	son_t *clapnsnap3 = NULL;
	son_t *clapnsnap4 = NULL;
	/* Création des autres variables */
	fenetre_t *fenetre = NULL;
	SDL_Event event;

	// INSTRUCTION(S)
	printf("Création de l'objet fenetre...");
	if(!( fenetre=creer_fenetre(NULL,SDL_WINDOW_SHOWN,"test_son") )){ // Pas d'objet fenetre de créer :
		MSG_ERR2("À la création de fenetre");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");

	printf("Création de la bande sonore...");
	if(!( bandeSonore=creer_son(SON_MUSIQUE,WAVES_SOUND) )){ // Pas d'objet son de créer :
		MSG_ERR2("À la création de la bande sonore");
		status = E_AUTRE;
		goto Quit;
	}
	bandeSonore->afficher( bandeSonore );
	printf("OK\n");

	printf("Création des autres sons...");
	if(!( clapnsnap1=creer_son(SON_EFFET,CLAP_SOUND) )){ // Pas d'objet son de créer :
		MSG_ERR2("À la création d'un clapnsnap");
		status = E_AUTRE;
		goto Quit;
	}
	printf("\n\t- ");
	clapnsnap1->afficher( clapnsnap1 );
	if(!( clapnsnap2=creer_son(SON_EFFET,SNARE_SOUND) )){ // Pas d'objet son de créer :
		MSG_ERR2("À la création d'un clapnsnap");
		status = E_AUTRE;
		goto Quit;
	}
	printf("\n\t- ");
	clapnsnap2->afficher( clapnsnap2 );
	if(!( clapnsnap3=creer_son(SON_EFFET,TECHNO_CLAP_SNARE_SOUND) )){ // Pas d'objet son de créer :
		MSG_ERR2("À la création d'un clapnsnap");
		status = E_AUTRE;
		goto Quit;
	}
	printf("\n\t- ");
	clapnsnap3->afficher( clapnsnap3 );
	if(!( clapnsnap4=creer_son(SON_EFFET,REVERB_SNARE_SOUND) )){ // Pas d'objet son de créer :
		MSG_ERR2("À la création d'un clapnsnap");
		status = E_AUTRE;
		goto Quit;
	}
	printf("\n\t- ");
	clapnsnap4->afficher( clapnsnap4 );
	printf("\n--> OK\n");

	printf("Lancement de la musique...");
	if(( status=lancer_son(bandeSonore,-1) )){
		MSG_ERR(E_SON,"Le son waves ne peut pas être joué");
		goto Quit;
	}
	printf("OK\n");

	printf("attente des évenements...");
	int quit = 0;
	while(!quit){
		SDL_WaitEvent(&event);
		switch( event.type ){
			case SDL_QUIT :
				quit = 1;
				break;
			case SDL_KEYDOWN :
				switch( event.key.keysym.sym ){
					case SDLK_SPACE :
						startPause();
						break;
					case SDLK_RIGHT :
						if(( status=lancer_son(clapnsnap1,0) )){
							MSG_ERR2("Problème à la lecture du son 1");
							goto Quit;
						}
						break;
					case SDLK_LEFT :
						if(( status=lancer_son(clapnsnap2,0) )){
							MSG_ERR2("Problème à la lecture du son 2");
							goto Quit;
						}
						break;
					case SDLK_UP :
						if(( status=lancer_son(clapnsnap3,0) )){
							MSG_ERR2("Problème à la lecture du son 3");
							goto Quit;
						}
						break;
					case SDLK_DOWN :
						if(( status=lancer_son(clapnsnap4,0) )){
							MSG_ERR2("Problème à la lecture du son 4");
							goto Quit;
						}
						break;
				}
				break;
		}
	}
	printf("OK\n");

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=bandeSonore->detruire(&bandeSonore)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de la bande sonore");
		return(err);
	}
	if( (err=clapnsnap1->detruire(&clapnsnap1)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de son 1");
		return(err);
	}
	if( (err=clapnsnap2->detruire(&clapnsnap2)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de son 2");
		return(err);
	}
	if( (err=clapnsnap3->detruire(&clapnsnap3)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de son 3");
		return(err);
	}
	if( (err=clapnsnap4->detruire(&clapnsnap4)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de son 4");
		return(err);
	}
	if( (err=fenetre->detruire(&fenetre)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de fenetre");
		return(err);
	}
	fermer_SDL();
	/* Affichage de fin */
	afficherSurvivant_son();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet son. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

