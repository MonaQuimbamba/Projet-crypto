#include "include/polynome.h"
#include "libsodium-stable/src/libsodium/include/sodium.h"


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
Matrix subraction_Polynome(Matrix *u,Matrix *v)
{

	Matrix res = newMatrix(v->nb_rows,1);

  //printf(" matU \n");
  Matrix t = transpose(u);
  //printMatrix(&t);
//  printf(" matV \n");
//  printMatrix(v);
	for(int i =0 ; i< res.nb_rows; i++)
		setElt(&res,0,i, abs(getElt(v,0,i) - getElt(&t,0,i))%2);

 return res;
}
Matrix createPolynome(int degre,int w)
{
    Matrix m;
    m = newMatrix(degre, 1);
    uint32_t elt;
    int i =0;
    while(i < w){
       elt = randombytes_uniform(degre);
       if(getElt(&m,0,elt)!=1){
         setElt(&m,0,elt, 1);
         i++;
       }
    }

    return m;
}
Matrix concatenationPoly(Matrix *u,Matrix *v)
{
   Matrix concat = newMatrix(u->nb_rows*2,1);
   int k;
   printf(" mat in lig %d et col %d \n",u->nb_rows,u->nb_columns );
   printf("lig %d et col %d \n",concat.nb_rows , concat.nb_columns);
   for(int i= 0 ; i < u->nb_columns;i++)
   {
      k=0;
     for(int j = 0 ; j < u->nb_rows*2;j++)
     {
       if(j <u->nb_columns) setElt(&concat,i,j,getElt(u,i,j));
       else
       {
         setElt(&concat,i,j,getElt(v,i,k));
         k++;
       }
     }
   }

   return concat;
}
Matrix getPolyFromCycleMatrix(Matrix *p)
{
      Matrix m;
      m = newMatrix(p->nb_rows, 1);
      for(int j=0; j<p->nb_rows; j++)
          setElt(&m,0,j, getElt(p,0,j));
      return m;
}
