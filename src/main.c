#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include "include/matrice.h"


#define maximum 10
#define minvalue 0.0005

Matrix startMatrix(int nb_rows,int nb_columns)
{
    Matrix m;
    m = newMatrix(nb_rows, nb_columns);
    int i,j;
    Elt elt;
    for(i=0; i<nb_rows; i++)
    {
        for(j=0; j<nb_columns; j++)
        {
          elt=rand() & 1;
          setElt(&m,i,j, elt);
        }
    }
    return m;
}



void main_inversion()
{
    //matrice
    /*Matrix m1 = startMatrix();
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
    deleteM(&m2);*/
    return;
}


void monPivot()
{

  Matrix m1 = startMatrix(maximum,maximum*2);

  int temporary, r ;
  int i, j, k, dimension, temp;                                  /* declaring counter variables for loops */


  dimension=3;

   /*   storing augmented matrix as a matrix of dimension
        (dimension)x(2*dimension) in 2D array  */
    int a[3][3]={
      {1,1,1},
        {1,1,0},
        {1,0,1}
    };
  /*{
    {1, 0, 0, 1, 1, 1, 1, 1, 0, 0 },
  {1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
  {1, 1, 0, 0, 0, 1, 0, 1, 1, 0 },
  {1, 1, 0, 1, 0, 0, 0, 1, 1, 0 },
  {1, 0, 1, 0, 1, 1, 0, 1, 1 ,0 },
  {1, 0, 1, 1, 0, 0, 0, 1, 0 ,0 },
  {1, 1, 0, 1, 0, 0, 1, 0, 1 ,0 },
  {1, 1, 1, 1, 1, 1, 1, 0, 1 ,0 },
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};*/
   printf("\n Enter a non-singular %dx%d matrix : \n",dimension,dimension);
   for(i=0; i<dimension; i++)
    for(j=0; j<dimension; j++)
      setElt(&m1,i,j,a[i][j]);
              //augmentedmatrix[i][j]=a[i][j];

  printf("\n Before Gauss-Jordan elimination, augmented matrix is : \n\n") ;
  for(i=0; i<dimension; i++)
  {
   for(j=0; j<2*dimension; j++)
        printf("  %d", getElt(&m1,i,j));
   printf("\n");
  }
  /* using gauss-jordan elimination */
  for(j=0; j<dimension; j++)
  {
   temp=j;
  /* finding maximum jth column element in last (dimension-j) rows */
   for(i=j+1; i<dimension; i++)
  if(getElt(&m1,i,j) > getElt(&m1,temp,j)) //if(augmentedmatrix[i][j]>augmentedmatrix[temp][j])
                         temp=i;

   if (abs(getElt(&m1,temp,j)<minvalue))//if(fabs(augmentedmatrix[temp][j])<minvalue)
              {
                 printf("\n Elements are too small to deal with !!!");
              }
  /* swapping row which has maximum jth column element */
   if(temp!=j)
             for(k=0; k<2*dimension; k++)
             {
               temporary=getElt(&m1,j,k);   //augmentedmatrix[j][k] ;
              setElt(&m1,j,k,getElt(&m1,temp,k));//augmentedmatrix[j][k]=augmentedmatrix[temp][k] ;
              setElt(&m1,temp,k,temporary);//augmentedmatrix[temp][k]=temporary ;
             }
 /* performing row operations to form required identity matrix out of the input matrix */
   for(i=0; i<dimension; i++)
             if(i!=j)
             {
             r=getElt(&m1,i,j);  //augmentedmatrix[i][j];
             for(k=0; k<2*dimension; k++)
             {

               //augmentedmatrix[i][k]= abs((int) (augmentedmatrix[i][k] - (augmentedmatrix[j][k]/augmentedmatrix[j][j])*r) % 2);
                Elt elt = abs((int) (getElt(&m1,i,k) - (getElt(&m1,j,k)/getElt(&m1,j,j))*r) % 2);
                setElt(&m1,i,k,elt);
             }

             }
             else
             {
             r=getElt(&m1,i,j); //augmentedmatrix[i][j];
             for(k=0; k<2*dimension; k++)
               setElt(&m1,i,k,getElt(&m1,i,k)/r);//augmentedmatrix[i][k]/=r ;
             }

  }

  /* Display augmented matrix */
  printf("\n After Gauss-Jordan elimination, augmented matrix is : \n\n") ;
  for(i=0; i<dimension; i++)
  {
   for(j=0; j<2*dimension; j++)
             printf("  %d", getElt(&m1,i,j));//augmentedmatrix[i][j]) ;
   printf("\n");
  }


  /* displaying inverse of the non-singular matrix */

  printf("\n\n\n The inverse of the entered non-singular matrix is : \n\n");

  for(i=0; i<dimension; i++)
  {
   for(j=dimension; j<2*dimension; j++)
             printf("  %d",getElt(&m1,i,j));//augmentedmatrix[i][j]);
   printf("\n");
  }

}

int main(int argc, char const *argv[]) {
  int n=4;
  int k=1;
  Matrix m1 = startMatrix(n-k,n);
  printf("\nmatrice H est  [%d][%d] =\n", m1.nb_rows, m1.nb_columns);
  printMatrix(&m1);

  Matrix s = startMatrix(n-k,1);
  printf("\nle vecteur S est  [%d][%d] =\n", s.nb_rows, s.nb_columns);
  //printMatrix(&s);

  Matrix mtrans =transpose(&m1);
  printf("\nla transpose de H est  [%d][%d] =\n", mtrans.nb_rows, mtrans.nb_columns);
  //printMatrix(&mtrans);


  Matrix tempPerm =Permutation_cols(&mtrans);
  printf("\nla permutation de H la matrice P  est  [%d][%d] =\n", tempPerm.nb_rows, tempPerm.nb_columns);
  Matrix perm =transpose(&tempPerm);
  printMatrix(&perm);


  Matrix matHP = multiplication(&m1,&perm);
  printf("\nla mat de HP est  [%d][%d] =\n", tempPerm.nb_rows, tempPerm.nb_columns);
  printMatrix(&matHP);

monPivot();
  return 0;
}
