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
SOURCE=$(filter-out src/main.c , $(wildcard src/*.c))
OBJET=$(SOURCE:src/%.c=objet/%.o)
LIB =
	# Autres


ifeq ($(OS),Windows_NT)
	RM=del
	OPEN=open
	CLEAR=cls
	DATE=date
else
	RM=rm -f
	OPEN=open
	CLEAR=clear
	DATE=$(shell date +%Y-%m-%d)
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
objet/%.o: src/%.c
	${CCOBJ} ${CFLAGS} $< -o $@




################### COMMANDES MAKEFILES ###################
# Commande de lancement des compilation
prog: clean ${PROGRAMME} laugth
test: ${TEST}
all: ${PROGRAMME} test
.PHONY: clean mr_proper laugth PATH PULL ADD COM TEST

#supression des fichier obsolette
clean:
	$(CLEAR)
	$(RM) objet/*.o
mr_proper: clean
	$(RM) ${PROGRAMME} $(wildcard bin/test_*)

#lancement du programme
laugth:
	${PROGRAMME}

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

TEST:
	$(info ceci est un test)
	$(info $(wildcard src/*.c) )
	$(info $(filter-out src/main.c, $(wildcard src/*.c)) )
	$(info $(OBJET) )

################### COMMANDES MAKEFILES ###################
