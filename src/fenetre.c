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
extern err_t ajouterBouton(fenetre_t *fen, void *widget, err_t (*action)(int argc,...), SDL_Color *couleur ){
	if( !fen ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de pointeur sur un objet fenetre_t");
		return(E_ARGUMENT);
	}
	bouton_t *b = creer_bouton(fen->rendu,widget,action,couleur);
	err_t err = E_OK;
	if(( err=liste_ajoute(fen->lstBoutons,b) )){
		MSG_ERR2("de l'ajout d'un widget à la fenêtre");
	}
	return(err);
}

extern err_t ajouterWidget(fenetre_t *fen, void* widget ){
	if( !fen ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de pointeur sur un objet fenetre_t");
		return(E_ARGUMENT);
	}
	err_t err = E_OK;
	if(( err=liste_ajoute(fen->lstWidgets,widget) )){
		MSG_ERR2("de l'ajout d'un widget à la fenêtre");
	}
	return(err);
}

extern err_t placer(fenetre_t *f, police_t *p, char *texte,SDL_Point *pos , img_t **img){
	// Vérifications des paramètres

	// Initialisation des variables
	SDL_Surface *surface = NULL;
	SDL_Rect rect;
	err_t err = E_OK;

	// Création de l'image
	if( p ){ // Si il y à une police, c'est du texte :
		if( (err=police_creerSurface_texte(&surface,p,texte,0)) ){
			MSG_ERR2("de la création de la surface du texte.");
			return err;
		}
		if(!( *img=creer_img_ParSurface(f->rendu,&surface) )){ // Pas d'objet img de créer :
			MSG_ERR2("de la création de img");
			return E_AUTRE;
		}
	} else { // Sinon, c'est une image
		if(!( *img=creer_img(f->rendu,texte) )){ // Pas d'objet img de créer :
			MSG_ERR2("de la création de img");
			return E_AUTRE;
		}
	}

	// Positionement du texte, sur le point indiqué
	if(( err=img_demandeTaille(*img,&rect) )){
		MSG_ERR2("de la modification de img");
		return(err);
	}
	rect.x = pos->x - (rect.w / 2);
	rect.y = pos->y - (rect.h / 2);
	if(( err=changerDest(*img,&rect) )){
		MSG_ERR2("de la modification de img");
		return(err);
	}

	// Renvoit des coordonée du bord en bas à droite
	pos->x+= rect.w  + SEP_WIDGET;
	pos->y+= rect.h + SEP_WIDGET;
	return E_OK;
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

#define arrondi 0.01
#define egalF(val1,val2) ( ((val2-arrondi)<val1) && (val1<(val2+arrondi) ) )
extern err_t rafraichir( fenetre_t *fenetre ){
	err_t err = E_OK;
	SDL_Point *vDim = &(fenetre->dim);
	SDL_Point dim = {0,0};
	SDL_GetWindowSize( fenetre->fenetre , &(dim.x) , &(dim.y) );
	float pL = ((float)dim.x) / ((float)vDim->x) ;
	float pH = ((float)dim.y) / ((float)vDim->y) ;
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
		if( (!egalF(pL,1) || !egalF(pH,1)) && ((widget_t*)w)->dest ){
			if(( err=actualiserDest(w,pL,pH) )){
				MSG_ERR2("de l'actualisation de la taille du widget");
				return(err);
			}
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
		if( (!egalF(pL,1) || !egalF(pH,1)) && (b->widget)->dest ){
			if(( err=actualiserDest(b->widget,pL,pH) )){
				MSG_ERR2("de l'actualisation de la taille du widget");
				return(err);
			}
		}
		if(( err=b->dessiner(b) )){
			MSG_ERR2("du dessin d'un bouton de la fenêtre");
			return(err);
		}
	}
	vDim->x = dim.x;
	vDim->y = dim.y;
	return(err);
}

extern SDL_Renderer *obtenir_Renderer( fenetre_t *f ){
	if( !f ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de pointeur sur un objet fenetre_t");
		return(NULL);
	}
	return f->rendu;
}

extern bouton_t *obtenir_boutonCliquer( fenetre_t *f , SDL_Point *curseur , int *ret ){
	err_t err = E_OK;
	if( ret ){	*ret = -1;	};
	for( int i=0 ; i<liste_taille(f->lstBoutons) ; i++ ){
		bouton_t *b = liste_recherche_obj(&err,f->lstBoutons,i);
		if( err ){
			MSG_ERR2("de la recherche d'un bouton de la fenêtre");
			return(NULL);
		}
		if( (b!=NULL) && (b->montrer) && (hover(b->widget,curseur)==1) ){
			if( ret ){	*ret = i;	};
			return(b);
		}
	}
	return(NULL);
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
	// Créer l'objet fenetre
	fenetre_t *fenetre = malloc( sizeof(fenetre_t) );
	if( !fenetre ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'fenetre'");
		return (fenetre_t*)NULL;
	}

	// Affecter les attributs
	if( dim ){
		( fenetre->dim ).x = dim->x;
		( fenetre->dim ).y = dim->y;
	} else {
		( fenetre->dim ).x = 500;
		( fenetre->dim ).y = 500;
	}
	dim = &( fenetre->dim );
	if( SDL_CreateWindowAndRenderer(dim->x,dim->y, flags, &(fenetre->fenetre),&(fenetre->rendu)) ){
		MSG_ERR2("de la création de la fenetre et de son renderer.");
		MSG_ERR_COMP("SDL_CreateWindowAndRenderer",SDL_GetError());
		return(NULL);
	}
	dim = NULL;
	if( titre ){
		SDL_SetWindowTitle( (fenetre->fenetre) , titre );
	}
	( fenetre->lstBoutons ) = creer_liste();
	( fenetre->lstWidgets ) = creer_liste();
	( fenetre->fond ) = NULL;
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

