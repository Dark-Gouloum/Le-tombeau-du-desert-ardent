/**
	* \file test/liste.c
	* \brief Test de l'objet liste.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 20 Mars 2023 16:47:26
	*
	* L'objet liste sert à stocké des objets..
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/liste.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
 #define nbElem_parCat 5
 #define nbElem (3*nbElem_parCat)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)
typedef struct string_s {
	err_t (*detruire)(void*);
	void (*afficher)(void*);
	char *string;
} string_t;
typedef struct fraction_s {
	err_t (*detruire)(void*);
	void (*afficher)(void*);
	int num;
	int denum;
} fraction_t;
typedef struct personnage_s {
	err_t (*detruire)(void*);
	void (*afficher)(void*);
	char *nom;
	char *prenom;
	int age;
} personnage_t;

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)
static int unsigned cmpt_personnage = 0;
static int unsigned cmpt_fraction = 0;
static int unsigned cmpt_string = 0;

// CRÉATION(S) DE(S) FONCTION(S)
/*	Fonction de création	*/
personnage_t * creer_personnage( char *nom , char *prenom , int age );
fraction_t * creer_fraction( int num , int denum );
string_t * creer_string( char *string );

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet liste. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
		/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
		/* Création d'un pointeur sur l'objet à tester */
	liste_t *liste = NULL;
		/* Création des autres variables */
	void *obj = NULL;

	// INSTRUCTION(S)
	printf("Création de l'objet liste...");
	if(!( liste=creer_liste() )){ // Pas d'objet liste de créer :
		MSG_ERR2("la création de la liste");
		status = E_AUTRE;
		goto Quit;
	}
	liste->afficher( liste );
	printf("OK\n");

	printf("La liste à %d élément (%d attenddu).\n", liste_taille(liste) , 0 );

	printf("Ajouts d'objet à la liste...\n");
	for( int i=0 ; i<nbElem_parCat ; i++ ){
		{ // Ajout d'un personnage
			char nom[10] , prenom[10] ;
			sprintf(nom,"nom_%d",i);
			sprintf(prenom,"prenom_%d",nbElem-i);
			int age = (nbElem * i) + 1;
			if(!( obj=creer_personnage(nom,prenom,age) )){
				MSG_ERR2("la création d'un personnage");
				status = E_AUTRE;
				goto Quit;
			}
			if(( err=liste_ajoute(liste,obj) )){
				MSG_ERR2("l'ajout d'un personnage");
				status = err;
				goto Quit;
			}
			printf("\t- "); ( (objet_t*)obj )->afficher( obj ); printf(" ajouté avec succés.\n");
		}
		{ // Ajout d'une fraction
			int entier1 = (nbElem - i) * i;
			int entier2 = (nbElem * i) + 1;
			if(!( obj=creer_fraction(entier1,entier2) )){
				MSG_ERR2("la création d'une fraction");
				status = E_AUTRE;
				goto Quit;
			}
			if(( err=liste_ajoute(liste,obj) )){
				MSG_ERR2("l'ajout d'une fraction");
				status = err;
				goto Quit;
			}
			printf("\t- "); ( (objet_t*)obj )->afficher( obj ); printf(" ajouté avec succés.\n");
		}
		{ // Ajout d'un string
			char string[10] ;
			sprintf(string,"string_%d",nbElem*i);
			if(!( obj=creer_string(string) )){
				MSG_ERR2("la création d'un string");
				status = E_AUTRE;
				goto Quit;
			}
			if(( err=liste_ajoute(liste,obj) )){
				MSG_ERR2("l'ajout d'un string");
				status = err;
				goto Quit;
			}
			printf("\t- "); ( (objet_t*)obj )->afficher( obj ); printf(" ajouté avec succés.\n");
		}
	}
	obj = NULL;
	printf("OK\n");

	printf("La liste à %d élément (%d attendu).\nAffichage :\n", liste_taille(liste) , nbElem );
	liste->afficher( liste );
	printf("\n");

	printf("Recherche d'élément dans la liste :\n");
	printf("\t- En utilisant un indice :\n");
	int i;
	{ // i incorrect (min)
		i = -5;
		printf("\t\t+ i=%d : --> ",i);
		obj = liste_recherche_obj( &err , liste , i );
		if( err ){
			printf("OK(code%d).\n",err);
		} else {
		printf("KO(");
		( (objet_t*)obj )->afficher( obj );
		printf(").\n");
		}
	}
	{ // i incorrect (max)
		i = liste_taille(liste) + 5;
		printf("\t\t+ i=%d : --> ",i);
		obj = liste_recherche_obj( &err , liste , i );
		if( err ){
			printf("OK(code%d).\n",err);
		} else {
		printf("KO(");
		( (objet_t*)obj )->afficher( obj );
		printf(").\n");
		}
	}
	{ // i correct
		i = liste_taille(liste) / 2;
		printf("\t\t+ i=%d : --> ",i);
		obj = liste_recherche_obj( &err , liste , i );
		if( err ){
			printf("KO(code%d).\n",err);
		} else {
		printf("OK(");
		( (objet_t*)obj )->afficher( obj );
		printf(").\n");
		}
	}
	i = -1;
	printf("\t- En utilisant un objet(");
	( (objet_t*)obj )->afficher( obj );
	printf(") : --> ");
	i = liste_recherche_pos( &err , liste , obj );
	if( err ){
		printf("KO(code%d).\n",err);
	} else {
		printf("OK(pos=%d).\n",i);
	}
	i = -1;

	printf("Suppression d'élément dans la liste :\n");
	i = liste_taille(liste) / 4;
	if(( err=liste_enlever_pos( liste , i ) )){
		MSG_ERR2("la suppression d'un élément (par son indice)");
		status = err;
		goto Quit;
	}
	if(( err=liste_enlever_obj( liste , obj ) )){
		MSG_ERR2("la suppression d'un élément (par un pointeur sur lui-même)");
		status = err;
		goto Quit;
	}
	if(( err=liste_enlever_pos( liste , i ) )){
		MSG_ERR2("la suppression d'un élément(par son indice)");
		status = err;
		goto Quit;
	}
	liste->afficher( liste );
	printf("\n");

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=liste->detruire(&liste)) ){ // Echec à la destruction :
		MSG_ERR2("la destruction de la liste");
		return(err);
	}
	/* Affichage de fin */
	afficherSurvivant_liste();
	printf("Il reste %i personnage_t.\n",cmpt_personnage);
	printf("Il reste %i fraction_t.\n",cmpt_fraction);
	printf("Il reste %i string_t.\n",cmpt_string);
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet liste. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

