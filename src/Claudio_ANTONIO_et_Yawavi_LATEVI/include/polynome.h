/**
 * \file polynome.h
 */

#ifndef __POLYNOME__
#define __POLYNOME__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "matrice.h"





/***********************************************
 * Represents a polynomial
 ***********************************************/
typedef int32_t integer;
typedef struct polynomial
{
    int * poly;
    int degree;

} polynomial;

//typedef integer polynomial[MAX_DEGREE + 1];

/**
 * Represents a degree of a polynomial
 */
typedef unsigned int degree;

/**
 * \brief fonction qui permet de faire la rotation circulante d'un polynôme , dans notre cas un polynôme est representé par un vecteur
 * \return void   */
void rotate(int arr[], int n);
/**
 * \brief fonction qui permet de faire une matrice  circulante d'un polynôme , dans notre cas un polynôme est representé par un vecteur
 * \return matrice circulante    */
Matrix rot(Matrix *m);
/**
 * \brief fonction qui permet de faire la subtraction de deux  polynômes , dans notre cas un polynôme est representé par un vecteur
 * \return polynome resultatant de la sub    */
Matrix subraction_Polynome(Matrix *u,Matrix *v);
/**
 * \brief fonction qui permet de concatener deux  polynômes , dans notre cas un polynôme est representé par un vecteur
 * \return le polynôme après la conactenation   */
Matrix concatenationPoly(Matrix *u,Matrix *v);

Matrix copy_poly_to_matrice(polynomial *p);
/**
 * \brief fonction qui permet de récuperer un polynôme d'une matrice  circulante, dans notre cas un polynôme est representé par un vecteur
 * \return le polynôme  */
Matrix getPolyFromCycleMatrix(Matrix *p);
polynomial createPolynome(int degree,int weight_h);
void p_print(polynomial *polynome);
polynomial createMod(int dp);
void p_write(int *p, degree dp, FILE *file);
polynomial p_copy(polynomial *p);
integer p_lead(polynomial *p);
polynomial mp_div(polynomial *p,polynomial *d);
polynomial mp_add(polynomial *p,polynomial *q);
//degree mp_sub(const polynomial p, degree dp, const polynomial q, degree dq, polynomial r, int m);
polynomial mp_mul(polynomial *p,polynomial *q);
polynomial mp_sub(polynomial *p,polynomial *q);
polynomial mp_mod(polynomial *p,polynomial *d);
integer mod(int64_t a, int m);
integer mi_add(integer a, integer b, int m);
integer mi_sub(integer a, integer b, int m);
integer mi_mul(integer a, integer b, int m);
integer mi_inv(integer a, int m);
integer mi_div(integer a, integer b, int m);
integer extended_gcd_int(integer a, integer b, integer* u, integer* v);
integer print_extended_gcd_int(integer a, integer b, integer* u, integer* v);
int max(int a, int b);

#endif
