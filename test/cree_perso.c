
/**
	* \file test/cree_perso.c
	* \brief Test de l'objet cree_perso.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Jeu. 09 Mars 2023 13:59:44
	*
	* L'objet cree_perso sert à FaitQuelqueChose.
	*
	*/
// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/menu.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int STOP = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
err_t quitter(int argc,...){
	printf("%s\n",__func__);
	STOP = 1;
	return E_OK;
}
err_t fermer(int argc,...){
	printf("%s\n",__func__);
	STOP = 1;
	return E_OK;
}
err_t bonjour(int argc,...){
	printf("%s\n",__func__);
	return E_OK;
}
err_t salut(int argc,...){
	printf("%s\n",__func__);
	return E_OK;
}
err_t test(int argc,...){
	printf("%s\n",__func__);
	return E_OK;
}
err_t theFunction(int argc,...){
	printf("%s\n",__func__);
	return E_OK;
}
err_t aaarg(int argc,...){
	printf("%s\n",__func__);
	return E_OK;
}
err_t RoBoTo(int argc,...){
	printf("%s\n",__func__);
	return E_OK;
}
err_t choix(int a,...){
	return(E_OK);
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet menu. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF|SDL_IMG , IMG_INIT_PNG ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	fenetre_t *menu = NULL;
	/* Création des autres variables */
	SDL_Event event;
	SDL_Point pos,curseur;
	SDL_Color blanc = {255,255,255,255};

	// INSTRUCTION(S)
	if(( status=creer_menu(SDL_WINDOW_SHOWN,NULL,&blanc,"fond.png",2,&menu,&pos) )){
		MSG_ERR2("de la création du menu");
		goto Quit;
	}

	printf("Chargement des boutons à afficher...");
	{
		char *nomBoutons[] = {
			"quitter"
			, "fermer"
			, "bonjour"
			, "salut"
			, "test"
			, "theFunction"
			, "aaarg"
			, "RoBoTo"
		};
		err_t (*actionBoutons[])(int argc,...) = {
			quitter
			, fermer
			, bonjour
			, salut
			, test
			, theFunction
			, aaarg
			, RoBoTo
		};
		if(( status=ajouterBouton_menu( menu, 8,nomBoutons,choix, &pos,3 ) )){
			MSG_ERR2("de la création du contenu du menu");
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
				obtenir_clique(&curseur);
				bouton_t *b = obtenir_boutonCliquer(menu, &curseur,NULL);
				if( b ){
					if(( err=b->action(0) )){
						MSG_ERR2("L'action d'un bouton");
						status = err;
						goto Quit;
					}
				}
			}
		}
		if(( err=rafraichir(menu) )){
			MSG_ERR2("du rafraichissement du contenu de la fenetre");
			status = err;
			goto Quit;
		}
		SDL_RenderPresent(obtenir_Renderer(menu));
	}
	status = E_OK;

	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=menu->detruire(&menu)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de menu");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet menu. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

