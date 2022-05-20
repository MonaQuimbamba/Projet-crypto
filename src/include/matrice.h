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
Matrix newMatrix(int nb_rows, int nb_columns);
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
Elt getElt(Matrix *m, int row, int column);

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
void setElt(Matrix *m, int row, int column, Elt val);
/**
 * \fn void deleteM(Matrix *m)
 * \brief fonction liberant l'espace mémoire alloué pour
 * la matrice donnée
 * \param m pointeur sur la matrice a liberer
 * \return void
 */
void deleteM(Matrix *m);
/**
 * \fn void prinMatrix(Marix *m)
 * \brief fonction qui affiche la matrice donnée
 * \param m pointeur sur la matrice a afficher
 * \return void
 */
void printMatrix(Matrix *m);
/**
 * \fn Matrix transpose(Matrix *m)
 * \brief fonction calculant la trans pose d'une matrice
 * \param m matrice de depart
 * \return transpose de la matrice donnee
 * \post creation d'une nouvelle matrice
 * necessite l'utilisation de deleteM(Matrix *)
 */
Matrix transpose(Matrix *m);
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
Matrix addition(Matrix *m1, Matrix *m2);

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
Matrix multiplication(Matrix *m1, Matrix *m2);
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
Matrix mult_scalar(Elt elt, Matrix *m);
/**
 * \brief fonction qui fait l'inversion d'une matrice , par le pivot de gauss
 * \return la matrice inverse  si cela est possible
 */
Matrix pivotGaus(Matrix *m);
/**
 * \brief fonction qui permet de faire la matrice (n-k)*(n-k) , à partir de la matrice H et e
 * \return la  matrice
 */
Matrix faire_U(int size_U,Matrix *h,Matrix *e,int w_erreur);
/**
 * \brief fonction qui calcule la distance de Hammmings
 * \return la distance de Hammming d'une matrice
 */
int poidHamming(Matrix *m);
/**
 * \brief fonction qui fait l'inversion d'une matrice , par le pivot de gauss
 * \return la matrice inverse  si cela est possible
 */
Matrix MatrixH(int nb_rows,int nb_columns);
int fillMatrixH(int nb_columns);
/**
 * \brief fonction qui permet de faire la concatenation de deux  matrice
 * \return la  matrice concatené
 */
Matrix concatenationMatrix(Matrix *u,Matrix *v);
/**
 * \brief fonction qui copie une matrice
 * \return une copie de la matrice
 */
Matrix copier_matrice(Matrix *m);

#endif
