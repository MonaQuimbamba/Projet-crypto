prog: main.o matrice.o
	gcc -Wall -o prog main.o matrice.o

main.o : main.c
	gcc -Wall -c -Wall main.c

matrice.o : matrice.c
	gcc -c -Wall matrice.c

clean :
	rm -f prog *.o
