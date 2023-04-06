/**
 * \file src/cree_perso.c
 * \brief Définition de l'objet cree_perso.
 * \author Dylan GRAMMONT
 * \version 0.1
 * \date Jeu. 09 Mars 2023 13:59:44
 *
 * L'objet cree_perso sert à FaitQuelqueChose.
 *
 */

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../lib/cree_perso.h"
#include "../lib/menu.h"
#include "../lib/police.h"
#include "../lib/img.h"
#include "../lib/joueur.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int STOP = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)


// CRÉATION(S) DE(S) FONCTION(S)
// Fonctions spéciale d'un objet cree_perso

// Methode commune à tout les objets

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



extern int creationPersonnage(joueur_t *perso, liste_t * lst_item,int nbItemAct)
{
	int nbItem = liste_taille(lst_item);
	// Definition des fonctions des bu
	int activee[nbItem];
	for (int i = 0; i < nbItem; i++)
	{
		activee[i] = 0;
	}
	int nbActivee = 0;

	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if (initialisation_SDL(SDL_TTF | SDL_IMG, IMG_INIT_PNG))
		return E_INIT;
	err_t status = E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	fenetre_t *fenetre = NULL;
	/* Création des autres variables */
	police_t *police = NULL;
	SDL_Color couleur = {255, 255, 255, 255};

	SDL_Event event;
	SDL_Point pos, curseur;

	int nbBout = 0;
	// Création du menu
	if ((status = creer_menu(SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN, "Cree Perso", &couleur, "backPerso.jpeg", &fenetre, &pos)))
	{
		MSG_ERR2("de la création du menu");
		return status;
	}
	printf("OK\n");
	
	// Création de la variable joueur
	joueur_t *joueur = creer_joueur();
	joueur->afficher(joueur);
	//afficher_joueurBis(joueur,fenetre->fenetre);
	char * nomItem[nbItem]; 
	for (int i = 0; i < nbItem; i++)
	{
		item_t * item = liste_recherche_obj(&status,lst_item,i);
		nomItem[i] = malloc(sizeof(char) * (strlen(item->nom)));
		strcpy(nomItem[i], item->nom);
		
	}

	// ajouter item
	printf("Ajout de boutons à la fenêtre...");

	
	printf("\t%d boutons charger.\n", nbItem);
	pos.y-=100; // fonctionne parfaitement
	if ((status = ajouterBouton_menu(fenetre, NULL, nbItem, nomItem, gerreItem, NULL, &pos, 3)))
	{
		MSG_ERR2("de la création du contenu du menu");
		return status;
	}

	printf("Attente du signal de fermeture...");
	status = E_AUTRE;
	while (!STOP)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				STOP = 1;
				break;
			case SDL_MOUSEBUTTONUP:
				
				obtenir_clique(&curseur);
				bouton_t *bouton = obtenir_boutonCliquer(fenetre, &curseur, &nbBout);
				if (bouton)
				{
					if( (status=bouton->action(3, nbBout,activee, &nbActivee) )){
						MSG_ERR2("de l'action du bouton");
						return status;
					}

					if (nbActivee == nbItemAct)
					{
						int * listActivee= malloc(sizeof(int)*nbActivee);
						int j =0;
						for(int i = 0; i < nbItem; i++){
							if(activee[i] == 1){
								listActivee[j] = i;
								j++;
							}
						}
						

						//ajouter item
						for(int i = 0; i < nbActivee; i++){
							ajouterItem(joueur, liste_recherche_obj(&status,lst_item,listActivee[i]));
						}
						joueur->afficher(joueur);
						return * listActivee;
						
						//lancer partie
						//livre ICI
					}
					bouton->afficher(bouton);
				}
				break;
			}
		}
		if ((status = rafraichir(fenetre)))
			goto Quit;
		SDL_RenderPresent(obtenir_Renderer(fenetre));
	}
	printf("OK\n");
	SDL_Delay(1000);
	status = E_OK;

Quit: /* Destruction des objets */
	if ((status = police->detruire(&police)))
	{ // Echec à la destruction :
		printf("Erreur à la destruction de stylo.\n");
		return (status);
	}
	if ((status = fenetre->detruire(&fenetre)))
	{ // Echec à la destruction :
		printf("Erreur à la destruction de fenetre.\n");
		return (status);
	}
	fermer_SDL();
	/* Affichage de fin */
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return (status);
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //
