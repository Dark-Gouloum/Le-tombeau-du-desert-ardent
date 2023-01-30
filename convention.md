# Convention
## Gestion des dossiers
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
## Organisation d'un fichier
  Tout fichier doit commencer par le bloque de commentaire suivant :
```c
/**
  * \file <nomFichier>.{c | h}
  * \brief <description>
  * \author <auteur principale> [<autres auteurs>...]
  * \version 0.1
  * \date <Jou>. <JJ> <Mo>. <AAAA> <HH>:<MM>:<SS>
  *
  * [descriptionDetaillé]
  *
  */

// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)

// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)

// CRÉATION(S) D(ES) ÉNUMÉRATION(S)

// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)

// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)

// CRÉATION(S) DE(S) FONCTION(S)

[
// PROGRAMME PRINCIPALE
int main(){  /* Programme qui <faitQuelqueChose> */
  // INITIALISATION DE(S) VARIABLE(S)
	// INSTRUCTION(S)
	// FIN DU PROGRAMME
	printf("\n\n\t\tFIN DU PROGRAMME\t\t\n\n");
	return 0;
} /* Programme qui <faitQuelqueChose> */
// PROGRAMME PRINCIPALE
]

// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //

```
## Ajout d'une fonctions ou d'un type
```c
/**
  * \brief <description>
  [* \param['direction'] <nomParamètre> <descriptionParamètre>]...
  * \exception <exception-object> <description>
  *
  * <descriptionDetaillé>
  */
  { <typeDeRetour> <nomFonction>(<listeDesParamètres>); | typedef {struct | enum} <Type>_s <Type>_t }
```
## Ajout d'une boucle...
### ...while
```c
/* <description> */
<initialisation>
while(<test>){
	<action>
	<incrémentation>
}
```
### ...do while
```c
/* <description> */
<initialisation>
do{
	<action>
	<incrémentation>
}while(<test>);
```
### ...for
```c
/* <description> */
for( <initialisation> ; <test> ; <incrémentation> ){
	<action>
}
```
## Ajout d'un test
```c
if(<test>){ // Si A
	<action>
} else if(<test>) { // Si B
	<action>
} else { // Si C
	<action>
}
switch(<nomVariable>){
	case <cas1>: // Si A
		<action>
		break;
	case <cas1>: // Si B
		<action>
		break;
	default: // Si C
		<action>
}
```
