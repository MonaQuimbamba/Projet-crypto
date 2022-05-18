#include "include/matrice.h"


/**
 * \fn Matrix newMatrix(int nb_rows, int nb_columns)
 * \brief fonction creant une nouvelle matrice nulle
 * de taille nb_rows*nb_columns
 * \param nb_rows nombre de lignes
 * \param nb_columns nombre de colonnes
 * \return nouvelle matrice
 * \post allocation memoire de la matrice implique l'utilisation
 * de la fonction deleteM(Matrix *) pour liberer la memoire
 */
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


/**
 * \fn Elt getElt(Matrix *m, int row, int column)
 * \brief fonction permettant de recuperer la valeur de l'element
 * de la matrice donné aux coordonnées données
 * \param m pointeur sur la matrice
 * \param row indice de la ligne de l'element
 * \param column indice de la colonne de l'element
 * \return la valeur de l'element
 * \pre la ligne et la colonne donnée doit etre dans la matrice
 */
Elt getElt(Matrix *m, int row, int column)
{
    return m->mat[row*m->nb_columns+column];
}


/**
 * \fn Elt setElt(Matrix *m, int row, int column)
 * \brief fonction permettant de redefinir la valeur de l'element
 * de la matrice donné aux coordonnées données
 * \param m pointeur sur la matrice
 * \param row indice de la ligne de l'element
 * \param column indice de la colonne de l'element
 * \return void
 * \pre la ligne et la colonne donnée doit etre dans la matrice
 */
void setElt(Matrix *m, int row, int column, Elt val)
{
    m->mat[row*m->nb_columns+column] = val;
    return;
}


/**
 * \fn void deleteM(Matrix *m)
 * \brief fonction liberant l'espace mémoire alloué pour
 * la matrice donnée
 * \param m pointeur sur la matrice a liberer
 * \return void
 */
void deleteM(Matrix *m)
{
    free(m->mat);
    return;
}

/**
 * \fn Matrix transpose(Matrix *m)
 * \brief fonction calculant la trans pose d'une matrice
 * \param m matrice de depart
 * \return transpose de la matrice donnee
 * \post creation d'une nouvelle matrice
 * necessite l'utilisation de deleteM(Matrix *)
 */
Matrix transpose(Matrix *m)
{
    Matrix m2 = newMatrix(m->nb_columns, m->nb_rows);
    int i,j;
    for (i=0; i<m2.nb_columns; i++)
	for(j=0; j<m2.nb_rows; j++)
	    setElt(&m2,j,i,getElt(m,i,j));
    return m2;
}


/**
 * \fn Matrix addition(Matrix *m1, Matrix *m2)
 * \brief fonction faisant l'addition entre deux matrices
 * quitte si l'addition est impossible
 * \param m1 pointeur sur la premiere matrice
 * \param m2 pointeur sur la deuxieme matrice
 * \return la matrice resultat de la somme des deux premieres
 * \post creation d'une nouvelle matrice implique
 * l'utilisation de la fonction deleteM(Matrix *)
 */
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


/**
 * \fn Matrix multiplication(Matrix *m1, Matrix *m2)
 * \brief fonction faisant la multiplication entre deux matrices
 * quitte si la multiplication est impossible
 * \param m1 pointeur sur la premiere matrice
 * \param m2 pointeur sur la deuxieme matrice
 * \return la matrice resultat du produit des deux premieres
 * \post creation d'une nouvelle matrice implique
 * l'utilisation de la fonction deleteM(Matrix *)
 */
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


/**
 * \fn Matrix mult_scalar(Elt elt, Matrix *m)
 * \brief fonction faisant la multiplication entre un scalaire
 * et une matrice
 * \param elt scalaire
 * \param m pointeur sur la matrice
 * \return la matrice resultat du produit de la matrice
 * par le scalaire
 * \post creation d'une nouvelle matrice implique
 * l'utilisation de la fonction deleteM(Matrix *)
 */
Matrix mult_scalar(Elt elt, Matrix *m)
{
    Matrix m2 = newMatrix(m->nb_rows, m->nb_columns);
    int i,j;
    for (i=0; i<m2.nb_rows; i++)
	for (j=0; j<m2.nb_columns; j++)
	    setElt(&m2,i,j,(getElt(m,i,j)*elt)%2);
    return m2;
}

