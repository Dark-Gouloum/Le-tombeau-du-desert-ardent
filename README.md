# Le tombeau du désert ardent
Ceci est un projet de L2 informatique de l'Université du Mans, mené du 19/01/2023 au 10/04/2023.
C'est un projet codé en C, avec la SDL, afin de nous faire découvrir la gestion de projet.
Le tombeau du désert ardent à pour objectif d'être un jeu textuelle, dans le même genre que la `forteresse du chaudront noir` de bob lennon.

## L'équipe :
- Chef de projet : Clément Fefeu
- Groupe : Clément Fefeu(clementfefeu) ; Victor FOUQUERAY(RyuAragi) ; Dylan GRAMMONT(dgrammont) ; Erwan PECHON(Dark Gouloum)

## Présentation
**Le tombeau du désert ardent** est un jeu vidéo dans l'univers de **la forteresse du chaudron noir**, de **Bob Lennon**.
Nous suivons l'histoire de *Steevee* , dans les *terres d'erenner*. C'est une aventure parallèle à celle du pyrobarbare et de son Billy.

**Le tombeau du désert ardent** est codé en **langage C**.
Toute la partie graphique à était faite à l'aide de la librairie **SLD2**.

## Installation
Pour installer le dossier il suiffit de faire un clone du répertoire distant.
Git clone https://github.com/Dark-Gouloum/Le-tombeau-du-desert-ardent.git

## Lancement
Pour lancer le programme il suffit d'éxécuter les commandes suivantes:
make all
./bin/leTombeauArdent.exe

## Contribuer
Les *pulls requests* sont les bienvenues.
Pour tout changement majeur, ouvrez une *issue* en premier pour discuter de ce que vous aimeriez changer, s'il vous plaît.

Assurez-vous de mettre à jour les tests appropriés, s'il vous plaît.

N'importe qui peut ajouter de nouvelles histoires, à conditions de suivre les régle de création d'histoire.
Ceci est nécessaire afin que notre programme puisse le lire, et l'interpréter sans problème.

## Créer une nouvelle histoire
Pour ajouter une histoire, il suffit de rajouter un dossier au nom de l'histoire dans le dossier `annexe/texte`.
### Le contenu minimal d'un dossier histoire
Chaque dossier d'histoire doit contenir les fichier :
|nom du fichier | utilité |
|:---:|:---:|
| `intro.txt` | Le fichier appelé au démarrage de l'histoire |
| `mort.txt` | Le fichier appelé lorsque le personnage meurt |
| `fin.txt` | Le fichier appelé à la fin du jeu, en cas de déaite, comme en cas de victoire |
| `resumer.txt` | Le fichier appelé lorsque l'utilisateur demande plus d'information sur l'histoire avant de lancer le jeu |
| `.save.txt` | Le fichier de sauvegarde de la progression du joueur, créer et gérer par le programme |
### Comment coder un chapitre de l'histoire
#### La significations des lignes du fichier
La premiere ligne du fichier est le nom du chapitre
Les autres lignes sont soit du texte, soit une commande.
Toutes lignes ne commençant pas par une balise spéciale est considéré comme du texte normale.
Toutes lignes vide est simplement ignoré.
Si une ligne devait finir par le carctère `\`, elle se verrait fusionné avec la ligne suivante.
#### Les balises spéciale
Une balise est le premier caractère de la ligne et peut-être l'un des caractère suivant :
| balise | signification | utilisation |
|:---:|:---:|:---:|
| `#` | commentaire | Toute la ligne est ignoré |
| `=` | contrôle d'affichage | Plusieur possibilité : <br> - laligne est `===` => mettre l'affichage en pause. <br> - la ligne est `=FIN=` => Arrêter définitivement la lecture de ce fichier. <br> - sinon,             => Insérer un saut de page. |
| `!` | image | la chaine de caractère qui suit cette balise est le chemin pour accéder à l'image, depuis le dossier `Annexe/image`. |
| `\` | ouvrir | la chaine de caractère qui suit cette balise est le chemin pour accéder au nouveau chapitre, depuis le dossier `Annexe/texte/<nomDeLHistoire>`. |
| `~` | épreuve | Doit être suivit par une lettre symbolisant le test, puis par le ou les paramètre du dit test. [Aller voir ici pour plus de détaille](#partEpreuve) |
| `+` | inventaire | [Aller voir ici pour plus de détaille](#partInventaire) |
| `:` | label | définit le nom d'un label. Un label va servir de point d'ancrage pour de futur saut de ligne. |
| `>` | aller à | Rejoint la ligne du label indiqué et ignore toutes les lignes entre les deux. |
| `?` | question | Demande à l'utilisateur de faire un choix et agis en raction. [Aller voir ici pour plus de détaille](#partQuestion) |
#### Les épreuves (#partEpreuve)
La ligne `~Lparam` lance l'épreuve `L` avec la liste de paramètre `param` :
| Valeur de `L` | paramètre attendu | action |
|:---:|:---:|:---:|
| `F` | `` | Vérifie si le personnage est assez fort pour réussir l'épreuve |
| `I` | `` | Vérifie si le personnage est assez Intelligent pour réussir l'épreuve |
| `D` | `` | Vérifie si le personnage est assez endurant pour réussir l'épreuve |
| `A` | `` | Vérifie si le personnage est assez agile pour réussir l'épreuve |
| `C` | `nom{F,I,A,C,D,P}` | Lance un combat avec l'enemie, telle que définit en paramètre |
#### La gestion de l'inventaire (#partInventaire)
La ligne `+[+-]Nparam` demande à l'utilisateur de choisir `N` objet dans une liste.
- Si le deuxième caractère est `-`, la liste proposée est l'inventaire du joueur, et les objets choisit seront perdu.
- Si le deuxième caractère est `+`, la liste proposée est définit par `param` en suivant la forme suivante : `{nom(Lm)...T}...`. Ce bloc est répétable autant de fois que nécessaire pour la création du bon nombre d'objet.
	- `nom` est le nom de l'objet.
	- `(Lm)` est un modificateur de l'objet telle que `L` est la stat modifié et `m` la valeur de la modification. Il peut y avoir autant de modificateur que nécessaire.
	- `T` le type de l'objet. Si `T` est renseigné, alors l'objet à des effets permanent. Les stats sont donc modifié dès la création, et l'objet n'est pas ajouté à l'inventaire.
Les objets peuvent modifié les stats suivantes :
| code | signification |
|:---:|:---:|
| `F` | La force |
| `I` | L'Intelligence |
| `D` | La défence |
| `A` | L'agilité |
| `C` | La chance de coup critique |
| `P` | Les Points de Vie |
#### Faire des choix (#partQuestion)
Le joueur à évidemment la possibilité de faire de nombreux choix au travers de son aventure.
La construction d'un choix se fait ainsi : `?[question]{reponse:Lparam}...} avec :
- `question` : la question posé à l'utilisateur.
- `réponse` : la réponse inscrit comme texte d'un bouton
- `Lparam` : Le code de l'action à éffectué et ses paramètre, suivant les possibilité :
| code | paramètre | action |
|:---:|:---:|:---:|
| `P` | `n` | ignore les `n` prochaines lignes |
| `O` | `nom` | Comme l'instruction d'ouverture de chapitre : la chaine de caractère qui suit cette balise est le chemin pour accéder au nouveau chapitre, depuis le dossier `Annexe/texte/<nomDeLHistoire>`. |
| `V` | `label` | Comme l'instruction d'aller à : Rejoint la ligne du label indiqué et ignore toutes les lignes entre les deux. |
| `E` | `Lparam` | Comme l'instrution d'épreuve. `L` est une lettre symbolisant le test, `param` constitut les paramètre du dit test. [Aller voir ici pour plus de détaille](#partEpreuve) |

## Licence

[The Unlicense](https://choosealicense.com/licenses/unlicense/)

## Autres
- [Tuto SDL](https://zestedesavoir.com/tutoriels/1014/utiliser-la-sdl-en-langage-c/)

## Gantt
https://docs.google.com/spreadsheets/d/1T3m6GhC8Kr_jLpmVmGk3p1HDNR4y20ySmLiQ6lNwbVk/edit?usp=sharing

## Script GDOC
https://docs.google.com/document/d/1kaS29bOb0Kaf2Mif5bz_9xBM4fjbOOjdSrPnP55SCW0/edit?usp=sharing

