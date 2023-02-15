#!/bin/bash
: '
	* AUTEUR : Erwan PECHON
	* VERSION : 0.1
	* DATE : Dim. 20 Nov. 2022 04:44:55
	* Script qui crée les fichiers utiles pour la définition d un objet % :
	* - ./lib/%.c
	* - ./src/%.c	====>	./objet/%.o (Compiler par le Makefile)
	* - ./test/%.c	====>	./bin/test_% (Compiler par le Makefile)
'

# CRÉATION DES VARIABLES GLOBALES
#	# Nombre de paramètre
nbParam_min=2
nbParam_max=3
#	# Fichier
Src="src"
Lib="lib"
Test="test"
#	# Auteur
Auteur="E"
E="Erwan PECHON"
D="Dylan GRAMMONT"
V="Victor FOUQUERAY"
C="Clément Fefeu"
#	# Autre
d=`date +"%a %d %b %Y %T" | sed -e "s/^\(.\)/\U\1/" | sed -e "s/\(^[^ ]* [^ ]*\) \(.\)/\1 \U\2/"`
action="FaitQuelqueChose"

# FONCTION
: ' Fonction qui convertit un caractère en entier
	* paramètre $1 : le caractère à convertir
	* return :
		- 10 ====> Erreur
		- 0 à 9 => L Entier correspondant
	'
convert(){
	for i in `seq 0 9` ; do
		if ( test $1 = "$i" ) then
			return $i
		fi
	done
	return 10
}
: ' Fonction qui test l éxistance  d un fichier :
	* paramètre $1 : le nom de l objet à tester
	* paramètre $2 : le dossier à tester
	* paramètre $3 : l extension du fichier
	* return : 0=inexistant ; 1=existant
	'
existe(){
	F="$2/$1.$3"
	if ( test -e $F ) then
		return 1
	fi
	return 0
}
: ' Fonction qui écrase les ancien fichier si nécéssaire.
	* supprimer si paramètre $1=1
	* paramètre $1 : le nom de l objet
	* return : 0=inexistant ; 1=existant
	'
supprimer(){
	if ( test $1 -eq 1 ) then
		F="$Src/$2.c"
		if ( test -e $F ) then
			rm -vi $F
		fi
		F="$Lib/$2.c"
		if ( test -e $F ) then
			rm -vi $F
		fi
		F="$Test/$2.c"
		if ( test -e $F ) then
			rm -vi $F
		fi
	fi
}

# VÉRIFIÉ LES PARAMÉTRES (Renvoyer 1 en cas d'erreur)
Usage="Usage : ./Modele_c.sh <auteur> <nomObjet> [<action>]"
Detail_aut="\t- <nomAuteurPrincipal> : V='$V', E='$E', C='$C', D='$D'."
Detail_nom="\t- <nomFichier> sans l'extension(\".c ou .h\")"
Detail_act="\t- Définition d'un objet qui sert à <action>"
Detail="$Detail_aut\n$Detail_nom\n$Detail_act"
Error="Nombre de paramètres incorrect : "
#	# Bon nombre de paramètre ? #
if ( test $# != $nbParam_min ) then
	if ( test $# != $nbParam_max ) then
		echo $Error $# " ($nbParam_min ou $nbParam_max paramétre attendu)"
		echo $Usage
		echo -e $Detail
		exit 1
	else
		action=$3
	fi
fi
#	# Bon type de paramètre ? #
#	#	# Test du paramètre <nomAuteur>
case $1 in
	"E")	auteur=$E	;;
	"C")	auteur=$C	;;
	"D")	auteur=$D	;;
	"V")	auteur=$V	;;
	*)	auteur=$1	;;
esac
shift
#	#	# Test du paramètre <nomFichier>
if ( test `expr index $1 .` -ne 0 ) then
	echo "La partie de l'extension (".$(echo $1 | cut -d. -f2)") est en trop :"
	echo -e $Detail_nom
	exit 1
fi
nom="$1"
shift
#	#	# Création du fichier <nomFichier>.
nom2=""
FExiste=0
suppr=0
i=1

cont=1
while ( test $cont -eq 1 ) ; do
	cont=0
	existe $nom $Src c
	FExiste=$?
	while ( test $FExiste -eq 1 ) ; do
		nom2="$nom"_"$i"
		echo "L'objet $nom existe déjà, que voulez-vous faire ?"
			echo -e "\t1) L'écraser"
			echo -e "\t2) Créer l'objet $nom2"
			echo -e "\t3) Changer le nom du fichier"
			echo -e "\t4) Abandonner"
		echo -n "Choix : "
		read choix
		convert $choix
		case $? in
			1) suppr=1 ;;
			2) nom=$nom2 ; i=expr`$i + 1` ;;
			3) echo -n "Nouveau nom : " ; read nom ; i=1 ;;
			4) echo "Abandon de la création du fichier" ; exit 2 ;;
			*) echo "Je ne connais pas cette possibilité"
		esac
		existe $nom $Src c
		FExiste=$?
	done
	supprimer $suppr $nom

	existe $nom $Lib h
	FExiste=$?
	while ( test $FExiste -eq 1 ) ; do
		cont=1
		nom2="$nom"_"$i"
		echo "L'objet $nom existe déjà, que voulez-vous faire ?"
			echo -e "\t1) L'écraser"
			echo -e "\t2) Créer l'objet $nom2"
			echo -e "\t3) Changer le nom du fichier"
			echo -e "\t4) Abandonner"
		echo -n "Choix : "
		read choix
		convert $choix
		case $? in
			1) suppr=1 ;;
			2) nom=$nom2 ; i=expr`$i + 1` ;;
			3) echo -n "Nouveau nom : " ; read nom ; i=1 ;;
			4) echo "Abandon de la création du fichier" ; exit 2 ;;
			*) echo "Je ne connais pas cette possibilité"
		esac
		existe $nom $Lib h
		FExiste=$?
	done
	supprimer $suppr $nom

	existe $nom $Test c
	FExiste=$?
	while ( test $FExiste -eq 1 ) ; do
		cont=1
		nom2="$nom"_"$i"
		echo "L'objet $nom existe déjà, que voulez-vous faire ?"
			echo -e "\t1) L'écraser"
			echo -e "\t2) Créer l'objet $nom2"
			echo -e "\t3) Changer le nom du fichier"
			echo -e "\t4) Abandonner"
		echo -n "Choix : "
		read choix
		convert $choix
		case $? in
			1) suppr=1 ;;
			2) nom=$nom2 ; i=expr`$i + 1` ;;
			3) echo -n "Nouveau nom : " ; read nom ; i=1 ;;
			4) echo "Abandon de la création du fichier" ; exit 2 ;;
			*) echo "Je ne connais pas cette possibilité"
		esac
		existe $nom $Test c
		FExiste=$?
	done
	supprimer $suppr $nom
done
Src="$Src/$nom.c"
Lib="$Lib/$nom.h"
Test="$Test/$nom.c"
touch $Src
touch $Lib
touch $Test

# SCRIPT
TAG="_$(echo $nom | tr a-z A-Z)_H_"
echo "#ifndef $TAG" >> $Lib
echo "#define $TAG" >> $Lib
echo "" >> $Lib

for F in $Src $Lib $Test ; do # En-tête #
	touch $F
	echo "/**" >> $F
	echo -e "\t* \\\file $F" >> $F
	echo -ne "\t* \\\brief " >> $F
done

echo -n "Définition" >> $Src
echo -n "Définition" >> $Lib
echo -n "Test" >> $Test

for F in $Src $Lib $Test ; do # En-tête #
	echo -e " de l'objet $nom." >> $F
	echo -e "\t* \\\author $auteur" >> $F
	echo -e "\t* \\\version 0.1" >> $F
	echo -e "\t* \\\date $d" >> $F
	echo -e "\t*" >> $F
	echo -e "\t* L'objet $nom sert à $action." >> $F
	echo -e "\t*" >> $F
	echo -e "\t*/\n" >> $F
	echo "// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)" >> $F
	echo -n "#include " >> $F
