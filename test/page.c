/**
	* \file test/page.c
	* \brief Test de l'objet page.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 23 Mars 2023 18:41:01
	*
	* L'objet page sert à afficher le contenu d'une page.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/page.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
int STOP = 0;
void imgG(SDL_Rect *rect){
	rectG->w = (dim.x/2) - MARGE_X;
	rectG->h = dim.y - MARGE_Y;
	rectG->x = MARGE_LIVRE_X;
	rectG->y = MARGE_LIVRE_Y;
}
void imgD(SDL_Rect *rect){
	rectD->w = (dim.x/2) - MARGE_X;
	rectD->h = dim.y - MARGE_Y;
	rectD->x = (dim.x/2);
	rectD->y = MARGE_LIVRE_Y;
}

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t quitter(int argc,...){
	printf("Quitter");
	STOP = 1;
	return E_OK;
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet page. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF|SDL_IMG , IMG_INIT_PNG ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	/* Création des autres variables */
	fenetre_t *fenetre = NULL;
	SDL_Renderer *rendu = NULL;
	img_t *img = NULL;
	police_t *police = NULL;
	SDL_Event event;
	SDL_Point curseur;
	SDL_Point pos;
	SDL_Point dim;
	SDL_Rect rectD;
	SDL_Rect rectG;

	// INSTRUCTION(S)
	printf("Création de l'objet fenetre...");
	if(!( fenetre=creer_fenetre(NULL,SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN,"test_fenetre") )){ // Pas d'objet fenetre de créer :
		MSG_ERR2("À la création de fenetre");
		status = E_AUTRE;
		goto Quit;
	}
	SDL_GetWindowSize( (fenetre->fenetre) , &(dim.x) , &(dim.y) );
	imgG(&rectG);
	imgD(&rectD);
	if(( err=rafraichir(fenetre) )){
		MSG_ERR2("du rafraichissement du contenu de la fenetre");
		status = err;
		goto Quit;
	}
	SDL_RenderPresent(obtenir_Renderer(fenetre));
	printf("OK\n");
	SDL_Delay(1000);

	printf("Ajout du contenu de la fenêtre...");
	// Ajout de l'image de fond
	rendu = obtenir_Renderer(fenetre);
	if(!( img=creer_img(rendu,"livreOuvert.png") )){ // Pas d'objet img de créer :
		MSG_ERR2("de la création de img");
		status = E_AUTRE;
		goto Quit;
	}
	if(( status=ajouterWidget(fenetre,img) )){
		printf("Erreur à l'ajout du bouton.\n");
		goto Quit;
	}
	// Création de la police
	if(!( police=creer_police(NULL,25,NULL) )){ // Pas d'objet police de créer :
		printf("Erreur à la création de police.\n");
		status = E_AUTRE;
		goto Quit;
	}
	// Ajout des boutons
	pos.x = dim.x / 2;
	pos.y = dim.y / 2;
	if(( status=placer(fenetre,police,"Quitter",&pos,&img) )){
		MSG_ERR2("du placement du texte sur la fenêtre");
		goto Quit;
	}
	if(( status=ajouterBouton(fenetre,img,quitter) )){
		MSG_ERR2("de l'ajout du bouton");
		goto Quit;
	}
	// Destruction de la police
	if(( status=police->detruire(&police) )){
		printf("Erreur à la destruction de police.\n");
		goto Quit;
	}
	// Ajout des images
	/*	Image de gauche	*/
	if(( status=placer(fenetre,NULL,"backPerso.jpeg",&pos,&img) )){
		MSG_ERR2("du placement du texte sur la fenêtre");
		goto Quit;
	}
	if(( err=changerDest(img,&rectG) )){
		MSG_ERR2("de la modification de img");
		return(err);
	}
	if(( status=ajouterWidget(fenetre,img) )){
		printf("Erreur à l'ajout du bouton.\n");
		goto Quit;
	}
	/*	Image de droite	*/
	if(( status=placer(fenetre,NULL,"fond.png",&pos,&img) )){
		MSG_ERR2("du placement du texte sur la fenêtre");
		goto Quit;
	}
	if(( err=changerDest(img,&rectD) )){
		MSG_ERR2("de la modification de img");
		return(err);
	}
	if(( status=ajouterWidget(fenetre,img) )){
		printf("Erreur à l'ajout du bouton.\n");
		goto Quit;
	}
	// Fin placement
	img = NULL;
	rendu = NULL;
	printf("OK\n");

	printf("Attente du signal d'arrêt...");
	status = E_AUTRE;
	while( !STOP ){
		while( SDL_PollEvent(&event) ){
			if( event.type == SDL_QUIT )
				STOP = 1;
			else if( (event.type==SDL_MOUSEBUTTONUP) ){
				obtenir_clique(&curseur);
				bouton_t *b = obtenir_boutonCliquer(fenetre, &curseur,NULL);
				if( b ){
					if(( err=b->action(0) )){
						MSG_ERR2("L'action d'un bouton");
						status = err;
						goto Quit;
					}
				}
			}
		}
		if(( err=rafraichir(fenetre) )){
			MSG_ERR2("du rafraichissement du contenu de la fenetre");
			status = err;
			goto Quit;
		}
		SDL_RenderPresent(obtenir_Renderer(fenetre));
	}
	printf("OK\n");

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=fenetre->detruire(&fenetre)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de fenetre");
		return(err);
	}
	fermer_SDL();
	/* Affichage de fin */
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet page. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

