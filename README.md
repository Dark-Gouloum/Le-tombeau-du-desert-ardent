# Le tombeau du désert ardent
Ceci est un projet de L2 informatique de l'Université du Mans, mené du 19/01/2023 au 10/04/2023.
C'est un projet codé en **C**, avec la **SDL**, afin de nous faire découvrir la gestion de projet.
Le tombeau du désert ardent a pour objectif d'être un jeu textuel, dans le même genre que **la forteresse du chaudron noir** de bob Lennon.

## L'équipe :
- Chef de projet : Clément Fefeu
- Groupe : Clément Fefeu(clementfefeu) ; Victor FOUQUERAY(RyuAragi) ; Dylan GRAMMONT(dgrammont) ; Erwan PECHON(Dark Gouloum)

## Présentation
**Le tombeau du désert ardent** est un jeu vidéo dans l'univers de **la forteresse du chaudron noir**, de **Bob Lennon**.
Nous suivons l'histoire de *Steevee* , dans les *terres d'erenner*. C'est une aventure parallèle à celle du pyrobarbare et de son Billy.

**Le tombeau du désert ardent** est codé en **langage C**.
Toute la partie graphique à était faite à l'aide de la librairie **SLD2**.

## Installation
Pour installer le dossier, il suffit de faire un clone du répertoire distant.
Git clone https://github.com/Dark-Gouloum/Le-tombeau-du-desert-ardent.git

## Lancement
Pour lancer le programme, il suffit d'exécuter les commandes suivantes:
make all
./bin/leTombeauArdent.exe

## Contribuer
Les *pulls requests* sont les bienvenues.
Pour tout changement majeur, ouvrez une *issue* en premier pour discuter de ce que vous aimeriez changer, s'il vous plaît.

Assurez-vous de mettre à jour les tests appropriés, s'il vous plaît.

N'importe qui peut ajouter de nouvelles histoires, à condition de suivre les règles de création d'histoire.
Ceci est nécessaire afin que notre programme puisse le lire, et l'interpréter sans problème.

