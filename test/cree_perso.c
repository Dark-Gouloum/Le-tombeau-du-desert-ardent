
/**
	* \file test/cree_perso.c
	* \brief Test de l'objet cree_perso.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Jeu. 09 Mars 2023 13:59:44
	*
	* L'objet cree_perso sert à FaitQuelqueChose.
	*
	*/
// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/menu.h"
#include "../lib/police.h"
#include "../lib/img.h"
#include "../lib/cree_perso.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int STOP = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)


err_t quitter(int argc,...){
	printf("%s\n",__func__);
	STOP = 1;
	return E_OK;
}
err_t fermer(int argc,...){
	printf("%s\n",__func__);
	STOP = 1;
	return E_OK;
}
err_t bonjour(int argc,...){
	printf("%s\n",__func__);
	return E_OK;
}
err_t salut(int argc,...){
	printf("%s\n",__func__);
	return E_OK;
}
err_t test(int argc,...){
	printf("%s\n",__func__);
	return E_OK;
}
err_t theFunction(int argc,...){
	printf("%s\n",__func__);
	return E_OK;
}
err_t aaarg(int argc,...){
	printf("%s\n",__func__);
	return E_OK;
}
err_t RoBoTo(int argc,...){
	printf("%s\n",__func__);
	return E_OK;
}
err_t choixBouton(int argc,...){
	err_t err = E_OK;
	if( argc < 1 ){
		MSG_ERR(E_ARGUMENT,"Il n'y à pas assez d'arguments");
		return(E_ARGUMENT);
	}
	va_list va;
	va_start(va,argc);
	int i = va_arg(va,int);
	switch( i ){
		case 0 :	err=quitter(0);	break;
		case 1 :	err=fermer(0);	break;
		case 2 :	err=aaarg(0);	break;
		case 3 :	err=bonjour(0);	break;
		case 4 :	err=salut(0);	break;
		case 5 :	err=test(0);	break;
		case 6 :	err=theFunction(0);	break;
		case 7 :	err=RoBoTo(0);	break;
		case 8 :	err=quitter(0);	break;
		default:
			err=E_ARGUMENT;
			char msg[ 40 ];
			sprintf(msg,"bouton inconnu : il faut 0<= %d < 9",i);
			MSG_ERR(err,msg);
	}
	va_end(va);
	return(err);
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet menu. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF|SDL_IMG , IMG_INIT_PNG ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	fenetre_t *menu = NULL;
	/* Création des autres variables */
	SDL_Event event;
	SDL_Point pos,curseur;
	SDL_Color blanc = {255,255,255,255};
	joueur_t * joueur = NULL;
	

    char * item[] = { "item/bag.png","item/amulatte.png","item/armure.png","item/bouc.png","item/coupe.png","item/epee.png","item/fromage.png","item/gant.png","item/gelano.png", };

	creationPersonnage(joueur,(int)(sizeof(item)/sizeof(item[0])),item,3);
}

	/* Programme qui test l'objet menu. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

