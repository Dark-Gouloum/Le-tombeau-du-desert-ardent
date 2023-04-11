/**
 * \file src/joueur.c
 * \brief Définition de l'objet joueur.
 * \author Dylan GRAMMONT
 * \version 0.1
 * \date Jeu. 23 Mars 2023 00:31:27
 *
 * L'objet joueur sert à gére le joueur (c'est le personnage principal.
 *
 */

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/joueur.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_joueur = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
// Fonctions spéciale d'un objet joueur
/*	Gestion de l'inventaire du joueur	*/
extern void afficher_invenventaire(joueur_t *joueur)
{
	if (!joueur || !(liste_taille(joueur->listItem)))
	{
		printf("Inventaire vide.\n");
		return;
	}
	printf("Le joueur %s à comme inventaire :\n", joueur->nom);
	joueur->listItem->afficher(joueur->listItem);
}

extern err_t ajouterItem(joueur_t *joueur, item_t *item)
{
	err_t err = E_OK;
	modificateur_t *modificateur = liste_recherche_obj(&err, item->lstModificateurs, 0);
	switch (modificateur->modif)
	{
	case STAT_FORCE:
		joueur->force += modificateur->valeur;
		break;
	case STAT_INTEL:
		joueur->intelligence += modificateur->valeur;
		break;
	case STAT_PV:
		joueur->PV += modificateur->valeur;
		break;
	case STAT_ARMURE:
		joueur->armure += modificateur->valeur;
		break;
	case STAT_CRITIQUE:
		joueur->critique += modificateur->valeur;
		break;
	case STAT_AGILITE:
		joueur->agilite += modificateur->valeur;
		break;

	default:
		MSG_ERR(E_ARGUMENT, "ce type de stat est inconnu");
		return E_AUTRE;
		break;
	}
	return liste_ajoute(joueur->listItem, item);
}

extern err_t supprimerItem_pos(joueur_t *joueur, int pos)
{
	return liste_enlever_pos(joueur->listItem, pos);
}
extern err_t supprimerItem(joueur_t *joueur, item_t *item)
{
	err_t err = E_OK;
	modificateur_t *modificateur = liste_recherche_obj(&err, item->lstModificateurs, 0);
	switch (modificateur->modif)
	{
	case STAT_FORCE:
		joueur->force -= modificateur->valeur;
		break;
	case STAT_INTEL:
		joueur->intelligence -= modificateur->valeur;
		break;
	case STAT_PV:
		joueur->PV -= modificateur->valeur;
		break;
	case STAT_ARMURE:
		joueur->armure -= modificateur->valeur;
		break;
	case STAT_CRITIQUE:
		joueur->critique -= modificateur->valeur;
		break;
	case STAT_AGILITE:
		joueur->agilite -= modificateur->valeur;
		break;

	default:
		MSG_ERR(E_ARGUMENT, "ce type de stat est inconnu");
		return E_AUTRE;
		break;
	}
	return liste_enlever_obj(joueur->listItem, item);
}
/*	Gestion de la sauvegarde du joueur	*/
extern err_t sauvegarder_joueur(joueur_t *joueur,FILE *f)
{
	err_t err = E_OK;
	item_t *item;
	// Ouverture du fichier en mode écriture
	if (!f)
	{
		char msg[8 + 35];
		sprintf(msg, "Impossible d'ouvrir le fichier '%s'", ".save.txt");
		MSG_ERR(E_AUTRE, msg);
		return (E_AUTRE);
	}
	if (!joueur)
	{
		MSG_ERR(E_AUTRE, "Il n'y à pas de joueur à sauvegardé");
		return (E_AUTRE);
	}
	int nbItem = liste_taille(joueur->listItem);
	// Écriture des valeurs de la structure dans le fichier
	fprintf(f, "%s\n", joueur->nom);
	fprintf(f, "%d %d %d %d %d %d\n", joueur->force, joueur->intelligence, joueur->PV, joueur->armure, joueur->critique, joueur->agilite);
	fprintf(f, "%d\n", nbItem);
	fprintf(f, "\n");
	// Ecriture des objet dans le fichier
	for (int i = 0; i < nbItem; i++)
	{
		item = liste_recherche_obj(&err, joueur->listItem, i);
		if (err)
		{
			char msg[40];
			sprintf(msg, "L'item N°%d n'à pas était retrouvé.", i);
			MSG_ERR2(msg);
			return (err);
		}
		if ((err = sauvegarder_item(f, item)))
		{
			char msg[55];
			sprintf(msg, "L'item N°%d n'à pas était sauvegardé.", i);
			MSG_ERR2(msg);
			return (err);
		}
	}
	return E_OK;
}

extern err_t charger_joueur(joueur_t **joueur,FILE *f)
{
	err_t err = E_OK;
	if (*joueur)
	{
		if ((err = ((*joueur)->detruire(joueur))))
		{
			MSG_ERR2("de la destruction de l'ancien joueur");
			return (err);
		}
	}
	item_t *item = NULL;
	int nbObj = 0;
	char nom[255];

	// Création du joueur
	if (!(*joueur = creer_joueur()))
	{
		MSG_ERR2("de la création du joueur");
		return (E_AUTRE);
	}

	// Écriture des valeurs de la structure dans le fichier
	{
		if (fscanf(f, "%s", nom) != 1)
		{
			MSG_ERR(E_OBTENIR, "Une erreur c'est produite lors de la lecture du nom du joueur");
			return (E_OBTENIR);
		}
		int fo, in, pv, ar, cr, ag;
		if (fscanf(f, "%d%d%d%d%d%d", &fo, &in, &pv, &ar, &cr, &ag) != 6)
		{
			MSG_ERR(E_OBTENIR, "Une erreur c'est produite lors de la lecture des stats du joueur");
			return (E_OBTENIR);
		}
		attribuer_personnage(*joueur, fo, in, pv, ar, cr, ag, nom);
	}
	if( fscanf(f,"%d",&nbObj) != 2 )
	{
		MSG_ERR(E_OBTENIR, "Une erreur c'est produite lors de la lecture de la progression du joueur");
		return (E_OBTENIR);
	}
	// Ecriture des objet dans le fichier
	for (int i = 0; i < nbObj; i++)
	{
		if ((err = charger_item(f, &item)))
		{
			char msg[40];
			sprintf(msg, "L'item N°%d n'à pas était recréer.", i);
			MSG_ERR2(msg);
			return (err);
		}
		if ((liste_ajoute((*joueur)->listItem, item)))
		{
			char msg[40];
			sprintf(msg, "L'item N°%d n'à pas était retrouvé.", i);
			MSG_ERR2(msg);
			return (err);
		}
		item = NULL;
	}
	return E_OK;
}

// Methode commune à tout les objets
static void afficher_joueur(joueur_t *joueur)
{
	afficher_personnage(joueur, "joueur");
	afficher_invenventaire(joueur);
}

static err_t detruire_joueur(joueur_t **joueur)
{
	// Suppression des attributs de l'objet joueur
	err_t err = E_OK;
	liste_t *liste = (*joueur)->listItem;
	if ((err = liste->detruire(&liste)))
	{
		MSG_ERR2("de la destruction de la liste d'item du joueur");
		return (err);
	}
	(*joueur)->listItem = liste;
	free((*joueur)->nom);

	// Suppression de l'objet joueur
	free((*joueur));
	(*joueur) = NULL;

	// Destruction de l'objet joueur réussie
	cmpt_joueur--;
	return (E_OK);
}

extern void afficherSurvivant_joueur()
{
	printf("Il reste %i joueur_t.\n", cmpt_joueur);
	afficherSurvivant_liste();
	afficherSurvivant_item();
}

extern joueur_t *creer_joueur()
{
	// Créer l'objet joueur
	joueur_t *joueur = malloc(sizeof(joueur_t));
	if (!joueur)
	{ // malloc à échouer :
		MSG_ERR(E_MEMOIRE, "malloc : pas assez de place pour créer un objet de type 'joueur'");
		return (joueur_t *)NULL;
	}

	// Affecter les attributs
	joueur->nom = NULL;
	if (!((joueur->listItem) = creer_liste()))
	{
		MSG_ERR2("la création de la liste d'item du joueur");
		return (joueur_t *)NULL;
	}
	attribuer_personnage(joueur, 2, 2, 10, 2, 2, 2, "steevee");

	// Affecter les methodes
	joueur->detruire = (err_t(*)(void *))detruire_joueur;
	joueur->afficher = (void (*)(void *))afficher_joueur;

	// Renvoyer le bouton
	cmpt_joueur++;
	return joueur;
}

extern void afficher_joueurBis(joueur_t *joueur, SDL_Window *window){
	err_t err = E_OK;
	char *msg = NULL;
	if(( err=lis_personnage(joueur,"joueur",&msg,28) )){
		MSG_ERR2("de l'écriture du message à afficher");
		return;
	}
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Les statistiques", msg, window);
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //
