/**
	* \file test/blocText.c
	* \brief Test de l'objet blocText.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 03 Avril 2023 20:43:50
	*
	* L'objet blocText sert à afficher du texte dans un bloc donnée.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/blocText.h"
#include "../lib/page.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
#define FICHIER_TEST "Annexe/text/test.txt"
#define SEPX 20
#define SEPY 20
int STOP = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t quitter(int argc,...){
	printf("%s",__func__);
	STOP = 1;
	return E_OK;
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet blocText. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF|SDL_IMG , IMG_INIT_PNG ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	blocText_t *texte = NULL;
	/* Création des autres variables */
	fenetre_t *fenetre = NULL;
	// SDL_Color stylo = {92,75,43,255};
	SDL_Color stylo = {255,255,255,255};
	SDL_Point pos;
	SDL_Point curseur;
	SDL_Event event;

	// INSTRUCTION(S)
	if(( err=creer_page(SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN,"test_texte","livreOuvertPlacement.png",&fenetre,&pos) )){ // Pas d'objet fenetre de créer :
		MSG_ERR2("de la création de la fenetre");
		goto Quit;
	}

	printf("Ajout du contenu de la fenêtre...\n");
	{ // Création du bouton de fermeture
		// Variables
		police_t *police = NULL;
		img_t *bouton = NULL;
		{ // Création de la police d'écriture
			if(!( police=creer_police(NULL,25,NULL) )){ // Pas d'objet police de créer :
				printf("Erreur à la création de police.\n");
				err = E_AUTRE;
				goto Quit;
			}
		}
		{ // Création du bouton de fermeture
			printf("\t\tCréation du bouton de fermeture\n");
			// Calcul de la position
			pos.y = 2 * ( (fenetre->dim).y / 4 );
			pos.x = 2 * ( (fenetre->dim).x / 4 );
			// Placage du texte
			if(( err=placer(fenetre,police,"Quitter",&pos,&bouton) )){
				MSG_ERR2("du placement du texte sur la fenêtre");
				goto Quit;
			}
			// Activation
			if(( err=ajouterBouton(fenetre,bouton,quitter,NULL) )){
				MSG_ERR2("de l'ajout du bouton");
				goto Quit;
			}
		}
		{ // Destruction de la police d'écriture
			if(( err=police->detruire(&police) )){
				printf("Erreur à la destruction de police.\n");
				goto Quit;
			}
		}
	}
	{ // Création du texte
		police_t *police = NULL;
		SDL_Rect rect;
		{ // rectangle limitant la taille du texte
			SDL_Point *dim = &( fenetre->dim );
			rect.h = ( (dim->y) * 765 ) / 1000;
			rect.w = ( (dim->x) * 311 ) / 1000;
			rect.x = ( (dim->x) * 171 ) / 1000;
			rect.y = ( (dim->y) * 125 ) / 1000;
			// Réduction
			int r = 20;
			( rect.h )-= r;
			( rect.w )-= r;
			( rect.x )+= r / 2;
			( rect.y )+= r / 2;
		}
		{ // Création de la police d'écriture
			police=creer_police(NULL,30,&stylo);
			if( !police ){
				MSG_ERR2("de la création de la police d'écriture");
				err = E_AUTRE;
				goto Quit;
			}
		}
		{ // Gestion du texte
			if(!( texte=creer_blocText(fenetre,"test.txt",&rect,&police,NULL) )){
				MSG_ERR2("de la création du fichier");
				return(E_AUTRE);
			}
			if(( err=ajouterWidget(fenetre,texte) )){
				MSG_ERR2("de l'ajout de img à la fenêtre");
				goto Quit;
			}
		}
	}

	printf("Attente du signal d'arrêt...\n");
	err = E_AUTRE;
	int etat = B_CONT;
	int numBouton = 0;
	while( !STOP ){
		while( SDL_PollEvent(&event) ){
			if( event.type == SDL_QUIT )
				STOP = 1;
			else if( (event.type==SDL_MOUSEBUTTONUP) ){
				obtenir_clique(&curseur);
				bouton_t *b = obtenir_boutonCliquer(fenetre, &curseur,&numBouton);
				if( b ){
					if( b == (texte->prec) ){ // Si bouton precedant
						if(( err=b->action(2,texte,&etat) )){
							MSG_ERR2("de l'affichage de l'ancien texte");
							goto Quit;
						}
						if( etat == B_FIN ){
							if(( err=bouton_cacher(texte->prec) )){
								MSG_ERR2("du masquage du bouton precedant");
								goto Quit;
							}
						}
						if(( err=bouton_montrer(texte->suiv) )){
							MSG_ERR2("du dé-masquage du bouton suivant");
							goto Quit;
						}
					} else if( b == (texte->suiv) ){ // Si bouton suivant
						if(( err=b->action(2,texte,&etat) )){
							MSG_ERR2("de l'affichage du nouveau texte");
							goto Quit;
						}
						if( etat == B_FIN ){ // Si le texte à atteint la fin
							if(( err=bouton_cacher(texte->suiv) )){
								MSG_ERR2("du masquage du bouton suivant");
								goto Quit;
							}
						} else if( etat == B_CONT ){
							if(( err=bouton_montrer(texte->prec) )){
								MSG_ERR2("du dé-masquage du bouton precedant");
								goto Quit;
							}
						}
					} else { // Tous les autres boutons
						if(( err=b->action(0) )){
							MSG_ERR2("de la fermeture du programme");
							goto Quit;
						}
					}
				}
			}
		}
		if(( err=rafraichir(fenetre) )){
			MSG_ERR2("du rafraichissement du contenu de la fenetre");
			goto Quit;
		}
		SDL_RenderPresent(obtenir_Renderer(fenetre));
	}
	printf("OK\n");

	err = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=texte->detruire(&texte)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de blocText");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_blocText();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(err);
}
	/* Programme qui test l'objet blocText. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

