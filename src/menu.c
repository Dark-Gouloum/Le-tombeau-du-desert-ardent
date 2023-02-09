/**
	* \file src/menu.c
	* \brief Définition de l'objet menu.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 01:17:05
	*
	* L'objet menu sert à créer et gérer le menu du jeu.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "../lib/menu.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
static void afficher_menu( menu_t *menu ){
}

static err_t detruire_menu( menu_t **menu ){
	free( (*menu) );
	(*menu) = NULL;
	return(E_OK);
}

extern menu_t * creer_menu(){
	menu_t *menu = malloc( sizeof(menu_t) );
	if( !menu ){ // malloc à échouer :
		printf("ERREUR : creer_menu :\n\tmalloc à échouer, pas assez de place de place disponible en mémoire.");\n
		return (menu_t*)NULL;
	}

	menu.detruire = (err_t (*)(void *))detruire_menu;
	menu.afficher = (void (*)(void *))afficher_menu;

	return menu;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

