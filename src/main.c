/**
	* \file main.c
	* \brief Le fichier source du produit final
	* \author Clement FEFEU ; Victor FOUQUERAY ; Dylan GRAMMONT ; Erwan PECHON
	* \version 0.1
	* \date Ven. 27 Janv. 2023 14:27:35
	*
	* Le fichier source du jeu 'Le tombeau du désert ardent'.
	* Aller voir le README.md pour plus de détaille.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "../lib/commun.h"
#include "../lib/menu.h"
#include "../lib/cree_perso.h"
#include "../lib/joueur.h"
#include "../lib/livre.h"


#include <time.h>


// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned STOP = 0;
err_t err=E_AUTRE, status=E_AUTRE;
#define FICHIER_TEST "test"

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

err_t lancerJeu(joueur_t * joueur){
	livre_t *livre = NULL;
	SDL_Event event;
	police_t *police = NULL;
	SDL_Color stylo = {92,75,43,255};
	{ // Création de la police d'écriture
		police=creer_police(NULL,30,&stylo);
		if( !police ){
			MSG_ERR2("de la création de la police d'écriture");
			err = E_AUTRE;
			return err;
		}
	}
	printf("Création du livre...\n");
	if(!( livre=creer_livre(SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN,"test_texte","livreOuvertPlacement.png",NULL,&police,joueur) )){
		MSG_ERR2("de la création du livre");
		err = E_AUTRE;
		return err;
	}
	printf("OK\n");

	printf("Ouverture du fichier de test...\n");
	if(( err=nouveauChapitre(livre,FICHIER_TEST) )){
		MSG_ERR2("de l'ouverture du fichier de test");
		return err;
	}
	printf("OK\n");

	printf("Attente d'un signal...\n");
	err = E_AUTRE;
	int STOP = 0;
	while( !STOP ){
		while( SDL_PollEvent(&event) ){
			if( event.type == SDL_QUIT )
				STOP = 1;
			else if( (event.type==SDL_MOUSEBUTTONUP) ){
				if(( err=livre_cliquer(livre,&STOP) )){
					MSG_ERR2("de l'activtion du bouton");
					return err;
				}
			}
		}
		if(( err=livre_rafraichir(livre) )){
			MSG_ERR2("du rafraichissement du contenu du livre");
			return err;
		}
	}
	printf("OK\n");
	return(E_OK);
}

// CRÉATION(S) DE(S) FONCTION(S)
err_t jouer(int argc,...){


	joueur_t * joueur = NULL;

	liste_t * item_list = creer_liste();
	if( item_list == NULL ){
		MSG_ERR(E_MEMOIRE,"Erreur lors de la création de la liste");
		return E_MEMOIRE;
	}
	/* Création des item */
	liste_ajoute(item_list,creer_item("item/bag.png"));
	liste_ajoute(item_list,creer_item("item/amulatte.png"));
	liste_ajoute(item_list,creer_item("item/armure.png"));
	liste_ajoute(item_list,creer_item("item/bouc.png"));
	liste_ajoute(item_list,creer_item("item/coupe.png"));
	liste_ajoute(item_list,creer_item("item/epee.png"));
	liste_ajoute(item_list,creer_item("item/fromage.png"));
	liste_ajoute(item_list,creer_item("item/gant.png"));
	liste_ajoute(item_list,creer_item("item/gelano.png"));

	/*ajouter valeur item*/
	ajouterModificateur(liste_recherche_obj(&err,item_list,0),STAT_PV,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,1),STAT_INTEL,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,2),STAT_ARMURE,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,3),STAT_ARMURE,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,4),STAT_INTEL,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,5),STAT_FORCE,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,6),STAT_PV,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,7),STAT_AGILITE,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,8),STAT_INTEL,1);

	item_list->afficher(item_list);

	creationPersonnage(&joueur,item_list,3);
	afficher_personnage(joueur,NULL);
	lancerJeu(joueur);
	STOP = 1;
	return E_OK;
}
err_t charger(int argc,...){
	printf("Bouton \"Charger\" cliqué !\n");
	return E_OK;
}
err_t options(int argc,...){
	printf("Bouton \"Options\" cliqué !\n");
	return E_OK;
}
err_t quitter(int argc,...){
	printf("Bouton \"Quitter\" cliqué !\n");
	STOP = 1;
	return E_OK;
}
err_t choixBouton(int argc,...){
	err_t err = E_OK;
	if( argc < 1 ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas assez d'arguments");
		return(E_ARGUMENT);
	}
	va_list va;
	va_start(va,argc);
	int i = va_arg(va,int);
	switch( i ){
		case 0 :	err=jouer(0);	break; //nouvelle partie
		case 1 :	err=charger(0);	break; //charger partie
		case 2 :	err=options(0);	break; //Options générale
		case 3 :	err=quitter(0);	break;
		default:
			err=E_ARGUMENT;
			char msg[ 40 ];
			sprintf(msg,"bouton inconnu : il faut 0<= %d < 9",i);
			MSG_ERR(err,msg);
	}
	va_end(va);
	return(err);
}
	

