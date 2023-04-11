/**
 * \file src/livre.c
 * \brief Définition de l'objet livre.
 * \author Erwan PECHON
 * \version 0.1
 * \date Lun. 03 Avril 2023 20:43:50
 *
 * L'objet livre sert à afficher du texte dans un livre donnée.
 *
 */

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/livre.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
#define TEXT_FIN 0
#define TEXT_NOUVEAU 1
#define TEXT_CONTINU 2
#define TEXT_QUESTION 3
#define MAX_LETTRE 500
static int unsigned cmpt_livre = 0;
extern char *chapDefaut = "intro";
extern char *histoireDefaut = "Origine";

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
// Fonctions spéciale d'un objet livre
static SDL_Rect * obtenirDestPage( livre_t *livre ){
	return &( (livre->zoneAff)[(livre->i)%2] );
}
static err_t ajouterImg( livre_t *livre , img_t *img ){
	err_t err = E_OK;
	img->dest = obtenirDestPage(livre);
	if(( err=liste_ajoute(livre->lstPage,img) )){
		MSG_ERR2("de l'ajout de la page à la liste des pages");
		return(E_AUTRE);
	}
	(livre->pos).x = 0;
	(livre->pos).y = 0;
	( livre->i )++;
	return(err);
}
static err_t commencerPage(livre_t *livre){
	SDL_Texture *t_page = NULL;
	SDL_Renderer *rendu = livre->fenetre->rendu;
	SDL_Point limAff = {	( (livre->zoneAff)[0] ).w	,	( (livre->zoneAff)[0] ).h	};
	{ // Copie de la page vierge
		t_page = SDL_CreateTexture(rendu, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, limAff.x, limAff.y);
		SDL_SetRenderTarget(rendu, t_page);
		SDL_RenderCopy(rendu, livre->page, NULL, NULL);
		SDL_SetRenderTarget(rendu, NULL);
	}
	err_t err = E_OK;
	{ // Ajout de la page vierge
		img_t *i_page = NULL;
		if(!( i_page=creer_img_ParTexture(rendu,&t_page) )){
			MSG_ERR2("de la transformation de la copie du modele de page en page");
			return(E_AUTRE);
		}
		if(( err=ajouterImg(livre,i_page) )){
			MSG_ERR2("de l'ajout de la page dans le livre");
			return(err);
		}
	}
	return(E_OK);
}

static err_t ajouterImgF( livre_t *livre , char *nomImg ){
	err_t err = E_OK;
	img_t *img = creer_img(livre->fenetre->rendu,nomImg);
	if( !img ){
		MSG_ERR2("du chargement de l'image");
		return(err);
	}
	if(( err=ajouterImg(livre,img) )){
		MSG_ERR2("de l'ajout de l'image");
		return(err);
	}
	( livre->avance ) = TEXT_NOUVEAU;
	return(err);
}
static err_t ajouterTexte( livre_t *livre , char *ligne , img_t *page , int *maxPosY ){
	err_t err=E_OK;
	img_t *nouvelleLigne = NULL;
	{ // Construire la nouvelle ligne
		SDL_Surface *surface = NULL;
		if(( err=police_creerSurface_texte(&surface,livre->police,ligne,(page->dest)->w) )){
			MSG_ERR2("de la création de la surface du texte");
			return(err);
		}
		if( !surface ){
			MSG_ERR(E_AUTRE,"la surface du texte n'à pas était créer");
			return(err);
		}
		if(!( nouvelleLigne=creer_img_ParSurface(page->rendu,&surface) )){
			MSG_ERR2("de la création de img");
			return(E_AUTRE);
		}
	}
	{ // Placer la nouvelle ligne
		SDL_Rect rect;
		if(( err=img_demandeTaille(nouvelleLigne,&rect) )){
			MSG_ERR2("de l'obtention de la taille de la nouvelle ligne du texte");
			return(err);
		}
		( rect.x ) = (livre->pos).x;
		( rect.y ) = ( *maxPosY );
		( *maxPosY )+= ( rect.h ) + 5;
		if(( err=changerDest(nouvelleLigne,&rect) )){
			MSG_ERR2("de la modification de la ligne");
			return(err);
		}
	}
	{ // Ajouter la nouvelle ligne
		// Fixation du renderer sur la texture
		SDL_SetRenderTarget( page->rendu , page->image );
		// Remplissage de la texture
		SDL_RenderCopy(page->rendu , nouvelleLigne->image , NULL , obtenirDest(nouvelleLigne) );
		// Réstauration du renderer
		SDL_SetRenderTarget(page->rendu , NULL);
		// Destruction de la ligne
		if(( err=nouvelleLigne->detruire(&nouvelleLigne) )){
			MSG_ERR2("de la destruction de la nouvelle ligne");
			return(err);
		}
	}
	return(E_OK);
}

