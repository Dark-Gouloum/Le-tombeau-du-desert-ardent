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
SOURCE=$(filter-out src/main.c, $(wildcard src/*.c) )
OBJET=$(SOURCE:src/%.c=objet/%.o)
LIB=$(SOURCE:src/%.c=lib/%.h)
	# Autres
DATE=
ifeq ($(OS),Windows_NT)
	DATE=
else
	DATE=$(shell date +%Y-%m-%d)
endif

# Commande
ifeq ($(OS),Windows_NT)
	RM=del
	CLEAR=cls
	OPEN=explorer.exe
else
	RM=rm -fv
	CLEAR=clear
	OPEN=open
endif





############### COMPILATION DES EXÉCUTABLES ###############
firstFIRSTfirst: pull
# Programme final
${PROGRAMME}: src/main.c ${OBJET} ${LIB}
	${CC} -o $@ $< ${OBJET} ${CFLAGS}

# Tests
bin/test_%: test/%.c ${OBJET} ${LIB}
	${CC} -o $@ $< ${OBJET} ${CFLAGS}

# Objets
objet/%.o: src/%.c lib/%.h
	${CCOBJ} ${CFLAGS} $< -o $@




################### COMMANDES MAKEFILES ###################
# Commande de lancement des compilation
prog: clean ${PROGRAMME} laugth
all: ${PROGRAMME} ${TEST}
.PHONY: clean mr_proper laugth PATH PULL ADD COM TEST

#supression des fichier obsolette
clean:
	$(CLEAR)
	$(RM) objet/*.o
mr_proper: clean
	$(RM) ${PROGRAMME} ${TEST}

#lancement du programme
laugth:
	./${PROGRAMME}

MESSAGE = mise à jour
#commande git
pull:
	git pull
MSG = mise à jour
git: mr_proper
	git add *
	git commit -am '${USER} ${DATE} ${MSG}'
	git push

#commande doxygen
doxygen:
	doxygen ./doc/Doxygen/config-file
	$(OPEN) ./doc/Doxygen/html/index.html

#commande test
TEST:
	$(info "test")

################### COMMANDES MAKEFILES ###################
