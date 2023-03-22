/**
	* \file src/son.c
	* \brief Définition de l'objet son.
	* \author Victor FOUQUERAY
	* \version 0.1
	* \date Mer. 22 Mars 2023 21:24:01
	*
	* L'objet son sert à gérer les sons et les musiques du jeu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/son.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_son = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet son
extern void startPause(){
	if( Mix_PausedMusic() == 1 ){
		Mix_ResumeMusic();
	} else {
		Mix_PauseMusic();
	}
}
extern err_t lancer_son(son_t *son,int nbRep){
	if( !son ){
		MSG_ERR(E_ARGUMENT,"il n'y à pas de son à lancer");
		return(E_ARGUMENT);
	}
	if( son->type == SON_EFFET){
		if( Mix_PlayChannel(-1, (son->stock).eff, nbRep) == -1 ){
			MSG_ERR(E_SON,"Le son waves ne peut pas être joué");
			MSG_ERR_COMP("Mix_PlayChannel",Mix_GetError());
			return(E_SON);
		}
	} else {
		if( Mix_PlayMusic((son->stock).mus, nbRep) == -1 ){
			MSG_ERR(E_SON,"Problème à la lecture du son");
			MSG_ERR_COMP("Mix_PlayMusic",Mix_GetError());
			return(E_SON);
		}
	}
	return(E_OK);
}

	// Methode commune à tout les objets
static void afficher_son( son_t *son ){
	if( !son ){
		printf("son{inexistant}");
	} else {
		printf("son{%s}",( (son->type == SON_MUSIQUE)?("La musique se charge petit à petit"):("L'effet sonore est enitièrement chargé") ) );
	}
}

static err_t detruire_son( son_t **son ){
	if( !(*son) ){
		MSG_ERR(E_ARGUMENT,"il n'y à pas de son à détruire");
		return(E_ARGUMENT);
	}

	// Suppression des attributs de l'objet son
	if( (*son)->type == SON_EFFET ){
		Mix_FreeChunk( ((*son)->stock).eff );
	} else {
		Mix_FreeMusic( ((*son)->stock).mus );
	}

	// Suppression de l'objet son
	free( (*son) );
	(*son) = NULL;

	// Destruction de l'objet son réussie
	cmpt_son--;
	return(E_OK);
}

extern void afficherSurvivant_son(){
	printf("Il reste %i son_t.\n",cmpt_son);
}

extern son_t * creer_son(typeSon_t type, char *nomSon){
	// Tests des paramètre
	if( !type ){
		MSG_ERR(E_ARGUMENT,"Je ne sais pas si mon son est une musique ou un effet sonore.");
		return (son_t*)NULL;
	}
	if( type == SON_UNK ){
		MSG_ERR(E_ARGUMENT,"Le type renseigné est inconnu");
		return (son_t*)NULL;
	}
	if( !nomSon ){
		MSG_ERR(E_ARGUMENT,"il n'y à pas de son à charger");
		return (son_t*)NULL;
	}

	// Créer l'objet son
	son_t *son = malloc( sizeof(son_t) );
	if( !son ){ // malloc à échouer :
		MSG_ERR(E_MEMOIRE,"malloc : pas assez de place pour créer un objet de type 'son'");
		return (son_t*)NULL;
	}

	// Affecter les attributs
	son->type = type;
	char nomF[ 15 + strlen(nomSon) ];
	sprintf(nomF,"Annexe/sons/%s",nomSon);
	if( type == SON_EFFET ){
		if(!( (son->stock).eff=Mix_LoadWAV(nomF) )){
			char msg[ 35 + strlen(nomF) ];
			sprintf(msg,"L'effet sonore ('%s') ne peut pas être chargé",nomF);
			MSG_ERR(E_SON,msg);
			MSG_ERR_COMP(nomF,"L'effet sonore doit IMPÉRATIVEMENT être au format '.wav'");
			MSG_ERR_COMP("Mix_LoadWAV",Mix_GetError());
			return (son_t*)NULL;
		}
	} else {
		if(!( (son->stock).mus=Mix_LoadMUS(nomF) )){
			char msg[ 35 + strlen(nomF) ];
			sprintf(msg,"La musique ('%s') ne peut pas être chargé",nomF);
			MSG_ERR(E_SON,msg);
			MSG_ERR_COMP("Mix_LoadMUS",Mix_GetError());
			return (son_t*)NULL;
		}
	}

	// Affecter les methodes
	son->detruire = (err_t (*)(void *))detruire_son;
	son->afficher = (void (*)(void *))afficher_son;

	// Renvoyer le bouton
	cmpt_son++;
	return son;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