static err_t sautLabel( livre_t *livre , char *label ){
	char ligne[MAX_LETTRE];
	(livre->avance) = TEXT_CONTINU;
	while( fscanf(livre->fichier, "%[^\n]\n", ligne) != EOF ){
		if( ligne[0] == ':' ){
			if( strcmp(ligne+1,label) == 0 ){
				return(E_OK);
			}
		} else if( strcmp(ligne,"=FIN=") == 0 ){
			break;
		}
	}
	(livre->avance) = TEXT_FIN;
	return(E_OK);
}
#define PRENDRE(var,type,fin,ligne) {\
	sscanf(ligne,type,var);\
	while( ligne[0] && (ligne[0]!=fin) ) ligne++;\
}
static err_t gererInventaire( livre_t *livre , char *ligne ){
	err_t err = E_OK;
	int nbAjout = 0;
	liste_t *liste = NULL;
	// Obtenir les donée de la ligne
	PRENDRE(&nbAjout,"%d{",'{',ligne);
	if( nbAjout < 0 ){
		liste = livre->joueur->listItem;
	} else {
		if(!( liste=creer_liste() )){
			MSG_ERR2("de la création de la liste d'item");
			return(err);
		}
		while( ligne[0] && (ligne[0]=='{') ){
			ligne++;
			item_t *item = NULL;
			{ // Obtention du nom
				char nom[ strlen(ligne)+1 ];
				PRENDRE(nom,"%[^(](",'(',ligne);
				if(!( item = creer_item(nom) )){
					MSG_ERR2("de la création d'un item");
					return(err);
				}
			}
			while( ligne[0] && (ligne[0]=='(') ){
				ligne++;
				char lMod = ligne[0];
				ligne++;
				int vMod = 0;
				stat_t sMod = STAT_UNK;
				PRENDRE(&vMod,"%d)",')',ligne);
				ligne++;
				switch( lMod ){
					case 'F' :	sMod = STAT_FORCE ;	break;
					case 'I' :	sMod = STAT_INTEL ;	break;
					case 'P' :	sMod =  STAT_PV   ;	break;
					case 'D' :	sMod= STAT_ARMURE ;	break;
					case 'C' :	sMod=STAT_CRITIQUE;	break;
					case 'A' :	sMod=STAT_AGILITE ;	break;
				}
				if(( err=ajouterModificateur(item,sMod,vMod) )){
					MSG_ERR2("de l'ajout d'un modificateur à l'objet");
					return(err);
				}
			}
			if( !(ligne[0]) || (ligne[0]!='}') ){
				MSG_ERR(E_FICHIER,"La liste de modificateur de l'objet est incomplete");
				return(E_FICHIER);
			}
			if(( err=liste_ajoute(liste,item) )){
				MSG_ERR2("de l'ajout d'un objet à la liste d'item");
				return(err);
			}
			ligne++;
		}
	}
	int ret = 0;
	if(( err=choix_item(livre->fenetre,livre->joueur,liste,nbAjout,&ret) )){
		MSG_ERR2("du choix des items");
		return(err);
	}
	if( nbAjout < 0 ){
		liste = NULL;
	} else {
		if(( err=liste->detruire(&liste) )){
			MSG_ERR2("de la destruction de la liste d'item");
			return(err);
		}
	}
	( livre->avance ) = TEXT_CONTINU;
	return(err);
}
static err_t epreuvePerso( livre_t *livre , char *ligne ){
	err_t err = E_OK;
	int reussi = 0;
	switch( *(ligne++) ){
		case 'C' :
			{
				PNJ_t *enemi = NULL;
				if(( err=lire_PNJ(ligne,&enemi) )){
				}
				assert(0);
			}
		default :
			{
				char msg[40];
				sprintf(msg,"Le type d'épreuve '%c' est inconnue.",*(ligne-1));
				MSG_ERR(E_FICHIER,msg);
				return(E_FICHIER);
			}
	}
	while( ligne[0] && (ligne[0]!='>') ) ligne++;
	if( !reussi ){
		while( ligne[0] && (ligne[0]!='|') ) ligne++;
	}
	ligne++;
	char label[ strlen(ligne) + 1 ];
	int i=0;
	for( i=0 ; ligne[i] && (ligne[i]!='|') ; i++ ) label[i] = ligne[i];
	label[i] = '\0';
	sautLabel( livre , label );
	( livre->avance ) = TEXT_CONTINU;
	return(err);
}
static err_t enlever_derniere_page( livre_t *livre ){
	err_t err = E_OK;
	if(( err=liste_enlever_pos(livre->lstPage,(livre->i)-1) )){
		MSG_ERR2("de la suppression de la dernière page");
		return(err);
	}
	( livre->i )--;
	( livre->avance ) = TEXT_NOUVEAU;
	return(err);
}

