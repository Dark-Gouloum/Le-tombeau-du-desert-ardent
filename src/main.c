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
#include "../lib/commun.h"
#include "../lib/menu.h"
#include "../lib/choix_item.h"
#include "../lib/joueur.h"
#include "../lib/livre.h"


#include <time.h>


// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned STOP = 0;
err_t err=E_AUTRE, status=E_AUTRE;
#define FICHIER_TEST "test"

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)


// CRÉATION(S) DE(S) FONCTION(S)
err_t jouer(int argc,...){
	fenetre_t *menu = NULL;
	char * histoire = NULL;
	err_t err = E_OK;
	{ // Tests sur les paramètres
		if( argc < 2 ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas assez d'arguments");
			return(E_ARGUMENT);
		}
		va_list va	;	va_start(va,argc)	;
		menu = va_arg(va,void*);
		histoire = va_arg(va,char*);
		va_end(va);
		if( !menu ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas de fenetre mere");
			return(E_ARGUMENT);
		}
		if( !histoire ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas d'histoire à charger");
			return(E_ARGUMENT);
		}
	}
	livre_t *livre = NULL;
	if(( err=nouveauJeu(menu,histoire,&livre) )){
		MSG_ERR2("de la création du jeu");
		return(err);
	}
	if(( err=livre_jouer(menu,&livre) )){
		MSG_ERR2("du déroulement du jeu");
		return(err);
	}
	return(err);
}
err_t charger(int argc,...){
	fenetre_t *menu = NULL;
	char * histoire = NULL;
	err_t err = E_OK;
	{ // Tests sur les paramètres
		if( argc < 2 ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas assez d'arguments");
			return(E_ARGUMENT);
		}
		va_list va	;	va_start(va,argc)	;
		menu = va_arg(va,void*);
		histoire = va_arg(va,char*);
		va_end(va);
		if( !menu ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas de fenetre mere");
			return(E_ARGUMENT);
		}
		if( !histoire ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas d'histoire à charger");
			return(E_ARGUMENT);
		}
	}
	livre_t *livre = NULL;
	if(( err=livre_charger(menu,&livre,histoire) )){
		MSG_ERR2("de la création du jeu");
		return(err);
	}
	if(( err=livre_jouer(menu,&livre) )){
		MSG_ERR2("du déroulement du jeu");
		return(err);
	}
	return(err);
}
err_t options(int argc,...){
	printf("Bouton \"Options\" cliqué !\n");
	return E_OK;
}
err_t quitter(int argc,...){
	printf("Bouton \"Quitter\" cliqué !\n");
	STOP = 1;
	return E_OK;
}
err_t choixBouton(int argc,...){
	err_t err = E_OK;
	int i = 0;
	fenetre_t *menu = NULL;
	char *histoire = NULL;
	{ // Tests des paramètres
		if( argc < 3 ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas assez d'arguments");
			return(E_ARGUMENT);
		}
		va_list va	;	va_start(va,argc)	;
		i = va_arg(va,int);
		menu = va_arg(va,void*);
		histoire = va_arg(va,char*);
		va_end(va);
	}
	switch( i ){
		case 0 :	err= jouer (2,menu,histoire);	break; //nouvelle partie
		case 1 :	err=charger(2,menu,histoire);	break; //charger partie
		case 2 :	err=options(2,menu,histoire);	break; //Options générale
		case 3 :	err=quitter(2,menu,histoire);	break; // Mettre fin à l'application
		default:
			err=E_ARGUMENT;
			char msg[ 40 ];
			sprintf(msg,"bouton inconnu : il faut 0<= %d < 9",i);
			MSG_ERR(err,msg);
	}
	return(err);
}
	

// PROGRAMME PRINCIPALE
int main(int argc, char *argv[]){  /* Programme qui lance le tombeau du desert ardent */
	char *histoire = NULL;
	if( argc<2 ){
		histoire = histoireDefaut;
	} else {
		histoire = argv[0];
	}
	// INITIALISATION DE(S) VARIABLE(S)
	//Lancement de la génération de nombre aléatoire
	 srand( time( NULL ) );
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t status=E_AUTRE;
	/* Création des autres variables */
		// Couleurs
	SDL_Color cEcriture = {255,255,255,255};
		// Gestion de la fenetre
	fenetre_t *fenetre = NULL;
	SDL_Point pos = { 0 , 0 };
	SDL_Point curseur;
	SDL_Event event;

	// INSTRUCTION(S)
	if(( status=creer_menu(SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN,NULL,&cEcriture,"fond.png",&fenetre,&pos) )){
		MSG_ERR2("de la création du menu");
		goto Quit;
	}

	printf("Chargement des boutons à afficher...\n");
	{ // Création du menu :
		// Création des noms
		char *nomBoutons[] = {
			"Jouer !"
			, "Charger"
			, "Options"
			, "Q uitter"
		};
		int nbBouton = TAILLE(nomBoutons);
		// Création de la police des boutons
		police_t *police = creer_police(NULL,20,&cEcriture);
		if( !police ){
			MSG_ERR2("de la création de la police d'écriture des boutons");
			status=E_AUTRE;
			goto Quit;
		}
		printf("\t%d boutons charger.\n",nbBouton );
		if(( status=ajouterBouton_menu(fenetre, police,nbBouton,nomBoutons, choixBouton,NULL, &pos,1) )){
			MSG_ERR2("de la création du contenu du menu");
			goto Quit;
		}
		printf("\t%d boutons ajouter.\n",nbBouton );
		// Destruction de la police des boutons
		if(( status=police->detruire(&police) )){
			MSG_ERR2("de la destruction de la police d'écriture des boutons");
			goto Quit;
		}
	}
	printf("OK\n");

	status = E_AUTRE;
	while( !STOP ){
		while( SDL_PollEvent(&event) ){
			if( event.type == SDL_QUIT )
				STOP = 1;
			else if( (event.type==SDL_MOUSEBUTTONUP) ){
				int numBouton;
				obtenir_clique(&curseur);
				bouton_t *b = obtenir_boutonCliquer(fenetre, &curseur, &numBouton);
				if( b ){
					if(( status=b->action(3,numBouton,fenetre,histoire) )){
						MSG_ERR2("L'action d'un bouton");
						goto Quit;
					}
				}
			}
		}
		if(( status=rafraichir(fenetre) )){
			MSG_ERR2("du rafraichissement du contenu de la fenetre");
			goto Quit;
		}
		SDL_RenderPresent(obtenir_Renderer(fenetre));
	}
	status = E_OK;

	// FIN DU PROGRAMME
Quit:
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
