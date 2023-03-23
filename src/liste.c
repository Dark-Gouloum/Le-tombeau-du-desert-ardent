/**
	* \file src/liste.c
	* \brief Définition de l'objet liste.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 20 Mars 2023 16:47:26
	*
	* L'objet liste sert à stocké des objets..
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdlib.h>
#include <stdio.h>

#include "../lib/liste.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
static int unsigned cmpt_liste = 0;
static int unsigned cmpt_liste_elem = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
	// Fonctions spéciale d'un objet liste
extern int liste_taille( liste_t *liste ){
	if( !liste ){
		MSG_ERR(E_ARGUMENT,"La liste n'éxiste pas");
		return(-1);
	}
	return liste->nb;
}

extern err_t liste_ajoute( liste_t *liste , void *objet ){
	// Tests des paramètre
	if( !liste ){
		MSG_ERR(E_ARGUMENT,"La liste n'éxiste pas");
		return(E_ARGUMENT);
	}
	if( !objet ){
		MSG_ERR(E_ARGUMENT,"L'objet à ajouter n'éxiste pas");
		return(E_ARGUMENT);
	}

	// Création de la nouvelle liste
	int nb = liste_taille(liste);
	void ** nouvelle_liste = malloc( sizeof(void*) * (nb+1) );
	if( !nouvelle_liste ){
		MSG_ERR_BASE("","malloc : ","malloc à échouer, pas assez de place de place disponible en mémoire");
		return(E_MEMOIRE);
	}

	// Copie de l'ancienne liste
	for( int i=0 ; i<nb ; i++ )
		nouvelle_liste[i] = (liste->liste)[i];
	free( (liste->liste) );
	(liste->liste) = nouvelle_liste;

	// Ajout du nouvelle élément
	(liste->liste)[nb] = objet;
	(liste->nb)++;

	// Valider l'ajout
	cmpt_liste_elem++;
	return(E_OK);
}

extern err_t liste_enlever_pos( liste_t *liste, int pos ){
	// Tests des paramètre
	if( !liste ){
		MSG_ERR(E_ARGUMENT,"La liste n'éxiste pas");
		return(E_ARGUMENT);
	}
	if( pos < 0 ){
		MSG_ERR(E_ARGUMENT,"pos est hors liste (<0)");
		return(E_ARGUMENT);
	}
	int nb = liste_taille(liste);
	if( nb == 0 ){
		MSG_ERR(E_ARGUMENT,"La liste est déjà vide.");
		return(E_ARGUMENT);
	} else if( (nb==1) && (pos==0) ){
	}
	if( pos >= nb ){
		MSG_ERR(E_ARGUMENT,"pos est hors liste (>nbElem)");
		return(E_ARGUMENT);
	}

	// Création de la nouvelle liste
	void ** nouvelle_liste = malloc( sizeof(void*) * (nb-1) );
	if( !nouvelle_liste ){
		MSG_ERR_BASE("","malloc : ","malloc à échouer, pas assez de place de place disponible en mémoire");
		return(E_MEMOIRE);
	}

	// Copie de l'ancienne liste
	for( int i=0,j=0 ; i<nb ; i++ ){
		if( i != pos ){
			nouvelle_liste[j++] = (liste->liste)[i];
		} else {
			err_t err = E_OK;
			void *obj = ( liste->liste )[i];
			if( (err=( ((objet_t*)obj)->detruire(&obj) )) ){
				MSG_ERR2("la destruction d'un élément");
				return(err);
			}
		}
	}
	free( (liste->liste) );
	(liste->liste) = nouvelle_liste;

	// Valider le retrait
	(liste->nb)--;
	cmpt_liste_elem--;
	return(E_OK);
}

extern err_t liste_enlever_obj( liste_t *liste, void * obj ){
	err_t err = E_OK;
	int pos = liste_recherche_pos( &err , liste , obj );
	if( err ){
		MSG_ERR2("la recherche d'un élément");
		return(err);
	}
	if( pos != -1 ){
		if(( err=liste_enlever_pos( liste , pos ) )){
			MSG_ERR2("la destruction d'un élément");
			return(err);
		}
	} else {
		printf("liste_enlever_obj : élément introuvable.\n");
	}
	return(err);
}

extern void * liste_recherche_obj( err_t *err , liste_t *liste , int pos ){
	if( !liste ){
		MSG_ERR(E_ARGUMENT,"La liste n'éxiste pas");
		*err = E_ARGUMENT;
		return(NULL);
	}
	if( pos < 0 ){
		MSG_ERR(E_ARGUMENT,"pos est hors liste (<0)");
		*err = E_ARGUMENT;
		return(NULL);
	}
	int nb = liste_taille(liste);
	if( nb == 0 ){
		printf("liste_recherche_obj : La liste est vide.");
		*err = E_OK;
		return(NULL);
	}
	if( pos >= nb ){
		MSG_ERR(E_ARGUMENT,"pos est hors liste (>nbElem)");
		*err = E_ARGUMENT;
		return(NULL);
	}
	*err = E_OK;
	return(( liste->liste )[pos]);
}

extern int liste_recherche_pos( err_t *err , liste_t *liste , void *obj ){
	*err = E_OK;
	if( !liste ){
		MSG_ERR(E_ARGUMENT,"La liste n'éxiste pas");
		return(E_ARGUMENT);
	}
	if( !obj ){
		MSG_ERR(E_ARGUMENT,"L'objet à chercher n'éxiste pas");
		return(E_ARGUMENT);
	}
	int nb = liste_taille(liste);
	if( nb == 0 ){
		printf("liste_recherche_pos : La liste est vide.");
		*err = E_OK;
		return(-1);
	}
	for( int i=0 ; i<nb ; i++ ){
		if( (liste->liste)[i] == obj ){
			return(i);
		}
	}
	return(-1);
}

	// Methode commune à tout les objets
static void afficher_liste( liste_t *liste ){
	printf("liste{");
	if( !liste ){
		MSG_ERR(E_ARGUMENT,"La liste n'éxiste pas");
		printf("inexistant");
	} else {
		void *obj;
		int nb = liste_taille(liste);
		if( nb == 0 ){
			printf("vide");
		} else {
			printf("%d elem =>",nb);
			obj = ( liste->liste )[0];
			( (objet_t*)obj )->afficher( obj );
			for( int i=1 ; i<nb ; i++ ){
				printf("\t");
				obj = ( liste->liste )[i];
				( (objet_t*)obj )->afficher( obj );
			}
			printf("<=");
		}
	}
	printf("}");
}

static err_t detruire_liste( liste_t **liste ){
	err_t err = E_OK;
	// Tests des paramètre
	if( !*liste ){
		MSG_ERR(E_ARGUMENT,"La liste n'éxiste pas");
		return(E_ARGUMENT);
	}
	// Suppression des attributs de l'objet liste
	void *obj;
	int nb = liste_taille(*liste);
	for( int i=0 ; i<nb ; i++ ){
		obj = ( (*liste)->liste )[i];
		if( (err=( ((objet_t*)obj)->detruire(&obj) )) ){
			MSG_ERR2("la destruction d'un élément");
			return(err);
		}
		cmpt_liste_elem--;
	}
	free( (*liste)->liste );

	// Suppression de l'objet liste
	free( (*liste) );
	(*liste) = NULL;

	// Destruction de l'objet liste réussie
	cmpt_liste--;
	return(E_OK);
}

extern void afficherSurvivant_liste(){
	printf("Il reste %i liste_t.\n",cmpt_liste);
	printf("Il reste %i element de liste_t.\n",cmpt_liste_elem);
}

extern liste_t * creer_liste(){
	// Créer l'objet liste
	liste_t *liste = malloc( sizeof(liste_t) );
	if( !liste ){ // malloc à échouer :
		MSG_ERR_BASE("","malloc : ","malloc à échouer, pas assez de place de place disponible en mémoire");
		return (liste_t*)NULL;
	}

	// Affecter les attributs
	liste->nb = 0;
	liste->liste = NULL;

	// Affecter les methodes
	liste->detruire = (err_t (*)(void *))detruire_liste;
	liste->afficher = (void (*)(void *))afficher_liste;

	// Renvoyer le bouton
	cmpt_liste++;
	return liste;
}

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