#define LSTCODE "POVE"
static err_t traiterCode( livre_t *livre , char codeAction , char *action , int *continuer ){
	err_t err = E_OK;
	{ // Vérifier les paramètre
		if( !livre ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas de livre à modifier");
			return(E_ARGUMENT);
		}
		if( !continuer ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas de variable pour indiquer s'il faut faire une pause ou continuer à écrire");
			return(E_ARGUMENT);
		}
	}
	*continuer = 0;
	switch( codeAction ){
		case '?' :
			(livre->avance) = TEXT_FIN;
			SDL_Event quitEvent;
			quitEvent.type = SDL_QUIT;
			SDL_PushEvent(&quitEvent);
			break;
		case 'P' :
			{
				int nbL = 0;
				sscanf(action+1,"%d",&nbL);
				char ligne[MAX_LETTRE];
				for( int i=0 ; (i<nbL) && (fscanf(livre->fichier,"%[^\n]\n",ligne)!=EOF) ; i++ ){
					if( strcmp(ligne,"=FIN=") == 0 ){
						(livre->avance) = TEXT_FIN;
						return(E_OK);
					}
				}
			}
			*continuer = 1;
			(livre->avance) = TEXT_CONTINU;
			break;
		case 'O' :
			if(( err=nouveauChapitre(livre,action+1) )){
				MSG_ERR2("du changement de chapitre");
				return(err);
			}
			break;
		case 'V' :
			if(( err=sautLabel(livre,action) )){
				MSG_ERR2("du saut vers un label");
				return(err);
			}
			*continuer = 1;
			(livre->avance) = TEXT_CONTINU;
			break;
		case 'E' :
			if(( err=epreuvePerso(livre,action+1) )){
				MSG_ERR2("d'une épreuve du joueur");
				return(err);
			}
			break;
		default :
			err=E_ARGUMENT;
			char msg[35];
			sprintf(msg,"Le code d'action '%c' est inconnue",codeAction);
			MSG_ERR(err,msg);
	}
	return(err);
}
static err_t livre_precedant(livre_t *livre){
	// Création des variables
	if( (livre->i) <= 2 ){
		MSG_ERR(E_OBTENIR,"Il n'y à pas de page précédente");
		return(E_OBTENIR);
	}
	( livre->i )-= ( ((livre->i)%2) == 0) + 1;
	return(E_OK);
}
static err_t livre_suivant(livre_t *livre){
	// Création des variables
	err_t err=E_OK;
	img_t *page = NULL;
	if( !(livre->fichier) ){
		MSG_ERR(E_FICHIER,"Il n'y à pas de fichier à lire");
		return(E_FICHIER);
	}

	{ // Vérifié s'il faut charger une page déjà créer
		int nb = liste_taille( livre->lstPage );
		if( (livre->i) < (nb-1) ){
			( livre->i )+= 2;
			return(E_OK);
		} else if( (livre->i) < nb ){
			( livre->i )+= 1;
			return(E_OK);
		}
	}
	SDL_Point *pos = &(livre->pos);

	// Page à ré-initialisé ?
	int nouvellePage = 0;
	if( (livre->avance) == TEXT_FIN ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de nouvelle page pour ce chapitre");
		return(E_ARGUMENT);
	} else if( (livre->avance) == TEXT_NOUVEAU ){
		if(( err=commencerPage(livre) )){
			MSG_ERR2("de la création d'une nouvelle page");
			return(err);
		}
		nouvellePage = 1;
	}
	(livre->avance) = TEXT_NOUVEAU;
	page = liste_recherche_obj( &err , livre->lstPage , (livre->i)-1 );
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
	char str_ligne[MAX_LETTRE];
	SDL_Point maxPos = { (livre->pos).x , (livre->pos).y };
	int texte = 1;
	while( texte && (maxPos.y<(page->dest->h-100)) ){
		texte = 0;
		if( fscanf(livre->fichier, "%[^\n]\n", str_ligne) == EOF ){
			(livre->avance) = TEXT_FIN;
			goto Stop;
		}
		int tailleLigne = strlen(str_ligne);
		while( str_ligne[tailleLigne-1]=='\\' ){
			str_ligne[--tailleLigne] = '\0';
			char nLigne[ MAX_LETTRE - tailleLigne ];
			if( fscanf(livre->fichier, "%[^\n]\n", nLigne) == EOF ){
				(livre->avance) = TEXT_FIN;
				goto Stop;
			}
			strcat( str_ligne , nLigne );
			tailleLigne = strlen(str_ligne);
		}
		switch( str_ligne[0] ){
			// Zone des lignes ignorée
			case ':' :
			case '#' :
			case '\0' :
				( livre->avance ) =TEXT_CONTINU;
				texte = 1;
				break;
			// Déplacement dans le fichier
			case '>' :
				if(( err=sautLabel(livre,str_ligne+1) )){
					MSG_ERR2("du saut vers un label");
					return(err);
				}
				break;
			case '\\' :
				if(( err=nouveauChapitre(livre,str_ligne+1) )){
					MSG_ERR2("du changement de chapitre");
					return(err);
				}
				break;
				// Temps d'affichage
			case '=' :
				if( strcmp(str_ligne,"===") == 0 ){
					(livre->avance) = TEXT_CONTINU;
					goto Stop;
				} else if( strcmp(str_ligne,"=FIN=") == 0 ){
					(livre->avance) = TEXT_FIN;
					goto Stop;
				}
				break;
			// personnage
			case '+' :
				if(( err=gererInventaire(livre,str_ligne+1) )){
					MSG_ERR2("d'un choix d'objet");
					return(err);
				}
				break;
			case '~' :
				if(( err=epreuvePerso(livre,str_ligne+1) )){
					MSG_ERR2("d'une épreuve du joueur");
					return(err);
				}
				break;
			// Choix
			case '?' :
				{
					char codeAction = '!';
					char *action = NULL;
					if(( err=lancer_QstRep(&(livre->police->couleur),str_ligne+1,livre->fenetre,LSTCODE,&codeAction,&action) )){
						MSG_ERR2("de la demande d'un choix au joueur");
						return(err);
					}
					if(( err=traiterCode(livre,codeAction,action,&texte) )){
						MSG_ERR2("du traitement du choix du joueur");
						return(err);
					}
					if( action ){
						free(action);
					}
				}
				break;
			// Contenu
			case '!' :
				if( nouvellePage ){
					if(( err=enlever_derniere_page(livre) )){
						MSG_ERR2("de la suppression de la dernière page(vide)");
						return(err);
					}
				}
				if(( err=ajouterImgF(livre,str_ligne+1) )){
					MSG_ERR2("de l'ajout d'une illustration");
					return(err);
				}
				break;
			default :
				texte = 1;
				if(( err=ajouterTexte(livre,str_ligne,page,&(maxPos.y)) )){
					MSG_ERR2("de l'ajout d'une ligne de texte dans la page actuel");
					return(err);
				}
		}
		if( (maxPos.y) < (pos->y) )
			(maxPos.y) = (pos->y);
	}
Stop:
	(livre->pos).x = maxPos.x;
	(livre->pos).y = maxPos.y;
	return(E_OK);
}

