/**
	* \file src/blocText.c
	* \brief Définition de l'objet blocText.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 03 Avril 2023 20:43:50
	*
	* L'objet blocText sert à afficher du texte dans un bloc donnée.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/blocText.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_blocText = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet blocText
extern err_t blocText_precedant(int argc,...){
	return(E_OK);
}
static err_t commencerPage(blocText_t *bloc){
	SDL_Texture *t_page = NULL;
	{ // Copie de la page vierge
		t_page = SDL_CreateTexture(bloc->rendu, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, bloc->dest->w, bloc->dest->h);
		SDL_SetRenderTarget(bloc->rendu, t_page);
		SDL_RenderCopy(bloc->rendu, bloc->page, NULL, NULL);
		SDL_SetRenderTarget(bloc->rendu, NULL);
	}
	img_t *i_page = NULL;
	{ // Transformation dela copie en image
		if(!( i_page=creer_img_ParTexture(bloc->rendu,&t_page) )){
			MSG_ERR2("de la transformation de la copie du modele de page en page");
			return(E_AUTRE);
		}
		i_page->dest = bloc->dest;
	}
	err_t err = E_OK;
	if(( err=liste_ajoute(bloc->lstPage,i_page) )){
		MSG_ERR2("de l'ajout de la page à la liste des pages");
		return(E_AUTRE);
	}
	(bloc->pos).x = (bloc->posMin).x;
	(bloc->pos).y = (bloc->posMin).y;
	( bloc->i )++;
	return(E_OK);
}
extern err_t blocText_suivant(int argc,...){
	// Création des variables
	err_t err=E_OK;
	blocText_t *bloc = NULL;
	img_t *nouvelleLigne = NULL;
	img_t *page = NULL;
	int *sortie = NULL;

	{ // Obtenir les arguments
		if( argc < 2 ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas le bon nombre d'argument");
			return(E_ARGUMENT);
		}
		va_list va;	va_start(va,argc);
		bloc = va_arg(va,void*);
		sortie = va_arg(va,int*);
		va_end(va);
		// Vérification des arguments
		if( !bloc ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas de bloc de texte à modifier");
			return(E_ARGUMENT);
		}
		if( !sortie ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas d'espace de retour sur l'état de la page");
			return(E_ARGUMENT);
		}
	}
	SDL_Point *pos = &(bloc->pos);

	// Page à ré-initialisé ?
	if( (*sortie) == B_FIN ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de nouvelle page pour ce chapitre");
		return(E_ARGUMENT);
	} else if( (*sortie) == B_CONT ){
		if(( err=commencerPage(bloc) )){
			MSG_ERR2("de la création d'une nouvelle page");
			return(err);
		}
	}
	*sortie = B_CONT;
	page = liste_recherche_obj( &err , bloc->lstPage , (bloc->i)-1 );
	if( err ){
		MSG_ERR2("de l'obtention de la page modifier");
		return(err);
	}
	if( !page ){
		err = E_OBTENIR;
		MSG_ERR(err,"Il n'y as pas de page à modifier");
		return(err);
	}

	// Création du nouveau texte
	int MAX_LETTRE = 500;
	char str_ligne[MAX_LETTRE];
	SDL_Point maxPos = { (bloc->pos).x , (bloc->pos).y };
	int nbLigne=0;
	while( maxPos.y < (bloc->posMax).y ){
		{ // Lire la nouvelle ligne
			if( fscanf(bloc->fichier, "%[^\n]\n", str_ligne) == EOF ){
				*sortie = B_FIN;
				break;
			}
			if( strcmp(str_ligne,"===") == 0 ){
				*sortie = B_PAUSE;
				break;
			} else if( strcmp(str_ligne,"=FIN=") == 0 ){
				*sortie = B_FIN;
				break;
			}
		}
		{ // Construire la nouvelle ligne
			SDL_Surface *surface = NULL;
			if(( err=police_creerSurface_texte(&surface,bloc->police,str_ligne,(bloc->dest)->w) )){
				MSG_ERR2("de la création de la surface du texte");
				return(err);
			}
			if( !surface ){
				MSG_ERR(E_AUTRE,"la surface du texte n'à pas était créer");
				return(err);
			}
			if(!( nouvelleLigne=creer_img_ParSurface(bloc->rendu,&surface) )){
				MSG_ERR2("de la création de img");
				return(E_AUTRE);
			}
		}
		{ // Placer la nouvelle ligne
			SDL_Rect rect;
			if(( err=img_demandeTaille(nouvelleLigne,&rect) )){
				char msg[ 60 ];
				sprintf(msg,"de l'obtention de la taille de la %dième ligne du texte",nbLigne);
				MSG_ERR2(msg);
				return(err);
			}
			( rect.x ) = (bloc->pos).x;
			( rect.y ) = ( maxPos.y );
			( maxPos.y )+= ( rect.h ) + 5;
			if(( err=changerDest(nouvelleLigne,&rect) )){
				MSG_ERR2("de la modification de la ligne");
				return(err);
			}
			if( (maxPos.x) < (pos->x) )
				(maxPos.x) = (pos->x);
			printf("\tafficher(%d/%d) -> '%s'\n",maxPos.y,(bloc->posMax).y,str_ligne);
			nbLigne++;
		}
		{ // Ajouter la nouvelle ligne
			// Fixation du renderer sur la texture
			SDL_SetRenderTarget( bloc->rendu , page->image );
			// Remplissage de la texture
			SDL_RenderCopy(bloc->rendu , nouvelleLigne->image , NULL , obtenirDest(nouvelleLigne) );
			// Réstauration du renderer
			SDL_SetRenderTarget(bloc->rendu , NULL);
			// Destruction de la ligne
			if(( err=nouvelleLigne->detruire(&nouvelleLigne) )){
				char msg[ 60 ];
				sprintf(msg,"de la destruction de la %dième ligne",nbLigne);
				MSG_ERR2(msg);
				return(err);
			}
		}
	}
	(bloc->pos).x = maxPos.x;
	(bloc->pos).y = maxPos.y;
	return(E_OK);
}

static err_t dessiner_blocText(blocText_t *bloc){
	if( !bloc ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de bloc de texte à dessiner");
		return(E_ARGUMENT);
	}
	err_t err = E_OK;
	if( !(bloc->i) ){
		return(err);
	}
	img_t *page = liste_recherche_obj( &err , bloc->lstPage , (bloc->i)-1 );
	if( err ){
		MSG_ERR2("de la recherche de la page à afficher");
		return(err);
	}
	if( !page ){
		err = E_OBTENIR;
		MSG_ERR(err,"La page à afficher n'à pas éait trouvé");
		return(err);
	}
	if(( err=(page->dessiner(page)) )){
		MSG_ERR2("du dessin de la page");
		return(err);
	}
	return(err);
}

	// Methode commune à tout les objets
static void afficher_blocText( blocText_t *blocText ){
	printf("blocText{}");
}

static err_t detruire_blocText( blocText_t **blocText ){
	if( !(*blocText) ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de bloc de texte à détruire.");
		return(E_ARGUMENT);
	}

	err_t err = E_OK;
	// Suppression des attributs de l'objet blocText
	{ // Destruction de la liste des pages
		liste_t *liste = (*blocText)->lstPage;
		int nb = liste_taille(liste);
		img_t *img = NULL;
		for( int i=0 ; i<nb ; i++ ){
			img = liste_recherche_obj( &err , liste , i );
			if( err ){
				char msg[ 50 ];
				sprintf(msg,"de la recherche de la %d-ième image sur %d",i+1,nb);
				MSG_ERR2(msg);
				return(err);
			}
			if( !img ){
				char msg[ 50 ];
				sprintf(msg,"La %d-ième image sur %d, n'à pas était trouvé",i+1,nb);
				err = E_OBTENIR;
				MSG_ERR(err,msg);
				return(err);
			}
			img->dest = NULL;
		}
		img = NULL;
		if(( err=liste->detruire(&liste) )){
			MSG_ERR2("de la destruction de la liste des pages");
			return(err);
		}
	}
	{ // Destruction de la police d'écriture
		police_t *police = (*blocText)->police;
		if(( err=police->detruire(&police) )){
			MSG_ERR2("de la destruction de la police d'écriture de texte");
			return(err);
		}
	}
	SDL_DestroyTexture( (*blocText)->page );
	fclose( (*blocText)->fichier );
	detruire_widget(*blocText);

	// Suppression de l'objet blocText
	free( (*blocText) );
	(*blocText) = NULL;

	// Destruction de l'objet blocText réussie
	cmpt_blocText--;
	return(E_OK);
}

extern void afficherSurvivant_blocText(){
	afficherSurvivant_liste();
	afficherSurvivant_police();
	afficherSurvivant_img();
	printf("Il reste %i blocText_t.\n",cmpt_blocText);
}

extern blocText_t * creer_blocText(fenetre_t *fenetre, char *nom, SDL_Rect *dest, police_t **police, SDL_Color *couleur){
	// Tests des paramètre
	if( !fenetre ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de fenetre mere");
		return(NULL);
	}
	if( !nom ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de fichier à ouvrir");
		return(NULL);
	}
	if( !dest ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de zone d'affichage pour le texte");
		return(NULL);
	}

	err_t err = E_OK;
	// Créer l'objet blocText
	blocText_t *blocText = malloc( sizeof(blocText_t) );
	if( !blocText ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'blocText'");
		return (blocText_t*)NULL;
	}

	// Affecter les attributs
	( blocText->i ) = 0;
	( blocText->pos ).x = 0;	( blocText->pos ).y = 0;
	( blocText->posMin ).x = 0;	( blocText->posMin ).y = 0;
	( blocText->posMax ).x = 0;	( blocText->posMax ).y = 0;
	{ // Création de la liste des pages
		( blocText->lstPage ) = creer_liste();
		if( !( blocText->lstPage ) ){
			MSG_ERR2("de la création de la liste des images de bloc de texte");
			return (blocText_t*)NULL;
		}
	}
	{ // Ouverture du fichier de script
		char nomFichier[ 15 + strlen(nom) ];
		sprintf(nomFichier,"Annexe/texte/%s",nom);
		( blocText->fichier ) = fopen( nomFichier , "r" );
		if( !( blocText->fichier ) ){
			char msg[ 30 + strlen(nomFichier) ];
			sprintf(msg,"de l'ouverture du fichier '%s'",nomFichier);
			MSG_ERR(E_FICHIER,msg);
			return (blocText_t*)NULL;
		}
	}
	{ // Création de la police d'écriture
		if( *police ){
			( blocText->police ) = *police;
			*police = NULL;
		} else {
			( blocText->police ) = creer_police(NULL,18,NULL);
		}
		if( !( blocText->police ) ){
			MSG_ERR2("de la création de la police d'écriture du bloc de texte");
			return (blocText_t*)NULL;
		}
	}

	{ // Gestion des attributs commun aux widgets
		if(( err=init_widget(blocText,fenetre->rendu) )){
			MSG_ERR2("du passage du rendu de la fenêtre mére");
			return (blocText_t*)NULL;
		}
		if(( err=changerDest(blocText,dest) )){
			MSG_ERR2("du passage de la destination d'affichage dans la fenêtre mére");
			return (blocText_t*)NULL;
		}
	}
	{ // Création d'une page vide
		SDL_Renderer *renderer = fenetre->rendu;
		SDL_Texture *t_page = NULL;
		img_t *imgTitre = NULL;
		SDL_Color c = { 0 , 0 , 0 , 0 };
		SDL_Rect titreDest = { 0 , 0 , 0 , 0 };
		{ // Création du titre
			police_t *po = blocText->police;
			SDL_Surface *surface = NULL;
			if( (err=police_creerSurface_texte(&surface,po,nom,dest->w)) ){
				MSG_ERR2("de la création de la surface du titre.");
				return(NULL);
			}
			if( !surface ){
				err = E_OBTENIR;
				MSG_ERR(err,"La création de la surface du titre à échouer.");
				return(NULL);
			}
			if(!( imgTitre=creer_img_ParSurface(renderer,&surface) )){
				MSG_ERR2("de la création de l'image du titre");
				return(NULL);
			}
		}
		{ // Positionnement du titre
			if(( err=img_demandeTaille(imgTitre,&titreDest) )){
				MSG_ERR2("de la demande de la taille du titre");
				return(NULL);
			}
			titreDest.x = ((dest->w)/2) - ((titreDest.w)/2);
			titreDest.y = 0;
		}
		{ // Création des marges du texte
			// Marge du titre
			( (blocText->posMin).x ) = dest->x;
			( (blocText->posMin).y ) = dest->y + titreDest.h;
			// Marge des boutons de contrôle
			( (blocText->posMax).x ) = dest->x + dest->w;
			( (blocText->posMax).y ) = dest->y + dest->h - titreDest.h;
		}
		{ // Création de la page
			// Création de la texture
			t_page = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, dest->w, dest->h);
			// Sauvegarde de la couleur du renderer
			SDL_GetRenderDrawColor(renderer, &(c.r),&(c.g),&(c.b),&(c.a));
			// Fixation du renderer sur la texture
			SDL_SetRenderTarget(renderer, t_page);
			// Remplissage de la texture
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 55);
			SDL_RenderFillRect(renderer, NULL);
			SDL_RenderCopy(renderer , imgTitre->image , NULL , &titreDest );
			// Réstauration du renderer
			SDL_SetRenderTarget(renderer, NULL);
			SDL_SetRenderDrawColor(renderer, (c.r),(c.g),(c.b),(c.a));
			// Sauvegarde de la texture
			( blocText->page ) = t_page;
		}
		{ // Création des boutons de contrôle
			police_t *po = blocText->police;
			img_t *bouton = NULL;
			SDL_Rect rect = { (blocText->posMin).x , (blocText->posMax).y , (dest->w)/2 , (dest->y)+(dest->h)-((blocText->posMax).y) };
			SDL_Point pos = { 0 , 0 };
			{ // Création du bouton précédent
				// Calcul de la position
				pos.x = rect.x;
				pos.y = rect.y;
				// Placage du texte
				if(( err=placer(fenetre,po,"Precedant",&pos,&bouton) )){
					MSG_ERR2("du placement du texte sur la fenêtre");
					return(NULL);
				}
				// Activation
				int i = liste_taille( fenetre->lstBoutons );
				if(( err=ajouterBouton(fenetre,bouton,blocText_precedant,couleur) )){
					MSG_ERR2("de l'ajout du bouton");
					return(NULL);
				}
				blocText->prec = liste_recherche_obj( &err , fenetre->lstBoutons , i );
				if( err ){
					MSG_ERR2("de la recherche du bouton precedant");
					return(NULL);
				}
				if( !(blocText->prec) ){
					MSG_ERR(E_OBTENIR,"Le bouton precedant n'à pas était trouvé");
					return(NULL);
				}
				if(( err=changerDest((blocText->prec)->widget,&rect) )){
					MSG_ERR2("du changement de la zone d'affichage du bouton precedant");
					return(NULL);
				}
			}
			{ // Création du bouton suivant
				// Calcul de la position
				rect.x+= rect.w;
				pos.x = rect.x;
				pos.y = rect.y;
				// Placage du texte
				if(( err=placer(fenetre,po,"Suivant",&pos,&bouton) )){
					MSG_ERR2("du placement du texte sur la fenêtre");
					return(NULL);
				}
				// Activation
				int i = liste_taille( fenetre->lstBoutons );
				if(( err=ajouterBouton(fenetre,bouton,blocText_suivant,couleur) )){
					MSG_ERR2("de l'ajout du bouton");
					return(NULL);
				}
				blocText->suiv = liste_recherche_obj( &err , fenetre->lstBoutons , i );
				if( err ){
					MSG_ERR2("de la recherche du bouton suivant");
					return(NULL);
				}
				if( !(blocText->suiv) ){
					MSG_ERR(E_OBTENIR,"Le bouton suivant n'à pas était trouvé");
					return(NULL);
				}
				if(( err=changerDest((blocText->suiv)->widget,&rect) )){
					MSG_ERR2("du changement de la zone d'affichage du bouton suivant");
					return(NULL);
				}
			}
		}
	}

	// Affecter les methodes
	blocText->dessiner = (err_t (*)(void *))dessiner_blocText;
	blocText->detruire = (err_t (*)(void *))detruire_blocText;
	blocText->afficher = (void (*)(void *))afficher_blocText;

	if(( err=commencerPage(blocText) )){
		MSG_ERR2("de l'ajout d'une nouvelle page");
		return(NULL);
	}

	// Renvoyer le bouton
	cmpt_blocText++;
	return blocText;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

