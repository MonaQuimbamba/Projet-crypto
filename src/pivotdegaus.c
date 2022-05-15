#include<stdio.h>
#include<math.h>
#define maximum 10
#define minvalue 0.0005

void main()
{
 int augmentedmatrix[maximum][2*maximum] ;
                                                                /* 2D array declared to store augmented matrix */
 int temporary, r ;
 int i, j, k, dimension, temp;                                  /* declaring counter variables for loops */



 printf("\n  INVERSE OF NON-SINGULAR MATRIX BY GAUSS-JORDAN ELIMINATION  METHOD");

 printf("\n Enter the dimension of the matrix to be provided as input : \n");
// scanf("%d",&
dimension=3;

 /*   storing augmented matrix as a matrix of dimension
      (dimension)x(2*dimension) in 2D array  */
  int a[3][3]={
    {1,1,1},
      {1,1,0},
      {1,0,1}
  };
  /*{{1, 0, 0, 1, 1, 1, 1, 1, 0, 0 },
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
            augmentedmatrix[i][j]=a[i][j];

 /* augmenting with identity matrix of similar dimensions */

 for(i=0;i<dimension; i++)
  for(j=dimension; j<2*dimension; j++)
      if(i==j%dimension)
         augmentedmatrix[i][j]=1;
      else
         augmentedmatrix[i][j]=0;

   printf("\n Before Gauss-Jordan elimination, augmented matrix is : \n\n") ;
   for(i=0; i<dimension; i++)
   {
    for(j=0; j<2*dimension; j++)
              printf("  %d",augmentedmatrix[i][j]) ;
    printf("\n");
   }

 /* using gauss-jordan elimination */

 for(j=0; j<dimension; j++)
 {
  temp=j;
 /* finding maximum jth column element in last (dimension-j) rows */
  for(i=j+1; i<dimension; i++)
if(augmentedmatrix[i][j]>augmentedmatrix[temp][j])
                        temp=i;

  if(abs(augmentedmatrix[temp][j])<minvalue)
             {
                printf("\n Elements are too small to deal with !!!");
             }
 /* swapping row which has maximum jth column element */
  if(temp!=j)
            for(k=0; k<2*dimension; k++)
            {
            temporary=augmentedmatrix[j][k] ;
            augmentedmatrix[j][k]=augmentedmatrix[temp][k] ;
            augmentedmatrix[temp][k]=temporary ;
            }
/* performing row operations to form required identity matrix out of the input matrix */
  for(i=0; i<dimension; i++)
            if(i!=j)
            {
            r=augmentedmatrix[i][j];
            for(k=0; k<2*dimension; k++)
            {

              augmentedmatrix[i][k]= abs((int) (augmentedmatrix[i][k] - (augmentedmatrix[j][k]/augmentedmatrix[j][j])*r) % 2);

            }

            }
            else
            {
            r=augmentedmatrix[i][j];
            for(k=0; k<2*dimension; k++)
              augmentedmatrix[i][k]/=r ;
            }

 }
 /* Display augmented matrix */
 printf("\n After Gauss-Jordan elimination, augmented matrix is : \n\n") ;
 for(i=0; i<dimension; i++)
 {
  for(j=0; j<2*dimension; j++)
            printf("  %d",augmentedmatrix[i][j]) ;
  printf("\n");
 }


 /* displaying inverse of the non-singular matrix */

 printf("\n\n\n The inverse of the entered non-singular matrix is : \n\n");

 for(i=0; i<dimension; i++)
 {
  for(j=dimension; j<2*dimension; j++)
            printf("  %d",augmentedmatrix[i][j]);
  printf("\n");
 }

 }
