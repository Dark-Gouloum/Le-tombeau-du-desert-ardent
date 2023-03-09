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

#include "../lib/cree_perso.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_cree_perso = 0;
static int STOP = 0;
// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
// Fonctions spéciale d'un objet cree_perso

// Methode commune à tout les objets
int itemUn,itemDeux=0;
static err_t valider(personage_t *perso){
		printf("Valider 2\n");
	
		STOP = 1;
		return E_OK;
	}

static err_t item1(){
		printf("Item 1\n");
		if(itemUn==1){
			itemUn=0;
		}else{
			itemUn=1;
		}
		printf("%d\n",itemUn);
		STOP = 1;
		return E_OK;
	}

static err_t item2(){
		printf("Item 2\n");
		if(itemDeux==1){
			itemDeux=0;
		}else{
			itemDeux=1;
		}
		printf("%d\n",itemDeux);
		STOP = 1;
		return E_OK;
	}



extern int creationPersonnage(personage_t *perso){
	//Definition des fonctions des bu
	
	int nbItem = 0;
	if (initialisation_SDL(SDL_TTF))
	{
		return E_INIT;
	}
	err_t status = E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	fenetre_t *fenetre = NULL;
	/* Création des autres variables */
	stylo_t *stylo = NULL;
	SDL_Point dim = {500, 500};
	SDL_Color couleur = {255, 255, 255, 255};
	SDL_Color fond = {255, 125, 60, 255};
	SDL_Event event;
	SDL_Point curseur;
	ancre_t ancre;
	ancre.point = (SDL_Point){100 / 2, (100 / 3) * 2};
	ancre.angle = ANGLE_MILLIEU;

	printf("Création de la fenêtre...");
	if (!(fenetre = creer_fenetre(dim, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, "Creation Perso")))
	{ // Pas d'objet fenetre de créer :
		printf("Erreur à la création de fenetre.\n");
		status = E_AUTRE;
		goto Quit;
	}
	changerFond_couleur(fenetre, fond);
	printf("OK\n");
	

	printf("Création du stylo...");
	if (!(stylo = creer_stylo(NULL, 20, couleur)))
	{ // Pas d'objet stylo de créer :
		printf("Erreur à la création de stylo.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");

	// ajouter item
	printf("Ajout de boutons à la fenêtre...");
	if ((status = ajouterBouton(fenetre, stylo, "item1", ancre, item1)))
	{ // Pas d'objet stylo de créer :
		printf("Erreur à l'ajout du premier bouton.\n");
		goto Quit;
	}
	ancre.point = (SDL_Point){100 / 2, (100 / 3)};
	if ((status = ajouterBouton(fenetre, stylo, "Item2", ancre, item2)))
	{ // Pas d'objet stylo de créer :
		printf("Erreur à l'ajout du deuxième bouton.\n");
		goto Quit;
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
				obtenir_souris(&curseur);
				bouton_t *bouton = obtenir_boutonCliquer(fenetre, &curseur);
				if (bouton)
				{
					nbItem++;
					if (nbItem == 3)
					{
						printf("Ajout de boutons à la fenêtre...");
						if ((status = ajouterBouton(fenetre, stylo, "Valider", ancre, valider)))
						{ // Pas d'objet stylo de créer :
							printf("Erreur à l'ajout du premier bouton.\n");
							goto Quit;
						}
					}
					bouton->afficher(bouton);
					bouton->action();
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
	if ((status = stylo->detruire(&stylo)))
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
