#!/bin/bash
: '
	* AUTEUR : Erwan PECHON
	* VERSION : 0.1
	* DATE : Ven. 03 févr. 2023 16:03:24
	* Script qui installe les librairies SDL
'

# CRÉATION DES VARIABLES GLOBALES
#	# Nombre de paramètre
nbParam=0

# VÉRIFIÉ LES PARAMÉTRES (Renvoyer 1 en cas d'erreur)
Usage="Usage : ./install_SDL.sh"
Error="Nombre de paramètres incorrect : "
#	# Bon nombre de paramètre ? #
if ( test $# != $nbParam ) then
	echo $Error $# " ($nbParam paramétre attendu)"
	echo $Usage
	exit 1
fi
#	# Bon type de paramètre ? #

# SCRIPT
Dep=$(pwd)
cd ~/Téléchargements/
lstFile=( $(find -name "SDL2*.tar.gz") )

for F in ${lstFile[*]} ; do
	echo $F
done

# FIN
cd $Dep
exit 0

