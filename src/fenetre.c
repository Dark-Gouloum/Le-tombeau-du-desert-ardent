/**
	* \file src/fenetre.c
	* \brief Définition de l'objet fenetre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mer. 15 Févr. 2023 14:30:07
	*
	* L'objet fenetre sert à crée et gére une fenêtre.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/fenetre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_fenetre = 0;
static Uint32 librairieInitialiser = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet fenetre
extern err_t initialisation_SDL(Uint32 choix){
	char *nomFonction = "initialisation_SDL : ";
	if( SDL_Init( SDL_INIT_VIDEO ) ){
		printf( "%sSDL_Init : %s" , MSG_E , SDL_GetError() );
		return E_INIT;
	}
	printf("%sSDL initialisé avec succés.\n",nomFonction);
	if( choix & SDL_TTF ){
		if( TTF_Init() ){
			printf( "%s%sTTF_Init : Un problème est survenu", MSG_E, nomFonction );
			return E_INIT;
		}
		librairieInitialiser+= SDL_TTF;
		printf("%sSDL_TTF initialisé avec succés.\n",nomFonction);
	}
	if( choix & SDL_IMAGE ){
		//if( TTF_Init() ){
		//printf( "%s%sTTF_Init : Un problème est survenu", MSG_E, nomFonction );
		//return E_INIT;
		//}
		//printf("%sSDL_image initialisé avec succés.\n",nomFonction);
	}
	return E_OK;
}
extern void fermer_SDL(){
	char *nomFonction = "fermer_SDL : ";
	if( librairieInitialiser & SDL_TTF ){
		TTF_Quit();
		printf("%sSDL_TTF quité avec succés.\n",nomFonction);
	}
	SDL_Quit();
	printf("%sSDL quité avec succés.\n",nomFonction);
}

extern SDL_Renderer *obtenir_Renderer( fenetre_t *f ){
	return f->rendu;
}
extern clique_t obtenir_souris( SDL_Point *point){
	Uint32 b = SDL_GetMouseState(&(point->x),&(point->y));
	if( b & SDL_BUTTON(1) )
		return CLIQUE_Gauche;
	if( b & SDL_BUTTON(2) )
		return CLIQUE_Mollette;
	if( b & SDL_BUTTON(3) )
		return CLIQUE_Droit;
	return CLIQUE_Erreur;
}
extern bouton_t *obtenir_boutonCliquer( fenetre_t *f, SDL_Point *point ){
	objet_t *bouton = NULL;
	liste_enTete( f->lstBoutons );
	while( liste_dansListe( f->lstBoutons ) ){
		liste_lit( f->lstBoutons , bouton );
		if( bouton_estCliquer( (bouton_t*)bouton , point ) ){
			return (bouton_t*)bouton;
		}
		assert(0);
		liste_suivant( f->lstBoutons );
	}
	return (bouton_t*)NULL;
}

extern err_t ajouterBouton(fenetre_t *fenetre , bouton_t *bouton){
	return liste_ajouteFin( fenetre->lstBoutons , (objet_t*)bouton );
}
extern err_t changerCouleur( fenetre_t *f , SDL_Color *c ){
	char * fonc = "changerCouleur : ";
	if( SDL_SetRenderDrawColor(f->rendu, c->r,c->g,c->b,c->a) ){
		printf("%s%sSDL_SetRenderDrawColor : %s",MSG_E,fonc, SDL_GetError());
		return E_COLOR;
	}
	return E_OK;
}
extern err_t changerFond_couleur( fenetre_t *f , SDL_Color *c ){
	char * fonc = "changerFond : ";
	err_t err = E_AUTRE;
	if(( err=changerCouleur( f,c ) ))
		return err;
	if( SDL_RenderClear(f->rendu) ){
		printf("%s%sSDL_RenderClear : %s",MSG_E,fonc, SDL_GetError());
		return E_AFFICHE;
	}
	return E_OK;
}

	// Methode commune à tout les objets
static void afficher_fenetre( fenetre_t *fenetre ){
	SDL_ShowWindow( fenetre->fenetre );
	SDL_RenderPresent( fenetre->rendu );
	SDL_Delay(100);
}

static err_t detruire_fenetre( fenetre_t **fenetre ){
	// Suppression des attributs de l'objet fenetre
	if( (*fenetre)->rendu ){
		SDL_DestroyRenderer( (*fenetre)->rendu );
	}
	if( (*fenetre)->fenetre ){
		SDL_DestroyWindow( (*fenetre)->fenetre );
	}
	( (*fenetre)->lstBoutons )->detruire( (*fenetre)->lstBoutons );

	// Suppression de l'objet fenetre
	free( (*fenetre) );
	(*fenetre) = NULL;

	// Destruction de l'objet fenetre réussie
	cmpt_fenetre--;
	return(E_OK);
}

extern void afficherSurvivant_fenetre(){
	afficherSurvivant_bouton();
	printf("Il reste %i fenetre_t.\n",cmpt_fenetre);
}

extern fenetre_t * creer_fenetre(SDL_Point dim, Uint32 flags, char *titre){
	// Définission des variables utiles
	char *nomFonction = "creer_fenetre : ";

	// Créer l'objet fenetre
	fenetre_t *fenetre = malloc( sizeof(fenetre_t) );
	if( !fenetre ){ // malloc à échouer :
		printf("%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\n",MSG_E,nomFonction);
		return (fenetre_t*)NULL;
	}

	// Affecter les attributs
	fenetre->fenetre = NULL;
	fenetre->rendu = NULL;
	if( SDL_CreateWindowAndRenderer(dim.x,dim.y, flags, &(fenetre->fenetre),&(fenetre->rendu)) ){
		printf("%s%sSDL_CreateWindowAndRenderer : %s.\n",MSG_E,nomFonction,SDL_GetError());
		return (fenetre_t*)NULL;
	}
	SDL_SetWindowTitle( fenetre->fenetre , titre );
	fenetre->lstBoutons = creer_listeObjet();

	// Affecter les methodes
	fenetre->detruire = (err_t (*)(void *))detruire_fenetre;
	fenetre->afficher = (void (*)(void *))afficher_fenetre;

	// Renvoyer le bouton
	cmpt_fenetre++;
	return fenetre;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

