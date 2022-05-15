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

Matrix Prange_ISD(int n,int k, Matrix *m, Matrix *s)
{

  int iter=50;
  Matrix e;
  e.valide=false;
  int i=0;
  while( i < iter )
  {

        //Matrix mtrans =transpose(m);
        //Matrix tempPerm =Permutation_cols(&mtrans);
        //printf("\nla permutation de H la matrice P  est  [%d][%d] =\n", tempPerm.nb_rows, tempPerm.nb_columns);
        Matrix perm = Permutation_alea(n);
        printf("\nla permutation  P  est  [%d][%d] =\n", perm.nb_rows, perm.nb_columns);
        printMatrix(&perm);
        Matrix matHP = multiplication(m,&perm);
        printf("\nla mat de HP est  [%d][%d] =\n", matHP.nb_rows, matHP.nb_columns);
        printMatrix(&matHP);
        Matrix matU =  faire_U(n-k,n,&matHP);
        printf("\nla mat U est  [%d][%d] =\n", matU.nb_rows, matU.nb_columns);
        printMatrix(&matU);
      if(monPivot(&matU))
      {
            Matrix  trans = transpose(&matU);
            printf("\nAfficher la transpose de matU [%d][%d] =\n",trans.nb_rows,trans.nb_columns);
            printMatrix(&trans);
            printf("\nAfficher la matrice s  [%d][%d] =\n",s->nb_rows,s->nb_columns);
            printMatrix(s);
            e = multiplication(s,&trans);
            e.valide=true;
            printf("\nAfficher la matrice e [%d][%d] =\n",e.nb_rows,e.nb_columns);
            printMatrix(&e);

            if(poidHamming(&e)==LIMITE) return e;

      }
      i++;
  }


  return e;
}





int main(int argc, char const *argv[]) {
  int n=4;
  int k=1;
  Matrix m = startMatrix(n-k,n);
  printf("\nmatrice H est  [%d][%d] =\n", m.nb_rows, m.nb_columns);
  printMatrix(&m);

  Matrix s = startMatrix(n-k,1);
  printf("\nle vecteur S est  [%d][%d] =\n", s.nb_rows, s.nb_columns);
  printMatrix(&s);




  Matrix e = Prange_ISD(n,k,&m,&s);
  if(e.valide) printMatrix(&e);

  return 0;
}
