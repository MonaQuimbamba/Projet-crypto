/**
 * \file polynome.h
 */

#ifndef __POLYNOME__
#define __POLYNOME__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "matrice.h"

/**
 * \brief fonction qui permet de créer un polynôme , dans notre cas un polynôme est representé par un vecteur
 * \return lae vecteur  */
Matrix createPolynome(int degre,int w);
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
/**
 * \brief fonction qui permet de récuperer un polynôme d'une matrice  circulante, dans notre cas un polynôme est representé par un vecteur
 * \return le polynôme  */
Matrix getPolyFromCycleMatrix(Matrix *p);
#endif
