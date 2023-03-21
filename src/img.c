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
	if( (*img)->source ){
		free( (*img)->source );
	}
	if( (*img)->dest ){
		free( (*img)->dest );
	}

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

	// Créer l'objet img
	img_t *img = malloc( sizeof(img_t) );
	if( !img ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'img'");
		return (img_t*)NULL;
	}

	// Affecter les attributs
	SDL_Texture *texture;
	if( !(texture=SDL_CreateTextureFromSurface( rendu , *surface ))  ){
		MSG_ERR_BASE("","SDL_CreateTextureFromSurface",SDL_GetError());
		return(NULL);
	}
	SDL_FreeSurface(*surface);
	*surface = NULL;
	img->image = texture;

	changerRendu(img,rendu);
	img->source = NULL;
	img->dest = NULL;

	// Affecter les methodes
	img->detruire = (err_t (*)(void *))detruire_img;
	img->afficher = (void (*)(void *))afficher_img;
	img->dessiner = (err_t (*)(void*))dessiner_img;

	// Renvoyer le bouton
	cmpt_img++;
	return img;
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

