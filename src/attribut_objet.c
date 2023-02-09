/**
	* \file src/attribut_objet.c
	* \brief Définition de l'objet attribut_objet.
	* \author Erwan PECHON
	* \version 0.1
	* \date Jeu. 09 Févr. 2023 01:19:08
	*
	* L'objet attribut_objet sert à définir les attribut en commun avec tout les objets.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include "../lib/attribut_objet.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
static void afficher_attribut_objet( attribut_objet_t *attribut_objet ){
}

static err_t detruire_attribut_objet( attribut_objet_t **attribut_objet ){
	free( (*attribut_objet) );
	(*attribut_objet) = NULL;
	return(E_OK);
}

extern attribut_objet_t * creer_attribut_objet(){
	attribut_objet_t *attribut_objet = malloc( sizeof(attribut_objet_t) );
	if( !attribut_objet ){ // malloc à échouer :
		printf("ERREUR : creer_attribut_objet :\n\tmalloc à échouer, pas assez de place de place disponible en mémoire.");\n
		return (attribut_objet_t*)NULL;
	}

	attribut_objet.detruire = (err_t (*)(void *))detruire_attribut_objet;
	attribut_objet.afficher = (void (*)(void *))afficher_attribut_objet;

	return attribut_objet;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