// PROGRAMME PRINCIPALE
int main(int argc, char *argv[]){  /* Programme qui lance le tombeau du desert ardent */
	// INITIALISATION DE(S) VARIABLE(S)
	//Lancement de la génération de nombre aléatoire
	 srand( time( NULL ) );
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t status=E_AUTRE;
	/* Création des autres variables */
		// Couleurs
	SDL_Color cEcriture = {255,255,255,255};
		// Gestion de la fenetre
	fenetre_t *fenetre = NULL;
	SDL_Point pos = { 0 , 0 };
	SDL_Point curseur;
	SDL_Event event;

	// INSTRUCTION(S)
	if(( status=creer_menu(SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN,NULL,&cEcriture,"fond.png",&fenetre,&pos) )){
		MSG_ERR2("de la création du menu");
		goto Quit;
	}

	printf("Chargement des boutons à afficher...\n");
	{ // Création du menu :
		// Création des noms
		char *nomBoutons[] = {
			"Jouer !"
			, "Charger"
			, "Options"
			, "Q uitter"
		};
		int nbBouton = TAILLE(nomBoutons);
		// Création de la police des boutons
		police_t *police = creer_police(NULL,20,&cEcriture);
		if( !police ){
			MSG_ERR2("de la création de la police d'écriture des boutons");
			status=E_AUTRE;
			goto Quit;
		}
		printf("\t%d boutons charger.\n",nbBouton );
		if(( status=ajouterBouton_menu(fenetre, police,nbBouton,nomBoutons, choixBouton,NULL, &pos,1) )){
			MSG_ERR2("de la création du contenu du menu");
			goto Quit;
		}
		printf("\t%d boutons ajouter.\n",nbBouton );
		// Destruction de la police des boutons
		if(( status=police->detruire(&police) )){
			MSG_ERR2("de la destruction de la police d'écriture des boutons");
			goto Quit;
		}
	}
	printf("OK\n");

	status = E_AUTRE;
	while( !STOP ){
		while( SDL_PollEvent(&event) ){
			if( event.type == SDL_QUIT )
				STOP = 1;
			else if( (event.type==SDL_MOUSEBUTTONUP) ){
				int numBouton;
				obtenir_clique(&curseur);
				bouton_t *b = obtenir_boutonCliquer(fenetre, &curseur, &numBouton);
				if( b ){
					if(( status=b->action(1,numBouton) )){
						MSG_ERR2("L'action d'un bouton");
						goto Quit;
					}
				}
			}
		}
		if(( status=rafraichir(fenetre) )){
			MSG_ERR2("du rafraichissement du contenu de la fenetre");
			goto Quit;
		}
		SDL_RenderPresent(obtenir_Renderer(fenetre));
	}
	status = E_OK;

	// FIN DU PROGRAMME
Quit:
	if(( status = fenetre->detruire( &fenetre ) )){ // Echec à la destruction :
		printf("Erreur à la destruction de fenetre.\n");
		return(status);
	}
	fermer_SDL();
	/* Affichage de fin */
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU PROGRAMME\t\t\n\n");
	return(status);
} /* Programme qui lance le tombeau du desert ardent */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //
