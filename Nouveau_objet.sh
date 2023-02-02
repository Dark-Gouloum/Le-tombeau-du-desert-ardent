#!/bin/bash
: '
	* AUTEUR : Erwan PECHON
	* VERSION : 0.1
	* DATE : Dim. 20 Nov. 2022 04:44:55
	* Script qui crée un fichier *.c
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
for F in $Src $Lib $Test ; do # En-tête #
	touch $F
	echo "/**" >> $F
	echo -e "\t* \\\file $F" >> $F
done

echo -e "\t* \\\brief Définition de l'objet $nom qui sert à $action." >> $Src
echo -e "\t* \\\brief Définition de l'objet $nom qui sert à $action." >> $Lib
echo -e "\t* \\\brief Test de l'objet $nom qui sert à $action." >> $Test

for F in $Src $Lib $Test ; do # En-tête #
	echo -e "\t* \\\author $auteur" >> $F
	echo -e "\t* \\\version 0.1" >> $F
	echo -e "\t* \\\date $d" >> $F
	echo -e "\t*" >> $F
done

echo -e "\t* Définition de l'objet $nom qui sert à $action." >> $Src
echo -e "\t* Définition de l'objet $nom qui sert à $action." >> $Lib
echo -e "\t* Test de l'objet $nom qui sert à $action." >> $Test

for F in $Src $Lib $Test ; do # En-tête #
	echo -e "\t*" >> $F
	echo "*/" >> $F
	echo -ne "\n" >> $F
	echo "// INCLUSION(S) DE(S) BIBLIOTHEQUE(S) NÉCÉSSAIRE(S)" >> $F
done

for F in $Src $Test ; do # Bibliotheque #
	echo  "#include \"../$Lib\"" >> $F
done

for F in $Src $Lib $Test ; do # Corps #
	echo -ne "\n" >> $F
	echo "// CRÉATION(S) DE(S) CONSTANTE(S) NUMÉRIQUE(S)" >> $F
	echo -ne "\n" >> $F
	echo "// CRÉATION(S) D(ES) ÉNUMÉRATION(S)" >> $F
	echo -ne "\n" >> $F
	echo "// CRÉATION(S) D(ES) STRUCTURE(S) ET D(ES) UNIONS(S)" >> $F
done

echo "typedef struct $nom"_"s $nom"_"t" >> $Lib
echo -e "struct $nom"_"s {\n}" >> $Src

for F in $Src $Lib $Test ; do # Corps #
	echo -ne "\n" >> $F
	echo "// CRÉATION(S) DE(S) CONSTANTE(S) DE STRUCTURE(S)" >> $F
	echo -ne "\n" >> $F
	echo "// CRÉATION(S) DE(S) FONCTION(S)" >> $F
	echo -e "\n" >> $F
done

# Programme #
echo "// PROGRAMME PRINCIPALE" >> $Test
echo -e "\t/* Programme qui $action */" >> $Test
echo -e "int main() {" >> $Test
echo -e "\t// INITIALISATION DE(S) VARIABLE(S)" >> $Test
echo -e "\t$nom"_"t obj;\n" >> $Test
echo -e "\t// INSTRUCTION(S)" >> $Test
echo -e "\t// FIN DU PROGRAMME" >> $Test
echo -e "\tprintf(\"\\\n\\\n\\\t\\\tFIN DU TEST\\\t\\\t\\\n\\\n\");" >> $Test
echo -e "\treturn 0;" >> $Test
echo -e "}" >> $F
echo -e "\t/* Programme qui $action */" >> $F
echo "// PROGRAMME PRINCIPALE" >> $F

for F in $Src $Lib $Test ; do # fin #
	echo -e "\n// #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### //\n" >> $F
done
# Dernière préparation du fichier #
	clear
	ls *
	echo -e "\n\n\t\tLes fichier $Src, $Lib et $Test ont était crée.\n\n"

# FIN
	exit 0

