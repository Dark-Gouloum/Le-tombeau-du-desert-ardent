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
static int unsigned cmpt_actionBouton = 0;
static SDL_Color cDefaut = { 0 , 0 , 0 , 255 };

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
typedef struct actionBouton_s {
#include "../lib/attributs_objet.h"
	char *nom;
	char codeAction;
	char *action;
} actionBouton_t;

static err_t detruire_actionBouton( actionBouton_t **actionBouton ){
	free( (*actionBouton)->nom );
	if( (*actionBouton)->action )
		free( (*actionBouton)->action );
	free( (*actionBouton) );
	(*actionBouton) = NULL;
	return(E_OK);
}
static void afficher_actionBouton( actionBouton_t *actionBouton ){
	printf("aB{%s:%c->%s}",actionBouton->nom,actionBouton->codeAction,actionBouton->action);
}
static actionBouton_t * creer_actionBouton( char *nom , char codeAction , char *action ){
	// Créer l'objet QstRep
	actionBouton_t *actionBouton = malloc( sizeof(actionBouton_t) );
	if( !actionBouton ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'QstRep'");
		return (actionBouton_t*)NULL;
	}

	// Affecter les attributs
	( actionBouton->nom ) = malloc( sizeof(char) * (strlen(nom)+1) );
	if( !(actionBouton->nom) ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un nom à l'objet de type 'QstRep'");
		return (actionBouton_t*)NULL;
	}
	( actionBouton->action ) = malloc( sizeof(char) * (strlen(nom)+1) );
	if( !(actionBouton->action) ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer une action à l'objet de type 'QstRep'");
		return (actionBouton_t*)NULL;
	}
	strcpy( actionBouton->nom , nom );
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
static err_t quitter(int argc,...){
	int *STOP = NULL;
	char *codeAction = NULL;
	{ // Vérification des paramètre
		if( argc < 2 ){
			MSG_ERR(E_ARGUMENT,"Pas assez d'argument");
			return(E_ARGUMENT);
		}
		va_list va ; va_start(va,argc);
		STOP = va_arg(va,int*);
		codeAction = va_arg(va,char*);
		va_end(va);
	}
	{ // Demande de fermeture de la prochaine fenêtre
		SDL_Event quitEvent;
		quitEvent.type = SDL_QUIT;
		SDL_PushEvent(&quitEvent);
	}
	*STOP = 1;
	*codeAction = '?';
	return(E_OK);
}
err_t reponse(int argc,...){
	liste_t *liste = NULL;
	char *r_codeAction = NULL;
	char **r_action = NULL;
	int *STOP = NULL;
	actionBouton_t *aB = NULL;
	int num = 0;
	err_t err = E_OK;
	{ // Tests des arguments
		if( argc < 5 ){
			MSG_ERR(E_ARGUMENT,"pas assez d'argument");
			return(E_ARGUMENT);
		}
		va_list va	;	va_start(va,argc)	;
		{ // Obtention
			liste = va_arg(va,void*);
			num = va_arg(va,int);
			STOP = va_arg(va,int*);
			r_codeAction = va_arg(va,char*);
			r_action = va_arg(va,char**);
		}
		va_end(va);
		err = E_ARGUMENT;
		{ //test
			if( num < 0 ){
				MSG_ERR(err,"Le bouton n'existe pas");
				return(err);
			}
			if( !liste ){
				MSG_ERR(err,"Il n'y à pas de liste de boutons");
				return(err);
			}
			if( !r_codeAction ){
				MSG_ERR(err,"Il n'y à pas de zone de retour du type d'action à entre-prendre");
				return(err);
			}
			int nb = liste_taille( liste );
			if( num >= nb ){
				return(quitter(2,STOP,r_codeAction));
			}
			if( !r_action ){
				MSG_ERR(err,"Il n'y à pas de zone de retour de l'action à entre-prendre");
				return(err);
			}
			if( *r_action ){
				MSG_ERR(err,"La zone de retour de l'action à entre-prendre est déjà occuper. (risque de fuite de mémoire)");
				MSG_ERR_COMP("La zone contient actuellement",*r_action);
				return(err);
			}
		}
		err = E_OK;
	}
	{ // Obtenir l'action à effectuer
		aB = liste_recherche_obj( &err , liste , num );
		if( err ){
			MSG_ERR2("de la recherche du bouton cliqué");
			return(err);
		}
		if( !aB ){
			err = E_OBTENIR;
			MSG_ERR(err,"Le bouton cliqué n'à pas était obtenu");
			return(err);
		}
	}
	{ // Remplir les zones de retour
		err = quitter(2,STOP,r_codeAction);
		*r_codeAction = aB->codeAction;
		*r_action = aB->action;
		aB->action = NULL;
		if( err ){
			MSG_ERR2("de la fermeture de la fenêtre");
		}
	}
	return(err);
}

// Methode commune à tout les objets
extern void afficherSurvivant_QstRep(){
	printf("Il reste %i bouton d'action.\n",cmpt_actionBouton);
}

#define ABS(x) (x<0)?(-x):(x)
extern err_t lancer_QstRep(SDL_Color *cPolice,char *ligne,fenetre_t *fMere,char *lstCodeAction, char *r_codeAction, char **r_action){
	printf("%s\n",*r_action);
	{ // Vérifié les paramètre
		if( !r_action ){
			MSG_ERR(E_ARGUMENT,"La zone de retour des paramètre de l'action n'existe pas");
			return(E_ARGUMENT);
		}
		if( *r_action ){
			MSG_ERR(E_ARGUMENT,"La zone de retour des paramètre de l'action est occupé");
			return(E_ARGUMENT);
		}
		if( !r_codeAction ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas de zone de retour pour le code de l'action");
			return(E_ARGUMENT);
		}
		if( !lstCodeAction ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas de liste de code d'action authorisé");
			return(E_ARGUMENT);
		}
		if( !fMere ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas de de fenêtre mére");
			return(E_ARGUMENT);
		}
		if( !ligne ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas de ligne à traiter");
			return(E_ARGUMENT);
		}
		if( !cPolice ){	cPolice = &cDefaut;	}
	}

	// Création des variables locales
	err_t err = E_OK,status=E_OK;
	police_t *police = NULL;
	liste_t *listeBoutons = NULL;
	fenetre_t *fenetre = NULL;
	SDL_Point pos = { 0 , 0 };
	char titre[ strlen(ligne) ];
	int i=0 , j=0;
	SDL_Event event;
	SDL_Point curseur;

	// Affectation des variables locales
	{ // Obtention du titre
		if( ligne[i++] != '[' ){
			err = E_ARGUMENT;
			char msg[ 40 + strlen(ligne) ];
			sprintf(msg,"'%c' est le 1er caractère lu dans '%s'",ligne[i-1],ligne);
			MSG_ERR(err,"Mauvais format");
			MSG_ERR_COMP("Il est attendu le caractère '[' en 1er position",msg);
			goto Stop;
		}
		for( ; (ligne[i]) && (ligne[i]!=']') ; i++ ){
			titre[j++] = ligne[i];
		}
		if( !(ligne[i]) ){
			err = E_FICHIER;
			MSG_ERR(err,"La question n'est pas compléte");
			goto Stop;
		}
		titre[j] = '\0';
	}
	if(!( police=creer_police(NULL,18,cPolice) )){
		MSG_ERR2("de la création de la police d'écriture");
		goto Stop;
	}
	if(!( listeBoutons=creer_liste() )){
		MSG_ERR2("de la création de la liste des boutons");
		goto Stop;
	}

	// Affecter les attributs
	{ // Création de la fenêtre
		Uint32 flags = SDL_GetWindowFlags(fMere->fenetre);
		if(( err=creer_menu(flags,titre,cPolice,NULL,&fenetre,&pos) )){
			MSG_ERR2("de la création du menu");
			goto Stop;
		}
		SDL_Color cFond = { 255-(cPolice->r) , 255-(cPolice->g) , 255-(cPolice->b) , cPolice->a };
		if(( err=changerFond(fenetre,&cFond) )){
			MSG_ERR2("du changement de la couleur du fond");
			goto Stop;
		}
	}
	{ // Analyse des boutons à ajouter
		for( i++ ; (ligne[i]) && (ligne[i]=='{') ; i++ ){ // Obtention d'un nouveau bouton
			char nomBouton[ strlen(ligne) ];
			char action[ strlen(ligne) ];
			char codeAction = '?';
			{ // Obtention du texte du bouton
				for( j=0,i++ ; (ligne[i]) && (ligne[i]!=':') ; i++ ){
					nomBouton[j++] = ligne[i];
				}
				if( !(ligne[i]) ){
					err = E_FICHIER;
					MSG_ERR(err,"Le texte du bouton n'est pas complet");
					goto Stop;
				}
				nomBouton[j] = '\0';
			}
			{ // Obtention du code de l'action du bouton
				i++;
				if( !( ligne[i] ) ){
					err = E_FICHIER;
					MSG_ERR(err,"Il n'y à pas de code d'action");
					goto Stop;
				}
				int z=0;
				codeAction = ligne[i];
				if( codeAction == '?' ){
					err = E_FICHIER;
					MSG_ERR(err,"Le code d'action '?' sert pour quitter l'application.");
					goto Stop;
				}
				while( lstCodeAction[z] && (lstCodeAction[z]!=codeAction) )
					z++;
				if( !( lstCodeAction[z] ) ){
					err = E_FICHIER;
					char msg[ 40 ];
					sprintf(msg,"Le code d'action '%c' est inconnue",codeAction);
					MSG_ERR(err,msg);
					goto Stop;
				}
			}
			{ // Obtention de l'action du bouton
				for( j=0,i++ ; (ligne[i]) && (ligne[i]!='}') ; i++ ){
					action[j++] = ligne[i];
				}
				if( !(ligne[i]) ){
					err = E_FICHIER;
					MSG_ERR(err,"L'action du bouton n'est pas complet");
					goto Stop;
				}
				action[j] = '\0';
			}
			{ // Sauvegarde des information obtenu
				actionBouton_t *act = creer_actionBouton(nomBouton,codeAction,action);
				if( !act ){
					MSG_ERR2("Le bouton n'à pas pùt être créer");
					err = E_AUTRE;
					goto Stop;
				}
				if(( err=liste_ajoute(listeBoutons,act) )){
					MSG_ERR2("de l'ajout d'un bouton à la liste");
					goto Stop;
				}
			}
		}
	}
	{ // Ajout des boutons
		int nb = liste_taille( listeBoutons );
		char *lstNomBoutons[nb+1];
		for( i=0 ; i<nb ; i++ ){
			actionBouton_t *aB = liste_recherche_obj( &err , listeBoutons , i );
			if( err ){
				char msg[ 40 ];
				sprintf(msg,"de la recherche du bouton n°%d",i+1);
				MSG_ERR2(msg);
				goto Stop;
			}
			if( !aB ){
				char msg[ 45 ];
				sprintf(msg,"Le bouton n°%d n'à pas était trouvé",i+1);
				MSG_ERR(E_OBTENIR,msg);
				goto Stop;
			}
			lstNomBoutons[i] = aB->nom;
		}
		lstNomBoutons[nb] = "Quitter";
		SDL_Color cFond = { 0 , 0 , 0 , 0 };
		if(( err=ajouterBouton_menu(fenetre,police,nb+1,lstNomBoutons,reponse,&cFond,&pos,3) )){
			MSG_ERR2("de l'ajout des boutons de réponse");
			goto Stop;
		}
	}
	{ // Redimensionné la fenêtre
		SDL_Point dim = { 0 , 0 };
		SDL_GetWindowSize( fMere->fenetre , &(dim.x) , &(dim.y) );
		SDL_SetWindowSize( fenetre->fenetre , dim.x , dim.y );
		SDL_RaiseWindow( fenetre->fenetre );
		SDL_HideWindow( fMere->fenetre );
	}

	// Attendre la réponse de l'utilisateur
	int STOP = 0;
	int numB = -1;
	while( !STOP ){
		while( SDL_PollEvent(&event) ){
			switch( event.type ){
				case SDL_QUIT :
					if(( err=quitter(2,&STOP,r_codeAction) )){
						MSG_ERR2("de la demande de fermeture de la fenetre");
						return(err);
					}
					break;
				case SDL_MOUSEBUTTONUP :
					obtenir_clique(&curseur);
					bouton_t *b = obtenir_boutonCliquer(fenetre, &curseur,&numB);
					if( b ){
						if(( err=b->action(5,listeBoutons,numB,&STOP,r_codeAction,r_action) )){
							MSG_ERR2("L'action d'un bouton");
							goto Stop;
						}
					}
			}
		}
		if(( err=rafraichir(fenetre) )){
			MSG_ERR2("du rafraichissement du contenu de la fenetre");
			goto Stop;
		}
		SDL_RenderPresent(obtenir_Renderer(fenetre));
	}
Stop:	// Quitter la fenêtre de Question Reponse
	if(( status=police->detruire(&police) )){
		MSG_ERR2("de la destruction de la police");
		if( !err ) err = status;
	}
	if(( status=listeBoutons->detruire(&listeBoutons) )){
		MSG_ERR2("de la destruction de la liste des boutons");
		if( !err ) err = status;
	}
	if(( status=fenetre->detruire(&fenetre) )){
		MSG_ERR2("de la destruction de la liste des boutons");
		if( !err ) err = status;
	}
	{ // Récuperer la fenêtre mere
		SDL_ShowWindow( fMere->fenetre );
		SDL_RaiseWindow( fMere->fenetre );
	}
	return(err);
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

