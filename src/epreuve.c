/**
 * \file src/epreuve.c
 * \brief Définition de l'objet epreuve.
 * \author Erwan PECHON
 * \version 0.1
 * \date Mar. 11 Avril 2023 13:38:08
 *
 * L'objet epreuve sert à tester les compétence du joueur.
 *
 */

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "../lib/epreuve.h"
#include "../lib/livre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
static err_t epreuve_combat( livre_t *livre , char *ligne, int *reussi){
	*reussi = 0;
	err_t err = E_OK;
	PNJ_t *enemi = NULL;
	if(( err=lire_PNJ(ligne,&enemi) )){
		MSG_ERR2("de la lecture de l'enemi à combattre");
		return(err);
	}
	*reussi = commbat_joueur((personnage_t*)livre->joueur,(personnage_t*)enemi,livre->fenetre->fenetre);
	return(err);
}

#define F(x) ( (coeff * x) + ajout )
#define IF(y) ( (y - ajout) / coeff )
#define DIFF_SUR(a) ( (ligne_fin.a) - (ligne_deb.a) )
#define CALC_COEFF {\
	coeff = ( (abs(DIFF_SUR(y)) * 1.) / (abs(DIFF_SUR(x)) * 1.) );\
	ajout = 0.;\
	ajout = F(ligne_deb.x) - ligne_deb.y;\
}
static err_t epreuve_agilite( livre_t *livre , char *ligne, int *reussi ){
	*reussi = 0;
	// Déclaration des variables
	err_t err = E_OK;
	int difficulte = 0;
	int trace = 0;
	int erreur = 100;
	int marge = 25;
	char cmpt[10];
	for( int i=0 ; i<10 ; i++ ) cmpt[i] = '\0';
	float coeff=0. , ajout=0. ;
	SDL_Event event;
	SDL_Point dim_f={0,0};
	SDL_Point curseur={0,0} , ligne_deb={0,0} , ligne_fin={0,0} ;
	SDL_Rect rect_deb={0,0,0,0} , rect_fin={0,0,0,0} ;
	SDL_Rect cmpt_rect = { 5 , 5 , 0 , 0 };
	SDL_Color blanc = {255,255,255,255};
	SDL_Window *fen = NULL;
	SDL_Renderer *rendu = NULL;
	SDL_Surface *surface = NULL;
	SDL_Texture *cmpt_texture = NULL;
	police_t *police = NULL;
	// Affectation des variables
	if(!( police=creer_police(NULL,0,&blanc) )){ // Pas d'objet police de créer :
		printf("Erreur à la création de police.\n");
		return(E_AUTRE);
	}
	{ // Obtention de la difficulte
		char c;
		sscanf(ligne,"%c",&c);
		switch( c ){
			case 'F' : difficulte = EPREUVE_FACILE(STAT_MAX_AGILI) ; break ;
			case 'M' : difficulte = EPREUVE_MOYEN(STAT_MAX_AGILI) ; break ;
			case 'D' : difficulte = EPREUVE_DIFF(STAT_MAX_AGILI) ; break ;
			default : MSG_ERR(E_FICHIER,"Ce type de difficulté est inconnue"); return(E_FICHIER);
		}
		difficulte-= obtenir_stat(STAT_AGILITE,livre->joueur);
		difficulte+= 2;
		difficulte/= 2;
		erreur-= difficulte;
	}
	{ // Création de la fenêtre
		SDL_DisplayMode current;
		if( SDL_GetCurrentDisplayMode(0,&current) !=0 ){
			err = E_OBTENIR;
			MSG_ERR(err,"Impossible de récupérer le mode d'affichage courant");
			MSG_ERR_COMP("SDL_GetCurrentDisplayMode",SDL_GetError());
			goto Stop;
		}
		dim_f.x = current.w / 2;
		dim_f.y = current.h / 2;
		fen = SDL_CreateWindow("Épreuve d'agilité", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dim_f.x+marge, dim_f.y+marge, SDL_WINDOW_SHOWN);
		if( !fen ){
			err = E_AUTRE;
			MSG_ERR(err,"Impossible de créer la fenêtre");
			MSG_ERR_COMP("SDL_CreateWindow",SDL_GetError());
			goto Stop;
		}
		dim_f.x-= marge * 2;
		dim_f.y-= marge * 2;
		rendu = SDL_CreateRenderer(fen, -1, SDL_RENDERER_ACCELERATED);
		if( !rendu ){
			err = E_AUTRE;
			MSG_ERR(err,"Impossible de créer le rendu");
			MSG_ERR_COMP("SDL_CreateRenderer",SDL_GetError());
			goto Stop;
		}
	}
	{ // Création du compteur
		sprintf(cmpt,"%03d/%03d",0%1000,difficulte%1000);
		if( (err=police_creerSurface_texte(&surface,police,cmpt,0)) ){
			MSG_ERR2("de la création de la surface du texte.");
			err = err;
			goto Stop;
		}
		if( !(cmpt_texture=SDL_CreateTextureFromSurface( rendu , surface ))  ){
			err = E_COLOR;
			MSG_ERR(err,"La création de la texture de l'image à échouer");
			MSG_ERR_COMP("SDL_Create_TextureFromSurface",SDL_GetError());
			goto Stop;
		}
		if( SDL_QueryTexture(cmpt_texture,NULL,NULL,&(cmpt_rect.w),&(cmpt_rect.h)) ){
			MSG_ERR2("de SDL_QueryTexture");
			return E_AUTRE;
		}
		SDL_FreeSurface( surface );
		surface = NULL;
	}
	{ // Création de la première ligne
		// Définition du carrée de départ
		rect_deb.x = marge;
		rect_deb.y = marge;
		rect_deb.w = erreur / 2;
		rect_deb.h = erreur / 2;
		// Définition du carrée d'arrivé
		rect_fin.x = dim_f.x;
		rect_fin.y = dim_f.y;
		rect_fin.w = erreur / 4;
		rect_fin.h = erreur / 4;
		// Création de la première ligne
		ligne_deb.x = rect_deb.x + (rect_deb.w/2);
		ligne_deb.y = rect_deb.y + (rect_deb.h/2);
		ligne_fin.x = rect_fin.x + (rect_fin.w/2);
		ligne_fin.y = rect_fin.y + (rect_fin.h/2);
		// Calcul du coefficiant de la première ligne
		CALC_COEFF;
	}
	// Instruction
	int i=0;
	while( i<difficulte ){
		// Dessiner la ligne
		SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
		SDL_RenderDrawLine(rendu, ligne_deb.x, ligne_deb.y+rect_deb.h/2, ligne_fin.x, ligne_fin.y+rect_fin.h/2 );
		SDL_RenderDrawLine(rendu, ligne_deb.x, ligne_deb.y-rect_deb.h/2, ligne_fin.x, ligne_fin.y-rect_fin.h/2 );
		// Dessiner la zone de départ
		SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255);
		SDL_RenderFillRect(rendu,&rect_deb);
		// Dessiner la zone d'arrivé
		SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
		SDL_RenderFillRect(rendu,&rect_fin);
		// Affiché le compteur
		SDL_RenderCopy(rendu, cmpt_texture, NULL, &cmpt_rect);
		// Afficher le rendu
		SDL_RenderPresent(rendu);
		SDL_Delay(100);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEMOTION) {
				SDL_GetMouseState(&(curseur.x), &(curseur.y));
			}
		}
		// Effacer le rendu précédent
		SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
		SDL_RenderClear(rendu);
		if( trace && !SDL_PointInRect(&curseur,&rect_deb) ){
			// Vérifier si la curseur est sur la ligne
			int deltaY = (rect_fin.y) - (rect_deb.y);
			int deltaX = (rect_fin.x) - (rect_deb.x);
			double num = 0.;
			num+= deltaY * curseur.x;
			num-= deltaX * curseur.y;
			num+= (rect_fin.x) * (rect_deb.y);
			num-= (rect_fin.y) * (rect_deb.x);
			double denum = 0.;
			denum+= pow( deltaY , 2 );
			denum+= pow( deltaX , 2 );
			double distance = fabs( num ) / sqrt( denum );
			if( distance > erreur ){
				printf("PERDU\n");
				goto Stop;
			}
			// Générer une nouvelle ligne aléatoire si la curseur atteint la fin de la ligne
			if( SDL_PointInRect(&curseur,&rect_fin) ){
				rect_deb.x = rect_fin.x;
				rect_deb.y = rect_fin.y;
				rect_fin.x = ( rand() % (dim_f.x-marge*2) ) + 25;
				rect_fin.y = ( rand() % (dim_f.y-marge*2) ) + 25;
				ligne_deb.x = rect_deb.x + (rect_deb.w/2);
				ligne_deb.y = rect_deb.y + (rect_deb.h/2);
				ligne_fin.x = rect_fin.x + (rect_fin.w/2);
				ligne_fin.y = rect_fin.y + (rect_fin.h/2);
				CALC_COEFF;
				i++;
				SDL_DestroyTexture( cmpt_texture );
				cmpt_texture = NULL;
				sprintf(cmpt,"%03d/%03d",i%1000,difficulte%1000);
				if( (err=police_creerSurface_texte(&surface,police,cmpt,0)) ){
					MSG_ERR2("de la création de la surface du texte.");
					goto Stop;
				}
				if( !(cmpt_texture=SDL_CreateTextureFromSurface( rendu , surface ))  ){
					err = E_COLOR;
					MSG_ERR(err,"La création de la texture de l'image à échouer");
					MSG_ERR_COMP("SDL_Create_TextureFromSurface",SDL_GetError());
					goto Stop;
				}
				SDL_FreeSurface( surface );
				surface = NULL;
			}
		} else {
			if( SDL_PointInRect(&curseur,&rect_deb) ){
				trace = 1;
			}
		}
	}
	*reussi = 1;
Stop:
	// Libération des ressources
	if(( err=police->detruire(&police) )){
		MSG_ERR2("de la destruction de la police");
		return(err);
	}
	SDL_DestroyRenderer(rendu);
	SDL_DestroyWindow(fen);
	return(err);
}
extern err_t epreuve_type(livre_t *livre, char *ligne, int *reussi){
	err_t err = E_OK;
	switch( ligne[0] ){
		case 'A' :
			if(( err=epreuve_agilite(livre,ligne+1,reussi) )){
				MSG_ERR2("de l'épreuve d'agilité");
			}
			break;
		case 'C' :
			if(( err=epreuve_combat(livre,ligne+1,reussi) )){
				MSG_ERR2("du combat");
			}
			break;
		default :
			{
				char msg[40];
				sprintf(msg,"Le type d'épreuve '%c' est inconnue.",*(ligne-1));
				MSG_ERR(E_FICHIER,msg);
				return(E_FICHIER);
			}
	}
	return(err);
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

