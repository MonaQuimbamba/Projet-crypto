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




int main(int argc, char const *argv[]) {
  int n=4;
  int k=1;

  Matrix ho = startMatrix(n,1);
  Matrix h1 = startMatrix(n,1);
  printf("\nmatrice Ho est  [%d][%d] =\n", ho.nb_rows, ho.nb_columns);
  printMatrix(&ho);

  printf("\nmatrice H1 est  [%d][%d] =\n", h1.nb_rows, h1.nb_columns);
  printMatrix(&h1);

  deleteM(&ho);
  deleteM(&h1);


  return 0;
}
