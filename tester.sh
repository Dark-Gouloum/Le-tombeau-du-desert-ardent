#!/bin/bash
: '
	* AUTEUR : Erwan PECHON
	* VERSION : 0.1
	* DATE : Mer. 25 Janv. 2023 13:34:37
	* Script qui lance des programme test_.
'

# CRÉATION DES VARIABLES GLOBALES
val=1

# CRÉATION(S) DE(S) FONCTION(S)

# VÉRIFIÉ LES PARAMÉTRES (Renvoyer 1 en cas d'erreur)
Usage="Usage : ./test.sh [-n] <classe>..."
Detail="\t- [-n] : Si présent, désactive valgrind.\n\t- <classe> : lance le programme test_<classe>, si existant."
Error="Nombre de paramètres incorrect : "
	# Bon nombre de paramètre ? #
	# Bon type de paramètre ? #
case $1 in
	"-n")	val=0;	shift	;;
esac

# SCRIPT
while ( test $# -ne 0 ) ; do
	echo -e "\n\nAppuyer sur ENTRÉE pour lancer le test sur $1 :"
	read V
	if ( test $val -eq 1 ) then
		valgrind --leak-check=full ./bin/test_$1
	else
		./bin/test_$1
	fi
	shift
done
echo -e "\n\n\t\tFIN DES TESTS\n\n"
ls ./bin/test_*[^.]? | cut -c12-
echo -e "\n\n"
ls

# FIN
	exit 0


# #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### #

