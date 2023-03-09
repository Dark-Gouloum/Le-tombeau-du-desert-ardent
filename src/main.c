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
err_t start(){
	printf("Bouton \"Start\" cliqué !\n");
	return E_OK;
}
err_t options(){
	printf("Bouton \"Options\" cliqué !\n");
	return E_OK;
}
err_t quitter(){
	printf("Bouton \"Quitter\" cliqué !\n");
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
	err_t status=E_AUTRE;
	/* Création des autres variables */
		// Couleurs
	SDL_Color cEcriture = {255,255,255,255};
	SDL_Color cFond = {0,0,0,255};
		// Gestion du texte
	stylo_t *stylo = NULL;
		// Gestion de la fenetre
	fenetre_t *fenetre = NULL;
	SDL_Point *curseur = malloc( sizeof(SDL_Point) );
	SDL_Point dim = {500,500};
	SDL_Event event;
		// Gestions des widgets
	ancre_t ancre;
	ancre.point = (SDL_Point){100/2,(100/3)*2};
	ancre.angle = ANGLE_MILLIEU;

	// INSTRUCTION(S)
	printf("Création de la fenêtre...");
	if(!( fenetre=creer_fenetre(dim, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE, argv[0]) )){ // Pas d'objet fenetre de créer :
		printf("Erreur à la création de fenetre.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");

	printf("changer l'arrière plan de la fenêtre...");
	changerFond_couleur(fenetre , cFond);
	printf("OK\n");

	printf("Création du titre...");
	if( !(stylo=creer_stylo( NULL , 52 , cEcriture )) ){ // Pas d'objet stylo de créer :
		printf("Erreur à la création de stylo.\n");
		status = E_AUTRE;
		goto Quit;
	}
	{
		ancre.point = (SDL_Point){100/2,(100/3)};
		texte_t *texte = creer_texte( obtenir_Renderer(fenetre) , stylo , argv[0] , ancre );
		if( !texte ){
			status = E_AUTRE;
			goto Quit;
		}
		if(( status=ajouterWidget(fenetre,texte) ))
			goto Quit;
	}
	if(( status=stylo->detruire(&stylo) )){ // Echec à la destruction :
		printf("Erreur à la destruction de stylo.\n");
		goto Quit;
	}
	printf("OK\n");

	printf("Ajout des boutons...");
	if( !(stylo=creer_stylo( NULL , 20 , cEcriture )) ){ // Pas d'objet stylo de créer :
		printf("Erreur à la création de stylo.\n");
		status = E_AUTRE;
		goto Quit;
	}
	char *nom[] ={
		"Start",
		"Options",
		"Quitter"
	};
	err_t (*fonc[])(void) = {
		start,
		options,
		quitter
	};
	for( int i=0 ; i<3 ; i++ ){
		ancre.point = (SDL_Point){100/2,(100/6)*(i+3)};
		if(( status=ajouterBouton(fenetre,stylo,nom[i],ancre,fonc[i]) ))
			goto Quit;
	}
	if(( status=stylo->detruire(&stylo) )){ // Echec à la destruction :
		printf("Erreur à la destruction de stylo.\n");
		goto Quit;
	}
	printf("OK\n");

	while( !STOP ){
		while( SDL_PollEvent(&event) ){
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
		}
	}
	status = E_OK;

	// FIN DU PROGRAMME
Quit:
	free(curseur);
	if(( status = fenetre->detruire( &fenetre ) )){ // Echec à la destruction :
		printf("Erreur à la destruction de fenetre.\n");
		return(status);
	}
	fermer_SDL();
	/* Affichage de fin */
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU PROGRAMME\t\t\n\n");
	return(status);
} /* Programme qui lance le tombeau du desert ardent */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //
