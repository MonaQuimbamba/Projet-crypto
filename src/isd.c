#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include <sys/random.h>
#include "include/matrice.h"

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
       //printf("\nle matrice U  est  [%d][%d] =\n", u.nb_rows, u.nb_columns);
       //printMatrix(&u);
       Matrix inverseU = pivotGaus(&u);
       if(inverseU.valide)
       {
         //printf("\nle l'inverse de U  est  [%d][%d] =\n", inverseU.nb_rows, inverseU.nb_columns);
         //printMatrix(&inverseU);
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





int main(int argc, char const *argv[]) {
  int n=4;
  int k=1;
  int t=2;
  Matrix h = MatrixH(n-k,n);
  printf("\nmatrice H est  [%d][%d] =\n", h.nb_rows, h.nb_columns);
  printMatrix(&h);

  Matrix e = MatrixErreur(1,n,t);
  printf("\nle vecteur e est  [%d][%d] =\n", e.nb_rows, e.nb_columns);
  printMatrix(&e);

  Matrix  transErreur = transpose(&e);
  Matrix s = multiplication(&h,&transErreur);
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
