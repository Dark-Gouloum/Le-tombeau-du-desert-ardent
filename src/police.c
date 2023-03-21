/**
	* \file src/police.c
	* \brief Définition de l'objet police.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mar. 21 Mars 2023 02:18:02
	*
	* L'objet police sert à gére les polices d'écritures du projets.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/police.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_police = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet police
extern err_t police_creerSurface_texte( SDL_Surface **surface , police_t *police , char *texte ){
	if( *surface ){
		MSG_ERR(E_ARGUMENT,"La variable de retour est occupé, risque de fuite de mémoire.");
		return(E_ARGUMENT);
	}
	if( !police ){
		MSG_ERR(E_ARGUMENT,"Pas de police d'écriture de renseigné.");
		return(E_ARGUMENT);
	}
	if( !texte ){
		MSG_ERR(E_ARGUMENT,"Pas de texte à écrire.");
		return(E_ARGUMENT);
	}
	(*surface) = TTF_RenderText_Solid( police->font , texte , police->couleur );
	if( !(*surface) ){
		MSG_ERR2("TTF : Création de la surface de texte.");
		return E_COLOR;
	}
	return(E_OK);
}

extern err_t police_changerCouleur( police_t *police , SDL_Color c ){
	(police->couleur).r = c.r;
	(police->couleur).g = c.g;
	(police->couleur).b = c.b;
	(police->couleur).a = c.a;
	return E_OK;
}

	// Methode commune à tout les objets
static void afficher_police( police_t *police ){
	printf("police{r=%d;g=%d;b=%d;a=%d}",police->couleur.r,police->couleur.g,police->couleur.b,police->couleur.a);
}

static err_t detruire_police( police_t **police ){
	// Suppression des attributs de l'objet police
	TTF_CloseFont( (*police)->font );

	// Suppression de l'objet police
	free( (*police) );
	(*police) = NULL;

	// Destruction de l'objet police réussie
	cmpt_police--;
	return(E_OK);
}

extern void afficherSurvivant_police(){
	printf("Il reste %i police_t.\n",cmpt_police);
}

extern police_t * creer_police(char *nomFont, int taille, SDL_Color *couleur){
	// Tester la validité des paramètre :
	if( !taille )
		taille = 18;
	if( !nomFont )
		nomFont = "Roboto/Roboto-Thin.ttf";
	char font[ 15 + strlen(nomFont) ];
	if( !sprintf(font,"Annexe/font/%s",nomFont) ){
		MSG_ERR(E_ARGUMENT,"Veuillez indiquer une police se trouvant dans le dossier \"Annexe/font\"");
		MSG_ERR_COMP("Essayer le format","\"nomPolice/variante.ttf\"");
		return (police_t*)NULL;
	}

	// Créer l'objet police
	police_t *police = malloc( sizeof(police_t) );
	if( !police ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"Impossible de créer la police.");
		return (police_t*)NULL;
	}

	// Affecter les attributs
	if( !(police->font=TTF_OpenFont( font , taille ))  ){
		char msg[ 40 + strlen(font) ];
		sprintf(msg,"de l'ouverture de la police '%s'",font);
		MSG_ERR2(msg);
		MSG_ERR_COMP("TTF_OpenFont",SDL_GetError());
		return (police_t*)NULL;
	}
	if( !couleur ){
		(police->couleur).r = 0;
		(police->couleur).g = 0;
		(police->couleur).b = 0;
		(police->couleur).a = 0;
	} else {
		(police->couleur).r = couleur->r;
		(police->couleur).g = couleur->g;
		(police->couleur).b = couleur->b;
		(police->couleur).a = couleur->a;
	}

	// Affecter les methodes
	police->detruire = (err_t (*)(void *))detruire_police;
	police->afficher = (void (*)(void *))afficher_police;

	// Renvoyer le bouton
	cmpt_police++;
	return police;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