static err_t livre_affBouton(livre_t *livre){
	err_t err = E_OK;
	if( (livre->i) < 3 ){
		if(( err=bouton_cacher(livre->prec) )){
			MSG_ERR2("du masquage du bouton precedant");
			return(err);
		}
	} else if( (livre->i) == 3 ){
		if(( err=bouton_montrer(livre->prec) )){
			MSG_ERR2("du dé-masquage du bouton précédent");
			return(err);
		}
	}
	int nb = liste_taille( livre->lstPage );
	if( (livre->i) == nb ){
		if( ((livre->avance)==TEXT_FIN) || ((livre->avance)==TEXT_FIN) ){
			if(( err=bouton_cacher(livre->suiv) )){
				MSG_ERR2("du masquage du bouton suivant");
				return(err);
			}
		}
	} else if( (livre->i) == (nb-1) ){
		if(( err=bouton_montrer(livre->suiv) )){
			MSG_ERR2("du dé-masquage du bouton suivant");
			return(err);
		}
	}
	return(err);
}
static err_t livre_quitter(int *stop){
		*stop = 1;
		return(E_OK);
}
extern err_t livre_cliquer(livre_t *livre,int *stop){
	// Vérification des arguments
	if( !livre ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de livree à modifier");
		return(E_ARGUMENT);
	}
	err_t err=E_OK;
	bouton_t *bouton = NULL;
	{ // Obtenir le bouton cliqué
		SDL_Point curseur;
		obtenir_clique(&curseur);
		bouton = obtenir_boutonCliquer(livre->fenetre,&curseur,NULL);
		if( !bouton ){
			return(E_OK);
		}
	}

	if( bouton == livre->prec ){
		if(( err=livre_precedant(livre) )){
			MSG_ERR2("de l'affichage de l'ancien texte");
			return(err);
		}
		if(( err=livre_affBouton(livre) )){
			MSG_ERR2("de la gestion de l'affichage des boutons de contrôle");
			return(err);
		}
	} else if( bouton == livre->suiv ){
		if(( err=livre_suivant(livre) )){
			MSG_ERR2("de l'affichage du nouveau texte");
			return(err);
		}
		if(( err=livre_affBouton(livre) )){
			MSG_ERR2("de la gestion de l'affichage des boutons de contrôle");
			return(err);
		}
	} else if( bouton == livre->stop ){
		return(livre_quitter(stop));
	} else if( bouton == livre->inve ){
	} else if( bouton == livre->stat ){
		afficher_joueurBis(livre->joueur,livre->fenetre->fenetre);
	} else { // Boutons de choix du texte
	}

	return(err);
}

static err_t livre_ajouter_bouton_gestion(livre_t *livre, char *text, SDL_Color *couleur,SDL_Rect *dest, bouton_t **sortie){
	img_t *bouton = NULL;
	SDL_Point pos = { dest->x , dest->y };
	err_t err = E_OK;
	// Placage du texte
	if(( err=placer(livre->fenetre,livre->police,text,&pos,&bouton,NULL) )){
		MSG_ERR2("du placement du texte sur la fenêtre");
		return(err);
	}
	// Activation
	int i = liste_taille( livre->fenetre->lstBoutons );
	if(( err=ajouterBouton(livre->fenetre,bouton,NULL,couleur) )){
		MSG_ERR2("de l'ajout du bouton à la fenêtre");
		return(err);
	}
	*sortie = liste_recherche_obj( &err , livre->fenetre->lstBoutons , i );
	if( err ){
		MSG_ERR2("de la recherche du bouton");
		return(err);
	}
	if( !(*sortie) ){
		MSG_ERR(E_OBTENIR,"Le bouton n'à pas était trouvé");
		return(E_OBTENIR);
	}
	if(( err=changerDest((*sortie)->widget,dest) )){
		MSG_ERR2("du changement de la zone d'affichage du bouton");
		return(err);
	}
	return(err);
}

#define arrondi 0.01
#define egalF(val1,val2) ( ((val2-arrondi)<val1) && (val1<(val2+arrondi) ) )
static void actualise_zoneAff(SDL_Rect *rect , float pL , float pH){
	(rect->h)*= pH;
	(rect->w)*= pL;
	(rect->x)*= pL;
	(rect->y)*= pH;
}
extern err_t livre_rafraichir(livre_t *livre){
	if( !livre ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de livree à dessiner");
		return(E_ARGUMENT);
	}
	err_t err = E_OK;
	{ // Actualiser la taille des pages
		SDL_Point *vDim = &(livre->fenetre->dim);
		SDL_Point dim = {0,0};
		SDL_GetWindowSize( livre->fenetre->fenetre , &(dim.x) , &(dim.y) );
		float pL = ((float)dim.x) / ((float)vDim->x) ;
		float pH = ((float)dim.y) / ((float)vDim->y) ;
		if( !egalF(pL,1) || !egalF(pH,1) ){
			actualise_zoneAff( &( (livre->zoneAff)[0] ) , pL , pH );
			actualise_zoneAff( &( (livre->zoneAff)[1] ) , pL , pH );
		}
	}
	if(( err=rafraichir(livre->fenetre) )){
		MSG_ERR2("du rafraichissement du contenu de la livre->fenetre");
		return(err);
	}
	int i = livre->i;
	if( i ){
		img_t *page = liste_recherche_obj( &err , livre->lstPage , (livre->i)-1 );
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
		if( (i%2) == 0 ){ // Si une deuxième page
			img_t *page = liste_recherche_obj( &err , livre->lstPage , (livre->i)-2 );
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
		}
	}
	SDL_RenderPresent(obtenir_Renderer(livre->fenetre));
	return(err);
}

