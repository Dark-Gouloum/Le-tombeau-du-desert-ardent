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
#include <assert.h>

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/fenetre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int STOP = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t quitter1(int argc,...){
	printf("bouton 1\n");
	STOP = 1;
	return E_OK;
}
err_t quitter2(int argc,...){
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
	err_t status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	fenetre_t *fenetre = NULL;
	/* Création des autres variables */
		// Couleurs
	SDL_Color couleur = {255,255,255,255};
	SDL_Color fond = {255,125,60,255};
		// Gestion du texte
	stylo_t *stylo = NULL;
		// Gestion de la fenetre
	SDL_Point curseur;
	SDL_Point dim = {500,500};
	SDL_Event event;
		// Gestions des widgets
	ancre_t *ancre;

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
	if( !(stylo=creer_stylo( NULL , 52 , couleur )) ){ // Pas d'objet stylo de créer :
		printf("Erreur à la création de stylo.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");

	printf("Création de l'ancre...");
	if(!( ancre=creer_ancre(1/2,0,ANGLE_MILLIEU) )){
		printf("Erreur à la création de fenetre.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");
	SDL_Delay(1000);

	printf("changer la couleur d'arrière plan de la fenêtre...");
	changerFond_couleur(fenetre , fond);
	printf("OK\n");
	SDL_Delay(1000);

	printf("Ajout de boutons à la fenêtre...");
	ancre->changerY( ancre , 1/3 );
	if(( status=ajouterBouton(fenetre , stylo , "Fermer !" , ancre , quitter1) )){ // Pas d'objet stylo de créer :
		printf("Erreur à l'ajout du premier bouton.\n");
		goto Quit;
	}
	ancre->changerY( ancre , 2/3 );
	if(( status=ajouterBouton(fenetre , stylo , "Quitter !" , ancre , quitter2) )){ // Pas d'objet stylo de créer :
		printf("Erreur à l'ajout du deuxième bouton.\n");
		goto Quit;
	}
	if(( status=rafraichir( fenetre ) ))
		goto Quit;
	SDL_RenderPresent(obtenir_Renderer(fenetre));
	printf("OK\n");
	SDL_Delay(1000);

	printf("affichage du contenu de la fenêtre...");
	fenetre->afficher( fenetre );
	printf("OK\n");
	SDL_Delay(1000);

	printf("Attente du signal de fermeture...");
	status = E_AUTRE;
	while( !STOP ){
		while( SDL_PollEvent(&event) ){
			switch( event.type ){
				case SDL_QUIT :
					STOP = 1;
					break;
				case SDL_MOUSEBUTTONUP :
					obtenir_souris(&curseur);
					bouton_t *bouton = obtenir_boutonCliquer( fenetre , &curseur );
					if( bouton ){
						bouton->afficher( bouton );
						bouton->action(0);
					}
					break;
			}
		}
		if(( status=rafraichir(fenetre) ))
			goto Quit;
		SDL_RenderPresent(obtenir_Renderer(fenetre));
	}
	printf("OK\n");
	SDL_Delay(1000);
	status = E_OK;

	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if(( status = fenetre->detruire( &fenetre ) )){ // Echec à la destruction :
		printf("Erreur à la destruction de fenetre.\n");
		return(status);
	}
	if(( status = stylo->detruire( &stylo ) )){ // Echec à la destruction :
		printf("Erreur à la destruction de stylo.\n");
		return(status);
	}
	if(( status = ancre->detruire( &ancre ) )){ // Echec à la destruction :
		printf("Erreur à la destruction de l'ancre.\n");
		return(status);
	}
	fermer_SDL();
	/* Affichage de fin */
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
/* Programme qui test l'objet fenetre. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

