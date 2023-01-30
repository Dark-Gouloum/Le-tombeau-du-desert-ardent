# Le-tombeau-du-désert-ardent
Ceci est un projet de L2 Informatique de l'Université du Mans, mené du 19/01/2023 au 10/04/2023.

## L'équipe :
- Chef de projet : Clément Feufeu
- Groupe : Clément Fefeu ; Victor FOUQUERAY ; Dylan GRAMMONT ; Erwan PECHON

## Présentation
'Le tombeau du désert ardent' est un jeu vidéo dans l'univers de 'La forteresse du chaudron noir', de Bob Lennon.
Nous suivont l'histoire de Steevee , dans les terres d'erenner. C'est une avanture parallèle à celle du pyro barbare et de son billy.

## Convention :
### Gestion des dossiers
- bin : Contient tout les éxecutable :
  - 'tombeauArdent.exe' : l'éxécutable du produit final
  - 'test_X' : l'éxéccutable testant tout ce qui est définie dans le fichier 'X.c' et 'X.h'.
- doc :
  - La documentation générer par doxygen
- lib :
  Tous les fichiers 'X.h', qui annonce les fonctions définit dans le fichier 'X.c' et tester dans le fichier 'test_X'
- src :
  - Le fichier 'main.c', qui est le fichier source du produit final : 'tombeauArdent.exe'
  - Tous les fichiers 'X.c', qui définissent les méthodes du fichier 'X.h'.
- test :
  - Tous les fichiers 'X.c', qui testent les méthodes du fichier 'X.h'. Il génére le fichier 'test_X'.
### Organisation d'un fichier
  Tout fichier doit commencer par le bloque de commentaire suivant :
```c
/*
  * AUTEUR(S) : <auteur principale> <autres auteurs>
  * VERSION : 0.1
  * DATE : Jou. XX Mo. AAAA HH:MM:SS
*/

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

// PROGRAMME PRINCIPALE
int main(){  /* Programme qui <faitQuelqueChose> */
  // INITIALISATION DE(S) VARIABLE(S)
	// INSTRUCTION(S)
	// FIN DU PROGRAMME
	printf("\n\n\t\tFIN DU PROGRAMME\t\t\n\n");
	return 0;
} /* Programme qui <faitQuelqueChose> */
// PROGRAMME PRINCIPALE

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

```
### Nouveau type
Les noms de type sont en minuscule, sauf la première lettre de chaque mots.
Il doit finir par '_t' pour le typedef, et '_s' pour le temps de sa définition
```c
typedef struct Type_s {
} Type_t
typedef enum TypeDeux_s {
} TypeDeux_t
```
### Commentaire
Les commentaire doivent être placé au début de chaque fichier, fonction, nouveau type, ou boucle.
#### Commentaire de fichier
```c
/**
  * \file <nomFichier>.c
  * \brief <faitQuelqueChose>
  * \author <auteur principale> [<autres auteurs>...]
  * \version 0.1
  * \date Jou. XX Mo. AAAA HH:MM:SS
  *
  * Ce programme <faitQuelqueChose>. [descriptionDetaillé]
  *
  */
```
#### Commentaire de fonctions
```c
/**
  * \brief <description>
  [* \param['direction'] <nomParamètre> <descriptionParamètre>]...
  * \exception <exception-object> <description>
  *
  * <descriptionDetaillé>
  */
```
#### Commentaire de nouveau type
```c
```
#### Commentaire de boucle
```c
```
