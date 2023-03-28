/**
	* \file test/blocText.c
	* \brief Test de l'objet blocText.
	* \author Erwan PECHON
	* \version 0.1
	* \date Lun. 27 Mars 2023 21:50:49
	*
	* L'objet blocText sert à afficher du texte dans une boite.
	* Il garde en mémoire jusqu'où le texte à était écrit.
	*
	*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)
#include <stdio.h>

#include "../lib/blocText.h"
#include "../lib/page.h"

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)
#define FICHIER_TEST "Annexe/text/test.txt"
#define SEPX 20
#define SEPY 20
int STOP = 0;

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)
int nouveauMot(char *mot,int i,FILE *fichier,char *action){
	char car;
	while(( car=fgetc(fichier) )){
		switch(car){
			case '\\':
				if(( car=fgetc(fichier) )){
					mot[i++] = car;
				}
				break;
			case '=':
				mot[i++] = car;
				if( i == 1 ){ // Si c'était le premier caractère du mot :
					int ret=0;
					if(( ret=nouveauMot(mot,i,fichier,action) )){
						if( strcmp(mot,"=FIN=\n") == 0 ){
							mot[0] = '\0';
							return 0;
						} else if( strcmp(mot,"===\n") == 0 ){
							mot[0] = '\0';
							return -2;
						}
					}
				}
				break;
			case '[':
				if( i == 0 ){ // Si c'est le premier caractère du mot :
					int cont=1;
					while( cont && (car=fgetc(fichier)) ){
						if( car==']' ){
							mot[i] = '\0';
							cont = 0;
						} else {
							mot[i++] = car;
						}
					}
					if(( car=fgetc(fichier) )){
						if( car=='(' ){
							int j=0;
							cont=1;
							while( cont && (car=fgetc(fichier)) ){
								if( car==')' ){
									action[j] = '\0';
									cont = 0;
								} else {
									action[j++] = car;
								}
							}
							return(-3);
						} else {
							mot[i++] = car;
							mot[i] = '\0';
							return(-1);
						}
					} else {
						mot[i] = '\0';
						return -1;
					}
				} else {
					mot[i++] = car;
				}
				break;
			case '\n':
			case '\t':
			case ' ':
				mot[i++] = car;
				mot[i] = '\0';
				return -1;
			default: mot[i++] = car;
		}
	}
	return 0;
}
err_t quitter(int argc,...){
	printf("Quitter");
	STOP = 1;
	return E_OK;
}

err_t ajouterText(fenetre_t *f, police_t *p, char *text, SDL_Point *pos){
	img_t *img = NULL;
	SDL_Rect *rect = NULL;
	err_t err;
	if(( err=placer(f,p,text,pos,&img) )){
		MSG_ERR2("du placement du texte sur la fenêtre");
		return(err);
	}
	if(!( rect=obtenirDest(img) )){
		MSG_ERR2("de l'obtention de la place occupé par le texte");
		return(err);
	}
	printf("%s(%ld caractères) : h=%d w=%d x=%d y=%d\n",text,strlen(text),rect->h,rect->w,rect->x,rect->y);
	if(( err=ajouterWidget(f,img) )){
		MSG_ERR2("de l'ajout du bouton");
		return(err);
	}
	return(E_OK);
}
err_t testText(fenetre_t *f, police_t *p, char *text, SDL_Point *posInit){
	err_t err;
	int nbCar = (int)strlen(text);
	int nbCar2 = (nbCar/3);
	int j=0,j2=0;
	char text2[ nbCar2 + 1 ];
	SDL_Point pos = { posInit->x , posInit->y };
	// Afichage du texte
	if(( err=ajouterText(f,p,text,&pos) )){
		MSG_ERR2("de l'ajout du texte de base");
		return(err);
	}
	( pos.x ) = posInit->x - SEPX;
	int ligneY = posInit->y + SEPY;
	j=0 ; j2=0;
	for( int i=0 ; i<3 ; i++ ){
		( pos.y ) = ligneY;
		( pos.x )+= SEPX;
		for( j2=0 ; (j<nbCar)&&(j2<(nbCar2-1)) ; j++,j2++ ){
			text2[j2] = text[j];
		}
		text2[j2] = '\0';
		if(( err=ajouterText(f,p,text2,&pos) )){
			char msg[40];
			sprintf(msg,"de l'ajout du sous-texte n°%d",i);
			MSG_ERR2(msg);
			return(err);
		}
	}
	( pos.y ) = ligneY;
	( pos.x )+= SEPX;
	for( j2=0 ; (j<nbCar)&&(j2<(nbCar2-1)) ; j++,j2++ ){
		text2[j2] = text[j];
	}
	text2[j2] = '\0';
	if(( err=ajouterText(f,p,text2,&pos) )){
		char msg[40];
		sprintf(msg,"de l'ajout du sous-texte final");
		MSG_ERR2(msg);
		return(err);
	}
	posInit->x = pos.x;
	posInit->y = pos.y;
	return(E_OK);
}

// PROGRAMME PRINCIPALE
	/* Programme qui test l'objet blocText. */
