all: isd mdpc

isd: isd.o matrice.o polynome.o
	gcc -Wall -o isd isd.o matrice.o polynome.o -lsodium

mdpc: mdpc.o matrice.o polynome.o md5.o
	gcc -Wall -o mdpc mdpc.o matrice.o polynome.o md5.o -lsodium

isd.o : isd.c
	gcc -Wall -c isd.c

mdpc.o : mdpc.c md5.o
	gcc -Wall -c  mdpc.c

polynome.o : polynome.c
	gcc -c -Wall polynome.c -lsodium

matrice.o : matrice.c
	gcc -c -Wall matrice.c -lsodium

md5.o : md5.c
	gcc -c -Wall md5.c

clean :
	rm -f isd mdpc *.o
