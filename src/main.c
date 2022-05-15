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
  //while(iter > 0 )
  {

        Matrix mtrans =transpose(m);
        Matrix tempPerm =Permutation_cols(&mtrans);
        //printf("\nla permutation de H la matrice P  est  [%d][%d] =\n", tempPerm.nb_rows, tempPerm.nb_columns);
        Matrix perm =transpose(&tempPerm);
        //printMatrix(&perm);
        Matrix matHP = multiplication(m,&perm);
        //  printf("\nla mat de HP est  [%d][%d] =\n", matHP.nb_rows, matHP.nb_columns);
        //printMatrix(&matHP);
       Matrix matU =  faire_U(n-k,n,&matHP);
       //printf("\nla mat U est  [%d][%d] =\n", matU.nb_rows, matU.nb_columns);
       //printMatrix(&matU);
      if(calcul_determinant_recursif(&matU)>0)
      {
            Matrix inverse = monPivot(&matU);
            //printf("\nla mat inverse de U^-1 est  [%d][%d] =\n", inverse.nb_rows, inverse.nb_columns);
            //printMatrix(&inverse);
            Matrix  trans = transpose(&matU);
            Matrix e = multiplication(s,&trans);
            printf("afficher e \n");
            printMatrix(&e);

            printf("afficher e \n");
            printMatrix(&trans);

            if(poidHamming(&e)==LIMITE) return e;

      }
      iter--;
  }

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

  printf(" Le resulat \n");
  Matrix e = Prange_ISD(n,k,&m,&s);
  if(e.valide) printMatrix(&e);

  return 0;
}
