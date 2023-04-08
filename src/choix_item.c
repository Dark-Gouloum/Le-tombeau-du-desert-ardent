/**
 * \file src/choix_item.c
 * \brief Définition de l'objet choix_item.
 * \author Dylan GRAMMONT
 * \version 0.1
 * \date Jeu. 09 Mars 2023 13:59:44
 *
 * L'objet choix_item sert à FaitQuelqueChose.
 *
 */

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../lib/choix_item.h"
#include "../lib/menu.h"
#include "../lib/img.h"
#include "../lib/joueur.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int STOP = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)


// CRÉATION(S) DE(S) FONCTION(S)
// Fonctions spéciale d'un objet choix_item

// Methode commune à tout les objets
static err_t quitter(int argc,...){
	int *STOP = NULL;
	int *retour = NULL;
	{ // Vérification des paramètre
		if( argc < 2 ){
			MSG_ERR(E_ARGUMENT,"Pas assez d'argument");
			return(E_ARGUMENT);
		}
		va_list va ; va_start(va,argc);
		STOP = va_arg(va,int*);
		retour = va_arg(va,int*);
		va_end(va);
	}
	{ // Demande de fermeture de la prochaine fenêtre
		SDL_Event quitEvent;
		quitEvent.type = SDL_QUIT;
		SDL_PushEvent(&quitEvent);
	}
	*STOP = 1;
	*retour = 0;
	return(E_OK);
}
static err_t gerreItem(int argc, ...){
	va_list va;
	va_start(va, argc);
	printf("GerreItem\n");
	if(argc != 3){
		MSG_ERR(E_ARGUMENT,"Il doit y avoir 3 arguments après argc.");
		return E_ARGUMENT;
	}else{
		int nbBout = va_arg(va, int);
		int *activee = va_arg(va, int *);
		int *nbActivee = va_arg(va, int *);

		if(activee[nbBout] == 1){
			activee[nbBout] = 0;
			(*nbActivee)--;
		}else{
			activee[nbBout] = 1;
			(*nbActivee)++;
		}

		printf("Item %d/%ls\n",nbBout,nbActivee);
		va_end(va);
		return E_OK;
	}
}


