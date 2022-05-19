all: isd mdpc

isd: isd.o matrice.o
	gcc -Wall -o isd isd.o matrice.o polynome.o -lsodium

mdpc: mdpc.o matrice.o polynome.o
	gcc -Wall -o mdpc mdpc.o matrice.o polynome.o -lsodium

isd.o : isd.c
	gcc -Wall -c isd.c

mdpc.o : mdpc.c
	gcc -Wall -c  mdpc.c

matrice.o : matrice.c
	gcc -c -Wall matrice.c -lsodium

polynome.o : polynome.c
	gcc -c -Wall polynome.c -lsodium

clean :
	rm -f prog *.o
