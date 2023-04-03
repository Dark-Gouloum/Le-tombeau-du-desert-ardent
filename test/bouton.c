/**
	* \file test/bouton.c
	* \brief Test de l'objet bouton.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 09:56:52
	*
	* L'objet bouton sert à définir des boutons.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/bouton.h"
#include "../lib/img.h"
#include "../lib/police.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
#define tailleFenetre_X 500
#define tailleFenetre_Y 500

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t quitter(int argc,...){
	printf("Quitter");
	return E_OK;
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet bouton. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF|SDL_IMG , IMG_INIT_PNG ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	bouton_t *bouton = NULL;
	/* Création des autres variables */
	SDL_Window *fenetre = NULL;
	SDL_Renderer *rendu = NULL;
	police_t *police = NULL;
	SDL_Surface *surface = NULL;
	SDL_Rect rect;
	img_t *img = NULL;
	SDL_Event event;
	SDL_Color color = {255,255,255,255};

	// INSTRUCTION(S)
	printf("Création de divers objet utile...");
	if(!( police=creer_police(NULL,52,NULL) )){ // Pas d'objet police de créer :
		printf("Erreur à la création de police.\n");
		status = E_AUTRE;
		goto Quit;
	}
	if( SDL_CreateWindowAndRenderer(tailleFenetre_X,tailleFenetre_Y, SDL_WINDOW_SHOWN, &fenetre,&rendu) ){
		MSG_ERR_BASE("","SDL_CreateWindowAndRenderer",SDL_GetError());
		status = E_AUTRE;
		goto Quit;
	}
	SDL_SetWindowTitle( fenetre , "test_bouton" );
	printf("OK\n");

	printf("Écriture d'un texte...");
	if( (status=police_creerSurface_texte(&surface,police,"TEST",0)) ){
		MSG_ERR2("de la création de la surface du texte.");
		goto Quit;
	}
	printf("OK\n");

	printf("Création d'un objet img...");
	if(!( img=creer_img_ParSurface(rendu,&surface) )){ // Pas d'objet img de créer :
		MSG_ERR2("de la création de img");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");

	printf("Réccupération de la taille de l'objet...");
	if(( status=img_demandeTaille(img,&rect) )){
		MSG_ERR2("de la modification de img");
		goto Quit;
	}
	rect.x = tailleFenetre_X / 2;
	rect.y = tailleFenetre_Y / 2;
	if(( status=changerDest(img,&rect) )){
		MSG_ERR2("de la modification de img2");
		goto Quit;
	}
	printf("OK\n");

	printf("Création de l'objet bouton...");
	if(!( bouton=creer_bouton(rendu,img,quitter,&color) )){ // Pas d'objet bouton de créer :
		MSG_ERR2("À la création de bouton");
		status = E_AUTRE;
		goto Quit;
	}
	img = NULL;
	printf("OK\n");

	printf("Affichage de la fenêtre et attente du signal d'arrêt...");
	status = E_AUTRE;
	SDL_Point curseur;
	while( status ){
		while( SDL_PollEvent(&event) ){
			if( event.type == SDL_QUIT )
				status = quitter(0);
			else if( (event.type==SDL_MOUSEBUTTONUP) ){
				obtenir_clique(&curseur);
				if( hover(bouton->widget,&curseur) ){
					status = bouton->action(0);
				}
			}
		}
		if( SDL_SetRenderDrawColor(rendu, 255,125,0,255) ){
			MSG_ERR_BASE("","SDL_SetRenderDrawColor",SDL_GetError());
			status = E_COLOR;
			goto Quit;
		}
		if( SDL_RenderClear(rendu) ){
			MSG_ERR_BASE("","SDL_RenderClear",SDL_GetError());
			status = E_AFFICHE;
			goto Quit;
		}
		if(( err=bouton->dessiner(bouton) )){
			MSG_ERR2("Dessin de bouton");
			status = err;
			goto Quit;
		}
		SDL_RenderPresent(rendu);
	}
	printf("OK\n");

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=bouton->detruire(&bouton)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de bouton");
		return(err);
	}
	fermer_SDL();
	/* Affichage de fin */
	afficherSurvivant_bouton();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet bouton. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

