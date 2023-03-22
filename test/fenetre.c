/**
	* \file test/fenetre.c
	* \brief Test de l'objet fenetre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 12:25:01
	*
	* L'objet fenetre sert à gérer une fenêtre de base.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/fenetre.h"
#include "../lib/police.h"
#include "../lib/img.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int STOP = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t quitter(int argc,...){
	printf("Quitter");
	STOP = 1;
	return E_OK;
}
err_t fermer(int argc,...){
	printf("Fermer");
	STOP = 1;
	return E_OK;
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet fenetre. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF|SDL_IMG , IMG_INIT_PNG ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	fenetre_t *fenetre = NULL;
	/* Création des autres variables */
	SDL_Point dim;
	SDL_Rect rect;
	SDL_Renderer *rendu = NULL;
	SDL_Surface *surface = NULL;
	img_t *img = NULL;
	img_t *imgFond = NULL;
	police_t *police = NULL;
	SDL_Event event;
	SDL_Point curseur;

	// INSTRUCTION(S)
	printf("Création de l'objet fenetre...");
	if(!( fenetre=creer_fenetre(NULL,SDL_WINDOW_SHOWN,"test_fenetre") )){ // Pas d'objet fenetre de créer :
		MSG_ERR2("À la création de fenetre");
		status = E_AUTRE;
		goto Quit;
	}
	SDL_GetWindowSize( (fenetre->fenetre) , &(dim.x) , &(dim.y) );
	if(( err=rafraichir(fenetre) )){
		MSG_ERR2("du rafraichissement du contenu de la fenetre");
		status = err;
		goto Quit;
	}
	SDL_RenderPresent(obtenir_Renderer(fenetre));
	printf("OK\n");
	SDL_Delay(1000);

	printf("Ajout du contenu de la fenêtre...");
	rendu = obtenir_Renderer(fenetre);
	if(!( imgFond=creer_img(rendu,"fond.png") )){ // Pas d'objet img de créer :
		MSG_ERR2("de la création de img");
		status = E_AUTRE;
		goto Quit;
	}
	if(( status=ajouterWidget(fenetre,imgFond) )){
		printf("Erreur à l'ajout du bouton.\n");
		goto Quit;
	}

	if(!( police=creer_police(NULL,25,NULL) )){ // Pas d'objet police de créer :
		printf("Erreur à la création de police.\n");
		status = E_AUTRE;
		goto Quit;
	}
	if( (status=police_creerSurface_texte(&surface,police,"Quitter")) ){
		MSG_ERR2("de la création de la surface du texte.");
		goto Quit;
	}
	if(!( img=creer_img_ParSurface(rendu,&surface) )){ // Pas d'objet img de créer :
		MSG_ERR2("de la création de img");
		status = E_AUTRE;
		goto Quit;
	}
	if(( status=img_demandeTaille(img,&rect) )){
		MSG_ERR2("de la modification de img");
		goto Quit;
	}
	rect.x = dim.x / 2;
	rect.y = 3*(dim.y / 6);
	if(( status=changerDest(img,&rect) )){
		MSG_ERR2("de la modification de img2");
		goto Quit;
	}
	if(( status=ajouterBouton(fenetre,img,quitter) )){
		printf("Erreur à l'ajout du bouton.\n");
		goto Quit;
	}

	if( (status=police_creerSurface_texte(&surface,police,"Fermer")) ){
		MSG_ERR2("de la création de la surface du texte.");
		goto Quit;
	}
	if(!( img=creer_img_ParSurface(rendu,&surface) )){ // Pas d'objet img de créer :
		MSG_ERR2("de la création de img");
		status = E_AUTRE;
		goto Quit;
	}
	if(( status=img_demandeTaille(img,&rect) )){
		MSG_ERR2("de la modification de img");
		goto Quit;
	}
	rect.x = dim.x / 2;
	rect.y = 4*(dim.y / 6);
	if(( status=changerDest(img,&rect) )){
		MSG_ERR2("de la modification de img2");
		goto Quit;
	}
	if(( status=ajouterBouton(fenetre,img,fermer) )){
		printf("Erreur à l'ajout du bouton.\n");
		goto Quit;
	}

	if( (status=police_creerSurface_texte(&surface,police,"TEST")) ){
		MSG_ERR2("de la création de la surface du texte.");
		goto Quit;
	}
	if(!( img=creer_img_ParSurface(rendu,&surface) )){ // Pas d'objet img de créer :
		MSG_ERR2("de la création de img");
		status = E_AUTRE;
		goto Quit;
	}
	if(( status=img_demandeTaille(img,&rect) )){
		MSG_ERR2("de la modification de img");
		goto Quit;
	}
	rect.x = dim.x / 2;
	rect.y = (dim.y / 6);
	if(( status=changerDest(img,&rect) )){
		MSG_ERR2("de la modification de img2");
		goto Quit;
	}
	if(( status=ajouterWidget(fenetre,img) )){
		printf("Erreur à l'ajout du bouton.\n");
		goto Quit;
	}

	if(( status=police->detruire(&police) )){
		printf("Erreur à la destruction de police.\n");
		goto Quit;
	}

	img = NULL;
	rendu = NULL;
	printf("OK\n");

	printf("Affichage de la fenêtre...");
	if(( err=rafraichir(fenetre) )){
		MSG_ERR2("du rafraichissement du contenu de la fenetre");
		status = err;
		goto Quit;
	}
	SDL_RenderPresent(obtenir_Renderer(fenetre));
	printf("OK\n");
	SDL_Delay(1000);

	printf("Modification de la taille de l'image de fond...");
	if(( status=img_demandeTaille(imgFond,&rect) )){
		MSG_ERR2("de la modification de img");
		goto Quit;
	}
	rect.w = dim.x;
	rect.h = dim.y;
	if(( status=changerDest(imgFond,&rect) )){
		MSG_ERR2("de la modification de img2");
		goto Quit;
	}
	printf("OK\n");
	SDL_Delay(1000);

	printf("Attente du signal d'arrêt...");
	status = E_AUTRE;
	int tour = 0;
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
		if( tour == 1000 ){
			printf("Modification de la taille de l'image de fond...");
			if(( status=img_demandeTaille(imgFond,&rect) )){
				MSG_ERR2("de la modification de img");
				goto Quit;
			}
			rect.w/= 2;
			rect.h/= 2;
			if(( status=changerDest(imgFond,&rect) )){
				MSG_ERR2("de la modification de img2");
				goto Quit;
			}
			printf("OK\n");
			SDL_Delay(1000);
			tour = 0;
		}
		SDL_RenderPresent(obtenir_Renderer(fenetre));
		tour++;
	}
	printf("OK\n");

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=fenetre->detruire(&fenetre)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de fenetre");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet fenetre. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