int main() {
	// INITIALISATION DE(S) VARIABLE(S)
	/* Lancement de la SDL */
	if( initialisation_SDL( SDL_TTF|SDL_IMG , IMG_INIT_PNG ) )
		return E_INIT;
	/* Création des variables d'états */
	err_t err=E_AUTRE, status=E_AUTRE;
	/* Création d'un pointeur sur l'objet à tester */
	/* Création des autres variables */
	fenetre_t *fenetre = NULL;
	SDL_Color stylo = {92,75,43,255};
	SDL_Point pos;
	SDL_Point curseur;
	SDL_Event event;

	// INSTRUCTION(S)	"livreOuvertPlacement.png"
	if(( status=creer_page(SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN,"test_texte",NULL,&fenetre,&pos) )){ // Pas d'objet fenetre de créer :
		MSG_ERR2("de la création de la fenetre");
		goto Quit;
	}

	printf("Ajout du contenu de la fenêtre...\n");
	{ // Création du bouton de fermeture
		printf("\tCréation du bouton de fermeture\n");
		// Déclaration des variables locales
		police_t *police = NULL;
		img_t *bouton = NULL;
		// Création de la police
		if(!( police=creer_police(NULL,25,NULL) )){ // Pas d'objet police de créer :
			printf("Erreur à la création de police.\n");
			status = E_AUTRE;
			goto Quit;
		}
		// Ajout des boutons
		pos.x = 3 * ( (fenetre->dim).x / 4 );
		pos.y = 3 * ( (fenetre->dim).y / 4 );
		if(( status=placer(fenetre,police,"Quitter",&pos,&bouton) )){
			MSG_ERR2("du placement du texte sur la fenêtre");
			goto Quit;
		}
		if(( status=ajouterBouton(fenetre,bouton,quitter) )){
			MSG_ERR2("de l'ajout du bouton");
			goto Quit;
		}
		// Destruction de la police
		if(( status=police->detruire(&police) )){
			printf("Erreur à la destruction de police.\n");
			goto Quit;
		}
	}
	{ // Création du texte
		printf("\tCréation du texte\n");
		// Déclaration des variables locales
		police_t *police = NULL;
		// Création de la police
		if(!( police=creer_police(NULL,16,&stylo) )){ // Pas d'objet police de créer :
			printf("Erreur à la création de police.\n");
			status = E_AUTRE;
			goto Quit;
		}
		// Ajout des boutons
		pos.x = ( (fenetre->dim).x / 4 );
		pos.y = ( (fenetre->dim).y / 4 );
		if(( status=testText(fenetre,police, "abcdefghijklmnopqrstuvwxyz" ,&pos) )){
			MSG_ERR2("du test sur les minuscules");
			goto Quit;
		}
		pos.x = ( (fenetre->dim).x / 4 );
		pos.y+= SEPY;
		if(( status=testText(fenetre,police, "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ,&pos) )){
			MSG_ERR2("du test sur les majuscules");
			goto Quit;
		}
		pos.x = ( (fenetre->dim).x / 4 );
		pos.y+= SEPY;
		if(( status=testText(fenetre,police, "123456789-+*/.,;:!&é\"'(-è_çà)=~#{[|\\^@]}µ%§$*ùê" ,&pos) )){
			MSG_ERR2("du test sur les symboles");
			goto Quit;
		}
		// Destruction de la police
		if(( status=police->detruire(&police) )){
			printf("Erreur à la destruction de police.\n");
			goto Quit;
		}
	}
	/*
	{ // Lecture du fichier
		FILE *fichier = NULL;
		int nbLettre=50;
		char mot[nbLettre];
		char action[nbLettre];
		printf("\tLecture du fichier '%s'.\n",FICHIER_TEST);
		if(!( fichier=fopen(FICHIER_TEST,"r") )){
			status = E_FICHIER;
			MSG_ERR(status,"Le fichier n'à pas pût s'ouvrir en mode lecture");
			goto Quit;
		}
		int etat = 1;
		while( etat ){
			etat=nouveauMot(mot,0,fichier,action);
			switch( etat ){
				case 0 :
					if( mot[0] == '\0' ){
						break;
					}
				case -1 :
					printf("%s",mot);
					break;
				case -2 :
					printf("Appuyer sur ENTRÉE pour continuer :");
					getchar();
					break;
				case -3 :
					printf("|Création du bouton`%s` envoyant à `%s`| ",mot,action);
					break;
				default:
					MSG_ERR2("de la récupération du nouveau mot.");
					return(etat);
			}
		}
		fclose(fichier);
	}
	printf("OK\n");
	*/

	printf("Attente du signal d'arrêt...\n");
	status = E_AUTRE;
	while( !STOP ){
		while( SDL_PollEvent(&event) ){
			if( event.type == SDL_QUIT )
				STOP = 1;
			else if( (event.type==SDL_MOUSEBUTTONUP) ){
				obtenir_clique(&curseur);
				bouton_t *b = obtenir_boutonCliquer(fenetre, &curseur,NULL);
				if( b ){
					if(( err=b->action(0) )){
						MSG_ERR2("L'action d'un bouton");
						status = err;
						goto Quit;
					}
				}
			}
		}
		if(( err=rafraichir(fenetre) )){
			MSG_ERR2("du rafraichissement du contenu de la fenetre");
			status = err;
			goto Quit;
		}
		SDL_RenderPresent(obtenir_Renderer(fenetre));
	}
	printf("OK\n");

	status = E_OK;
	// FIN DU PROGRAMME
Quit:	/* Destruction des objets */
	if( (err=fenetre->detruire(&fenetre)) ){ // Echec à la destruction :
		MSG_ERR2("À la destruction de fenetre");
		return(err);
	}
	fermer_SDL();
	/* Affichage de fin */
	afficherSurvivant_fenetre();
	printf("\n\n\t\tFIN DU TEST\t\t\n\n");
	return(status);
}
	/* Programme qui test l'objet blocText. */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