done

echo -ne "<stdlib.h>\n#include <stdio.h>\n\n#include \"../$Lib" >> $Src
echo -ne "<stdio.h>\n\n#include \"../$Lib" >> $Test
echo -ne "\"err.h" >> $Lib

for F in $Src $Lib $Test ; do # Corps #
	echo -e "\"\n" >> $F
	echo -e "// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)" >> $F
done

echo "static int unsigned cmpt"_"$nom = 0;" >> $Src

for F in $Src $Lib $Test ; do # Corps #
	echo -e "\n// CRÉATION(S) D(ES) ÉNUMÉRATION(S)\n" >> $F
	echo "// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)" >> $F
done

echo -e "/** \\\brief La structure $nom"_"t." >> $Lib
echo -e "\t* \\\author $auteur" >> $Lib
echo -e "\t*" >> $Lib
echo -e "\t* La structure $nom"_"t sert à $action." >> $Lib
echo -e "\t*" >> $Lib
echo -e "\t*/" >> $Lib
echo "typedef struct $nom"_"s {" >> $Lib
echo "#include \"attributs_objet.h\"" >> $Lib
echo -e "\tint var; //!< Une simple variable." >> $Lib
echo "} $nom"_"t;" >> $Lib

for F in $Src $Lib $Test ; do # Corps #
	echo -e "\n// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)\n" >> $F
	echo "// CRÉATION(S) DE(S) FONCTION(S)" >> $F
done

echo -e "\t// Fonctions spéciale d'un objet $nom" >> $Src
echo -e "\n\t// Methode commune à tout les objets" >> $Src
echo -e "static void afficher"_"$nom( $nom"_"t *$nom ){\n}\n" >> $Src
echo -e "static err_t detruire"_"$nom( $nom"_"t **$nom ){" >> $Src
echo -e "\t// Suppression des attributs de l'objet $nom" >> $Src
echo -e "\n\t// Suppression de l'objet $nom" >> $Src
echo -e "\tfree( (*$nom) );" >> $Src
echo -e "\t(*$nom) = NULL;" >> $Src
echo -e "\n\t// Destruction de l'objet $nom réussie" >> $Src
echo -e "\tcmpt_$nom--;" >> $Src
echo -e "\treturn(E_OK);" >> $Src
echo -e "}\n" >> $Src

echo -e "extern void afficherSurvivant"_"$nom(){" >> $Src
echo -e "\tprintf(\"Il reste %i $nom"_"t.\\\n\",cmpt"_"$nom);" >> $Src
echo -e "}\n" >> $Src
echo -e "/**\\\brief La fonction affichant le nombre d'objet non détruit." >> $Lib
echo -e "\t* \\\author $auteur" >> $Lib
echo -e "\t*" >> $Lib
echo -e "\t* La fonction 'afficherSurvivant"_"$nom' est prévue pour fonctionner dans le fichier 'projet/test/$nom.c'." >> $Lib
echo -e "\t* Cette fonction affiche le nombre de $nom non-détruit, ainsi que le nombre d'objet inclut dans $nom qui n'ont pas était détruit." >> $Lib
echo -e "\t*" >> $Lib
echo -e "\t*/" >> $Lib
echo "extern void afficherSurvivant"_"$nom();" >> $Lib
echo -ne "\n" >> $Lib

