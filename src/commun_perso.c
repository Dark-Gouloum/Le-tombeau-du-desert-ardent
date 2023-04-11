/**
 * \file src/commun_perso.c
 * \brief Définition de l'objet personnage.
 * \author Dylan GRAMMONT
 * \version 0.1
 * \date Mer. 22 Mars 2023 23:59:23
 *
 * L'objet personnage sert à gérer les personnages du jeu.
 *
 */

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lib/commun_perso.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
#define VAL_DEFAUT(max) (max / 5)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
static int lancer_de(int stat, int statMax)
{
	int rng = rand() % statMax + 1;
	if (rng > STAT_NORM(stat, statMax))
	{
		printf("\nRng echoue: %d\n", rng);
		return 0;
	}
	else
	{
		printf("\nrng pas echoue : %d\n", rng);
		return 1;
	}
}

#define VAL(val, max) ((val == 0) ? (VAL_DEFAUT(max)) : (val))
static void attribuer_personnage_bis(personnage_t *personnage, int force, int intelligence, int PV, int armure, int critique, int agilite, char *nom)
{
	if (!personnage)
	{
		return;
	}
	personnage->force = VAL(force, STAT_MAX_FORCE);
	personnage->intelligence = VAL(intelligence, STAT_MAX_INTEL);
	personnage->PV = VAL(PV, STAT_MAX_PV);
	personnage->armure = VAL(armure, STAT_MAX_ARMURE);
	personnage->critique = VAL(critique, STAT_MAX_CRITIQ);
	personnage->agilite = VAL(agilite, STAT_MAX_AGILI);
	if (nom)
	{
		if (personnage->nom)
		{
			free(personnage->nom);
			personnage->nom = NULL;
		}
		personnage->nom = (char *)malloc(sizeof(char) * (strlen(nom) + 1));
		strcpy(personnage->nom, nom);
	}
}
extern void attribuer_personnage(void *personnage, int force, int intelligence, int PV, int armure, int critique, int agilite, char *nom)
{
	attribuer_personnage_bis(personnage, force, intelligence, PV, armure, critique, agilite, nom);
}

static void assembleStr(char *msg, char *tmp, char *sType, int vType, int taille, char *pattern)
{
	int i = 0, j = 0, len = strlen(pattern);
	{ // Début de ligne
		tmp[i++] = '\t';
		tmp[i++] = '-';
		tmp[i++] = ' ';
		tmp[i] = '\0';
	}
	{ // Lecture du type
		char TMP[strlen(sType) + 1];
		strncpy(TMP, sType, taille - 13);
		TMP[taille - 13] = '\0';
		strcat(tmp, TMP);
		i = strlen(tmp);
	}
	{ // Complétion
		while (i < (taille - 10))
		{
			if (j == len)
			{
				j = 0;
			}
			tmp[i++] = pattern[j++];
		}
		tmp[i] = '\0';
	}
	{ // Ajout de la valeur
		char TMP[10];
		sprintf(TMP, "-> : %d\n", vType);
		strcat(tmp, TMP);
		strcat(msg, tmp);
	}
}
static err_t lis_personnage_bis(personnage_t *personnage, char *type, char **msg, int t_Ligne)
{
	if (!msg)
	{
		MSG_ERR(E_ARGUMENT, "Pas de zone de retour pour le texte");
		return (E_ARGUMENT);
	}
	if (*msg)
	{
		MSG_ERR(E_ARGUMENT, "Zone de retour pour le texte déjà occupé");
		return (E_ARGUMENT);
	}
	if (!personnage)
	{
		MSG_ERR(E_ARGUMENT, "Personnage inexistant");
		return (E_ARGUMENT);
	}
	if (t_Ligne < 15)
	{
		t_Ligne = 15;
	}
	char *sType = ((type) ? (type) : ("personnage"));
	*msg = malloc(sizeof(char) * (strlen(sType) + strlen(personnage->nom) + 32 + t_Ligne * 6));
	if (!(*msg))
	{
		MSG_ERR(E_MEMOIRE, "malloc à échoué, pas assez d'espace disponible");
		return (E_MEMOIRE);
	}
	char tmp[t_Ligne];
	sprintf(*msg, "Le %s %s à comme statistique :\n", sType, personnage->nom);
	char sep[] = " -";
	assembleStr(*msg, tmp, "PV", STAT_NORM(personnage->PV, STAT_MAX_PV), t_Ligne, sep);
	assembleStr(*msg, tmp, "Force", STAT_NORM(personnage->force, STAT_MAX_FORCE), t_Ligne, sep);
	assembleStr(*msg, tmp, "Agilite", STAT_NORM(personnage->agilite, STAT_MAX_AGILI), t_Ligne, sep);
	assembleStr(*msg, tmp, "Armure", STAT_NORM(personnage->armure, STAT_MAX_ARMURE), t_Ligne, sep);
	assembleStr(*msg, tmp, "Critique", STAT_NORM(personnage->critique, STAT_MAX_CRITIQ), t_Ligne, sep);
	assembleStr(*msg, tmp, "Intelligence", STAT_NORM(personnage->intelligence, STAT_MAX_INTEL), t_Ligne, sep);
	return (E_OK);
}
extern err_t lis_personnage(void *personnage, char *type, char **msg, int tailleLigne)
{
	return lis_personnage_bis(personnage, type, msg, tailleLigne);
}

