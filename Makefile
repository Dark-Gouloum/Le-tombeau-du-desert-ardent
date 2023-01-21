include Makefile.compilation
LIB = lib
EXECU_DIR = bin

PROG = tombeauArdent.exe

SRC=$(wildcard $(SRC)/*.c)
OBJ=$(SRC:.c=.o)
LIB =
TEST =


DATE=$(shell date +%Y-%m-%d)

cache:ProgFinal
all: mr_proper ${PROG} ${TEST}
ProgFinal:clean ${PROG} laugth

#Compilation du programme final
${PROG}: ${OBJ} ${LIB}
	${CC} -o $@ ${OBJ} src/main.c ${LIBS} ${INCS} ${FLAGS}

#compilation des objets
%.o: %.c
	${CCOBJ} ${CFLAGS} $(SRC)/%.c -o $@

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