echo "extern $nom"_"t * creer"_"$nom(){" >> $Src
echo -e "\t// Définission des variables utiles" >> $Src
echo -e "\tchar *nomFonction = \"creer"_"$nom : \";" >> $Src
echo -e "\n\t// Créer l'objet $nom" >> $Src
echo -e "\t$nom"_"t *$nom = malloc( sizeof($nom"_"t) );" >> $Src
echo -e "\tif( !$nom ){ // malloc à échouer :" >> $Src
echo -e "\t\tprintf(\"%s%smalloc : malloc à échouer, pas assez de place de place disponible en mémoire.\\\n\",MSG_E,nomFonction);" >> $Src
echo -e "\t\treturn ($nom"_"t*)NULL;" >> $Src
echo -e "\t}" >> $Src
echo -e "\n\t// Affecter les attributs" >> $Src
echo -e "\n\t// Affecter les methodes" >> $Src
echo -e "\t$nom->detruire = (err_t (*)(void *))detruire"_"$nom;" >> $Src
echo -e "\t$nom->afficher = (void (*)(void *))afficher"_"$nom;" >> $Src
echo -e "\n\t// Renvoyer le bouton" >> $Src
echo -e "\tcmpt_$nom++;" >> $Src
echo -e "\treturn $nom;" >> $Src
echo -e "}" >> $Src
echo -e "/**\\\brief La fonction créant un objet $nom"_"t." >> $Lib
echo -e "\t* \\\author $auteur" >> $Lib
echo -e "\t* \\\param[in,out] utilite" >> $Lib
echo -e "\t* \\\return un pointeur sur un $nom"_"t." >> $Lib
echo -e "\t*" >> $Lib
echo -e "\t* La fonction 'creer"_"$nom' crée un objet $nom." >> $Lib
echo -e "\t*" >> $Lib
echo -e "\t*/" >> $Lib
echo "extern $nom"_"t * creer"_"$nom();" >> $Lib

# Programme #
encadre="\t/* Programme qui test l'objet $nom. */"
echo -e "\n// PROGRAMME PRINCIPALE" >> $Test
echo -e "$encadre" >> $Test
echo -e "int main() {" >> $Test
echo -e "\t// INITIALISATION DE(S) VARIABLE(S)" >> $Test
echo -e "\t/* Création des variables d'états */" >> $Test
echo -e "\terr_t err=E_AUTRE, status=E_AUTRE;" >> $Test
echo -e "\t/* Création d'un pointeur sur l'objet à tester */" >> $Test
echo -e "\t$nom"_"t *$nom = NULL;\n" >> $Test
echo -e "\t/* Création des autres variables */" >> $Test
echo -e "\t// INSTRUCTION(S)" >> $Test
echo -e "\tif(!( $nom=creer"_"$nom() )){ // Pas d'objet $nom de créer :" >> $Test
echo -e "\t\tprintf(\"Erreur à la création de $nom.\\\n\");" >> $Test
echo -e "\t\tstatus = E_AUTRE;" >> $Test
echo -e "\t\tgoto Quit;" >> $Test
echo -e "\t}" >> $Test
echo -e "\tstatus = E_OK;" >> $Test
echo -e "\n\t// FIN DU PROGRAMME" >> $Test
echo -e "Quit:\t/* Destruction des objets */" >> $Test
echo -e "\terr = $nom->detruire( &$nom );" >> $Test
echo -e "\tif( err != E_OK ){ // Echec à la destruction :" >> $Test
echo -e "\t\tprintf(\"Erreur à la destruction de $nom.\\\n\");" >> $Test
echo -e "\t\treturn(err);" >> $Test
echo -e "\t}" >> $Test
echo -e "\t/* Affichage de fin */" >> $Test
echo -e "\tafficherSurvivant"_"$nom();" >> $Test
echo -e "\tprintf(\"\\\n\\\n\\\t\\\tFIN DU TEST\\\t\\\t\\\n\\\n\");" >> $Test
echo -e "\treturn(status);" >> $Test
echo -e "}" >> $Test
echo -e "$encadre" >> $Test
echo "// PROGRAMME PRINCIPALE" >> $Test

for F in $Src $Lib $Test ; do # fin #
	echo -e "\n// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //\n" >> $F
done

echo "#endif" >> $Lib

# Dernière préparation du fichier #
	clear
	ls *
	echo -e "\n\n\t\tLes fichier $Src, $Lib et $Test ont était crée.\n\n"

# FIN
	exit 0

