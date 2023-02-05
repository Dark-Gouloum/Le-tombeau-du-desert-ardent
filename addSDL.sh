#!/bin/bash
: '
	* AUTEUR : Erwan PECHON
	* VERSION : 0.1
	* DATE : Dim. 05 Févr. 2023 16:13:08
	* Script qui installe une bibliothéque SDL.
'

# CRÉATION DES VARIABLES GLOBALES
	nbParam=0

# CRÉATION(S) DE(S) FONCTION(S)

# VÉRIFIÉ LES PARAMÉTRES (Renvoyer 1 en cas d'erreur)
	Usage="Usage : ./addSDL.sh"
	Detail=""
	Error="Nombre de paramètres incorrect : "
	# Bon nombre de paramètre ? #
		if ( test $# != $nbParam ) then
			echo $Error $# " ($nbParam attendu)"
			echo $Usage
			exit 1
		fi
	# Bon type de paramètre ? #

# SCRIPT
clear
echo -n "dossier d'installation : " ; pwd
dossierInstall=$(pwd)
cd ~/Téléchargements
echo -n "chargement du dossier : " ; pwd
lstSDLArchive=( $(find . -name "SDL2*-*.tar.gz") )
echo "[${lstSDLArchive[*]}]"

for SDLArchive in ${lstSDLArchive[*]} ; do
	clear
	echo -e "\t\tinstalation de $SDLArchive."
	echo -e "\tAppuyer sur ENTRÉE pour lancer le décompilage de l'archive." ; read V
	tar -xzvf $SDLArchive
	rm -vi $SDLArchive
	version=$(basename $SDLArchive .tar.gz | cut -d- -f2 )
	SDL=$(echo $SDLArchive | cut -d- -f1 | cut -d/ -f2)
	cd ./$SDL-$version
	echo -n "chargement du dossier : " ; pwd
	echo -e "\tAppuyer sur ENTRÉE pour lancer la compilation de la $SDL." ; read V
	./configure --prefix=$dossierInstall/SDL2
	make
	make install
	if ( test $SDL = "SDL2" ) then
		echo -e "\tAppuyer sur ENTRÉE pour lancer l'ajout de la $SDL au systéme." ; read V
		if ( ! test -e $HOME/.bashrc ) then
			touch $HOME/.bashrc
			echo "$HOME/.bashrc créer"
		fi
		echo -e "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$dossierInstall/SDL2/lib" >> $HOME/.bashrc
		echo "LD_LIBRARY_PATH mis à jour"
		echo "export PATH=$dossierInstall/SDL2/bin:$PATH" >> $HOME/.bashrc
		echo "PATH mis à jour"
		source ~/.bashrc
		echo "systéme actualiser"
		mkdir $dossierInstall/SDL2/doc
	fi
	if ( test -e ./docs ) then
		echo -e "\tAppuyer sur ENTRÉE pour récuppérer la doc." ; read V
		mv ./docs/* $dossierInstall/SDL2/doc
	else
		ls
		echo -e "\tAppuyer sur ENTRÉE pour continuer (pas de documentation)." ; read V
	fi
	echo -e "\tAppuyer sur ENTRÉE pour supprimer les fichiers inutiles." ; read V
	cd ../
	rm -rvf ./$SDL-$version
done

# FIN
cd $dossierProjet
echo -n "chargement du dossier : " ; pwd
echo -e "\n\n\t\tFIN DU SCRIPT\n\n"
exit 0


# #####-#####-#####-#####-##### FIN PROGRAMMATION #####-#####-#####-#####-##### #

