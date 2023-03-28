/**
 * \file src/bouton.c
 * \brief Définition de l'objet bouton.
 * \author Erwan PECHON
 * \version 0.1
 * \date Mar. 21 Mars 2023 09:56:52
 *
 * L'objet bouton sert à définir des boutons.
 *
 */

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/bouton.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_bouton = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
// Fonctions spéciale d'un objet bouton
static err_t dessiner_bouton(bouton_t *bouton){
	if (!bouton)
	{
		MSG_ERR(E_ARGUMENT, "Il n'y à pas de bouton à dessiner.");
		return (E_ARGUMENT);
	}
	widget_t *w = bouton->widget;
	if (!w)
	{
		MSG_ERR(E_OBTENIR, "Il n'y à pas de widget.");
		return (E_OBTENIR);
	}
	if (!(w->dest))
	{
		MSG_ERR(E_OBTENIR, "Il n'y à pas de zone bouton.");
		return (E_OBTENIR);
	}
	SDL_Color color;
	if (SDL_GetRenderDrawColor(w->rendu, &(color.r), &(color.g), &(color.b), &(color.a))){
		MSG_ERR2("de la sauvegarde de la couleur du pinceau du rendu");
		MSG_ERR_COMP("SDL_GetRenderDrawColor", SDL_GetError());
		return E_AUTRE;
	}
	if (SDL_SetRenderDrawColor(w->rendu, (bouton->color).r, (bouton->color).g, (bouton->color).b, (bouton->color).a)){
		MSG_ERR2("du changement de couleur du pinceau du rendu");
		MSG_ERR_COMP("SDL_SetRenderDrawColor", SDL_GetError());
		return E_AUTRE;
	}
	if (SDL_RenderFillRect(w->rendu, w->dest)){
		MSG_ERR2("du dessin du rectangle sur le rendu");
		MSG_ERR_COMP("SDL_RenderFillRect", SDL_GetError());
		return E_AUTRE;
	}
	if (SDL_SetRenderDrawColor(w->rendu, 255, 0, 0, 255)){
		MSG_ERR2("du changement de couleur du pinceau du rendu");
		MSG_ERR_COMP("SDL_SetRenderDrawColor", SDL_GetError());
		return E_AUTRE;
	}
	if (SDL_RenderDrawRect(w->rendu, w->dest)){
		MSG_ERR2("du dessin du rectangle sur le rendu");
		MSG_ERR_COMP("SDL_RenderFillRect", SDL_GetError());
		return E_AUTRE;
	}
	if (SDL_SetRenderDrawColor(w->rendu, color.r, color.g, color.b, color.a)){
		MSG_ERR2("de la restauration de la couleur du pinceau du rendu");
		MSG_ERR_COMP("SDL_SetRenderDrawColor", SDL_GetError());
		return E_AUTRE;
	}
	w->dessiner((void *)w);
	return E_OK;
}

// Methode commune à tout les objets
static void afficher_bouton(bouton_t *bouton)
{
	printf("bouton{}");
}

static err_t detruire_bouton(bouton_t **bouton)
{
	if (!(*bouton))
	{
		MSG_ERR(E_ARGUMENT, "Il n'y à pas de bouton à détruire.");
		return (E_ARGUMENT);
	}
	// Suppression des attributs de l'objet bouton
	((*bouton)->widget)->detruire(&((*bouton)->widget));

	// Suppression de l'objet bouton
	free((*bouton));
	(*bouton) = NULL;

	// Destruction de l'objet bouton réussie
	cmpt_bouton--;
	return (E_OK);
}

extern void afficherSurvivant_bouton()
{
	printf("Il reste %i bouton_t.\n", cmpt_bouton);
}

extern bouton_t *creer_bouton(SDL_Renderer *rendu, void *widget, err_t (*action)(int argc, ...), SDL_Color *couleur)
{
	// Tests des paramètre
	if (!rendu)
	{
		MSG_ERR(E_ARGUMENT, "Il n'y à pas de rendu où afficher le bouton.");
		return (NULL);
	}

	// Créer l'objet bouton
	bouton_t *bouton = malloc(sizeof(bouton_t));
	if (!bouton)
	{ // malloc à échouer :
		MSG_ERR(E_MEMOIRE, "malloc : pas assez de place pour créer un objet de type 'bouton'");
		return (bouton_t *)NULL;
	}

	// Affecter les attributs
	bouton->widget = widget;
	bouton->action = action;
	// test de la couleur
	if(couleur){
		(bouton->color).r = couleur->r;
		(bouton->color).g = couleur->g;
		(bouton->color).b = couleur->b;
		(bouton->color).a = couleur->a;
	} else {
		(bouton->color).r = 122;
		(bouton->color).g = 122;
		(bouton->color).b = 122;
		(bouton->color).a = 255;
	}

	// Affecter les methodes
	bouton->detruire = (err_t(*)(void *))detruire_bouton;
	bouton->afficher = (void (*)(void *))afficher_bouton;
	bouton->dessiner = (err_t(*)(void *))dessiner_bouton;

	// Renvoyer le bouton
	cmpt_bouton++;
	return bouton;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //
