#include <math.h>
#include <stdio.h>
#define taille 3



void print_mat(int n , int *aorig)
{
	 int i,j;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			printf("%8.1d", aorig[j+i*n]);
		}
		printf("\n");
	}
}
int gjinv (int *a, int n, int *b)
{
	int i, j, k, p;
	int f, g, tol;
	if (n < 1) return -1;  /* Function Body */
	f = 0;  /* Frobenius norm of a */
	for (i = 0; i < n; ++i)
  {
		for (j = 0; j < n; ++j)
    {
			g = a[j+i*n];
			f += g * g;
		}
	}

	printf(" g %d et f  %d\n",g,f);
	f = sqrt(f);
	tol = f * 2.2204460492503131e-016;

	printf(" g %d et f %d tol %d\n",g,f,tol);
	for (i = 0; i < n; ++i)
  {  /* Set b to identity matrix. */
		for (j = 0; j < n; ++j)
		{
			b[j+i*n] = (i == j) ? 1. : 0.;
		}
	}
	printf(" matric identidade \n");
	print_mat(n,b);
	printf("\n");

	// Gaus jordan
	for (k = 0; k < n; ++k) /* Main loop */
	{
						f = a[k+k*n];  /* Find pivot. */
						p = k;
						for (i = k+1; i < n; ++i)
						{
										g = a[k+i*n];
										if (g > f)
										{
											f = g;
											p = i;
										}
						}

						if (f < tol) return 1;  /* Matrix is singular. */


						if (p != k)
						{  /* Swap rows. */
							for (j = k; j < n; ++j)
							{
								f = a[j+k*n];
								a[j+k*n] = a[j+p*n];
								a[j+p*n] = f;
							}
							for (j = 0; j < n; ++j)
							{
								f = b[j+k*n];
								b[j+k*n] = b[j+p*n];
								b[j+p*n] = f;
							}
						}

						f = 1. / a[k+k*n];  /* Scale row so pivot is 1. */
						for (j = k; j < n; ++j) a[j+k*n] =(a[j+k*n]* f)%2;
						for (j = 0; j < n; ++j) b[j+k*n] =(b[j+k*n]* f)%2;

						for (i = 0; i < n; ++i) /* Subtract to get zeros. */
						{
							if (i == k) continue;
							f = a[k+i*n];
							for (j = k; j < n; ++j) a[j+i*n] = ((a[j+i*n])-(a[j+k*n] * f))%2;
							for (j = 0; j < n; ++j) b[j+i*n] =((b[j+i*n]) - (b[j+k*n] * f))%2;
						}
	}
	return 0;
}


int main (void)
{
	static int aorig[taille*taille] = {1,1,1,1,0,1,1,1,1};
	int a[taille*taille], b[taille*taille], c[taille*taille];
	int n = taille;
	int i, j, k, ierr;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			a[j+i*n] = aorig[j+i*n];
		}
	}
	ierr = gjinv (a, n, b);
	printf("gjinv returns #%i\n\n", ierr);
	printf("matrix:\n");
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			printf("%8.1d", aorig[j+i*n]);
		}
		printf("\n");
	}
	printf("\ninverse:\n");
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			printf("%8.1d", b[j+i*n]);
		}
		printf("\n");
	}

	/*
	for (j = 0; j < n; ++j) {
		for (k = 0; k < n; ++k) {
			c[k+j*n] = 0.;
			for (i = 0; i < n; ++i) {
				c[k+j*n] += aorig[i+j*n] * b[k+i*n];
			}
		}
	}
	printf("\nmatrix @ inverse:\n");
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			printf("%8.1d", c[j+i*n]);
		}
		printf("\n");
	}
	ierr = gjinv (b, n, a);
	printf("\ngjinv returns #%i\n", ierr);
	printf("\ninverse of inverse:\n");
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			printf("%8.1d", a[j+i*n]);
		}
		printf("\n");
	}*/
	return 0;
}
