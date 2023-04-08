
/**
	* \file test/choix_item.c
	* \brief Test de l'objet choix_item.
	* \author Dylan GRAMMONT
	* \version 0.1
	* \date Jeu. 09 Mars 2023 13:59:44
	*
	* L'objet choix_item sert à FaitQuelqueChose.
	*
	*/
// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/menu.h"
#include "../lib/police.h"
#include "../lib/img.h"
#include "../lib/choix_item.h"

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
	err_t err=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	/* Création des autres variables */
	joueur_t * joueur = creer_joueur();
	
	/*Création des iteem*/

	liste_t * item_list = creer_liste();
	if( item_list == NULL ){
		MSG_ERR(E_MEMOIRE,"Erreur lors de la création de la liste");
		return E_MEMOIRE;
	}
	
	/* Création des item */
	liste_ajoute(item_list,creer_item("item/bag.png"));
	liste_ajoute(item_list,creer_item("item/amulatte.png"));
	liste_ajoute(item_list,creer_item("item/armure.png"));
	liste_ajoute(item_list,creer_item("item/bouc.png"));
	liste_ajoute(item_list,creer_item("item/coupe.png"));
	liste_ajoute(item_list,creer_item("item/epee.png"));
	liste_ajoute(item_list,creer_item("item/fromage.png"));
	liste_ajoute(item_list,creer_item("item/gant.png"));
	liste_ajoute(item_list,creer_item("item/gelano.png"));

	/*ajouter valeur item*/
	ajouterModificateur(liste_recherche_obj(&err,item_list,0),STAT_PV,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,1),STAT_INTEL,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,2),STAT_ARMURE,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,3),STAT_ARMURE,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,4),STAT_INTEL,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,5),STAT_FORCE,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,6),STAT_PV,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,7),STAT_AGILITE,1);
	ajouterModificateur(liste_recherche_obj(&err,item_list,8),STAT_INTEL,1);

	item_list->afficher(item_list);

	int ret = 0;
	if(( err=choix_item(NULL,joueur,item_list,3,&ret) )){
		MSG_ERR2("du choix de 3 objets");
	}
	/* Affichage de fin */
	if(( err=item_list->detruire(&item_list) )){
		MSG_ERR2("La liste d'item n'à pas était détruit");
	}
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(err);
}

	/* Programme qui test l'objet menu. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

