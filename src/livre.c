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
	while( fscanf(livre->fichier, "%[^\n]\n", ligne) != EOF ){
		if( ligne[0] == ':' ){
			if( strcmp(ligne+1,label) == 0 ){
				return(E_OK);
			}
		} else if( strcmp(ligne,"=FIN=") == 0 ){
			(livre->avance) = TEXT_FIN;
			return(E_OK);
		}
	}
	(livre->avance) = TEXT_FIN;
	return(E_OK);
}
static err_t gererInventaire( livre_t *livre , char *ligne ){
	err_t err = E_OK;
	int nbAjout = 0;
	liste_t *liste = NULL;
	{ // Obtenir le nombre d'objet à séléctionné
		sscanf(ligne,"%d{",&nbAjout);
		while( ligne[0] && (ligne[0]!='{') );
	}
	if( nbAjout < 0 ){
		liste = livre->joueur->listItem;
	} else {
		if(!( liste=creer_liste() )){
			MSG_ERR2("de la création de la liste d'item");
			return(err);
		}
		int i=0 , j=0 ;
		while( ligne[i] && (ligne[i]=='{') ){
			i++;
			item_t *item = NULL;
			{ // Obtention du nom
				char nom[ strlen(ligne+i)+1 ];
				for( j=0 ; ligne[i] && (ligne[i]!='(') ; i++ ){
					nom[j++] = ligne[i];
				}
				if( !(ligne[i]) ){
					MSG_ERR(E_FICHIER,"Le nom de l'objet est incomplet");
					return(E_FICHIER);
				}
				nom[j++] = '\0';
				if(!( item = creer_item(nom) )){
					MSG_ERR2("de la création d'un item");
					return(err);
				}
			}
			while( ligne[i] && (ligne[i]=='(') ){
				i++;
				char lMod = '\0';
				int vMod = 0;
				stat_t sMod = STAT_UNK;
				sscanf(ligne+i,"%c%d)",&lMod,&vMod);
				while( ligne[i] && (ligne[i]!=')' ) );
				if( !(ligne[i]) ){
					MSG_ERR(E_FICHIER,"Un modificateur de l'objet est incomplet");
					return(E_FICHIER);
				}
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
				i++;
			}
			if( !(ligne[i]) || (ligne[i]!='}') ){
				MSG_ERR(E_FICHIER,"La liste de modificateur de l'objet est incomplete");
				return(E_FICHIER);
			}
			if(( err=liste_ajoute(liste,item) )){
				MSG_ERR2("de l'ajout d'un objet à la liste d'item");
				return(err);
			}
			i++;
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
	return(err);
}
static err_t epreuvePerso( livre_t *livre , char *ligne ){
	err_t err = E_OK;
	return(err);
}

#define LSTCODE ""
static err_t traiterCode( livre_t *livre , char codeAction , char *action ){
	err_t err = E_OK;
	switch( codeAction ){
		case '?' :
			(livre->avance) = TEXT_FIN;
			SDL_Event quitEvent;
			quitEvent.type = SDL_QUIT;
			SDL_PushEvent(&quitEvent);
			break;
		case 'P' :
			(livre->avance) = TEXT_CONTINU;
			int nbL = 0;
			sscanf(action+1,"%d",&nbL);
			char ligne[MAX_LETTRE];
			for( int i=0 ; (i<nbL) && (fscanf(livre->fichier,"%[^\n]\n",ligne)!=EOF) ; i++ ){
				if( strcmp(ligne,"=FIN=") == 0 ){
					(livre->avance) = TEXT_FIN;
					return(E_OK);
				}
			}
			break;
		case 'O' :
			if(( err=nouveauChapitre(livre,action+1) )){
				MSG_ERR2("du changement de chapitre");
				return(err);
			}
			(livre->avance) = TEXT_NOUVEAU;
			break;
		case 'V' :
			if(( err=sautLabel(livre,action+1) )){
				MSG_ERR2("du saut vers un label");
				return(err);
			}
			(livre->avance) = TEXT_CONTINU;
			break;
		case 'E' :
			if(( err=epreuvePerso(livre,action+1) )){
				MSG_ERR2("d'une épreuve du joueur");
				return(err);
			}
			(livre->avance) = TEXT_NOUVEAU;
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
	int nbLigne=0;
	while( maxPos.y < (page->dest->h) ){
		if( fscanf(livre->fichier, "%[^\n]\n", str_ligne) == EOF ){
			(livre->avance) = TEXT_FIN;
			goto Stop;
		}
		int tailleLigne = strlen(str_ligne);
		while( str_ligne[tailleLigne-1]=='\\' ){
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
			break;
			// Déplacement dans le fichier
			case '>' :
				if(( err=sautLabel(livre,str_ligne+1) )){
					MSG_ERR2("du saut vers un label");
					return(err);
				}
				(livre->avance) = TEXT_CONTINU;
				break;
			case '\\' :
				if(( err=nouveauChapitre(livre,str_ligne+1) )){
					MSG_ERR2("du changement de chapitre");
					return(err);
				}
				(livre->avance) = TEXT_NOUVEAU;
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
				(livre->avance) = TEXT_NOUVEAU;
				break;
			// personnage
			case '+' :
				if(( err=gererInventaire(livre,str_ligne+1) )){
					MSG_ERR2("d'un choix d'objet");
					return(err);
				}
				(livre->avance) = TEXT_CONTINU;
			case '~' :
				if(( err=epreuvePerso(livre,str_ligne+1) )){
					MSG_ERR2("d'une épreuve du joueur");
					return(err);
				}
				(livre->avance) = TEXT_CONTINU;
			// Choix
			case '?' :
				(livre->avance) = TEXT_CONTINU;
				char codeAction = '\0';
				char *action = NULL;
				if(( err=lancer_QstRep(&(livre->police->couleur),str_ligne,livre->fenetre,LSTCODE,&codeAction,&action) )){
					MSG_ERR2("de la demande d'un choix au joueur");
					return(err);
				}
				if(( err=traiterCode(livre,codeAction,action) )){
					MSG_ERR2("du traitement du choix du joueur");
					return(err);
				}
				free(action);
				break;
			// Contenu
			case '!' :
				if( nouvellePage ){
					if(( err=liste_enlever_pos(livre->lstPage,(livre->i)-1) )){
						MSG_ERR2("de la suppression de la dernière page(vide)");
						return(err);
					}
				}
				if(( err=ajouterImgF(livre,str_ligne+1) )){
					MSG_ERR2("de l'ajout d'une illustration");
					return(err);
				}
				(livre->avance) = TEXT_NOUVEAU;
				break;
			default :
				if(( err=ajouterTexte(livre,str_ligne,page,&(maxPos.y)) )){
					MSG_ERR2("de l'ajout d'une ligne de texte dans la page actuel");
					return(err);
				}
		}
		if( (maxPos.x) < (pos->x) )
			(maxPos.x) = (pos->x);
		nbLigne++;
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
		printf("Bouton d'arrêt cliqué.\n");
		*stop = 1;
		return(E_OK);
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
	if(( err=placer(livre->fenetre,livre->police,text,&pos,&bouton) )){
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

char chapDefaut[] = "intro";
extern err_t nouveauChapitre(livre_t *livre, char *nomChap){
	if( !livre ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de livre à modifier");
		return(E_ARGUMENT);
	}
	if( nomChap ){
		nomChap = chapDefaut;
	}

	err_t err = E_OK;
	if( livre->fichier ){
		fclose( livre->fichier );
		livre->fichier = NULL;
	}
	/*
	if( livre->page ){
		SDL_DestroyTexture( livre->page );
		livre->page = NULL;
	}
	*/
	/*
	{ // Ouverture du fichier de script
		char *nomFichier = malloc( sizeof(char) * (strlen(nomChap)+strlen(livre->nomHistoire)+25) );
		sprintf(nomFichier,"Annexe/texte/%s/%s.txt",livre->nomHistoire,nomChap);
		( livre->fichier ) = fopen( nomFichier , "r" );
		if( !( livre->fichier ) ){
			char msg[ 30 + strlen(nomFichier) ];
			sprintf(msg,"de l'ouverture du fichier '%s'",nomFichier);
			MSG_ERR(E_FICHIER,msg);
			return(E_FICHIER);
		}
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
	*/
	/*
	{ // Suppression de l'historique de l'ancien chapitre
		liste_t *liste = livre->lstPage;
		if(( err=liste->detruire(&liste) )){
			MSG_ERR2("de la destruction de l'historique de l'ancien chapitre");
			return(err);
		}
		liste = creer_liste();
		if( !liste ){
			MSG_ERR2("de la création de l'historique du nouveau chapitre");
			return(err);
		}
		livre->lstPage = liste;
		livre->i = 0;
	}
	*/
	/*
	{ // Création d'une page vide
		SDL_Renderer *renderer = livre->fenetre->rendu;
		img_t *imgTitre = NULL;
		SDL_Rect titreDest = { 0 , 0 , 0 , 0 };
		SDL_Point limAff = { ( (livre->zoneAff)[0] ).w , ( (livre->zoneAff)[0] ).h };
		char str_titre[150];
		if(( err=commencerPage(livre) )){
			MSG_ERR2("de la création de la nouvelle page");
			return(err);
		}
		if( fscanf(livre->fichier, "%[^\n]\n", str_titre) == EOF ){
			MSG_ERR(E_FICHIER,"À la lecture du titre du nouveau chapitre");
			return(err);
		}
		{ // Création du titre
			SDL_Surface *surface = NULL;
			police_t *po = livre->police;
			if( (err=police_creerSurface_texte(&surface,po,str_titre,limAff.x)) ){
				MSG_ERR2("de la création de la surface du titre.");
				return(err);
			}
			if( !surface ){
				err = E_OBTENIR;
				MSG_ERR(err,"La création de la surface du titre à échouer.");
				return(err);
			}
			if(!( imgTitre=creer_img_ParSurface(renderer,&surface) )){
				MSG_ERR2("de la création de l'image du titre");
				return(err);
			}
		}
		{ // Positionnement du titre
			if(( err=img_demandeTaille(imgTitre,&titreDest) )){
				MSG_ERR2("de la demande de la taille du titre");
				return(err);
			}
			titreDest.x = ((limAff.x)/2) - ((titreDest.w)/2);
			titreDest.y = 0;
		}
		{ // Ajouter le titre
			img_t *page = liste_recherche_obj( &err , livre->lstPage , (livre->i)-1 );
			// Fixation du renderer sur la texture
			SDL_SetRenderTarget( page->rendu , page->image );
			// Remplissage de la texture
			SDL_RenderCopy(page->rendu , imgTitre->image , NULL , obtenirDest(imgTitre) );
			// Réstauration du renderer
			SDL_SetRenderTarget(page->rendu , NULL);
			// Destruction de la ligne
			if(( err=imgTitre->detruire(&imgTitre) )){
				MSG_ERR2("de la destruction de la nouvelle ligne");
				return(err);
			}
		}
	}
	*/
	livre->avance = TEXT_NOUVEAU;
	return(E_OK);
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
char histoireDefaut[] = "Origine";
extern livre_t * creer_livre(Uint32 flags, char *titreF, char *fondF, SDL_Color *fondB, police_t **police,joueur_t *joueur, char *nomHistoire){
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
	printf("\tCréation de l'objet fenetre...");
	if(!( fenetre=creer_fenetre(NULL,flags,titreF) )){ // Pas d'objet fenetre de créer :
		MSG_ERR2("À la création de fenetre");
		return(NULL);
	}
	printf("OK\n");
	if( fondF ){
		printf("\tAjout de l'arrière plan de la fenêtre...");
		img_t *img = NULL;
		if(!( img=creer_img(fenetre->rendu,fondF) )){ // Pas d'objet img de créer :
			MSG_ERR2("de la création de l'arrière plan de la fenetre");
			return(NULL);
		}
		if(( err=ajouterWidget(fenetre,img) )){
			MSG_ERR2("de l'ajout de l'arrière plan de la fenetre");
			return(NULL);
		}
		printf("OK\n");
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
	nouveauChapitre( livre , "test" );
	if(( err=livre_affBouton(livre) )){
		MSG_ERR2("de la gestion de l'affichage des boutons de contrôle");
		return(NULL);
	}										

	// Affecter les methodes
	livre->joueur = joueur;
	livre->detruire = (err_t (*)(void *))detruire_livre;
	livre->afficher = (void (*)(void *))afficher_livre;

	// Renvoyer le bouton
	cmpt_livre++;
	return livre;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

