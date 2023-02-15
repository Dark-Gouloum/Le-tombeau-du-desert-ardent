/**
	* \file test/listeObjet.c
	* \brief Test de l'objet listeObjet.
	* \author Erwan PECHON
	* \version 0.1
	* \date Mer. 15 Févr. 2023 15:17:01
	*
	* L'objet listeObjet sert à stocke de nombreux objet.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../lib/listeObjet.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
typedef struct pers_s {
#include "../lib/attributs_objet.h"
	char *nom, *prenom;
} pers_t;
typedef struct frac_s {
#include "../lib/attributs_objet.h"
	int haut, bas;
} frac_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
void afficher_pers( pers_t *p ){
	printf("{%s %s}",p->nom, p->prenom);
}
void afficher_frac( frac_t *f ){
	printf("{%d/%d}",f->haut, f->bas);
}

err_t detruire_pers( pers_t **p ){
	free( (*p)->nom );
	free( (*p)->prenom );
	free( (*p) );
	p = NULL;
	return E_OK;
}
err_t detruire_frac( frac_t **f ){
	free( (*f) );
	f = NULL;
	return E_OK;
}

pers_t *creer_pers(char *nom, char *prenom){
	pers_t *p = malloc( sizeof(pers_t) );
	p->nom = malloc( sizeof(char) * (strlen(nom)+1) );
	p->prenom = malloc( sizeof(char) * (strlen(prenom)+1) );
	strcpy( p->nom , nom );
	strcpy( p->prenom , prenom );

	p->detruire = (err_t (*)(void*))detruire_pers;
	p->afficher = (void (*)(void*))afficher_pers;
	return p;
}
frac_t *creer_frac(int x, int y){
	frac_t *f = malloc( sizeof(frac_t) );
	f->haut = x;
	f->bas = y;

	f->detruire = (err_t (*)(void*))detruire_frac;
	f->afficher = (void (*)(void*))afficher_frac;
	return f;
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet listeObjet. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	listeObjet_t *listeObjet = NULL;

	/* Création des autres variables */
	// INSTRUCTION(S)
	printf("Création d'une liste d'objet...");
	if(!( listeObjet=creer_listeObjet() )){ // Pas d'objet listeObjet de créer :
		printf("Erreur à la création de listeObjet.\n");
		status = E_AUTRE;
		goto Quit;
	}
	printf("OK.\n");

	printf("\nTest si liste vide...%s\n", (liste_estVide(listeObjet))?("OK"):("KO") );
	printf("Test si hors liste...%s\n\n", (liste_dansListe(listeObjet))?("KO"):("OK") );

	printf("Création de 4 objets...");
	pers_t *pers1 = creer_pers("aaaa","bbbb");	pers1->afficher( pers1 );
	pers_t *pers2 = creer_pers("cccc","dddd");	pers1->afficher( pers2 );
	frac_t *frac1 = creer_frac(1,2);	frac1->afficher( frac1 );
	frac_t *frac2 = creer_frac(3,4);	frac2->afficher( frac2 );
	printf("OK.\n");
	printf("Ajout des 4 objets à la liste...");
	liste_ajouteFin( listeObjet , (objet_t*)pers1 );
	liste_ajouteFin( listeObjet , (objet_t*)frac1 );
	liste_ajouteFin( listeObjet , (objet_t*)frac2 );
	liste_ajouteFin( listeObjet , (objet_t*)pers2 );
	objet_t *obj = (objet_t*)frac2;
	obj->afficher(obj);
	printf("OK.\n");

	printf("\nTest si liste non vide...%s\n", (liste_estVide(listeObjet))?("KO"):("OK") );
	printf("Test si hors liste...%s\n", (liste_dansListe(listeObjet))?("KO"):("OK") );
	printf("Placement en tête de liste.\n");
	liste_enTete( listeObjet );
	printf("Test si dans liste...%s\n\n", (liste_dansListe(listeObjet))?("OK"):("KO") );

	printf("Affichage de la liste :\n");
	listeObjet->afficher( listeObjet );

	printf("Suppression de 2 éléments...");
	liste_enTete(listeObjet);
	for( int i=0 ; i<3 ; i++)
		liste_suivant(listeObjet);
	if( liste_dansListe(listeObjet) )
		liste_enlever(listeObjet);
	liste_precedent(listeObjet);
	if( liste_dansListe(listeObjet) )
		liste_enlever(listeObjet);
	printf("OK.\n");
	printf("Affichage de la liste :\n");
	listeObjet->afficher( listeObjet );

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	err = listeObjet->detruire( &listeObjet );
	if( err != E_OK ){ // Echec à la destruction :
		printf("Erreur à la destruction de listeObjet.\n");
		return(err);
	}
	/* Affichage de fin */
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	afficherSurvivant_listeObjet();
	return(status);
}
	/* Programme qui test l'objet listeObjet. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

