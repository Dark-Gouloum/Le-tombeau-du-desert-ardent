include Makefile.compilation
LIBRAIRIES = lib
EXECUTABLE = bin

PROGRAMME = $(EXECUTABLE)/tombeauArdent.exe

SOURCE=$(wildcard $(SRC)/*.c)
OBJET=$(SRC:.c=.o)
LIB =
TEST =
DATE=$(shell date +%Y-%m-%d)

cache: $(PROGRAMME)
all: mr_proper ${PROGRAMME} ${TEST}
ProgFinal: clean ${PROG} laugth

#Compilation du programme final
${PROGRAMME}: ${OBJET} ${LIB}
	${CC} -o $@ ${OBJET} src/main.c ${CFLAGS}

#compilation des objets
%.o: $(SRC)/%.c
	${CCOBJ} ${CFLAGS} $< -o $@

#test des fonction du jeux

#supression des fichier obsolette
clean:
	clear
	rm -r -f ${PROG}
	rm  -f object/*.o
mr_proper:
	make clean
	rm -r -f ${TEST}

#lancement du programme
laugth:
	./${PROG}
#commande git
PATH:
	-export LD_LIBRARY_PATH="${LIEN}"
PULL:
	git pull
ADD:
	git add .
COM:
	git commit -m '${USER} ${DATE}  mise à jour'
ME:
	make clean
	make ADD
	make COM
	git push origin meo
LE:
	make clean
	make ADD
	make COM
	git push origin leopolde
MA:
	make clean
	make ADD
	make COM
	git push origin max
MO:
	make clean
	make ADD
	make COM
	git push origin Morgane
TEST:
	echo > $@
