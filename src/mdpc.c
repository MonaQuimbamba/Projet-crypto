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

void rotate(int arr[], int n)
{
int x = arr[n-1], i;
for (i = n-1; i > 0; i--)
	arr[i] = arr[i-1];
arr[0] = x;
}


Matrix rot(Matrix *m)
{
	Matrix rot=newMatrix(m->nb_rows,m->nb_rows);
	int k = 0;
  Elt elt ;
  int tab[m->nb_rows];
  for(int i=0 ; i<m->nb_rows;i++) tab[i]=getElt(m,0,i);
  for(int i = 0 ; i < rot.nb_rows; i++)
  {
    for(int j = 0 ; j < rot.nb_columns ;j++)
    {
       elt = tab[j];
       setElt(&rot,i,j,elt);
    }
    rotate(tab,m->nb_rows);
  }
	return rot;
}



void bitFlipping(Matrix *ho, Matrix *h1,Matrix *s,int t,int w)
{
    Matrix u = newMatrix(s->nb_rows,1);
    Matrix v = newMatrix(s->nb_rows,1);

    Matrix u_v = concatenationMatrix(&u,&v);
    printf("\nmatrice (u,v) est  [%d][%d] =\n", u_v.nb_rows, u_v.nb_columns);
    printMatrix(&u_v);

    Matrix rot_h1 = rot(h1);
    printf("\nmatrice rot(h1) est  [%d][%d] =\n", rot_h1.nb_rows, rot_h1.nb_columns);
    printMatrix(&rot_h1);
    Matrix h_neg = mult_scalar(-1,ho);
    Matrix rot_ho_neg = rot(&h_neg);
    printf("\nmatrice rot(-ho) est  [%d][%d] =\n", rot_ho_neg.nb_rows, rot_ho_neg.nb_columns);
    printMatrix(&rot_ho_neg);

    Matrix trans_rot_ho=transpose(&rot_ho_neg);
    Matrix trans_rot_h1=transpose(&rot_h1);

    printf("\nmatrice trnas_rot_h1 est  [%d][%d] =\n", trans_rot_h1.nb_rows, trans_rot_h1.nb_columns);
    printMatrix(&trans_rot_h1);

    Matrix H = concatenationMatrix(&trans_rot_ho,&trans_rot_h1);
    printf("\nmatrice H est  [%d][%d] =\n", H.nb_rows, H.nb_columns);
    printMatrix(&H);

    Matrix syndrome=s;

    printf("\nmatrice syndrome est  [%d][%d] =\n", syndrome.nb_rows, syndrome.nb_columns);
    printMatrix(&syndrome);

    Matrix flipped_positions =  newMatrix(1,2*s->nb_rows);
    printf("\nmatrice flipped_positions est  [%d][%d] =\n", flipped_positions.nb_rows, flipped_positions.nb_columns);
    printMatrix(&flipped_positions);

    Matrix sum = multiplication(&syndrome,&H);
    printf("\nmatrice sum est  [%d][%d] =\n", sum.nb_rows, sum.nb_columns);
    printMatrix(&sum);

    /*Matrix rot_h1 = rot(h1);
    printf("\nmatrice rot(h1) est  [%d][%d] =\n", rot_h1.nb_rows, rot_h1.nb_columns);
    printMatrix(&rot_h1);

    printf("||u||=%d, ||v||=%d ||s||=%d\n",poidHamming(&u),poidHamming(&v),poidHamming(s));
    //while()*/


}




int main(int argc, char const *argv[]) {
  int n=4;
  int w=2;
  int t=3;


  // Alice
  Matrix ho = createPolynome(n,1,t);
  setElt(&ho,0,0,1);
  setElt(&ho,0,1,0);
  setElt(&ho,0,2,1);
  setElt(&ho,0,3,1);
  Matrix h1 = createPolynome(n,1,t);
  setElt(&h1,0,0,1);
  setElt(&h1,0,1,1);
  setElt(&h1,0,2,1);
  setElt(&h1,0,3,0);
  printf("\nmatrice ho est  [%d][%d] =\n", ho.nb_rows, ho.nb_columns);
  printMatrix(&ho);
  printf("\nmatrice h1 est  [%d][%d] =\n", h1.nb_rows, h1.nb_columns);
  printMatrix(&h1);

  Matrix Ho = rot(&ho);
  //printf("\nmatrice cyclique de ho est  [%d][%d] =\n", Ho.nb_rows, Ho.nb_columns);
  //printMatrix(&Ho);

  Matrix inverse_ho = pivotGaus(&Ho);
  //printf("\n l'inverse de la matrice cyclique de ho est  [%d][%d] =\n", inverse_ho.nb_rows, inverse_ho.nb_columns);
  //if(inverse_ho.valide==true)   printMatrix(&inverse_ho);

  Matrix h = multiplication(&inverse_ho,&h1);
  printf("\nmatrice h est  [%d][%d] =\n", h.nb_rows, h.nb_columns);
  printMatrix(&h);

  Matrix H = rot(&h);
  //printf("\nmatrice cyclique de h est  [%d][%d] =\n", H.nb_rows, H.nb_columns);
  //printMatrix(&H);


  // Bob
  Matrix eo = MatrixErreur(n,1,t);
  Matrix e1 = MatrixErreur(n,1,t);
  setElt(&e1,0,1,0);
  setElt(&e1,0,2,1);

  printf("\nmatrice eo est  [%d][%d] =\n", eo.nb_rows, eo.nb_columns);
  printMatrix(&eo);

  printf("\nmatrice e1 est  [%d][%d] =\n", e1.nb_rows, e1.nb_columns);
  printMatrix(&e1);

  Matrix c1 = multiplication(&H,&e1);
  //printf("\nmatrice c1 est  [%d][%d] =\n", c1.nb_rows, c1.nb_columns);
  //printMatrix(&c1);

  Matrix c = addition(&eo,&c1);
  //printf("\nmatrice c est  [%d][%d] =\n", c.nb_rows, c.nb_columns);
  //printMatrix(&c);

  Matrix s = multiplication(&Ho,&c);
  printf("\nmatrice s est  [%d][%d] =\n", s.nb_rows, s.nb_columns);
  printMatrix(&s);

  bitFlipping(&ho,&h1,&s,t,w);


  deleteM(&eo);
  deleteM(&e1);
  deleteM(&ho);
  deleteM(&h1);
  deleteM(&h);
  deleteM(&inverse_ho);
  deleteM(&c1);
  deleteM(&s);
  deleteM(&H);
  deleteM(&Ho);


  return 0;
}