static void afficher_personnage_bis(personnage_t *personnage, char *type)
{
	char *msg = NULL;
	if ((lis_personnage_bis(personnage, type, &msg, 30)))
	{
		MSG_ERR2("Impossible d'écrire la ligne");
		return;
	}
	printf("%s", msg);
	free(msg);
	return;
}
extern void afficher_personnage(void *personnage, char *type)
{
	afficher_personnage_bis(personnage, type);
}

static int combat_personnage_bis(personnage_t *att, personnage_t *def, SDL_Window *window)
{
	err_t err = E_OK;
	char * msg=malloc(sizeof(char)*220);
	msg[0] = '\0';
	char temp[50];
	temp[0] = '\0';
	char *tempDeux = NULL;

	if (lancer_de(def->agilite, EPREUVE_FACILE(STAT_MAX_AGILI)))
	{
		return (0);
	}
	else
	{
		int degat = (att->force);
		if (lancer_de(att->critique, EPREUVE_DIFF(STAT_MAX_CRITIQ)))
		{
			degat *= 2;
		}
		degat -= (def->armure);
		if (degat < 0)
		{
			degat = 0;
		}
		def->PV -= degat;

		snprintf(temp, 50, "%s a mis %d a %s\n", att->nom, degat, def->nom);
		strcat(msg, temp);
		if ((err = lis_personnage(att, "Attaquant", (char **)&tempDeux, 28)))
		{
			MSG_ERR2("de l'écriture du message à afficher");
		}
		msg = realloc(msg, sizeof(char) * (strlen(msg) + strlen(tempDeux) + 1));
		strcat(msg, tempDeux);
		free(tempDeux);
		tempDeux = NULL;
		if ((err = lis_personnage(def, "Defenseur", (char **)&tempDeux, 28)))
		{
			MSG_ERR2("de l'écriture du message à afficher");
		}
		msg = realloc(msg, sizeof(char) * (strlen(msg) + strlen(tempDeux) + 1));
		strcat(msg, tempDeux);
		free(tempDeux);
		tempDeux = NULL;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
								 "Combat",
								 msg,
								 window);
	}
}

extern int commbat_joueur(personnage_t *personnage, personnage_t *ennemi, SDL_Window *window)
{

	while (1)
	{
		combat_personnage_bis(personnage, ennemi, window);
		if (ennemi->PV <= 0)
		{
			return 1;
		}
		combat_personnage_bis(ennemi, personnage, window);
		if (personnage->PV <= 0)
		{
			return 0;
		}
	}
}

static int crochetageBis(personnage_t *perso)
{
	if (lancer_de(perso->agilite, EPREUVE_FACILE(STAT_MAX_AGILI)))
	{
		printf("Vous avez Reussi  votre crochetage.\n");
		return 0;
	}
	else
	{
		return 1;
	}
}
extern int crochetage(void *perso)
{
	return crochetageBis(perso);
}
// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //
