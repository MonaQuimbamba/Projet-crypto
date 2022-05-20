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



Matrix Prange_ISD(int n,int k, Matrix *h, Matrix *s,Matrix *e,int w_erreur)
{

  int iter=50;
  Matrix e_res;
  e_res.valide=false;
  int i=0;
   while( i < iter )
  {

       Matrix u =  faire_U(n-k,h,e,w_erreur);
       printf("\nla matrice U est  [%d][%d] =\n", u.nb_rows, u.nb_columns);
       //printMatrix(&u);
       //printf(" avant passed \n");
       Matrix inverseU = pivotGaus(&u);
       //printf("  passed \n");
      if(inverseU.valide)
       {

         printf("\nla matrice inverse de U est  [%d][%d] =\n", inverseU.nb_rows, inverseU.nb_columns);
         //printMatrix(&inverseU);
        //printf(" avant passed \n");
         e_res = multiplication(&inverseU,s);
         //printf(" passed \n");
        if(poidHamming(&e_res)==w_erreur){
           e_res.valide=true;
           return e_res;
         }
       }
      i++;
  }
  return e_res;
}



/*
n=400 k=200 poids de l'erreur t=20 (parametres faciles pour un McEliece)
n=1000 k=500 t=10
*/

int main(int argc, char const *argv[]) {
  int n=1000;
  int k=500;
  int w_erreur=10;
  Matrix h = MatrixH(n-k,n);
  //printf("\nmatrice H est  [%d][%d] =\n", h.nb_rows, h.nb_columns);
  //printMatrix(&h);

  Matrix e = createPolynome(n,w_erreur);
  printf("\nle vecteur e est  [%d][%d] =\n", e.nb_rows, e.nb_columns);
  Matrix  e_trans = transpose(&e);
  //printMatrix(&e_trans);
  Matrix s = multiplication(&h,&e);
  printf("\nla matrice s=H*e^t est  [%d][%d] =\n", s.nb_rows, s.nb_columns);
  //printMatrix(&s);

  Matrix ee = Prange_ISD(n,k,&h,&s,&e,w_erreur);
  if(ee.valide){
    printf("\nla matrice e après le prange est  [%d][%d] =\n", ee.nb_rows, ee.nb_columns);
    printMatrix(&ee);
    deleteM(&ee);
  }
  deleteM(&h);
  deleteM(&s);
  deleteM(&e);

  return 0;
}
