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
  */
  int main(){
    printf("hello world");
    return 0;
  }
  ```
### Nom de constante
### Nom de variable
### Nom de fonction
### Nouveau type
### Commentaire
