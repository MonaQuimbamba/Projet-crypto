#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include "include/matrice.h"

Matrix startMatrix()
{
    Matrix m;
    int nb_rows,nb_columns;
    nb_rows=10;
    nb_columns=10;
    m = newMatrix(nb_rows, nb_columns);
    int i,j;
    Elt elt;
    int a[10][10]={{1, 0, 0, 1, 1, 1, 1, 1, 0, 0 },
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
    {1, 1, 0, 0, 0, 1, 0, 1, 1, 0 },
    {1, 1, 0, 1, 0, 0, 0, 1, 1, 0 },
    {1, 0, 1, 0, 1, 1, 0, 1, 1 ,0 },
    {1, 0, 1, 1, 0, 0, 0, 1, 0 ,0 },
    {1, 1, 0, 1, 0, 0, 1, 0, 1 ,0 },
    {1, 1, 1, 1, 1, 1, 1, 0, 1 ,0 },
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };
    for(i=0; i<nb_rows; i++)
    {
        for(j=0; j<nb_columns; j++)
        {
          elt=a[i][j];
          setElt(&m,i,j, elt);
        }
    }
    return m;
}


void main_inversion()
{
    //matrice
    Matrix m1 = startMatrix();
    printf("\nmatrice est  [%d][%d] =\n", m1.nb_rows, m1.nb_columns);
    printMatrix(&m1);
    Matrix m2;
    if(m1.valide)
    {
      m2 = matrice_inverse_gauss(&m1);
      printf("\nmatrice inverse: [%d][%d] =\n", m2.nb_rows, m2.nb_columns);
      printMatrix(&m2);
    }
    deleteM(&m1);
    deleteM(&m2);
    return;
}

int main(int argc, char const *argv[]) {
   main_inversion();
  return 0;
}
