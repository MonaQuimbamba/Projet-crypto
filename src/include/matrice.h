/**
 * \file matrice.h
 */

#ifndef __MATRIX__
#define __MATRIX__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


#define maximum 1000
#define minvalue 0.0005

typedef int Elt;
typedef struct matrix
{
    Elt * mat;
    int nb_rows, nb_columns;
    bool valide;
} Matrix;


Matrix newMatrix(int nb_rows, int nb_columns);
Elt getElt(Matrix *m, int row, int column);
void setElt(Matrix *m, int row, int column, Elt val);
void deleteM(Matrix *m);
void printMatrix(Matrix *m);
Matrix transpose(Matrix *m);
Matrix addition(Matrix *m1, Matrix *m2);
Matrix multiplication(Matrix *m1, Matrix *m2);
Matrix mult_scalar(Elt elt, Matrix *m);
Matrix pivotGaus(Matrix *m);
Matrix startMatrix(int nb_rows,int nb_columns);
Matrix faire_U(int size_U,Matrix *h);
int poidHamming(Matrix *m);
bool verify_tab(int *tab,int val,int size_U);
Matrix MatrixH(int nb_rows,int nb_columns);
int fillMatrixH(int nb_columns);
Matrix concatenationMatrix(Matrix *u,Matrix *v);
Matrix copier_matrice(Matrix *m);

#endif
