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
 * \brief fonction qui copie une matrice
 * \return une copie de la matrice
 */
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


/**
 * \fn bool isSymetric(Matrix *m)
 * \brief fonction verifiant si la matrice est sysmetrique
 * \param m pointeur sur la matrice
 * \return true si elle est symetrique false sinon
 */
bool isSymetric(Matrix *m)
{
    if(!isSquare(m))
    {
        return false;
    }
    int i,j;
    for (i=0; i<m->nb_columns; i++)
    {
        for (j=0; j<m->nb_rows; j++)
        {
            if (getElt(m,i,j) != getElt(m,j,i)) return false;
        }
    }
    return true;
}


/**
 * \fn bool isSquare(Matrix *m)
 * \brief fonction verifiant si la matrice est carre
 * \param m pointeur sur la matrice
 * \return true si elle est carre false sinon
 */
bool isSquare(Matrix *m)
{
    if (m->nb_rows == m->nb_columns) return true;
    else return false;
}


/**
 * \fn bool isTriangular(Matrix *m)
 * \brief fonction verifiant si la matrice est triangulaire
 * \param m pointeur sur la matrice
 * \return true si elle est triangulaier false sinon
 */
bool isTriangular(Matrix *m)
{
    if(!isSquare(m))
        return false;
    else
    {
        bool res = true;
        int i,j;
        for(i=0; i<m->nb_rows; i++)
            for(j=i+1; j<m->nb_columns; j++)
                if(getElt(m,i,j)!=0)
                    res = false;
        if(res==false)
        {
            res = true;
            for(i=0; i<m->nb_rows; i++)
                for(j=0; j<i; j++)
                    if(getElt(m,i,j)!=0)
                        res = false;
        }
        return res;
    }
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
 * \fn Matrix comatrice(Matrix *m, int no_row, int no_column)
 * \brief creer la comatrice a partie de la matrice donné
 * et de coordonnées du cofacteur
 * \a m pointeur sur la matrice
 * \a no_row no de la ligne du cofatceur
 * \a no_column no de la colonne du cofacteur
 * \return comatrice
 * \post creer une matrice => utilisation de free
 */
Matrix comatrice(Matrix *m, int no_row, int no_column)
{
    Matrix comatrice = newMatrix(m->nb_rows-1,m->nb_columns-1);
    int im,ic;
    int jm,jc;
    for(jm=0,jc=0;jm<m->nb_rows && jc<comatrice.nb_rows;jm++,jc++)
    {
        if(jm==no_row && jm<m->nb_rows-1)
            jm++;
        for(im=0,ic=0;im<m->nb_columns && ic<comatrice.nb_columns;im++,ic++)
        {
            if(im==no_column && im<m->nb_columns-1)
                im++;
            setElt(&comatrice,jc,ic,getElt(m,jm,im));
        }
    }
    return comatrice;
}


/**
 * \fn Elt rec_det(Matrix *m, int no_row, int no_column)
 * \brief calcul le determinant de la comatrice de m
 * en enlevant la ligne no_row et la colonne no_column
 * usage interne a calcul_determinant_recursif()
 * \a m pointeur sur la matrice
 * \a no_row no de la ligne a enlever
 * \a no_column no de la colonne a enlever
 * \return det de la comatrice
 */
Elt rec_det(Matrix *m, int no_row, int no_column)
{
    Elt det=0;
    int i,coef;
    Matrix m1 = comatrice(m,no_row,no_column);
    printMatrix(&m1);
    if(m1.nb_rows==2)
    {
        det=getElt(&m1,0,0)*getElt(&m1,1,1)-getElt(&m1,1,0)*getElt(&m1,0,1);
    }
    else
    {
        for(i=0;i<m1.nb_columns;i++)
        {
            if(i%2==0)
                coef=1;
            else
                coef=-1;
            det+=getElt(&m1,0,i)*rec_det(&m1,0,i)*coef;
        }
    }
    deleteM(&m1);
    return det;
}


/**
 * \fn Elt calcul_determinant_recursif(Matrix *m)
 * \brief fonction qui calcul le determinant d'une matrice par la methode
 * recursive
 * \a m pointeur sur la matrice
 * \return determinant de la matrice
 */
Elt calcul_determinant_recursif(Matrix *m)
{
    Elt det=0;
    int i,coef;
    if(m->nb_rows==1)
        det=getElt(m,0,0);
    else if(m->nb_rows==2)
    {
        det=getElt(m,0,0)*getElt(m,1,1)-getElt(m,1,0)*getElt(m,0,1);
    }
    else
    {
        for(i=0;i<m->nb_columns;i++)
        {
            if(i%2==0)
                coef=1;
            else
                coef=-1;
            det+=getElt(m,0,i)*rec_det(m,0,i)*coef;
        }
    }
    return det;
}


/**
 * \fn Elt calcul_determinant_triangulaire(Matrix *m)
 * \brief fonction qui calcule le determinant d'une matrice
 * triangulaire
 * \a m pointeur sur la matrice
 * \return determinant de la matrice
 * \pre la matrice doit etre triangulaire
 */
Elt calcul_determinant_triangulaire(Matrix *m)
{
    Elt det=1;
    int i;
    for(i=0;i<m->nb_rows;i++)
    {
        det *= getElt(m,i,i);
    }
    return det;
}


/**
 * \brief fonction qui fait la soustraction d'une ligne par la
 * ligne du pivot de gauss pour enlever l'element en tête
 */
void soustraction_gauss_inverse(Matrix *tmp_old,Matrix *old,Matrix *tmp_new,
        Matrix *new,int ligne_pivot,int colonne_pivot,int j)
{
    int i;
    for(i=colonne_pivot;i<tmp_old->nb_columns;i++)
    {

        //augmentedmatrix[i][k]= abs((int) (augmentedmatrix[i][k] - (augmentedmatrix[j][k]/augmentedmatrix[j][j])*r) % 2);
        int val = abs((int) (getElt(tmp_old,j,i)- getElt(tmp_old,ligne_pivot,i)*getElt(tmp_old,j,colonne_pivot))   %2);
        setElt(old,j,i,val);
    }
    for(i=0;i<tmp_new->nb_columns;i++)
    {
        int val =abs ((int) (getElt(tmp_new,j,i)-getElt(tmp_new,ligne_pivot,i)*getElt(tmp_old,j,colonne_pivot))%2);
        setElt(new,j,i,val);
    }
}


/**
 * \brief fonction qui divise la ligne du pivot par sa tête
 * pour obtenir un pivot égale à 1
 */
void reduire_pivot_inverse(Matrix *old,Matrix *new,Elt val_pivot,int ligne_pivot)
{
    int i;
    for(i=0;i<old->nb_columns;i++)
    {
        setElt(old,ligne_pivot,i,getElt(old,ligne_pivot,i)/val_pivot);
    }
    for(i=0;i<new->nb_columns;i++)
    {
        setElt(new,ligne_pivot,i,getElt(new,ligne_pivot,i)/val_pivot);
    }
}


/**
 * \brief fonction qui inverse deux lignes dans une matrice
 */
void echanger_ligne(Matrix *m,int ligne1, int ligne2)
{
    Elt copie_ligne1[m->nb_columns];
    int i;
    for(i=0;i<m->nb_columns;i++)
    {
        copie_ligne1[i]=getElt(m,ligne1,i);
    }
    for(i=0;i<m->nb_columns;i++)
    {
        setElt(m,ligne1,i,getElt(m,ligne2,i));
    }
    for(i=0;i<m->nb_columns;i++)
    {
        setElt(m,ligne2,i,copie_ligne1[i]);
    }
}


/**
 * \fn Matrix matrice_inverse(Matrix *m)
 * \brief fonction qui calcule l'inverse d'une matrice
 * \a m pointeur sur la matrice
 * \return nouvelle matrice
 */
Matrix matrice_inverse_gauss(Matrix *m)
{
    Matrix old = copier_matrice(m);
    Matrix new = newMatrix(old.nb_rows,old.nb_columns);
    Matrix tmp_old,tmp_new;
    int i,j;
    bool pivot=false;
    Elt val_pivot;
    int ligne_pivot,colonne_pivot;
    for(i=0;i<new.nb_rows;i++)
        setElt(&new,i,i,1);
    for(i=0;i<old.nb_columns;i++)
    {
        pivot=false;
        colonne_pivot=i;
        for(j=i;j<old.nb_rows && pivot==false;j++)
        {
            if(getElt(&old,i,j)!=0)
            {
                pivot=true;
                val_pivot=getElt(&old,i,j);
                ligne_pivot=j;
            }
        }
        if(!pivot)
        {
            fprintf(stderr,"la matice n'est pas inversible\n");
            new.valide=false;
            return new;
        }
        else
        {
            reduire_pivot_inverse(&old,&new,val_pivot,ligne_pivot);
            echanger_ligne(&old,ligne_pivot,colonne_pivot);
            echanger_ligne(&new,ligne_pivot,colonne_pivot);
            ligne_pivot=colonne_pivot;
            tmp_old = copier_matrice(&old);
            tmp_new = copier_matrice(&new);
            for(j=0;j<old.nb_rows;j++)
            {
                if(j!=ligne_pivot)
                {
                    soustraction_gauss_inverse(&tmp_old,&old,
                            &tmp_new,&new,ligne_pivot,colonne_pivot,j);
                }
            }
            deleteM(&tmp_old);
            deleteM(&tmp_new);
        }
    }
    deleteM(&old);
    return new;
}


/**
 * \brief fonction calculant la matrice des cofacteur d'une matrice donnée
 */
Matrix coFacteurM(Matrix *a)
{
    int i,j;
    int signe;
    Matrix new = newMatrix(a->nb_rows,a->nb_columns);
    Matrix co;
    for(i=0;i<a->nb_rows;i++)
    {
        for(j=0;j<a->nb_columns;j++)
        {
            if((i+j)%2==0)
                signe = 1;
            else
                signe =-1;
            co = comatrice(a,i,j);
            setElt(&new,i,j,signe*calcul_determinant_recursif(&co));
            deleteM(&co);
        }
    }
    return new;
}

/*
 * \brief fonction calculant la matice inverse de la matrice
 * donnée, avec la methode des cofacteurs
 */
Matrix matrice_inverse_cofacteur(Matrix *m)
{
    Matrix new;
    Elt det = calcul_determinant_recursif(m);
    if(det>-0.01 && det<0.01)
    {
        printf("la matrice n'est pas inversible");
        new.valide=false;
        return new;
    }
    else
    {
        new = coFacteurM(m);
        printMatrix(&new);
        new= transpose(&new);
        printMatrix(&new);
        new = mult_scalar(1/det,&new);
        printMatrix(&new);
        return new;
    }
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

Matrix Permutation_cols(Matrix *m)
{
  int i,j;
  Matrix m2 = newMatrix( m->nb_rows, m->nb_rows);
  int v=0;
  for (i=m->nb_columns-1; i>=-1; i--)
  {
    for(j=0; j<m->nb_rows; j++)
    {
            if(i==-1)
                  setElt(&m2,v,j,getElt(m,j,m->nb_columns-1));
            else
                setElt(&m2,v,j,getElt(m,j,i));
    }
    v++;

  }
  return m2;

}
