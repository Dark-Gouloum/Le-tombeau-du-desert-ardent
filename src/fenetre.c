/**
	* \file src/fenetre.c
	* \brief Définition de l'objet fenetre.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 12:25:01
	*
	* L'objet fenetre sert à gérer une fenêtre de base.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/fenetre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_fenetre = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet fenetre
extern err_t ajouterBouton(fenetre_t *fen, void *widget, err_t (*action)(int argc,...) ){
	if( !fen ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de pointeur sur un objet fenetre_t");
		return(E_ARGUMENT);
	}
	bouton_t *b = creer_bouton(fen->rendu,widget,action);
	return liste_ajoute(fen->lstBoutons,b);
}

extern err_t ajouterWidget(fenetre_t *fen, void* widget ){
	if( !fen ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de pointeur sur un objet fenetre_t");
		return(E_ARGUMENT);
	}
	return liste_ajoute(fen->lstWidgets,widget);
}

extern err_t changerFond( fenetre_t *f , SDL_Color *c ){
	if( !f ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de pointeur sur un objet fenetre_t");
		return(E_ARGUMENT);
	}
	if( !c ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de pointeur sur la nouvelle couleur de fond");
		return(E_ARGUMENT);
	}
	if( f->fond ){
		free( f->fond );
		f->fond = NULL;
	}
	f->fond = malloc( sizeof(SDL_Color) );
	if( !(f->fond) ){
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'SDL_Color'");
		return(E_MEMOIRE);
	}
	( f->fond )->r = c->r;
	( f->fond )->g = c->g;
	( f->fond )->b = c->b;
	( f->fond )->a = c->a;
	return E_OK;
}

extern err_t clean( fenetre_t *f ){
	if( !f ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de pointeur sur un objet fenetre_t");
		return(E_ARGUMENT);
	}
	if( SDL_SetRenderDrawColor(f->rendu, (f->fond)->r,(f->fond)->g,(f->fond)->b,(f->fond)->a) ){
		MSG_ERR(E_COLOR,"Impossible de charge la couleur d'arrière plan");
		MSG_ERR_COMP("SDL_SetRenderDrawColor",SDL_GetError());
		return(E_COLOR);
	}
	if( SDL_RenderClear(f->rendu) ){
		MSG_ERR(E_COLOR,"Impossible de nettoyer la fenetre");
		MSG_ERR_COMP("SDL_RenderClear",SDL_GetError());
		return(E_AFFICHE);
	}
	return E_OK;
}

extern err_t rafraichir( fenetre_t *fenetre ){
	err_t err = E_OK;
	if(( err=clean(fenetre) )){
		MSG_ERR2("de la remise à 0 du contenu de la fenêtre");
		return(err);
	}
	for( int i=0 ; i<liste_taille(fenetre->lstWidgets) ; i++ ){
		void *w = liste_recherche_obj(&err,fenetre->lstWidgets,i);
		if( err ){
			MSG_ERR2("de la recherche d'un widget de la fenêtre");
			return(err);
		}
		if(( err=((widget_t*)w)->dessiner(w) )){
			MSG_ERR2("du dessin d'un widget de la fenêtre");
			return(err);
		}
	}
	for( int i=0 ; i<liste_taille(fenetre->lstBoutons) ; i++ ){
		bouton_t *b = liste_recherche_obj(&err,fenetre->lstBoutons,i);
		if( err ){
			MSG_ERR2("de la recherche d'un bouton de la fenêtre");
			return(err);
		}
		if(( err=b->dessiner(b) )){
			MSG_ERR2("du dessin d'un bouton de la fenêtre");
			return(err);
		}
	}
	return(err);
}

extern SDL_Renderer *obtenir_Renderer( fenetre_t *f ){
	if( !f ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de pointeur sur un objet fenetre_t");
		return(NULL);
	}
	return f->rendu;
}

extern bouton_t *obtenir_boutonCliquer( fenetre_t *f , SDL_Point *curseur ){
	err_t err = E_OK;
	for( int i=0 ; i<liste_taille(f->lstBoutons) ; i++ ){
		bouton_t *b = liste_recherche_obj(&err,f->lstBoutons,i);
		if( err ){
			MSG_ERR2("de la recherche d'un bouton de la fenêtre");
			return(NULL);
		}
		if( hover(b->widget,curseur) == 1 ){
			return(b);
		}
	}
	return NULL;
}

extern err_t ajouterBouton(fenetre_t *fen, stylo_t *s, char *txt, err_t (*fonc)(int argc,...)){
	bouton_t *bouton;
	if(!( bouton=creer_bouton( fen->rendu , s , txt , fonc) )){
		return E_AUTRE;
	}
	return liste_ajoute( fen->lstBoutons , bouton );
}
extern err_t ajouterWidget(fenetre_t *fen, void* widget){
	return liste_ajoute( fen->lstBoutons , widget );
}

extern void changerFond_couleur( fenetre_t *f , SDL_Color c ){
	(f->fond).r = c.r;
	(f->fond).g = c.g;
	(f->fond).b = c.b;
	(f->fond).a = c.a;
}
extern err_t rafraichir( fenetre_t *f ){
	char * fonc = "rafraichir : ";
	if( SDL_SetRenderDrawColor(f->rendu, (f->fond).r,(f->fond).g,(f->fond).b,(f->fond).a) ){
		printf("%s%sSDL_SetRenderDrawColor : %s",MSG_E,fonc, SDL_GetError());
		return E_COLOR;
	}
	if( SDL_RenderClear(f->rendu) ){
		printf("%s%sSDL_RenderClear : %s",MSG_E,fonc, SDL_GetError());
		return E_AFFICHE;
	}
	for( int i=0 ; i<liste_taille( f->lstWidgets ) ; i++ ){
		widget_t *widget = liste_lit( f->lstWidgets , i);
		widget->dessiner( &taille , f->rendu , widget );
		taille.x = tailleCB.x	;	taille.y = tailleCB.y	;
	}
	for( int i=0 ; i<liste_taille( f->lstBoutons ) ; i++ ){
		widget_t *widget = liste_lit( f->lstBoutons , i);
		widget->dessiner( &taille , f->rendu , widget );
		taille.x = tailleCB.x	;	taille.y = tailleCB.y	;
	}
	return E_OK;
}

	// Methode commune à tout les objets
static void afficher_fenetre( fenetre_t *fenetre ){
	printf("fenetre{}");
}

static err_t detruire_fenetre( fenetre_t **fenetre ){
	if( !(*fenetre) ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de fenetre à détruire");
		return(E_ARGUMENT);
	}
	// Suppression des attributs de l'objet fenetre
	if( (*fenetre)->rendu )
		SDL_DestroyRenderer( (*fenetre)->rendu );
	if( (*fenetre)->fenetre )
		SDL_DestroyWindow( (*fenetre)->fenetre );
	if( (*fenetre)->fond )
		free( (*fenetre)->fond );
	if( (*fenetre)->lstBoutons )
		( (*fenetre)->lstBoutons )->detruire(&( (*fenetre)->lstBoutons ));
	if( (*fenetre)->lstWidgets )
		( (*fenetre)->lstWidgets )->detruire(&( (*fenetre)->lstWidgets ));

	// Suppression de l'objet fenetre
	free( (*fenetre) );
	(*fenetre) = NULL;

	// Destruction de l'objet fenetre réussie
	cmpt_fenetre--;
	return(E_OK);
}

extern void afficherSurvivant_fenetre(){
	afficherSurvivant_liste();
	printf("Il reste %i fenetre_t.\n",cmpt_fenetre);
}

extern fenetre_t * creer_fenetre(SDL_Point *dim, Uint32 flags, char *titre){
	// Tests des paramètre
	int dimX=500 , dimY=500;
	if( dim ){
		dimX = dim->x;
		dimY = dim->y;
	}

	// Créer l'objet fenetre
	fenetre_t *fenetre = malloc( sizeof(fenetre_t) );
	if( !fenetre ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'fenetre'");
		return (fenetre_t*)NULL;
	}

	// Affecter les attributs
	if( SDL_CreateWindowAndRenderer(dimX,dimY, flags, &(fenetre->fenetre),&(fenetre->rendu)) ){
		MSG_ERR2("de la création de la fenetre et de son renderer.");
		MSG_ERR_COMP("SDL_CreateWindowAndRenderer",SDL_GetError());
		return(NULL);
	}
	if( titre ){
		SDL_SetWindowTitle( (fenetre->fenetre) , titre );
	}
	( fenetre->lstBoutons ) = creer_liste();
	( fenetre->lstWidgets ) = creer_liste();
	SDL_Color c = {255,125,0,255};
	if(( changerFond(fenetre,&c) )){
		MSG_ERR2("du changement de la couleur d'arrière plan de la fenetre.");
		return(NULL);
	}


	// Affecter les methodes
	fenetre->detruire = (err_t (*)(void *))detruire_fenetre;
	fenetre->afficher = (void (*)(void *))afficher_fenetre;

	// Renvoyer le bouton
	cmpt_fenetre++;
	return fenetre;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

