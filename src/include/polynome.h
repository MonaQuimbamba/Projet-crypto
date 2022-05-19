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


Matrix createPolynome(int degre,int w);
void rotate(int arr[], int n);
Matrix rot(Matrix *m);
Matrix subraction_Polynome(Matrix *u,Matrix *v);
Matrix concatenationPoly(Matrix *u,Matrix *v);
Matrix getPolyFromCycleMatrix(Matrix *p);
#endif