/*	Personnage	*/
err_t personnage_detruire( personnage_t ** personnage ){
	if( !(*personnage) ){
		err_t err = E_ARGUMENT;
		MSG_ERR(err,"Il n'y à pas de personnages à détruire.");
		return(err);
	}
	free( (*personnage)->nom );
	free( (*personnage)->prenom );
	free(*personnage);
	*personnage = NULL;
	return(E_OK);
}
void personnage_afficher( personnage_t * const personnage ){
	printf( "personnage{" );
	if(  personnage )
		printf( "%s %s à %d années" , personnage->prenom , personnage->nom ,personnage->age ) ;
	else
		printf( "inexistant" );
	printf( "}" );
}
personnage_t * creer_personnage( char *nom , char *prenom , int age ){
	personnage_t *personnage = (personnage_t*)malloc( sizeof(personnage_t) );
	if( !personnage ){
		MSG_ERR(E_MEMOIRE,"lors de la creation d'un objet de type personnage_t");
		return((personnage_t *)NULL);
	}
	size_t size = sizeof(char) * (strlen(nom)+1);
	if( (personnage->nom = malloc(size)) == NULL ){
		MSG_ERR(E_MEMOIRE,"lors de la creation de l'attribut 'nom' de l'objet de type 'personnage_t'");
		return((personnage_t *)NULL);
	}
	size = sizeof(char) * (strlen(prenom)+1);
	if( (personnage->prenom = malloc(size)) == NULL ){
		MSG_ERR(E_MEMOIRE,"lors de la creation de l'attribut 'prenom' de l'objet de type 'personnage_t'");
		return((personnage_t *)NULL);
	}

	strcpy( personnage->nom , nom );
	strcpy( personnage->prenom , prenom );
	personnage->age = age;
	personnage->detruire = (err_t (*)(void*))personnage_detruire;
	personnage->afficher = (void (*)(void*))personnage_afficher;
	return( personnage ) ;
}

/*	Fraction	*/
err_t fraction_detruire( fraction_t ** fraction ){
	if( !(*fraction) ){
		err_t err = E_ARGUMENT;
		MSG_ERR(err,"Il n'y à pas de fractions à détruire.");
		return(err);
	}
	free(*fraction);
	*fraction = NULL;
	return(E_OK);
}
void fraction_afficher( fraction_t * const fraction ){
	printf( "fraction{" );
	if(  fraction )
		printf( "%d/%d" , fraction->num , fraction->denum );
	else
		printf( "inexistant" );
	printf( "}" );
}
fraction_t * creer_fraction( const int numerateur , const int denominateur ){
	fraction_t * fraction = NULL;
	if( (fraction = malloc(sizeof(fraction_t))) == NULL ){
		MSG_ERR(E_MEMOIRE,"lors de la creation d'un objet de type fraction_t");
		return((fraction_t *)NULL);
	}
	fraction->num = numerateur;
	fraction->denum = denominateur;
	fraction->detruire = (err_t (*)(void*))fraction_detruire;
	fraction->afficher = (void (*)(void*))fraction_afficher;
	return( fraction ) ;
}

/*	String	*/
err_t string_detruire( string_t ** string ){
	if( !(*string) ){
		err_t err = E_ARGUMENT;
		MSG_ERR(err,"Il n'y à pas de string à détruire.");
		return(err);
	}
	free( (*string)->string );
	free(*string);
	*string = NULL;
	return(E_OK);
}
void string_afficher( string_t * const string ){
	printf( "string{" );
	if(  string )
		printf( "%s" , string->string);
	else
		printf( "inexistant" );
	printf( "}" );
}
string_t * creer_string( char * const chaine ){
	string_t * string = NULL;
	if( (string = malloc(sizeof(string_t))) == NULL ){
		MSG_ERR(E_MEMOIRE,"lors de la creation d'un objet de type string_t");
		return((string_t *)NULL);
	}
	size_t size = sizeof(char) * (strlen(chaine)+1);
	if( (string->string = malloc(size)) == NULL ){
		MSG_ERR(E_MEMOIRE,"lors de la creation de l'attribut 'string' de l'objet de type 'string_t'");
		return((string_t *)NULL);
	}

	strcpy( string->string , chaine );
	string->detruire = (err_t (*)(void*))string_detruire;
	string->afficher = (void (*)(void*))string_afficher;
	return( string ) ;
}

