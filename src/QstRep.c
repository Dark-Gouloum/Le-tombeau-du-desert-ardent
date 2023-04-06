/**
	* \file src/QstRep.c
	* \brief Définition de l'objet QstRep.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 06 Avril 2023 07:47:37
	*
	* L'objet QstRep sert à proposer des choix à l'utilisateur.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/QstRep.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_QstRep = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
typedef struct actionBouton_s {
#include "../lib/attribut_objet.h"
	char *nom;
	char codeAction;
	char *action;
} actionBouton_t;

static actionBouton_t * creer_actionBouton( char *nom , char codeAction , char *action ){
	// Créer l'objet QstRep
	actionBouton_t *actionBouton = malloc( sizeof(actionBouton_t) );
	if( !actionBouton ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'QstRep'");
		return (actionBouton_t*)NULL;
	}

	// Affecter les attributs
	( actionBouton->nom ) = malloc( sizeof(char) * (strlen(nom)+1) );
	strcpy( actionBouton->nom , nom );
	( actionBouton->action ) = malloc( sizeof(char) * (strlen(action)+1) );
	strcpy( actionBouton->action , action );
	( actionBouton->codeAction ) = codeAction;

	// Affecter les methodes
	actionBouton->detruire = (err_t (*)(void *))detruire_actionBouton;
	actionBouton->afficher = (void (*)(void *))afficher_actionBouton;

	// Renvoyer le bouton
	cmpt_actionBouton++;
	return actionBouton;
}

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet QstRep

	// Methode commune à tout les objets
static void afficher_QstRep( QstRep_t *QstRep ){
	printf("QstRep{}");
}

static err_t detruire_QstRep( QstRep_t **QstRep ){
	// Suppression des attributs de l'objet QstRep

	// Suppression de l'objet QstRep
	free( (*QstRep) );
	(*QstRep) = NULL;

	// Destruction de l'objet QstRep réussie
	cmpt_QstRep--;
	return(E_OK);
}

extern void afficherSurvivant_QstRep(){
	printf("Il reste %i QstRep_t.\n",cmpt_QstRep);
}

extern QstRep_t * creer_QstRep(){
	// Tests des paramètre


	// Créer l'objet QstRep
	QstRep_t *QstRep = malloc( sizeof(QstRep_t) );
	if( !QstRep ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'QstRep'");
		return (QstRep_t*)NULL;
	}

	// Affecter les attributs

	// Affecter les methodes
	QstRep->detruire = (err_t (*)(void *))detruire_QstRep;
	QstRep->afficher = (void (*)(void *))afficher_QstRep;

	// Renvoyer le bouton
	cmpt_QstRep++;
	return QstRep;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