## Créer une nouvelle histoire
Pour ajouter une histoire, il suffit de rajouter un dossier au nom de l'histoire dans le dossier `annexe/texte`.
### Le contenu minimal d'un dossier histoire
Chaque dossier d'histoire doit contenir les fichiers :
|nom du fichier | utilité |
|:---:|:---:|
| `intro.txt` | le fichier appelé au démarrage de l'histoire |
| `mort.txt` | le fichier appelé lorsque le personnage meurt |
| `fin.txt` | le fichier appelé à la fin du jeu, en cas de défaite, comme en cas de victoire |
| `resumer.txt` | le fichier appelé lorsque l'utilisateur demande plus d'information sur l'histoire avant de lancer le jeu |
| `.save.txt` | Le fichier de sauvegarde de la progression du joueur, créer et gérer par le programme |
### Comment coder un chapitre de l'histoire
#### La signification des lignes du fichier
La première ligne du fichier est le nom du chapitre
Les autres lignes sont soit du texte, soit une commande.
Toutes lignes ne commençant pas par une balise spéciale sont considérées comme du texte normal.
Toutes lignes vides sont simplement ignorées.
Si une ligne devait finir par le caractère `\`, elle se verrait fusionnée avec la ligne suivante.
#### Les balises spéciales
Une balise est le premier caractère de la ligne et peut-être l'un des caractères suivants :
| balise | signification | utilisation |
|:---:|:---:|:---:|
| `#` | commentaire | toute la ligne est ignorée |
| `=` | contrôle d'affichage | Plusieurs possibilités : <br> - l’aligne est `===` => mettre l'affichage en pause. <br> - la ligne est `=FIN=` => arrêter définitivement la lecture de ce fichier. <br> - sinon,             => Insérer un saut de page. |
| `!` | image | la chaine de caractère qui suit cette balise est le chemin pour accéder à l'image, depuis le dossier `annexe/image`. |
| `\` | ouvrir | la chaine de caractère qui suit cette balise est le chemin pour accéder au nouveau chapitre, depuis le dossier `annexe/texte/<nomDeLHistoire>`. |
| `~` | Épreuve | doit être suivit par une lettre symbolisant le test, puis par le ou les paramètres du dit test. [Aller voir ici pour plus de détaille](#partEpreuve) |
| `+` | inventaire | [aller voir ici pour plus de détaille](#partInventaire) |
| `:` | label | définit le nom d'un label. Un label va servir de point d'ancrage pour de futur saut de ligne. |
| `>` | Aller a | rejoint la ligne du label indiqué et ignore toutes les lignes entre les deux. |
| `?` | question | Demande à l'utilisateur de faire un choix et agis en rection. [Aller voir ici pour plus de détail.](#partQuestion) |
#### Les épreuves (#partEpreuve)
La ligne `~Lparam` lance l'épreuve `L` avec la liste de paramètre `param` :
| Valeur de `L` | paramètre attendu | action |
|:---:|:---:|:---:|
| `F` | `` | Vérifie si le personnage est assez fort pour réussir l'épreuve |
| `I` | `` | Vérifie si le personnage est assez intelligent pour réussir l'épreuve |
| `D` | `` | Vérifie si le personnage est assez endurant pour réussir l'épreuve |
| `A` | `` | Vérifie si le personnage est assez agile pour réussir l'épreuve |
| `C` | `nom{F,I,A,C,D,P}` | Lance un combat avec l'ennemi, telle que définie en paramètre |
#### La gestion de l'inventaire (#partInventaire)
La ligne `+[+-]Nparam` demande à l'utilisateur de choisir `N` objets dans une liste.
- Si le deuxième caractère est `-`, la liste proposée est l'inventaire du joueur, et les objets choisit seront perdu.
- Si le deuxième caractère est `+`, la liste proposée est définie par `param` en suivant la forme suivante : `{nom(Lm)...T}...`. ce bloc est répétable autant de fois que nécessaire pour la création du bon nombre d'objets.
	- `nom` est le nom de l'objet.
	- `(Lm)` est un modificateur de l'objet tel que `L` est la stats modifiées et `m` la valeur de la modification. Il peut y avoir autant de modificateurs que nécessaire.
	- `T` le types de l'objet. Si `T` est renseigné, alors l'objet à des effets permanent. Les stats sont donc modifiées dès la création, et l'objet n'est pas ajouté à l'inventaire.
Les objets peuvent modifier les stats suivantes :

| code | signification |
|:---:|:---:|
| `F` | La force |
| `I` | L'Intelligence |
| `D` | La défense |
| `A` | L'agilité |
| `C` | La chance de coup critique |
| `P` | Les Points de Vie |
#### Faire des choix (#partQuestion)
Le joueur à évidemment la possibilité de faire de nombreux choix au travers de son aventure.
La construction d'un choix se fait ainsi : `?[question]{reponse:Lparam}...} avec :
- `question` : la question posée à l'utilisateur.
- `réponse` : la réponse inscrite comme texte d'un bouton
- `Lparam` : Le code de l'action à effectuer et ses paramètres, suivant les possibilités :

| code | paramètre | action |
|:---:|:---:|:---:|
| `P` | `n` | ignore les `n` prochaines lignes |
| `O` | `nom` | Comme l'instruction d'ouverture de chapitre : la chaine de caractère qui suit cette balise est le chemin pour accéder au nouveau chapitre, depuis le dossier `annexe/texte/<nomDeLHistoire>`. |
| `V` | `label` | Comme l'instruction d'aller à : Rejoint la ligne du label indiqué et ignore toutes les lignes entre les deux. |
| `E` | `Lparam` | Comme l'instruction d'épreuve. `L` est une lettre symbolisant le test, `param` constitue les paramètres du dit test. [Aller voir ici pour plus de détail.](#partEpreuve) |

## Licence

[The Unlicense](https://choosealicense.com/licenses/unlicense/)

## Autres
- [Tuto SDL](https://zestedesavoir.com/tutoriels/1014/utiliser-la-sdl-en-langage-c/)

## Gantt
https://docs.google.com/spreadsheets/d/1T3m6GhC8Kr_jLpmVmGk3p1HDNR4y20ySmLiQ6lNwbVk/edit?usp=sharing

## Script GDOC
https://docs.google.com/document/d/1kaS29bOb0Kaf2Mif5bz_9xBM4fjbOOjdSrPnP55SCW0/edit?usp=sharing