/**
 * \fn void prinMatrix(Marix *m)
 * \brief fonction qui affiche la matrice donnée
 * \param m pointeur sur la matrice a afficher
 * \return void
 */
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
          elt=rand() % 2;
          setElt(&m,j,i, elt);
        }
    }
    return m;
}

int fillMatrixH(int nb_columns){

  return 0;
}

Matrix MatrixH(int nb_rows,int nb_columns)
{
    Matrix m;
    m = newMatrix(nb_rows, nb_columns);
    int i,j;
    Elt elt;
    for(i=0; i<nb_rows; i++)
    {
        int num = rand() %(nb_columns - 0 + 1) + 0;
        for(j=0; j<nb_columns; j++)
        {
          if (j==num || i==0) elt=1;
          else elt=fillMatrixH(nb_columns);
          setElt(&m,i,j, elt);
        }
    }
    return m;
}

Matrix MatrixErreur(int nb_rows,int nb_columns,int t)
{
    Matrix m;
    m = newMatrix(nb_rows, nb_columns);
    int i,j;
    Elt elt;
    for(i=0; i<nb_rows; i++)
    {

        for(j=0; j<nb_columns; j++)
        {
          if (t>0) elt=1;
          else elt=fillMatrixH(nb_columns);
          setElt(&m,i,j, elt);
          t--;
        }
    }
    return m;
}

Matrix pivotGaus(Matrix *m)
{

  int augmentedmatrix[maximum][2*maximum];
  int temporary, r ;
  int i, j, k, dimension, temp;
  dimension=m->nb_rows;

  Matrix inverse = startMatrix(dimension,dimension);
  inverse.valide=true;
  // remplir la matrix
  for(i=0; i<dimension; i++)
   for(j=0; j<dimension; j++)
             augmentedmatrix[i][j]=getElt(m,i,j);

  /// faire l'identite
  for(i=0;i<dimension; i++)
   for(j=dimension; j<2*dimension; j++)
       if(i==j%dimension)
          augmentedmatrix[i][j]=1;
       else
          augmentedmatrix[i][j]=0;

  // using gauss-jordan elimination
  for(j=0; j<dimension; j++)
  {
   temp=j;
  // finding maximum jth column element in last (dimension-j) rows
   for(i=j+1; i<dimension; i++)
 if(augmentedmatrix[i][j]>augmentedmatrix[temp][j])
                         temp=i;

   if(abs(augmentedmatrix[temp][j])<minvalue)
              {
                // printf("\n Elements are too small to deal with !!!");
                 inverse.valide=false;
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

  for(i=0; i<dimension; i++)
  {
    int val=0;
   for(j=dimension; j<2*dimension; j++)
   {
     setElt(&inverse,i,val,augmentedmatrix[i][j]);
     val++;
   }

  }

  return inverse;

}

bool verify_tab(int *tab,int val,int size_U)
{
   for(int i =0 ; i < size_U ;i++)
   {
     if(tab[i]==val) return false;
   }
   return true;
}

Matrix faire_U(int size_U,Matrix *h)
{
    int i,j;
   int index[size_U];
  for(int i=0 ; i < size_U ; i++) index[i]=0;

  i = 0;
  while(i < size_U)
  {

      srand(time(NULL));
     int num = rand() %(size_U - 0 + 1) + 0;
    if(i==0)
    {
      index[i]=num;
      i++;
    }

    else{

     if(verify_tab(index,num,size_U)){
        index[i]=num;
        i++;
      }
    }

  }

  //for(int i=0 ; i < size_U ; i++) printf("%d\n", index[i]);
  //printf("\n");
  // remplir Mat U avec les bonnes collones
  Matrix mU = startMatrix(size_U,size_U);

  for(i=0; i<h->nb_rows; i++)
  {
    int val=0;
    for(j=0; j<size_U; j++)
    {
      setElt(&mU,i,val,getElt(h,i,index[j]));
      val++;
    }
  }

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

Matrix createPolynome(int nb_rows,int nb_columns,int w)
{
    Matrix m;
    m = newMatrix(nb_rows, nb_columns);
    int i,j;
    Elt elt;
    for(i=0; i<nb_rows; i++)
    {
        int lig = rand() % (nb_rows -3 + 1) +3 ;
        for(j=0; j<nb_columns; j++)
        {
          int col = rand() % (nb_rows -3 + 1) +3;
          if (lig+col%2!=0 & w>0){
            elt=1;
              w--;
          }
          else elt=fillMatrixH(nb_columns);
          setElt(&m,i,j, elt);

        }
    }
    return m;
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
