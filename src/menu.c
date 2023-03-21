/**
	* \file src/menu.c
	* \brief Définition de l'objet menu.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 14:21:44
	*
	* L'objet menu sert à créer un menu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/menu.h"
#include "../lib/liste.h"
#include "../lib/police.h"
#include "../lib/img.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
typedef struct elemListe_bouton_s {
#include "../lib/attributs_objet.h"
	char *texte;
	err_t (*action)(int argc,...);
} elemListe_bouton_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)
static liste_t *listeBoutons = NULL;

// CRÉATION(S) DE(S) FONCTION(S)
/* Définition des élément de la liste des boutons à ajouter */
static err_t detruire_elemListe_bouton( elemListe_bouton_t **e ){
	free( (*e)->texte );
	free( (*e) );
	e = NULL;
	return E_OK;
}
static elemListe_bouton_t * creer_elemListe_bouton( char *texte , err_t (*action)(int argc,...) ){
	// Créer l'objet
	elemListe_bouton_t * elem = malloc( sizeof(elemListe_bouton_t) );
	if( !elem ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'elem'");
		return NULL;
	}

	// Affecter les attributs
	elem->texte = malloc( sizeof(char) * (strlen(texte)+1) );
	if( !(elem->texte) ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'string'");
		return NULL;
	}
	strcpy( (elem->texte) , texte );
	elem->action = action;

	// Affecter les methodes
	elem->detruire = (err_t (*)(void *))detruire_elemListe_bouton;
	elem->afficher = (void (*)(void *))NULL;

	// Renvoyer le bouton
	return elem;
}
extern err_t prepaMenu(){
	if(!( listeBoutons = creer_liste() )){
		MSG_ERR2("de la création de la liste des boutons à ajouter à la fenêtre");
		return(E_AUTRE);
	}
	return(E_OK);
}

/* Définition des boutons à ajouter */
extern err_t ajouterBouton_liste( char *texte , err_t (*action)(int argc,...) ){
	void *elem = creer_elemListe_bouton( texte , action );
	return liste_ajoute(listeBoutons,elem);
}

static err_t creer_texte(police_t *p,fenetre_t *f, char *texte,SDL_Point *pos , img_t **img){
	SDL_Surface *surface = NULL;
	SDL_Rect rect;
	err_t err = E_OK;
	if( (err=police_creerSurface_texte(&surface,p,texte)) ){
		MSG_ERR2("de la création de la surface du texte.");
		return err;
	}
	if(!( *img=creer_img_ParSurface(f->rendu,&surface) )){ // Pas d'objet img de créer :
		MSG_ERR2("de la création de img");
		return E_AUTRE;
	}
	if(( err=img_demandeTaille(*img,&rect) )){
		MSG_ERR2("de la modification de img");
		return(err);
	}
	rect.x = pos->x - (rect.w / 2);
	rect.y = pos->y;
	if(( err=changerDest(img,&rect) )){
		MSG_ERR2("de la modification de img");
		return(err);
	}
	pos->x+= (rect.w/2) + 10;
	pos->y+= rect.h + 10;
	return E_OK;
}

static err_t construire_menu( fenetre_t *f , SDL_Point *dim, SDL_Point *pos, int nbCol ){
	pos->x = ( dim->x / (nbCol+1) );
	err_t err = E_OK;
	int nb = liste_taille(listeBoutons);
	int maxPosY = pos->y;
	int actuPosY = pos->y;
	int actuPosX = pos->x;
	police_t *police = NULL;
	img_t *img = NULL;

	if(!( police=creer_police(NULL,18,NULL) )){ // Pas d'objet police de créer :
		MSG_ERR2("de la création de la police d'écriture du titre de la fenetre");
		return(E_AUTRE);
	}
	for( int i=0,l=0,c=0 ; i<nb ; i++ ){
		if( c == nbCol ){
			c = 0;
			l++;
			pos->y = maxPosY;
			pos->x = actuPosX;
		}
		elemListe_bouton_t *elem = liste_recherche_obj(&err,listeBoutons,i);
		if( err ){
			MSG_ERR2("bouton non trouvé");
			return(err);
		}
		if(( err=creer_texte(police,f,elem->texte,pos,&img) )){
			MSG_ERR2("de la création du texte du bouton");
			return(err);
		}
		if(( err=ajouterBouton(f,img,elem->action) )){
			MSG_ERR2("l'ajout du bouton");
			return(err);
		}
		if( maxPosY < pos->y ){
			maxPosY = pos->y;
		}
		pos->y = actuPosY;
	}
	if(( err=police->detruire( &police ) )){
		MSG_ERR2("de la destruction de la police d'écriture du titre de la fenetre");
		return(E_AUTRE);
	}
	return(E_OK);
}

extern err_t creer_menu(Uint32 flags, char *titre, char *fond , int nbCol , fenetre_t **fenetre){
	if( *fenetre ){
		MSG_ERR(E_ARGUMENT,"Il y à déjà une fenêtre, rique de fuite de mémoire.");
		return(E_ARGUMENT);
	}
	img_t * img = NULL;
	police_t *police = NULL;
	SDL_Point dim;
	SDL_Point pos = {0,0};
	err_t err = E_OK;

	printf("Création de l'objet fenetre...");
	if(!( *fenetre=creer_fenetre(NULL,flags|SDL_WINDOW_FULLSCREEN,titre) )){
		MSG_ERR2("À la création de fenetre");
		return(E_AUTRE);
	}
	SDL_GetWindowSize( ((*fenetre)->fenetre) , &(dim.x) , &(dim.y) );
	printf("OK\n");

	if( fond ){
		printf("Ajout de l'arrière plan de la fenêtre...");
		if(!( img=creer_img((*fenetre)->rendu,fond) )){ // Pas d'objet img de créer :
			MSG_ERR2("de la création de l'arrière plan de la fenetre");
			return(E_AUTRE);
		}
		if(( err=ajouterWidget(*fenetre,img) )){
			MSG_ERR2("de l'ajout de l'arrière plan de la fenetre");
			return(err);
		}
	}

	if(!( police=creer_police(NULL,25,NULL) )){ // Pas d'objet police de créer :
		MSG_ERR2("de la création de la police d'écriture du titre de la fenetre");
		return(E_AUTRE);
	}
	pos.x = dim.x / 2;
	pos.y = 10;
	if( titre ){
		if(( err=creer_texte(police,*fenetre,titre,&pos,&img) )){
			MSG_ERR2("de la création de la police d'écriture du titre de la fenetre");
			return(err);
		}
	} else {
		if(( err=creer_texte(police,*fenetre,"MENU",&pos,&img) )){
			MSG_ERR2("de la création de la police d'écriture du titre de la fenetre");
			return(err);
		}
	}
	if(( err=ajouterWidget(*fenetre,img) )){
		MSG_ERR2("de l'ajout du titre à la fenetre");
		return(err);
	}
	if(( err=police->detruire( &police ) )){
		MSG_ERR2("de la destruction de la police d'écriture du titre de la fenetre");
		return(E_AUTRE);
	}

	return construire_menu( *fenetre , &dim,&pos, nbCol );
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