static err_t suprChap( livre_t *livre ){
	err_t err = E_OK;
	{ // Destruction de la liste des pages
		liste_t *liste = livre->lstPage;
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
	if( livre->fichier ){ // Fermeture du fichier
		fclose( livre->fichier );
		livre->fichier = NULL;
	}
	// Remise à 0 du positionnemant dans la page vide
	( livre->pos ).x = 0;
	( livre->pos ).y = 0;
	( livre->i ) = 0;
	return(E_OK);
}

extern err_t nouveauChapitre(livre_t *livre, char *nomChap){
	if( !livre ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de livre à modifier");
		return(E_ARGUMENT);
	}
	if( !nomChap ){
		nomChap = chapDefaut;
	}

	err_t err = E_OK;
	if(( err=suprChap(livre) )){
		MSG_ERR2("de la destruction du chapitre actuelle");
		return(err);
	}
	{ // Ouverture du fichier de script
		int tailleChaine = strlen(nomChap) + strlen(livre->nomHistoire) + 25;
		char *nomFichier = malloc( sizeof(char) * tailleChaine );
		sprintf(nomFichier,"Annexe/texte/%s/%s.txt",livre->nomHistoire,nomChap);
		( livre->fichier ) = fopen( nomFichier , "r" );
		if( !( livre->fichier ) ){
			char msg[ 30 + strlen(nomFichier) ];
			sprintf(msg,"de l'ouverture du fichier '%s'",nomFichier);
			MSG_ERR(E_FICHIER,msg);
			return(E_FICHIER);
		}
	}
	{ // Ajout du nouveau chapitre à la liste
		char *nomFichier = malloc( sizeof(char) * (strlen(nomChap)+1) );
		strcpy(nomFichier,nomChap);
		int nb = ( livre->nbChap );
		char **lstNomFichier = malloc( sizeof(char*) * (nb+1) );
		for( int i=0 ; i<nb ; i++ ){
			lstNomFichier[i] = ( livre->lstChap )[i];
		}
		if( nb ){
			free( livre->lstChap );
		}
		( livre->lstChap ) = lstNomFichier;
		( livre->lstChap )[ livre->nbChap ] = nomFichier;
		( livre->nbChap )++;
	}
	{ // Création de l'historique du nouveau chapitre
		livre->lstPage = creer_liste();
		if( !(livre->lstPage) ){
			MSG_ERR2("de la création de l'historique du nouveau chapitre");
			return(err);
		}
		livre->i = 0;
	}
	/*
	{ // Ajout du titre du chapitre
		char ligne[MAX_LETTRE];
		if( fscanf(livre->fichier, "%[^\n]\n", ligne) == EOF ){
			(livre->avance) = TEXT_FIN;
			return(E_OK);
		}
		err_t err=E_OK;
		img_t *nouvelleLigne = NULL;
		img_t *page = NULL;
		{ // Obtenir la page vierge
			printf(">>%d -> ",livre->i);
			if(( err=commencerPage(livre) )){
				MSG_ERR2("de la création d'une nouvelle page");
				return(err);
			}
			printf("%d<<\n",livre->i);
			page = liste_recherche_obj( &err , livre->lstPage , (livre->i)-1 );
			if( err ){
				MSG_ERR2("de l'obtention de la page modifier");
				return(err);
			}
			if( !page ){
				err = E_OBTENIR;
				MSG_ERR(err,"Il n'y as pas de page à modifier");
				return(err);
			}
		}
		{ // Construire la nouvelle ligne
			SDL_Surface *surface = NULL;
			if(( err=police_creerSurface_texte(&surface,livre->police,ligne,(page->dest)->w) )){
				MSG_ERR2("de la création de la surface du texte");
				return(err);
			}
			if( !surface ){
				MSG_ERR(E_AUTRE,"la surface du texte n'à pas était créer");
				return(err);
			}
			if(!( nouvelleLigne=creer_img_ParSurface(page->rendu,&surface) )){
				MSG_ERR2("de la création de img");
				return(E_AUTRE);
			}
		}
		{ // Placer la nouvelle ligne
			SDL_Rect rect;
			if(( err=img_demandeTaille(nouvelleLigne,&rect) )){
				MSG_ERR2("de l'obtention de la taille de la nouvelle ligne du texte");
				return(err);
			}
			( rect.x ) = ( ((livre->zoneAff)[0]).w / 2) - ( (rect.w) / 2 );
			( rect.y ) = ( ((livre->zoneAff)[0]).h );
			( (livre->pos).x ) = 0;
			( (livre->pos).y )+= ( rect.h ) + 5;
			if(( err=changerDest(nouvelleLigne,&rect) )){
				MSG_ERR2("de la modification de la ligne");
				return(err);
			}
		}
		{ // Ajouter la nouvelle ligne
			// Fixation du renderer sur la texture
			SDL_SetRenderTarget( page->rendu , page->image );
			// Remplissage de la texture
			SDL_RenderCopy(page->rendu , nouvelleLigne->image , NULL , obtenirDest(nouvelleLigne) );
			// Réstauration du renderer
			SDL_SetRenderTarget(page->rendu , NULL);
			// Destruction de la ligne
			if(( err=nouvelleLigne->detruire(&nouvelleLigne) )){
				MSG_ERR2("de la destruction de la nouvelle ligne");
				return(err);
			}
		}
	}
	livre->avance = TEXT_CONTINU;
	*/
	if(( err=livre_sauvegarde(livre) )){
		MSG_ERR2("de la sauvegarde du livre");
		return(E_OK);
	}
	livre->avance = TEXT_NOUVEAU;
	return(E_OK);
}

extern err_t livre_jouer(fenetre_t *fMere,livre_t **livre){
	err_t err = E_OK;
	SDL_Event event;
	{ // Redimensionné la fenêtre
		SDL_Point dim = { 0 , 0 };
		SDL_GetWindowSize( fMere->fenetre , &(dim.x) , &(dim.y) );
		SDL_SetWindowSize( (*livre)->fenetre->fenetre , dim.x , dim.y );
		SDL_RaiseWindow( (*livre)->fenetre->fenetre );
		SDL_HideWindow( fMere->fenetre );
	}
	err = E_AUTRE;
	int STOP = 0;
	while( !STOP ){
		while( SDL_PollEvent(&event) ){
			switch( event.type ){
				case SDL_QUIT :
					livre_quitter(&STOP);
					break;
				case SDL_MOUSEBUTTONUP :
					if(( err=livre_cliquer(*livre,&STOP) )){
						MSG_ERR2("de l'activtion du bouton");
						goto Stop;
					}
					break;
				case SDL_KEYDOWN :
					switch( event.key.keysym.sym ){
						case SDLK_p :
							if(( err=livre_precedant(*livre) )){
								MSG_ERR2("de l'affichage de l'ancien texte");
								return(err);
							}
							if(( err=livre_affBouton(*livre) )){
								MSG_ERR2("de la gestion de l'affichage des boutons de contrôle");
								return(err);
							}
							break;
						case SDLK_s :
							if(( err=livre_suivant(*livre) )){
								MSG_ERR2("de l'affichage du nouveau texte");
								return(err);
							}
							if(( err=livre_affBouton(*livre) )){
								MSG_ERR2("de la gestion de l'affichage des boutons de contrôle");
								return(err);
							}
							break;
						case SDLK_t :
							afficher_joueurBis((*livre)->joueur,(*livre)->fenetre->fenetre);
							break;
						case SDLK_i :
							break;
						case SDLK_q :
							if( SDL_GetModState() & KMOD_CTRL ){
								livre_quitter(&STOP);
							}
							break;
					}
					break;
			}
		}
		if(( err=livre_rafraichir(*livre) )){
			MSG_ERR2("du rafraichissement du contenu du livre");
			goto Stop;
		}
	}
Stop:
	if(( err=(*livre)->detruire(livre) )){
		MSG_ERR2("de la destruction du livre");
	}
	{ // Redimensionné la fenêtre
		SDL_ShowWindow( fMere->fenetre );
		SDL_RaiseWindow( fMere->fenetre );
	}
	return(err);
}
extern err_t nouveauJeu(fenetre_t *fMere,char *nomHistoire, livre_t **livre){
	err_t err = E_OK;
	police_t *police = NULL;
	SDL_Color stylo = { 92 , 75 , 43 , 255 };
	{ // Création de la police d'écriture
		police=creer_police(NULL,30,&stylo);
		if( !police ){
			MSG_ERR2("de la création de la police d'écriture");
			return E_AUTRE;
		}
	}
	Uint32 flags = SDL_GetWindowFlags(fMere->fenetre);
	if(!( *livre=creer_livre(flags,"livreOuvert.png",NULL,&police,nomHistoire) )){
		MSG_ERR2("de la création du livre");
		return(E_AUTRE);
	}
	return(err);
}

extern err_t livre_sauvegarde(livre_t *livre){
	err_t err = E_OK;
	FILE *f = NULL;
	{ // Ouverture du fichier de sauvegarde
		char nomF[ 30 + strlen(livre->nomHistoire) ];
		sprintf(nomF,"Annexe/texte/%s/.save.txt",livre->nomHistoire);
		if(!( f=fopen(nomF,"w") )){
			char msg[ 40 + strlen(nomF) ];
			sprintf(msg,"Impossible d'ouvrir le fichier '%s'",nomF);
			MSG_ERR(E_FICHIER,msg);
			return(E_FICHIER);
		}
	}
	{ // Sauvegarde de la liste des chapitre parcourus
		for( int i=0 ; i<(livre->nbChap) ; i++ ){
			fprintf(f,"%s\n",(livre->lstChap)[i]);
		}
		fprintf(f,"===\n");
	}
	if(( err=sauvegarder_joueur(livre->joueur,f) )){
		MSG_ERR2("de la sauvegarde du joueur");
		return(err);
	}
	fclose(f);
	return(err);
}
extern err_t livre_charger(fenetre_t *fMere,livre_t **livre,char *nomHistoire){
	err_t err = E_OK;
	FILE *f = NULL;
	if(( err=nouveauJeu(fMere,nomHistoire,livre) )){
		MSG_ERR2("de l'ouverture de l'histoire");
		return(err);
	}
	{ // Ouverture du fichier de sauvegarde
		char nomF[ 30 + strlen((*livre)->nomHistoire) ];
		sprintf(nomF,"Annexe/texte/%s/.save.txt",(*livre)->nomHistoire);
		if(!( f=fopen(nomF,"r") )){
			char msg[ 40 + strlen(nomF) ];
			sprintf(msg,"Impossible d'ouvrir le fichier '%s'",nomF);
			MSG_ERR(E_FICHIER,msg);
			return(E_FICHIER);
		}
	}
	{ // Lecture de la liste des chapitre parcourus
		char ligne[ MAX_LETTRE ];
		int nb = 0;
		char **lstNomFichier = NULL;
		while( fscanf((*livre)->fichier, "%[^\n]\n", ligne) != EOF ){
			if( strcmp(ligne,"===") == 0 ){
				break;
			}
			char *nomFichier = malloc( sizeof(char) * (strlen(ligne)+1) );
			strcpy(nomFichier,ligne);
			char **lstNomFichier_tmp = malloc( sizeof(char*) * (nb+1) );
			for( int i=0 ; i<nb ; i++ ){
				lstNomFichier_tmp[i] = lstNomFichier[i];
			}
			if( nb ){
				free( lstNomFichier );
			}
			lstNomFichier = lstNomFichier;
			lstNomFichier[nb] = nomFichier;
			nb++;
		}
		( (*livre)->lstChap ) = lstNomFichier;
		( (*livre)->nbChap ) = nb;
	}
	if(( err=charger_joueur( &((*livre)->joueur),f ) )){
		MSG_ERR2("du chargement du joueur");
		return(err);
	}
	fclose(f);
	return(err);
}

// Methode commune à tout les objets
static void afficher_livre( livre_t *livre ){
	printf("livre{}");
}

static err_t detruire_livre( livre_t **livre ){
	if( !(*livre) ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de livree à détruire.");
		return(E_ARGUMENT);
	}

	err_t err = E_OK;
	// Suppression des attributs de l'objet livre
	{ // Destruction de la liste des pages
		liste_t *liste = (*livre)->lstPage;
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
		police_t *police = (*livre)->police;
		if(( err=police->detruire(&police) )){
			MSG_ERR2("de la destruction de la police d'écriture du texte");
			return(err);
		}
	}
	if( (*livre)->page ){
		SDL_DestroyTexture( (*livre)->page );
	}
	if( (*livre)->fichier ){
		fclose( (*livre)->fichier );
	}
	if( (*livre)->fenetre ){
		if(( err=((*livre)->fenetre)->detruire(&( (*livre)->fenetre )) )){
			MSG_ERR2("de la destruction de la fenêtre");
			return(err);
		}
	}
	if( (*livre)->joueur ){
		if(( err=((*livre)->joueur)->detruire(&( (*livre)->joueur )) )){
			MSG_ERR2("de la destruction du joueur");
			return(err);
		}
	}
	if( (*livre)->nomHistoire ){
		free( (*livre)->nomHistoire );
	}
	if( (*livre)->lstChap ){
		char **liste = ( (*livre)->lstChap );
		int nb = ( (*livre)->nbChap );
		for( int i=0 ; i<nb ; i++ ){
			free( liste[i] );
		}
		free( liste );
	}

	// Suppression de l'objet livre
	free( (*livre) );
	(*livre) = NULL;

	// Destruction de l'objet livre réussie
	cmpt_livre--;
	return(E_OK);
}

extern void afficherSurvivant_livre(){
	afficherSurvivant_fenetre();
	afficherSurvivant_QstRep();
	printf("Il reste %i livre_t.\n",cmpt_livre);
}
extern livre_t * creer_livre(Uint32 flags, char *fondF, SDL_Color *fondB, police_t **police, char *nomHistoire){
	err_t err = E_OK;
	// Créer l'objet livre
	livre_t *livre = malloc( sizeof(livre_t) );
	if( !livre ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'livre'");
		return (livre_t*)NULL;
	}
	if( !nomHistoire ){
		nomHistoire = histoireDefaut;
	}

	// Création des variables locales
	fenetre_t *fenetre = NULL;

	// Affectation des variables locales
	if(!( fenetre=creer_fenetre(NULL,flags,nomHistoire) )){ // Pas d'objet fenetre de créer :
		MSG_ERR2("À la création de fenetre");
		return(NULL);
	}
	if( fondF ){
		img_t *img = NULL;
		if(!( img=creer_img(fenetre->rendu,fondF) )){ // Pas d'objet img de créer :
			MSG_ERR2("de la création de l'arrière plan de la fenetre");
			return(NULL);
		}
		if(( err=ajouterWidget(fenetre,img) )){
			MSG_ERR2("de l'ajout de l'arrière plan de la fenetre");
			return(NULL);
		}
	}
	SDL_Point *dim = &( fenetre->dim );

	// Affecter les attributs
	( livre->fenetre ) = fenetre;
	( livre->nomHistoire ) = malloc( sizeof(char) * (strlen(nomHistoire)+1) );
	if( !(livre->nomHistoire) ){
		MSG_ERR2("À la création du nom de l'histoire");
		return(NULL);
	}
	strcpy( (livre->nomHistoire) , nomHistoire );
	livre->page = NULL;
	livre->fichier = NULL;
	{ // Définition de l'espace à gauche
		( (livre->zoneAff)[0] ).h = ( (dim->y) * 765 ) / 1000;
		( (livre->zoneAff)[0] ).w = ( (dim->x) * 311 ) / 1000;
		( (livre->zoneAff)[0] ).x = ( (dim->x) * 171 ) / 1000;
		( (livre->zoneAff)[0] ).y = ( (dim->y) * 125 ) / 1000;
	}
	{ // Définition de l'espace à droite
		( (livre->zoneAff)[1] ).h = ( (dim->y) * 750 ) / 1000;
		( (livre->zoneAff)[1] ).w = ( (dim->x) * 301 ) / 1000;
		( (livre->zoneAff)[1] ).x = ( (dim->x) * 511 ) / 1000;
		( (livre->zoneAff)[1] ).y = ( (dim->y) * 127 ) / 1000;
	}
	{ //Les attributs de contrôle du texte
		( livre->i ) = 0;
		( livre->nbChap ) = 0;
		( livre->avance ) = TEXT_NOUVEAU;
		( livre->pos ).x = 0;	( livre->pos ).y = 0;
	}
	{ // Création des listes
		( livre->lstPage ) = creer_liste();
		if( !( livre->lstPage ) ){
			MSG_ERR2("de la création de la liste des images de livree");
			return (livre_t*)NULL;
		}
		( livre->lstChap ) = NULL;
	}
	{ // Création de la police d'écriture
		( livre->police ) = NULL;
		if( *police ){
			( livre->police ) = *police;
			*police = NULL;
		} else {
			( livre->police ) = creer_police(NULL,18,NULL);
		}
		if( !( livre->police ) ){
			MSG_ERR2("de la création de la police d'écriture du livree");
			return (livre_t*)NULL;
		}
	}
	{ // Création de la page vide
		SDL_Texture *t_page = NULL;
		SDL_Renderer *renderer = livre->fenetre->rendu;
		SDL_Point limAff = {	( (livre->zoneAff)[0] ).w	,	( (livre->zoneAff)[0] ).h	};
		SDL_Color c = { 0 , 0 , 0 , 0 };
		// Création de la texture
		t_page = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, limAff.x, limAff.y);
		// Sauvegarde de la couleur du renderer
		SDL_GetRenderDrawColor(renderer, &(c.r),&(c.g),&(c.b),&(c.a));
		// Fixation du renderer sur la texture
		SDL_SetRenderTarget(renderer, t_page);
		// Remplissage de la texture
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderFillRect(renderer, NULL);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 55);
		SDL_RenderDrawPoint(renderer,  limAff.x, limAff.y);
		SDL_RenderDrawPoint(renderer,  0, limAff.y);
		SDL_RenderDrawPoint(renderer, 0 , 0);
		SDL_RenderDrawPoint(renderer,  limAff.x, 0);
		SDL_RenderDrawPoint(renderer,  limAff.x/2, limAff.y/2);
		// Réstauration du renderer
		SDL_SetRenderTarget(renderer, NULL);
		SDL_SetRenderDrawColor(renderer, (c.r),(c.g),(c.b),(c.a));
		// Sauvegarde de la texture
		( livre->page ) = t_page;
	}
	{ // Création des boutons de contrôle
		int nbBouton = 5;
		char *nomBoutons[nbBouton];
		bouton_t **boutons[nbBouton];
		{ // Préparations des boutons à créer
			nomBoutons[0]="Précédant"   	;	boutons[0]=&( livre->prec )	;	*(boutons[0])=NULL	;
			nomBoutons[1]="Staitistique"	;	boutons[1]=&( livre->stat )	;	*(boutons[1])=NULL	;
			nomBoutons[2]="QUITTER"     	;	boutons[2]=&( livre->stop )	;	*(boutons[2])=NULL	;
			nomBoutons[3]="Inventaire"  	;	boutons[3]=&( livre->inve )	;	*(boutons[3])=NULL	;
			nomBoutons[4]="Suivant"     	;	boutons[4]=&( livre->suiv )	;	*(boutons[4])=NULL	;
		}
		int zoneB_y = ( (livre->zoneAff)[0] ).y + ( (livre->zoneAff)[0] ).h;
		SDL_Rect destB = { 0 , zoneB_y , (dim->x)/nbBouton , (dim->y)-(zoneB_y) };
		for( int i=0 ; i<nbBouton ; i++ ){
			destB.x = i * destB.w;
			if((  err=livre_ajouter_bouton_gestion(livre,nomBoutons[i],fondB,&destB,boutons[i]) )){
				char msg[ 45 + strlen(nomBoutons[i]) ];
				sprintf(msg,"de l'ajout du %s-ième bouton dans la fenêtre",nomBoutons[i]);
				MSG_ERR2(msg);
				return(NULL);
			}
		}
	}
	if(( err=livre_affBouton(livre) )){
		MSG_ERR2("de la gestion de l'affichage des boutons de contrôle");
		return(NULL);
	}
	if(!( livre->joueur=creer_joueur() )){
		MSG_ERR2("Le joueur n'a pas était créer");
		return(NULL);
	}
	if(( err=nouveauChapitre(livre,NULL) )){
		MSG_ERR2("de l'ouverture du premier fichier de l'histoire");
		return(NULL);
	}

	// Affecter les methodes
	livre->detruire = (err_t (*)(void *))detruire_livre;
	livre->afficher = (void (*)(void *))afficher_livre;

	// Renvoyer le bouton
	cmpt_livre++;
	return livre;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

