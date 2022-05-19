#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include <sys/random.h>
#include "include/matrice.h"
#include "include/polynome.h"
#include "sodium.h"


#define LIMITE 20

Matrix Prange_ISD(int n,int k, Matrix *h, Matrix *s,int t)
{

  int iter=50;
  Matrix e;
  e.valide=false;
  int i=0;
 while( i < iter )
  {
       Matrix u =  faire_U(n-k,h);
       Matrix inverseU = pivotGaus(&u);
      if(inverseU.valide)
       {
         e = multiplication(&inverseU,s);
         if(poidHamming(&e)==t){
           e.valide=true;
           return e;
         }
       }
      i++;
  }
  return e;
}



/*
n=400 k=200 poids de l'erreur t=20 (parametres faciles pour un McEliece)
n=1000 k=500 t=10
*/

int main(int argc, char const *argv[]) {
  int n=10;
  int k=5;
  int t=3;
  Matrix h = MatrixH(n-k,n);
  printf("\nmatrice H est  [%d][%d] =\n", h.nb_rows, h.nb_columns);
  printMatrix(&h);

  Matrix e = createPolynome(n,t);
  printf("\nle vecteur e est  [%d][%d] =\n", e.nb_rows, e.nb_columns);
  printMatrix(&e);

  Matrix s = multiplication(&h,&e);
  printf("\nla matrice S=H*e^t est  [%d][%d] =\n", s.nb_rows, s.nb_columns);
  printMatrix(&s);

  Matrix ee = Prange_ISD(n,k,&h,&s,t);
 if(ee.valide){
    printf("\nla matrice e après le prange est  [%d][%d] =\n", ee.nb_rows, ee.nb_columns);
    printMatrix(&ee);
  }
  deleteM(&h);
  deleteM(&s);
  deleteM(&e);
  deleteM(&ee);
  return 0;
}
