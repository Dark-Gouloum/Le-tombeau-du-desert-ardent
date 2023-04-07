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
int STOP = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t quitter(int argc,...){
	printf("Quitter");
	STOP = 1;
	return E_OK;
}
err_t QstRep(int argc,...){
	err_t err = E_OK;
	va_list va; va_start(va,argc);
	Uint32 flags = va_arg(va,long);
	SDL_Color *cPolice = va_arg(va,void*);
	char *ligne = va_arg(va,char*);
	fenetre_t *fMere = va_arg(va,void*);
	char *lstCodeAction = va_arg(va,char*);
	char *r_codeAction = va_arg(va,char*);
	char **r_action = va_arg(va,char**);
	va_end(va);
	if(( err=lancer_QstRep(flags,cPolice,ligne,fMere,lstCodeAction,r_codeAction,r_action) )){
		MSG_ERR2("du lancement de la fenêtre de question-réponse");
	}
	va_end(va);
	return(err);
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet QstRep. */
int main(int argc,char *argv[]) {
	if( argc != 2 ){
		MSG_ERR(E_ARGUMENT,"Pas le bon nombre d'arguments");
		return(E_ARGUMENT);
	}
	if( argv[1][0] != '?' ){
		MSG_ERR(E_ARGUMENT,"Ce n'est pas une question");
		return(E_ARGUMENT);
	}
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF|SDL_IMG , IMG_INIT_PNG ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE;
	/* Création des autres variables */
	fenetre_t *fenetre = NULL;
	SDL_Color noir = { 0 , 0 , 0 , 255 };
	SDL_Event event;
	SDL_Point curseur;

	// INSTRUCTION(S)
	printf("Création de l'objet fenetre...");
	if(!( fenetre=creer_fenetre(NULL,SDL_WINDOW_SHOWN,"test_fenetre") )){ // Pas d'objet fenetre de créer :
		MSG_ERR2("À la création de fenetre");
		err = E_AUTRE;
		goto Quit;
	}
	printf("OK\n");

	{ // Ajout des boutons
		img_t *img = NULL;
		police_t *police = NULL;
		SDL_Point pos = { 0 , 0 };;
		SDL_Point dim = { 0 , 0 };
		// Création de la police
		if(!( police=creer_police(NULL,25,NULL) )){ // Pas d'objet police de créer :
			printf("Erreur à la création de police.\n");
			err = E_AUTRE;
			goto Quit;
		}
		printf("Ajout du contenu de la fenêtre...");
		SDL_GetWindowSize( (fenetre->fenetre) , &(dim.x) , &(dim.y) );
		char *nomBouton[] = {	"Quitter !"	,	"QstRep !"	};
		err_t (*action[])(int argc,...) = { quitter , QstRep };
		for( int i=0 ; i<2 ; i++ ){
			pos.x = dim.x / 2;
			pos.y = (3+i) * (dim.y/6);
			if(( err=placer(fenetre,police,nomBouton[i],&pos,&img) )){
				MSG_ERR2("du placement du texte sur la fenêtre");
				goto Quit;
			}
			if(( err=ajouterBouton(fenetre,img,action[i],NULL) )){
				MSG_ERR2("de l'ajout du bouton");
				goto Quit;
			}
		}
		printf("OK\n");
		// Destruction de la police
		if(( err=police->detruire(&police) )){
			printf("Erreur à la destruction de police.\n");
			goto Quit;
		}
	}

	char lstCodeAction[] = "MOI";
	char codeAction = '\0';
	char *action = NULL;
	Uint32 flags = SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN;

	printf("Attente du signal d'arrêt...\n");
	while( !STOP ){
		while( SDL_PollEvent(&event) ){
			switch( event.type ){
				case SDL_QUIT :
					STOP = 1;
					break;
				case SDL_MOUSEBUTTONUP :
					obtenir_clique(&curseur);
					bouton_t *b = obtenir_boutonCliquer(fenetre, &curseur,NULL);
					if( b ){
						if(( err=b->action(7,flags,&noir,argv[1]+1,fenetre,lstCodeAction,&codeAction,&action) )){
							MSG_ERR2("L'action d'un bouton");
							goto Quit;
						}
						if( codeAction == '?' ){
							STOP = 1;
							break;
						} else if( action ){
							switch( codeAction ){
								case 'M' :
									printf("MOI->%s\n",action);
									break;
								case 'O' :
									printf("MOI->%s<-MOI\n",action);
									break;
								case 'I' :
									printf("%s<-MOI\n",action);
									break;
								case '?' :
									STOP = 1;
									break;
								default :
									err = E_ARGUMENT;
									MSG_ERR(err,"codeAction inconnue");
									goto Quit;
							}
							free( action );
							action = NULL;
						}
					}
			}
		}
		if(( err=rafraichir(fenetre) )){
			MSG_ERR2("du rafraichissement du contenu de la fenetre");
			goto Quit;
		}
		SDL_RenderPresent(obtenir_Renderer(fenetre));
	}
	printf("...OK\n");

	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if(( err=fenetre->detruire(&fenetre) )){
		MSG_ERR2("de la destruction de la fenêtre");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(err);
}
	/* Programme qui test l'objet QstRep. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

