/**
	* \file test/fenetre.c
	* \brief Test de l'objet fenetre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mer. 15 Févr. 2023 14:30:07
	*
	* L'objet fenetre sert à crée et gére une fenêtre.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/fenetre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int STOP = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
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
/* Programme qui test l'objet fenetre. */
int main(int argc, char *argv[]) {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF ) )
		return E_INIT;
	/* Création des variables d'états */
	char *nomFont="Roboto/Roboto-Thin.ttf";
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	fenetre_t *fenetre = NULL;
	/* Création des autres variables */
	stylo_t *stylo = NULL;
	SDL_Point *curseur = malloc( sizeof(SDL_Point) );
	SDL_Point dim = {500,500};
	SDL_Color couleur = {255,255,255,255};
	SDL_Color fond = {255,125,60,255};
	SDL_Event event;

	// INSTRUCTION(S)
	printf("Création de la fenêtre...");
	if(!( fenetre=creer_fenetre(dim, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, argv[0]) )){ // Pas d'objet fenetre de créer :
		printf("Erreur à la création de fenetre.\n");
		status = E_AUTRE;
		goto Quit;
	}
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

	printf("changer la couleur d'arrière plan de la fenêtre...");
	changerFond_couleur(fenetre , &fond);
	SDL_RenderPresent(obtenir_Renderer(fenetre));
	printf("OK\n");
	SDL_Delay(1000);

	printf("Ajout de boutons à la fenêtre...");
	ajouterBouton(
			fenetre,
			creer_bouton(obtenir_Renderer(fenetre),stylo,"Fermer !",(SDL_Point){(dim.x)/2,2*(dim.y)/3},ANGLE_MILLIEU,quitter1)
		);
	ajouterBouton(
			fenetre,
			creer_bouton(obtenir_Renderer(fenetre),stylo,"Quitter !",(SDL_Point){(dim.x)/2,(dim.y)/3},ANGLE_MILLIEU,quitter2)
		);
	SDL_RenderPresent(obtenir_Renderer(fenetre));
	printf("OK\n");
	SDL_Delay(1000);

	printf("affichage du contenu de la fenêtre...");
	fenetre->afficher( fenetre );
	printf("OK\n");
	SDL_Delay(1000);

	printf("Attente du signal de fermeture...");
	status = E_AUTRE;
	while( !STOP ){ while( SDL_PollEvent(&event) ){
		switch( event.type ){
			case SDL_QUIT :
				STOP = 1;
				break;
			case SDL_MOUSEBUTTONUP :
				obtenir_souris(curseur);
				bouton_t *bouton = obtenir_boutonCliquer( fenetre , curseur );
				if( bouton ){
					bouton->afficher( bouton );
					bouton->action();
				}
				break;
		}
	} }
	printf("OK\n");
	SDL_Delay(1000);
	status = E_OK;

	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	free(curseur);
	err = stylo->detruire( &stylo );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de stylo.\n");
		return(err);
	}
	err = fenetre->detruire( &fenetre );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de fenetre.\n");
		return(err);
	}
	fermer_SDL();
	/* Affichage de fin */
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
/* Programme qui test l'objet fenetre. */
// PROGRAMME PRINCIPALE
//
//
// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
//
//

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

