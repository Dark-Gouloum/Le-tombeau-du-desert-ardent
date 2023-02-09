/**
	* \file test/attribut_objet.c
	* \brief Test de l'objet attribut_objet.
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

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet attribut_objet. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	err_t err = E_AUTRE;
	attribut_objet_t *attribut_objet = creer_attribut_objet();

	// INSTRUCTION(S)
	if( !attribut_objet ){ // Pas d'objet attribut_objet de créer :
		printf("Erreur à la création de attribut_objet.\n");
		return(E_AUTRE);
	}
	// FIN DU PROGRAMME
	err = attribut_objet.detruire( &attribut_objet );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de attribut_objet.\n");
		return(err);
	}
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(E_OK);
}
	/* Programme qui test l'objet attribut_objet. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

