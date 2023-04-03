/**
	* \file src/img.c
	* \brief Définition de l'objet img.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 04:23:47
	*
	* L'objet img sert à gérer une image.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/img.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_img = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet img
extern err_t img_demandeTaille( img_t *img , SDL_Rect *rect ){
	if( SDL_QueryTexture(img->image,NULL,NULL,&(rect->w),&(rect->h)) ){
		MSG_ERR2("de SDL_QueryTexture");
		return E_AUTRE;
	}
	return E_OK;
}
extern err_t img_copier( img_t **nouv , img_t *img , SDL_Point *tailleMin , SDL_Point *pos ){
	{ // Tests des arguments
		if( *nouv ){
			MSG_ERR(E_ARGUMENT,"Il y à déjà une image dans la zone de retour. Risque de fuite de mémoire");
			return E_ARGUMENT;
		}
		if( !img ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas d'image à copier");
			return E_ARGUMENT;
		}
		if( !(img->dest) ){
			fprintf(stderr, "ATTENTION : %s(%s:%d) : L'image à modifier n'as pas de dimension. Aucune modification.\n",__func__,__FILE__,__LINE__);
			return(E_OK);
		}
	}
	err_t err = E_OK;
	img_t *c_img = NULL;
	// Création de la nouvelle image
	SDL_Renderer *rendu = img->rendu;
	int c_h=img->dest->h , c_w=img->dest->w ;
	if( tailleMin ){ // Vérification de la taille de l'image à copier
		img->dest->h = (( c_h < (tailleMin->y) )?(tailleMin->y):(c_h));
		img->dest->w = (( c_w < (tailleMin->x) )?(tailleMin->x):(c_w));
	}
	{ // Création de la nouvelle image
		int h = img->dest->h;
		int w = img->dest->w;
		SDL_Surface *surface = surface = SDL_CreateRGBSurface(0, 10, 10, 32, 0, 0, 0, 0);
		if( !surface ){
			MSG_ERR(E_COLOR,"Impossible de créer une image vide");
			MSG_ERR_COMP("SDL_CreateRGBSurface",SDL_GetError());
			return(E_COLOR);
		}
		if(!( c_img=creer_img_ParSurface(rendu,&surface) )){
			MSG_ERR2("Impossible de créer la copie de l'image");
			return(E_AUTRE);
		}
		SDL_DestroyTexture( c_img->image );
		c_img->image = SDL_CreateTexture(rendu, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		if( !(c_img->image) ){
			MSG_ERR(E_COLOR,"Impossible de créer une image vide");
			MSG_ERR_COMP("SDL_CreateTexture",SDL_GetError());
			return(E_COLOR);
		}
	}
	{ // Copie des attributs d'un widget
		if(( err=changerDest(c_img,obtenirDest(img)) )){
			MSG_ERR2("Impossble de copier l'emplacement de l'image");
			return(err);
		}
		if(( err=changerSource(c_img,obtenirSource(img)) )){
			MSG_ERR2("Impossble de copier la source de l'image");
			return(err);
		}
	}
	{ // Copie de la texture
		SDL_SetTextureBlendMode( c_img->image , SDL_BLENDMODE_BLEND );
		SDL_Color c = { 0 , 0 , 0 , 0 };
		{ // Lié le rendu à la nouvelle image pour la modifié
			if( SDL_GetRenderDrawColor(rendu, &(c.r),&(c.g),&(c.b),&(c.a)) ){
				MSG_ERR(E_COLOR,"La couleur n'à pas était récupérer");
				MSG_ERR_COMP("SDL_GetRenderDrawColor",SDL_GetError());
				return(E_COLOR);
			}
			if( SDL_SetRenderTarget(rendu,c_img->image) ){
				MSG_ERR(E_COLOR,"Le rendu n'as pas était fixé sur la nouvelle texture");
				MSG_ERR_COMP("SDL_SetRenderTarget",SDL_GetError());
				return(E_COLOR);
			}
		}
		{ // Nettoyé le fond de la nouvelle image
			if( SDL_SetRenderDrawColor(rendu, 0,0,0,0) ){
				MSG_ERR(E_COLOR,"La couleur n'à pas était changé");
				MSG_ERR_COMP("SDL_SetRenderDrawColor",SDL_GetError());
				return(E_COLOR);
			}
			if( SDL_RenderClear(rendu) ){
				MSG_ERR(E_COLOR,"Le rendu de la texture n'à pas était néttoyer");
				MSG_ERR_COMP("SDL_RenderClear",SDL_GetError());
				return(E_COLOR);
			}
		}
		SDL_Rect dest = { 0 , 0 , c_h , c_w };
		if( pos ){
			dest.x = pos->x;
			dest.y = pos->y;
		}
		SDL_RenderCopy( rendu , img->image , obtenirSource(img) , &dest );
		{ // Remmettre le rendu à son état d'origine
			if( SDL_SetRenderTarget(rendu,NULL) ){
				MSG_ERR(E_COLOR,"Le rendu n'as pas était re-fixé sur la fenêtre");
				MSG_ERR_COMP("SDL_SetRenderTarget",SDL_GetError());
				return(E_COLOR);
			}
			if( SDL_SetRenderDrawColor(rendu, (c.r),(c.g),(c.b),(c.a)) ){
				MSG_ERR(E_COLOR,"La couleur n'à pas était restauré");
				MSG_ERR_COMP("SDL_SetRenderDrawColor",SDL_GetError());
				return(E_COLOR);
			}
		}
	}
	// Validation de la fusion
	*nouv = c_img;
	return E_OK;
}
extern err_t img_fusion( img_t **imgContenant , img_t *img2 ){
	img_t *img1 = *imgContenant;
	{ // Tests des arguments
		if( !img1 ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas d'image à modifier");
			return E_ARGUMENT;
		}
		if( !img2 ){
			MSG_ERR(E_ARGUMENT,"Il n'y à pas d'image à ajouter");
			return E_ARGUMENT;
		}
		if( !(img1->dest) ){
			fprintf(stderr, "ATTENTION : %s(%s:%d) : L'image à modifier n'as pas de dimension. Aucune modification.\n",__func__,__FILE__,__LINE__);
			return(E_OK);
		}
		if( !(img2->dest) ){
			fprintf(stderr, "ATTENTION : %s(%s:%d) : L'image à copier n'as pas de dimension. Aucune copie.\n",__func__,__FILE__,__LINE__);
			return(E_OK);
		}
	}
	err_t err = E_OK;
	// Calcul des données de la nouvelle image
	SDL_Rect destN = { 0 , 0 , 0 , 0 }; // L'emplacement pris par la nouvelle image
	SDL_Rect destImg[] = { // Les emplacements pris par les images dans la nouvelle image
		{ 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 }
	};
	{ // Calcul de la largeur
		int largeur_cible = 0;
		int decalage = 0;
		// Obtention des donnée de placement des deux images à fusionné
		int x1=img1->dest->x , x2=img2->dest->x ;
		int w1=img1->dest->w , w2=img2->dest->w ;
		// Préparation des donnée de placement des deux images dans la nouvelle image
		destImg[0].x = x1;
		destImg[1].x = x2;
		// On calcul le décalage entre les deux images
		if( x2 < x1 ){
			int t = x2;
			x2 = x1;
			x1 = t;
		}
		decalage = x2 - x1;
		// On calcul la dimension de la nouvelle image, afin de contenir les deux images
		largeur_cible = decalage +  w2 ;
		if( largeur_cible < w1 ){
			largeur_cible = w1;
		}
		// La position de la nouvelle image dans la fenêtre
		destN.w = largeur_cible;
		destN.x = x1;
		// Les emplacement pris par les anciennes images dans la nouvelle
		destImg[0].x-= x1;
		destImg[0].w = w1;
		destImg[1].x-= x1;
		destImg[1].w = w2;
	}
	{ // Calcul de la hauteur
		int hauteur_cible = 0;
		int decalage = 0;
		// Obtention des donnée de placement des deux images à fusionné
		int y1=img1->dest->y , y2=img2->dest->y ;
		int h1=img1->dest->h , h2=img2->dest->h ;
		// Préparation des donnée de placement des deux images dans la nouvelle image
		destImg[0].y = y1;
		destImg[1].y = y2;
		// On calcul le décalage entre les deux images
		if( y2 < y1 ){
			int t = y2;
			y2 = y1;
			y1 = t;
		}
		decalage = y2 - y1;
		// On calcul la dimension de la nouvelle image, afin de contenir les deux images
		hauteur_cible = decalage +  h2 ;
		if( hauteur_cible < h1 ){
			hauteur_cible = h1;
		}
		// La position de la nouvelle image dans la fenêtre
		destN.h = hauteur_cible;
		destN.y = y1;
		// Les emplacement pris par les anciennes images dans la nouvelle
		destImg[0].y-= y1;
		destImg[0].h = h1;
		destImg[1].y-= y1;
		destImg[1].h = h2;
	}
	{ // S'assurer que l'image 1 soit modifiable
		int texture_access = 0;
		int h=img1->dest->h , w=img1->dest->w ;
		SDL_QueryTexture(img1->image, NULL, &texture_access, NULL, NULL);
		if( (texture_access!=SDL_TEXTUREACCESS_TARGET) || (h<destN.h) || (w<destN.w) ){
			img_t *img1C = NULL;
			SDL_Point tailleMin = { destN.w , destN.h };
			SDL_Point emplacement = { destImg[0].x , destImg[0].y };
			if(( err=img_copier(&img1C,img1,&tailleMin,&emplacement) )){
				MSG_ERR2("Impossible d'active le SDL_TEXTUREACCESS_TARGET de l'image 1");
				return(err);
			}
			if(( err=img1->detruire(&img1) )){
				MSG_ERR2("Impossible l'image intermediaire");
				return(err);
			}
			img1 = img1C;
		}
	}
	// Création de la nouvelle image
	SDL_Renderer *rendu = img1->rendu;
	{ // Remplissage de la nouvelle image
		// Fixé le rendu sur l'image à modifié
		if( SDL_SetRenderTarget(rendu,img1->image) ){
			MSG_ERR(E_COLOR,"Le rendu n'as pas était fixé sur l'image à modifié");
			MSG_ERR_COMP("SDL_SetRenderTarget",SDL_GetError());
			return(E_COLOR);
		}
		// Insérer l'image
		SDL_RenderCopy( rendu , img2->image , obtenirSource(img2) , &(destImg[1]) );
		// Remmettre le rendu à son état d'origine
		if( SDL_SetRenderTarget(rendu,NULL) ){
			MSG_ERR(E_COLOR,"Le rendu n'as pas était re-fixé sur la fenêtre");
			MSG_ERR_COMP("SDL_SetRenderTarget",SDL_GetError());
			return(E_COLOR);
		}
	}
	// Validation de la fusion
	img1->dest->x = destN.x;
	img1->dest->y = destN.y;
	img1->dest->w = destN.w;
	img1->dest->h = destN.h;
	*imgContenant = img1;
	return E_OK;
}
extern err_t dessiner_img( img_t *img ){
	if( !img ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas d'image à dessiner.");
		return(E_ARGUMENT);
	}
	SDL_RenderCopy(img->rendu, img->image, obtenirSource(img), obtenirDest(img));
	return E_OK;
}

	// Methode commune à tout les objets
static void afficher_img( img_t *img ){
	printf("img{}");
}

static err_t detruire_img( img_t **img ){
	if( !(*img) ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas d'image à détruire.");
		return(E_ARGUMENT);
	}

	// Suppression des attributs de l'objet img
	SDL_DestroyTexture( (*img)->image );
	detruire_widget(*img);

	// Suppression de l'objet img
	free( (*img) );
	(*img) = NULL;

	// Destruction de l'objet img réussie
	cmpt_img--;
	return(E_OK);
}

extern void afficherSurvivant_img(){
	printf("Il reste %i img_t.\n",cmpt_img);
}

extern img_t * creer_img_ParTexture(SDL_Renderer *rendu, SDL_Texture **texture){
	// Tester la validité des paramètre
	if( !(*texture) ){
		MSG_ERR(E_ARGUMENT,"L'image n'à pas était transmise.");
		return(NULL);
	}
	if( !rendu ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de rendu où afficher l'image.");
		return(NULL);
	}

	err_t err = E_OK;
	// Créer l'objet img
	img_t *img = malloc( sizeof(img_t) );
	if( !img ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'img'");
		return (img_t*)NULL;
	}

	// Affecter les attributs
	if(( err=init_widget(img,rendu) )){
		MSG_ERR2("de l'affectation des attributs de widget");
		return(NULL);
	}
	img->image = *texture;
	*texture = NULL;

	// Affecter les methodes
	img->detruire = (err_t (*)(void *))detruire_img;
	img->afficher = (void (*)(void *))afficher_img;
	img->dessiner = (err_t (*)(void*))dessiner_img;

	// Renvoyer le bouton
	cmpt_img++;
	return img;
}
extern img_t * creer_img_ParSurface(SDL_Renderer *rendu, SDL_Surface **surface){
	// Tester la validité des paramètre
	if( !(*surface) ){
		MSG_ERR(E_ARGUMENT,"L'image n'à pas était transmise.");
		return(NULL);
	}
	if( !rendu ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de rendu où afficher l'image.");
		return(NULL);
	}

	SDL_Texture *texture = NULL;
	if( !(texture=SDL_CreateTextureFromSurface( rendu , *surface ))  ){
		MSG_ERR(E_COLOR,"La création de la texture de l'image à échouer");
		MSG_ERR_COMP("SDL_CreateTextureFromSurface",SDL_GetError());
		return(NULL);
	}
	SDL_FreeSurface(*surface);
	*surface = NULL;
	return creer_img_ParTexture(rendu,&texture);
}
extern img_t * creer_img(SDL_Renderer *rendu, const char *nomFichier){
	// Tester la validité des paramètre
	if( !nomFichier ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas de fichier à ouvrir.");
		return(NULL);
	}
	char fichier[ 15 + strlen(nomFichier) ];
	if( !sprintf(fichier,"Annexe/images/%s",nomFichier) ){
		MSG_ERR(E_ARGUMENT,"Veuillez indiquer une image se trouvant dans le dossier \"Annexe/images/\"");
		MSG_ERR_COMP("Essayer le format","\"nomImage.png\"");
		return NULL;
	}

	SDL_Surface *surface = IMG_Load(fichier);
	if( surface == NULL ){
		char msg[ 40 + strlen(fichier) ];
		if( !sprintf(msg,"erreur de chargement de l'image '%s'",fichier) ){
			MSG_ERR(E_AUTRE,"Quelque chose empêche l'écriture du nom du fichier à ouvrir");
			return NULL;
		}
		MSG_ERR(E_OBTENIR,msg);
		return(NULL);
	}
	return creer_img_ParSurface(rendu,&surface);
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

