/**
	* \file src/boite.c
	* \brief Définition de l'objet boite.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 16 Mars 2023 13:15:38
	*
	* L'objet boite sert à encapsuler des widgets.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/boite.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_boite = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet boite
extern err_t ajouter_widget_boite( boite_t *boite , void *widget ){
	err_t err = E_OK;
	if( (!err) )
		err=liste_ajoute(boite->lstWidgets , widget);

	return err;
}

	// Methode commune à tout les widgets
static err_t dessiner_boite(SDL_Point *pt, SDL_Renderer *r, boite_t *boite){
	int i=0;
	int nbWidgets = liste_taille( boite->lstWidgets );

	int xModMax=0 , yModMax=0;
	SDL_Point pos = { 0 , 0 };

	err_t err = E_OK;
	void *widget;

	for( i=0 ; (!err) && (i<nbWidgets) ; i++ ){
		if( pos.x > boite->xMax ){ // Si fin de la ligne atteint :
			// Début de la ligne
			if( xModMax < pos.x )
				xModMax = pos.x;
			pos.x = 0;
			// Saut de ligne
			pos.y = pos.y + yModMax + boite->ecart;
		}
		// Définir le coin en haut à gauche du widget suivant
		SDL_Point ptWidget = {
			pt->x + pos.x + 100,
			pt->y + pos.y
		};
		// Obtention du widget à dessiner
		widget = liste_lit( boite->lstWidgets , i );
		// Dessiner le nouveau widget
		err = ( (widget_t*)widget )->dessiner(&ptWidget, r, widget);
		// Vérifier si c'était le widget le plus haut de la ligne
		if( yModMax < ptWidget.y )
			yModMax = ptWidget.y;
		// Actualiser la taille de la ligne
		pos.x+= ptWidget.x + boite->ecart;
	}
	pos.y = pos.y + yModMax;
	// Renvoyé le coin en bas à droite de la boite
	pt->x = xModMax;
	pt->x = yModMax;
	if( err ){
		printf("\t%sdessiner_boite : une erreur est survenu.\n",MSG_E);
	}
	return err;
}

	// Methode commune à tout les objets
static void afficher_boite( boite_t *boite ){
	printf("boite{ ");
	( boite->lstWidgets )->afficher( boite->lstWidgets );
	printf(" }");
}

static err_t detruire_boite( boite_t **boite ){
	// Suppression des attributs de l'objet boite
	liste_t *liste = ( (*boite)->lstWidgets );
	err_t err = liste->detruire( &liste );
	if( err ){
		printf("\t%sdetruire_boite : une erreur est survenu.",MSG_E);
		return err;
	}

	// Suppression de l'objet boite
	free( (*boite) );
	(*boite) = NULL;

	// Destruction de l'objet boite réussie
	cmpt_boite--;
	return(E_OK);
}

extern void afficherSurvivant_boite(){
	afficherSurvivant_liste();
	printf("Il reste %i boite_t.\n",cmpt_boite);
}

extern boite_t * creer_boite(int xMax,int ecart){
	// Définission des variables utiles
	char *nomFonction = "creer_boite : ";

	// Créer l'objet boite
	boite_t *boite = malloc( sizeof(boite_t) );
	if( !boite ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (boite_t*)NULL;
	}

	// Affecter les attributs
	boite->xMax = xMax;
	boite->ecart = ecart;
	boite->lstWidgets = creer_liste();
	if( !boite->lstWidgets ){
		printf("\t%s%screer_liste : Une erreur est survenu.\n",MSG_E,nomFonction);
		return (boite_t*)NULL;
	}

	// Affecter les methodes
	boite->detruire = (err_t (*)(void *))detruire_boite;
	boite->dessiner = (err_t (*)(SDL_Point*,SDL_Renderer*,void*))dessiner_boite;
	boite->afficher = (void (*)(void *))afficher_boite;

	// Renvoyer le bouton
	cmpt_boite++;
	return boite;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