extern err_t choix_item(fenetre_t *fMere,joueur_t *perso, liste_t * lst_item,int nbAjout,int *retour){
	err_t err = E_ARGUMENT;
	int var = 0;
	{ // Test des paramètre
		if( !fMere ){
			MSG_ALERTE("","ATTENTION","Il n'y à pas de fenetre mere","");
		}
		if( !perso ){
			MSG_ERR(err,"Il n'y à pas de joueur");
			return(err);
		}
		if( !lst_item ){
			MSG_ERR(err,"Il n'y à pas de liste d'item");
			return(err);
		}
		if( !nbAjout ){
			MSG_ERR(err,"Le joueur ne peut pas séléctionner d'objet");
			return(err);
		}
		if( retour ){
			MSG_ALERTE("","ATTENTION",analyse_err(err),"Il n'y à pas de zone de retour pour indiquer un potentielle abandon");
			retour = &var;
		}
	}
	err = E_OK;

	// INITIALISATION DE(S) VARIABLE(S)
	/* Création des variables locales */
	// Dynamique
	fenetre_t *fenetre = NULL;
	// Statique
	int nbItem = liste_taille(lst_item);
	bouton_t *b_quit = NULL;
	int activee[nbItem];
	int listActivee[ (nbAjout<0)?(-nbAjout):(nbAjout) ];
	SDL_Color couleur = {255, 255, 255, 255};
	SDL_Event event;
	SDL_Point pos, curseur;
	int nbActivee = 0;
	int enlever = 0;

	// INSTRUCTION(S)
	{ // Affectation des variables locales
		for( int i=0 ; i<nbItem ; i++ )
			activee[i] = 0;
		if( nbAjout < 0 ){
			nbAjout*= -1;
			enlever = 1;
		}
	}
	{ // Création du menu et échange de fenêtre active
		if ((err = creer_menu(SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN, "Cree Perso", &couleur, "backPerso.jpeg", &fenetre, &pos))) {
			MSG_ERR2("de la création du menu");
			return err;
		}
		printf("OK\n");
		if( fMere ){
			SDL_Point dim = { 0 , 0 };
			SDL_GetWindowSize( fMere->fenetre , &(dim.x) , &(dim.y) );
			SDL_SetWindowSize( fenetre->fenetre , dim.x , dim.y );
			SDL_HideWindow( fMere->fenetre );
		}
		SDL_RaiseWindow( fenetre->fenetre );
	}
	{ // Création des boutons de la fenêtre
		char *nomItem[nbItem+1];
		for( int i=0 ; i<nbItem ; i++ ){
			item_t *item = liste_recherche_obj( &err , lst_item , i );
			if( err ){
				return(err);
			}
			if( !item ){
				return(E_OBTENIR);
			}
			char *nomItemI = malloc( sizeof(char) * (strlen(item->nom)+12) );
			if( !nomItemI ){
				return(E_MEMOIRE);
			}
			sprintf(nomItemI,"item/%s.png",item->nom);
			strcpy( nomItemI , item->nom );
			nomItem[i] = nomItemI;
		}
		nomItem[nbItem] = "Quitter.png";
		printf("Ajout de boutons à la fenêtre...");
		pos.y-=100; // fonctionne parfaitement
		int nbB = liste_taille( fenetre->lstBoutons );
		if(( err=ajouterBouton_menu(fenetre, NULL, nbItem+1, nomItem, gerreItem, NULL, &pos, 3))){
			MSG_ERR2("de la création du contenu du menu");
			return err;
		}
		b_quit = liste_recherche_obj( &err , fenetre->lstBoutons , nbItem+nbB );
		if( err ){
			return(err);
		}
		if( !b_quit ){
			return(E_OBTENIR);
		}
		b_quit->action = quitter;
		printf("\t%d boutons charger.\n", nbItem+1);
	}

	printf("Attente du signal de fermeture...\n");
	int nbBout = 0;
	while(1){
		while( SDL_PollEvent(&event) ){
			switch( event.type ){
				case SDL_QUIT:
					if(( err=quitter(2,&STOP,retour) )){
						MSG_ERR2("de la demande de fermeture de la fenetre");
						return(err);
					}
					break;
				case SDL_MOUSEBUTTONUP:
					obtenir_clique(&curseur);
					bouton_t *bouton = obtenir_boutonCliquer(fenetre, &curseur, &nbBout);
					if( bouton ){
						if( bouton==b_quit ){
							if(( err=bouton->action(2,&STOP,retour) )){
								return(err);
							}
						}
						if( (err=bouton->action(3, nbBout,activee, &nbActivee) )){
							MSG_ERR2("de l'action du bouton");
							return err;
						}
						if (nbActivee == nbAjout){
							int j =0;
							for(int i = 0; i < nbItem; i++){
								if(activee[i] == 1){
									listActivee[j] = i;
									j++;
								}
							}
							if(( err=quitter(2,&STOP,retour) )){
								return(err);
							}
							*retour = nbActivee;
						}
						bouton->afficher(bouton);
					}
					break;
			}
			if( STOP )
				goto Stop;
		}
		if ((err = rafraichir(fenetre)))
			goto Quit;
		SDL_RenderPresent(obtenir_Renderer(fenetre));
	}
Stop:
	printf("...OK\n");

	printf("%s des objets choisit à l'inventaire...", (enlever)?("Suppression"):("Ajout") );
	int j=0;
	for( int i=0 ; i<nbAjout ; i++ ){
		j = listActivee[i];
		if( (j<0) || (nbItem<j) ){
			return(E_ARGUMENT);
		}
		if( enlever ){
			if(( err=supprimerItem_pos(perso,j) )){
				return(err);
			}
		} else {
			item_t *item = liste_recherche_obj( &err , lst_item , j );
			if( err ){
				return(err);
			}
			if( !item ){
				return(E_OBTENIR);
			}
			if(( err=ajouterItem(perso,item) )){
				return(err);
			}
		}
	}
	printf("OK\n");
Quit: /* Destruction des objets */
	if ((err = fenetre->detruire(&fenetre))){
		printf("Erreur à la destruction de fenetre.\n");
		return (err);
	}
	if( fMere ){
		SDL_ShowWindow( fMere->fenetre );
		SDL_RaiseWindow( fMere->fenetre );
	}
	return(err);
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //
