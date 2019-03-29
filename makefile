siguel: main.o inSVG.o outSVG.o
	gcc -o siguel main.o inSVG.o outSVG.o

main.o: main.c inSVG.h structs.h outSVG.h
	gcc -c main.c -o main.o

inSVG.o: inSVG.c inSVG.h outSVG.h structs.h
	gcc -c inSVG.c -o inSVG.o

outSVG.o: outSVG.c outSVG.h structs.h
	gcc -c outSVG.c -o outSVG.o