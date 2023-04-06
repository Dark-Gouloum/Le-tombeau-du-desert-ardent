/**
	* \file test/QstRep.c
	* \brief Test de l'objet QstRep.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 06 Avril 2023 07:47:37
	*
	* L'objet QstRep sert à proposer des choix à l'utilisateur.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/QstRep.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet QstRep. */
int main(int argc,char *argv[]) {
	if( argc != 2 ){
		MSG_ERR(E_ARGUMENT,"Pas le bon nombre d'arguments");
		return(E_ARGUMENT);
	}
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF|SDL_IMG , IMG_INIT_PNG ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	fenetre_t *menu = NULL;
	/* Création des autres variables */
	SDL_Event event;
	SDL_Point curseur;
	SDL_Point pos = { 0 , 0 };
	if(!( liste_t listeBoutons = creer_liste() )){
		MSG_ERR2("de la création de la liste de boutons");
		return(E_AUTRE);
	}
	char * ligne = argv[1];
	char titre[ strlen(ligne) ];

	// INSTRUCTION(S)
	printf("Étude de la chaine de caractère\n");
	printf("\t- Obtention de la question...");
	if( ligne[0] != '[' ){
		err = E_ARGUMENT;
		MSG_ERR(err,"Mauvais format");
		goto Quit;
	}
	int i=1 ; j=0;
	for( ; (ligne[i]) && (ligne[i]!=']') ; i++ ){
		titre[j++] = ligne[i];
	}
	if( !(ligne[i]) ){
		err = E_FICHIER;
		MSG_ERR(,"La question n'est pas compléte");
		goto Quit;
	}
	titre[j] = '\0';
	printf("OK\n");

	printf("\t- Création de la fenêtre de dialogue...");
	if(( status=creer_menu(SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN,titre,NULL,&menu,&pos) )){
		MSG_ERR2("de la création du menu");
		goto Quit;
	}
	printf("OK\n");

	printf("\t- Création de la liste de bouton...");
	for( i++ ; (ligne[i]) && (ligne[i]=='{') ; i++ ){ // Obtention d'un nouveau bouton
		char nomBouton[ strlen(ligne) ];
		char actionBouton[ strlen(ligne) ];
		char codeAction;
		{ // Obtention du texte du bouton
			for( j=0,i++ ; (ligne[i]) && (ligne[i]!=':') ; i++ ){
				nomBouton[j++] = ligne[i];
			}
			if( !(ligne[i]) ){
				err = E_FICHIER;
				MSG_ERR(err,"Le texte du bouton n'est pas complet");
				goto Quit;
			}
			nomBouton[j] = '\0';
		}
		{ // Obtention du code de l'action du bouton
			i++;
			if( !( ligne[i] ) ){
				err = E_FICHIER
				MSG_ERR(err,"Il n'y à pas de code d'action");
				gotoQuit;
			}
			codeAction = ligne[i]
		}
		{ // Obtention de l'action du bouton
			for( j=0,i++ ; (ligne[i]) && (ligne[i]!='}') ; i++ ){
				action[j++] = ligne[i];
			}
			if( !(ligne[i]) ){
				err = E_FICHIER;
				MSG_ERR(err,"L'action du bouton n'est pas complet");
				goto Quit;
			}
			action[j] = '\0';
		}
		{ // Sauvegarde des information obtenu
			actionBouton_t *act = creer_actionBouton(nomBouton,codeAction,actionBouton);
			if( !act ){
				MSG_ERR2("Le bouton n'à pas pùt être créer");
				err = E_AUTRE;
				goto Quit;
			}
			if(( err=liste_ajoute(listeBoutons,act) )){
				MSG_ERR2("de l'ajout d'un bouton à la liste");
				goto Quit;
			}
		}
	}
	printf("OK\n");

	printf("Ajout de la liste de bouton...");
	printf("OK\n");

	printf("Attente de la réponse de l'utilisateur...\n");
	printf("OK\n");

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if(( err=fenetre->detruire(&fenetre) )){
		MSG_ERR2("de la destruction de la fenêtre");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet QstRep. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

