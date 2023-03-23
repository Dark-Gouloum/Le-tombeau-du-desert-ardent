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


// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned STOP = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t jouer(int argc,...){
	printf("Bouton \"Start\" cliqué !\n");
	return E_OK;
}
err_t charger(int argc,...){
	printf("Bouton \"Charger\" cliqué !\n");
	return E_OK;
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
	if( argc < 1 ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas assez d'arguments");
		return(E_ARGUMENT);
	}
	va_list va;
	va_start(va,argc);
	int i = va_arg(va,int);
	switch( i ){
		case 0 :	err=jouer(0);	break; //nouvelle partie
		case 1 :	err=charger(0);	break; //charger partie
		case 2 :	err=options(0);	break; //Options générale
		case 3 :	err=quitter(0);	break;
		default:
			err=E_ARGUMENT;
			char msg[ 40 ];
			sprintf(msg,"bouton inconnu : il faut 0<= %d < 9",i);
			MSG_ERR(err,msg);
	}
	va_end(va);
	return(err);
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
		// Gestion de la fenetre
	fenetre_t *fenetre = NULL;
	SDL_Point curseur;
	SDL_Point dim = {750,500};
	SDL_Point pos = {0,0};
	SDL_Event event;

	// INSTRUCTION(S)
	if(( status=creer_menu(SDL_WINDOW_SHOWN,NULL,&cFond,"fond.png",&fenetre,&pos) )){
		MSG_ERR2("de la création du menu");
		goto Quit;
	}

	printf("Chargement des boutons à afficher...");
	{
		char *nomBoutons[] = {
			"Jouer !"
			, "Charger"
			, "Options"
			, "quitter"
		};
		int nbBouton = TAILLE(nomBoutons);
		printf("\n%d\n",nbBouton );
		if(( status=ajouterBouton_menu( fenetre, nbBouton,nomBoutons,choixBouton, &pos,1)  )){
			MSG_ERR2("de la création du contenu du menu");
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
					if(( status=b->action(1,numBouton) )){
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
