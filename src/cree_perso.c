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

static err_t valider(int argc, ...){
	va_list va;	va_start(va,argc);
	personage_t *perso = va_arg( va, void* );
	printf("Valider\n");

	STOP = 1;
	va_end( va );
	return E_OK;
}

static err_t item(int argc,...){
	if(argc!=5)
		return E_AUTRE;
	va_list va;	va_start(va,argc);

	liste_t * liste = va_arg(va,void *);
	bouton_t * bouton = va_arg(va,void *);
	int nbItem  = va_arg(va,int);
	int * activee  = va_arg(va,int *);
	int * nbActivee = va_arg(va,int *);

	int i = liste_recherche(liste,bouton);
	if(activee[i]==1){
		activee[i]=0;
		nbActivee--;
	}else{
		activee[i]=1;
		nbActivee++;
	}

	printf("Item %d/%d\n",i,nbItem);
	va_end( va );
	return E_OK;
}



extern int creationPersonnage(personage_t *perso, int nbItem){
	//Definition des fonctions des bu
	int  activee[nbItem];
	for(int i=0;i<nbItem;i++){
		activee[i]=0;
	}
	int  nbActivee=0;


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
	ancre_t *ancre;

	printf("Création de la fenêtre...");
	if (!(fenetre = creer_fenetre(dim, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, "Creation Perso")))
	{ // Pas d'objet fenetre de créer :
		printf("Erreur à la création de fenetre.\n");
		status = E_AUTRE;
		goto Quit;
	}
	changerFond_couleur(fenetre, fond);
	printf("OK\n");

	printf("Création de l'ancre...");
	if (!( ancre=creer_ancre(0,0,ANGLE_MILLIEU) )){
		printf("Erreur à la création de l'ancre.\n");
		status = E_AUTRE;
		goto Quit;
	}
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
	int maxObjLigne = 3;
	char * nomItem = "item";
	for(int i=0 ; i<nbItem ; i++){
		sprintf(nomItem,"item %d",i);

		float x = i % maxObjLigne;
		x*= maxObjLigne;
		ancre->changerX( ancre , x );
		float y = i / maxObjLigne;
		y*= (nbItem/maxObjLigne) + 1;
		ancre->changerY( ancre , y );

		if(( status = ajouterBouton(fenetre, stylo, nomItem, ancre, item) )){ // Pas d'objet stylo de créer :
			printf("Erreur à l'ajout du %dieme bouton.\n",i);
			goto Quit;
		}
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
							if((status = ajouterBouton(fenetre, stylo, "Valider", ancre, valider)))
							{ // Pas d'objet stylo de créer :
								printf("Erreur à l'ajout du premier bouton.\n");
								goto Quit;
							}
						}
						bouton->afficher(bouton);
						bouton->action(2,fenetre->lstBoutons,bouton);
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
