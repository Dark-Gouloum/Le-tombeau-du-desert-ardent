############# CRÉATION DES VARIABLES GLOBALES #############
# Options de compilation
include Makefile.compilation

# Nom de fichiers
	# Programme final
PROGRAMME = bin/leTombeauArdent.exe
	# Fichier test
srcTEST = $(wildcard test/*.c)
TEST = $(srcTEST:test/%.c=bin/test_%)
	# Fichier objet
SOURCE=$(shell find src -name "*.c" ! -name "main.c")
OBJET=$(SOURCE:src/%.c=objet/%.o)
LIB =
	# Autres
DATE=$(shell date +%Y-%m-%d)




############### COMPILATION DES EXÉCUTABLES ###############
# Programme final
${PROGRAMME}: src/main.c ${OBJET} ${LIB}
	${CC} -o $@ $< ${OBJET} ${CFLAGS}

# Tests
bin/test_%: test/%.c ${OBJET} ${LIB}
	${CC} -o $@ $< ${OBJET} ${CFLAGS}

# Objets
objet/%.o: src/%.c
	${CCOBJ} ${CFLAGS} $< -o $@




################### COMMANDES MAKEFILES ###################
# Commande de lancement des compilation
Prog: clean ${PROGRAMME} laugth
all: mr_proper ${PROGRAMME} ${TEST}
.PHONY: clean mr_proper laugth PATH PULL ADD COM TEST

#supression des fichier obsolette
clean:
	clear
	rm -f objet/*.o
mr_proper: clean
	rm -rf ${PROGRAMME} ${TEST}

#lancement du programme
laugth:
	./${PROGRAMME}

MESSAGE = mise à jour
#commande git
PULL:
	git pull
ADD: mr_proper
	git add *
MSG = mise à jour
COMM:
	git commit -am '${USER} ${DATE} ${MSG}'
PUSH: ADD COMM
	git push

#commande doxygen
doxygen:
		doxygen ./doc/Doxygen/config-file
		open ./doc/Doxygen/html/index.html


################### COMMANDES MAKEFILES ###################
