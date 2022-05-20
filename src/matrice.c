#include "include/matrice.h"
#include "libsodium-stable/src/libsodium/include/sodium.h"


Matrix newMatrix(int nb_rows, int nb_columns)
{
    Matrix m;
    m.mat = (Elt *) malloc(sizeof(Elt)*nb_rows*nb_columns);
    m.nb_rows=nb_rows;
    m.nb_columns=nb_columns;
    m.valide=true;
    int i,j;
    for(i=0; i<m.nb_rows; i++)
        for(j=0; j<m.nb_columns; j++)
            setElt(&m,i,j,0);
    return m;
}
Elt getElt(Matrix *m, int row, int column)
{
    return m->mat[row*m->nb_columns+column];
}
void setElt(Matrix *m, int row, int column, Elt val)
{
    m->mat[row*m->nb_columns+column] = val;
    return;
}
void deleteM(Matrix *m)
{
    free(m->mat);
    return;
}
Matrix transpose(Matrix *m)
{
    Matrix m2 = newMatrix(m->nb_columns, m->nb_rows);
    int i,j;
    for (i=0; i<m2.nb_columns; i++)
	for(j=0; j<m2.nb_rows; j++)
	    setElt(&m2,j,i,getElt(m,i,j));
    return m2;
}
Matrix addition(Matrix *m1, Matrix *m2)
{
    Matrix m3 = newMatrix(m1->nb_rows, m1->nb_columns);
    if (m1->nb_rows != m2->nb_rows || m1->nb_columns != m2->nb_columns)
    {
	fprintf(stderr,"addition impossible\n");
	m3.valide=false;
        return m3;
    }
    else
    {
	int i,j;
	for (i=0; i<m3.nb_rows; i++)
	    for (j=0; j<m3.nb_columns; j++)
		setElt(&m3,i,j,(getElt(m1,i,j)+getElt(m2,i,j))%2);
	return m3;
    }
}
Matrix multiplication(Matrix *m1, Matrix *m2)
{
    Matrix m3 = newMatrix(m1->nb_rows, m2->nb_columns);
    if (m1->nb_columns != m2->nb_rows )
    {
	fprintf(stderr,"multiplication impossible\n");
        m3.valide=false;
        return m3;
    }
    else
    {
	int i,j,k;
	Elt elt;
	for (i=0; i<m3.nb_rows; i++)
	    for (j=0; j<m3.nb_columns; j++)
	    {
		elt=0;
		for (k=0; k<m1->nb_columns; k++)
		    elt +=getElt(m1,j,k)*getElt(m2,k,i);
		setElt(&m3,i,j,abs(elt%2));
	    }
	return m3;
    }
}
Matrix mult_scalar(Elt elt, Matrix *m)
{
    Matrix m2 = newMatrix(m->nb_rows, m->nb_columns);
    int i,j;
    for (i=0; i<m2.nb_rows; i++)
	for (j=0; j<m2.nb_columns; j++)
	    setElt(&m2,i,j,(abs(getElt(m,i,j)*elt)%2));
    return m2;
}
void printMatrix(Matrix *m)
{
    if(!m->valide)
    {
        printf("la matrice est invalide\n");
        return;
    }
    int i,j;
    for(i=0; i<m->nb_rows; i++)
    {
        for(j=0; j<m->nb_columns; j++)
        {
            printf(" %d ", getElt(m,i,j));
        }
        putchar('\n');
    }
    return ;
}
Matrix MatrixH(int nb_rows,int nb_columns)
{
    Matrix m;
    m = newMatrix(nb_rows, nb_columns);
    int i,j;
     uint32_t elt;
    for(i=0; i<nb_rows; i++)
    {

        for(j=0; j<nb_columns; j++)
        {
          elt = randombytes_uniform(2);
          setElt(&m,i,j, elt);
        }
    }
    return m;
}
Matrix pivotGaus(Matrix *m)
{

  //int augmentedmatrix[maximum][2*maximum];
  //int *augmentedmatrix = (int *)malloc(maximum * maximum*2 * sizeof(int));

  int augmentedmatrix[maximum][2*maximum];
  int temporary, r ;
  int i, j, k, dimension, temp;
  dimension=m->nb_rows;

  Matrix inverse = newMatrix(dimension,dimension);
  inverse.valide=true;
  for(i=0; i<dimension; i++){
    for(j=0; j<dimension; j++){
      augmentedmatrix[i][j]=getElt(m,i,j);
    }
  }
  for(i=0;i<dimension; i++){
    for(j=dimension; j<2*dimension; j++){
      if(i==j%dimension){
           augmentedmatrix[i][j]=1;
      }
      else{
         augmentedmatrix[i][j]=0;
      }
    }
  }


  // using gauss-jordan elimination
  for(j=0; j<dimension; j++)
  {
    temp=j;
   for(i=j+1; i<dimension; i++){
      if(augmentedmatrix[i][j]>augmentedmatrix[temp][j])temp=i;
   }




   if(abs(augmentedmatrix[temp][j])<minvalue)
              {
                // printf("\n Elements are too small to deal with !!!");
                 inverse.valide=false;
                 //printf(" la valeur de l'inverse  pour not est %d\n",inverse.valide);
                 return inverse;
              }
  // swapping row which has maximum jth column element
   if(temp!=j)
             for(k=0; k<2*dimension; k++)
             {
             temporary=augmentedmatrix[j][k] ;
             augmentedmatrix[j][k]=augmentedmatrix[temp][k] ;
             augmentedmatrix[temp][k]=temporary ;
             }
 // performing row operations to form required identity matrix out of the input matrix
   for(i=0; i<dimension; i++)
             if(i!=j){
             r=augmentedmatrix[i][j];
             for(k=0; k<2*dimension; k++){

               augmentedmatrix[i][k]= abs((int) (augmentedmatrix[i][k] - (augmentedmatrix[j][k]/augmentedmatrix[j][j])*r) % 2);

             }

             }
             else{
             r=augmentedmatrix[i][j];
             for(k=0; k<2*dimension; k++) augmentedmatrix[i][k]/=r ;
             }

  }

  for(i=0; i<dimension; i++)
  {
    int val=0;
   for(j=dimension; j<2*dimension; j++)
   {
     setElt(&inverse,i,val,augmentedmatrix[i][j]);
     val++;
   }

  }

  //printf(" la valeur de l'inverse est %d\n",inverse.valide);
  return inverse;
}
Matrix faire_U(int size_U,Matrix *h,Matrix *e,int w_erreur)
{
  int i,j;
  int n =h->nb_columns;
  int *index=  (int*) malloc(n * sizeof(int));
  int w_matU=0;
// ajouter les conditions pour satisfaire rapport entre les '1' de x et T
  for( i=0 ; i < n ; i++)  index[i] = getElt(e,0,i)==1 ? 1 :0;
  w_matU=size_U - w_erreur;

  //for(i=0; i < n ; i++) printf(" avant [%d]\n",index[i]);
//  printf(" poids manquent %d\n",w_matU);
  uint32_t elt;
   i =0;
  while(i < w_matU){
     elt = randombytes_uniform(n);
     if( index[elt]!=1){
       index[elt] = 1;
       i++;
     }
  }


  int *col_index = (int*) malloc(size_U*sizeof(int));
  int id=0;
  for(i=0; i < n ; i++)
  {
        if(index[i]==1){
         col_index[id]=i;
         id++;
       }
  }



  //for(i=0; i < n ; i++) printf(" tab [%d]\n",index[i]);
  //printf("\n=====\n");
  //for(i=0; i < size_U ; i++) printf(" index [%d]\n",col_index[i]);
   //remplir Mat U avec les bonnes collones
  Matrix mU = newMatrix(size_U,size_U);

  for(i=0; i<size_U; i++)
    for(j=0; j<h->nb_rows; j++)
    setElt(&mU,j,i,getElt(h,j,col_index[i]));

  //free(index);
  //free(col_index);

  return mU;

}
int poidHamming(Matrix *m)
{
    int poids=0;
    int i,j;
    for(i=0; i<m->nb_rows; i++)
        for(j=0; j<m->nb_columns; j++)
            if(getElt(m,i,j)==1) poids++;
    return poids;
}
Matrix copier_matrice(Matrix *m)
{
    Matrix new;
    new.mat = (Elt *) malloc(sizeof(Elt)*m->nb_rows*m->nb_columns);
    new.nb_rows=m->nb_rows;
    new.nb_columns=m->nb_columns;
    new.valide=m->valide;
    int i,j;
    for(i=0; i<new.nb_rows; i++)
        for(j=0; j<new.nb_columns; j++)
            setElt(&new,i,j,getElt(m,i,j));
    return new;
}
Matrix concatenationMatrix(Matrix *u,Matrix *v)
{
   Matrix concat = newMatrix(u->nb_rows,u->nb_columns*2);
   int k;
   for(int i= 0 ; i < u->nb_rows;i++)
   {
      k=0;
     for(int j = 0 ; j < u->nb_columns*2;j++)
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
