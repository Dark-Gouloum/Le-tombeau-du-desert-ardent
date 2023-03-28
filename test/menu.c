/**
	* \file test/menu.c
	* \brief Test de l'objet menu.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 14:21:44
	*
	* L'objet menu sert à créer un menu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/menu.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int STOP = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t cliquer(int argc,...){
	char *txt = NULL;
	if( argc < 1 ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas assez d'arguments");
		return(E_ARGUMENT);
	} else {
		va_list va;	va_start(va,argc);
		txt = va_arg(va,void*);
		va_end(va);
	}
	printf("\t%s : %s.\n",__func__,txt);
	return E_OK;
}
err_t quitter(int argc,...){
	err_t err = E_OK;
	if( argc < 1 ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas assez d'arguments");
		return(E_ARGUMENT);
	} else {
		va_list va;	va_start(va,argc);
		if(( err=cliquer(1,va_arg(va,void*)) )){
			MSG_ERR2("de l'affichage du bouton dans le terminal");
		}
		va_end(va);
	}
	STOP = 1;
	return err;
}
err_t choixBouton(int argc,...){
	err_t err = E_OK;
	int i = -1;
	char *txt;
	if( argc < 3 ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas assez d'arguments");
		return(E_ARGUMENT);
	} else {
		va_list va;	va_start(va,argc);
		i = va_arg(va,int);
		int argc = va_arg(va,int);
		if( !(i<argc) ){
			char msg[ 70 ];
			sprintf(msg,"Le bouton %d n'est pas dans le tableau de %d boutons",i+1,argc);
			MSG_ERR(E_ARGUMENT,msg);
			return(E_ARGUMENT);
		}
		txt = va_arg(va,char**)[i];
		va_end(va);
	}
	switch( i ){
		case 0 :	err=quitter(1,txt);	break;
		default:	err=cliquer(1,txt);	break;
	}
	return(err);
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet menu. */
int main(int argc, char *argv[]) {
	// VÉRIFICATION DES PARAMÈTRE
	/* Obtention du nom du programme */
	char nomProg[strlen( argv[0]) + 1 ];
	strcpy( nomProg , argv[0] );
	/* Obtention des paramètre de la fenêtre */
	Uint32 windowFlags = SDL_WINDOW_SHOWN;
	if( argc > 1 ){
		if( strcmp(argv[1],"-r") == 0 ){
			windowFlags = windowFlags|SDL_WINDOW_RESIZABLE;
			argv++;
			argc--;
		} else {
			windowFlags = windowFlags|SDL_WINDOW_FULLSCREEN;
		}
	} else {
		windowFlags = windowFlags|SDL_WINDOW_FULLSCREEN;
	}

	// INITIALISATION DU PROGRAMME
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF|SDL_IMG , IMG_INIT_PNG ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	fenetre_t *menu = NULL;
	/* Création des autres variables */
	SDL_Event event;
	SDL_Point pos,curseur;
	SDL_Color blanc = {255,255,255,255};

	// INSTRUCTION(S)
	if(( status=creer_menu(windowFlags,nomProg,&blanc,"fond.png",&menu,&pos) )){
		MSG_ERR2("de la création du menu");
		goto Quit;
	}

	printf("Chargement des boutons à afficher...");
	{ // Création du menu :
		pos.x = 0;
		argv[0] = "Quitter";
		// Création de la police des boutons
		police_t *police = creer_police(NULL,20,NULL);
		if( !police ){
			MSG_ERR2("de la création de la police d'écriture des boutons");
			status=E_AUTRE;
			goto Quit;
		}
		printf("\t%d boutons charger.\n",argc );
		if(( status=ajouterBouton_menu(menu, police,argc,argv, choixBouton,NULL, &pos,3) )){
			MSG_ERR2("de la création du contenu du menu");
			goto Quit;
		}
		printf("\t%d boutons ajouter.\n", argc);
		// Destruction de la police des boutons
		if(( status=police->detruire(&police) )){
			MSG_ERR2("de la destruction de la police d'écriture des boutons");
			goto Quit;
		}
	}
	printf("OK\n");


	printf("Attente du signal de fin...\n");
	status = E_AUTRE;
	while( !STOP ){
		while( SDL_PollEvent(&event) ){
			if( event.type == SDL_QUIT )
				STOP = 1;
			else if( (event.type==SDL_MOUSEBUTTONUP) ){
				int numBouton;
				obtenir_clique(&curseur);
				bouton_t *b = obtenir_boutonCliquer(menu, &curseur, &numBouton);
				if( b ){
					if(( err=b->action(3,numBouton,argc,argv) )){
						MSG_ERR2("L'action d'un bouton");
						status = err;
						goto Quit;
					}
				}
			}
		}
		if(( err=rafraichir(menu) )){
			MSG_ERR2("du rafraichissement du contenu de la fenetre");
			status = err;
			goto Quit;
		}
		SDL_RenderPresent(obtenir_Renderer(menu));
	}
	printf("Signal de fin reçu\n");

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=menu->detruire(&menu)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de menu");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet menu. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

