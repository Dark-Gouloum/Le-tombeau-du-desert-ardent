#!/bin/bash
: '
	* AUTEUR : Erwan PECHON
	* VERSION : 0.1
	* DATE : Mer. 25 Janv. 2023 13:34:37
	* Script qui lance des programme test_.
'

# CRÉATION DES VARIABLES GLOBALES
val=1
cl=0

# CRÉATION(S) DE(S) FONCTION(S)

# VÉRIFIÉ LES PARAMÉTRES (Renvoyer 1 en cas d'erreur)
Usage="Usage : ./test.sh [-nc] <classe>..."
Detail="\t- [-n] : Si présent, désactive valgrind.\n\t- [-c] : si présent, recompile tout.\n\t- <classe> : lance le programme test_<classe>, si existant."
Error="Nombre de paramètres incorrect : "
	# Bon nombre de paramètre ? #
	# Bon type de paramètre ? #
case $1 in
	# Si deux des trois paramètres :
	"-cn")	val=0;	cl=1;	shift	;;
	"-nc")	val=0;	cl=1;	shift	;;
	# Si un seul paramètre :
	"-n")	val=0;	shift	;;
	"-c")	cl=1;	shift	;;
esac
lstExec=()

# SCRIPT
clear
# Création des noms d'éxécutable à lancer :
while ( test $# -ne 0 ) do
	lstExec=( ${lstExec[*]} ./bin/test_$1 )
	shift
done
# Détruire les anciens éxecutables
rm -vf ${lstExec[*]}
# Compiler
if ( test $cl -eq 0 ) then
	make all
else
	make clean all
fi
# Éxecuter les programmes
Fval="valgrind.log"
Fval2="valgrind-2.log"
rm -f $Fval
touch $Fval
for File in ${lstExec[*]} ; do
	echo -e "\n\nAppuyer sur ENTRÉE pour lancer le test sur '$File' :"
	read V
	if (test $val -eq 1 ) then
		valgrind --leak-check=full --show-reachable=yes -s --track-origins=yes --log-file="$Fval" $File
	else
		$File
	fi
done
echo -e "\n\n\t\tFIN DES TESTS\n\n"
ls ./bin/test_*[^.]? | cut -c12-
echo -e "\n\n"
ls

# FIN
	exit 0


# #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### #

