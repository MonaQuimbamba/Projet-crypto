prog: mdpc.o matrice.o
	gcc -Wall -o prog mdpc.o matrice.o

mdpc.o : mdpc.c
	gcc -Wall -c -Wall mdpc.c

matrice.o : matrice.c
	gcc -c -Wall matrice.c

clean :
	rm -f prog *.o
