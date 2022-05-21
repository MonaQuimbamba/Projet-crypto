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
	//int k = 0;
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
polynomial createPolynome(int degree,int weight_h)
{
	polynomial res;
	res.poly = (int *) malloc(sizeof(int)*degree);
	res.degree= degree;
    unsigned int i;
   for (i = 0; i <= degree; i++)
	  if (i==degree) res.poly[i]=  1;
		else res.poly[i]=  0;

		int64_t elt;
    i =0;
    while(i < weight_h){
       elt = randombytes_uniform(degree);
       if( res.poly[elt]!=1){
         res.poly[elt]= 1;
         i++;
       }
    }

    return res;
}
polynomial createMod(int dp)
{
	polynomial res;
	res.poly = (int *) malloc(sizeof(int)*dp);
	res.degree= dp;

	for (int i = 0; i <= dp; i++)
			if(i==dp || i==0 ) res.poly[i]= 1;
			else res.poly[i]=0;
	return res;

}
int max(int a, int b)
{
    return a < b ? b : a;
}
void p_print(polynomial *polynome)
{
	 int *p = polynome->poly;
	 int dp = polynome->degree;
   p_write(p, dp, stdout);
   printf("\n");
}
void p_write(int *p, degree dp, FILE *file)
{
    int i;
    integer v;
    if (dp == 0)
    {
        fprintf(file, " %d", p[0]);
        return;
    }
    for (i = dp; i >= 0; i--)
    {
        if (p[i] == 0)
        {
            continue;
        }
        if (p[i] < 0)
        {
            v = -p[i];
            fprintf(file, " -");
        }
        else
        {
            v = p[i];
            if (i != dp)
            {
                fprintf(file, " +");
            }
        }
        if (v != 1 || i == 0)
        {
            fprintf(file, " %d", v);
        }
        if (i > 1)
        {
            fprintf(file, " X^%d", i);
        }
        else if (i == 1)
        {
            fprintf(file, " X");
        }
    }
}
polynomial p_copy(polynomial *p)
{

	polynomial res;
	int dp = p->degree;
	res.poly = (int *) malloc(sizeof(int)*dp);
	assert(res.poly != NULL);
	res.degree= dp;
  for (int i = 0; i <= dp; i++)
          res.poly[i] = p->poly[i];

    return res;
}
integer p_lead(polynomial *p)
{
    return p->poly[p->degree];
}
polynomial mp_add(polynomial *p,polynomial *q)
{
	unsigned int i;

	int dp = p->degree;
	int dq = q->degree;

	polynomial r;

	int m=2;

	/* Calculate polynomial r */
	if (dp < dq)
	{
			r.poly = (int *) malloc(sizeof(int)*dq);

			for (i = 0; i <= dp; i++)
			{
					r.poly[i] = mi_add(p->poly[i], q->poly[i], m);
			}
			for (i = dp + 1; i <= dq; i++)
			{
					r.poly[i] = mod(q->poly[i], m);
			}
	}
	else
	{
		r.poly = (int *) malloc(sizeof(int)*dp);
			for (i = 0; i <= dq; i++)
			{
					r.poly[i] = mi_add(p->poly[i], q->poly[i], m);
			}
			for (i = dq + 1; i <= dp; i++)
			{
					r.poly[i] = mod(p->poly[i], m);
			}
	}

	/* Calculate degree dr */
	for (i = max(dp, dq); i > 0; i--)
	{
			if (r.poly[i] != 0)
			{
					r.degree =i;
					return r;
			}
	}
	r.degree=0;
	return r;
}
polynomial mp_sub(polynomial *p,polynomial *q)
{
    unsigned int i;
		int m=2;
    int dp = p->degree;
		int dq= q->degree;
		polynomial r;

    if (dp < dq)
    {
				r.poly = (int *) malloc(sizeof(int)*dp);
        for (i = 0; i <= dp; i++)
        {
            r.poly[i] = mi_sub(p->poly[i], q->poly[i], m);
        }
        for (i = dp + 1; i <= dq; i++)
        {
            r.poly[i] = mod(-1* (q->poly[i]), m);
        }
    }
    else
    {
				r.poly = (int *) malloc(sizeof(int)*dq);
        for (i = 0; i <= dq; i++)
        {
            r.poly[i] = mi_sub(p->poly[i], q->poly[i], m);
        }
        for (i = dq + 1; i <= dp; i++)
        {
            r.poly[i] = mod(p->poly[i], m);
        }
    }

    for (i = max(dp, dq); i > 0; i--)
    {
        if (r.poly[i] != 0)
        {
						r.degree=i;
            return r;
        }
    }
			r.degree=0;
    return r;
}
Matrix copy_poly_to_matrice(polynomial *p)
{
				Matrix res = newMatrix(p->degree,1);
				for(int i=0 ; i <=res.nb_rows;i++) setElt(&res,0,i,p->poly[i]);
				return res;
}
/*
degree mp_mul(const polynomial p, degree dp, const polynomial q, degree dq, polynomial r, int m)
{
    unsigned int i, j;


    degree dr = dp + dq;
    if (dr > MAX_DEGREE)
    {
        fprintf(stderr,
                "Mod Error: max degree for polynomials is %d (%d is too big). Exit.\n", MAX_DEGREE, dr);
        exit(EXIT_FAILURE);
    }


    for (i = 0; i <= dr; i++)
    {
        r[i] = 0;
    }

    for (i = 0; i <= dp; i++)
    {
        for (j = 0; j <= dq; j++)
        {
            r[i + j] = mi_add(r[i + j], mi_mul(p[i], q[j], m), m);
        }
    }
    return dr;
}

*/
polynomial mp_div(polynomial *p,polynomial *d)
{
    int i, j;
    integer t;
		polynomial r;
		int dp = p->degree;
		r.poly = (int *) malloc(sizeof(int)*dp);
		r.degree= dp;
		polynomial q;
		q.poly = (int *) malloc(sizeof(int)*dp);
    int dd = d->degree;
		int m =2;
    int dq = dp - dd;
    if (dq < 0)
    {
        q.poly[0] = 0;
					q.degree= 0;
        return q;
    }
     r =p_copy(p);

    for (i = dp; i >= (int)dd; i--)
    {
        q.poly[i - dd] = t = mi_div(r.poly[i], d->poly[dd], m);
        r.poly[i] = 0;

        for (j = 0; j < dd; j++)
        {
            r.poly[i - dd + j] = mod(r.poly[i - dd + j] - d->poly[j] * t, m);
        }
    }

		q.degree= dq;
    return q;
}

polynomial mp_mod(polynomial *p,polynomial *d)
{
    int i, j, t, dr;
		int m = 2;

		polynomial r;
		int dp = p->degree;
    // Init remainder r
		int dd = d->degree;
    r = p_copy(p);
    dr = r.degree;
    for (i = dp; i >= dd; i--)
    {
        t = mi_div(r.poly[i], d->poly[dd], m);
        r.poly[i] = 0;

        for (j = 0; j < dd; j++)
        {
            r.poly[i - dd + j] = mod(r.poly[i - dd + j] - d->poly[j] * t, m);
        }
    }
    // Calculate degree dr
    for (i = dr; i > 0; i--)
    {
        if (r.poly[i] != 0)
        {
					  r.degree=i;
            return r;
        }
    }
		r.degree=0;
    return r;
}

integer mod(int64_t a, int m)
{
    integer r = a % m;
    return r < 0 ? r + m : r;
}

integer mi_add(integer a, integer b, int m)
{
    return mod(a + b, m);
}

integer mi_sub(integer a, integer b, int m)
{
    return mod(a - b, m);
}

integer mi_mul(integer a, integer b, int m)
{
    return mod(a * b, m);
}
integer mi_inv(integer a, int m)
{
    integer r, u, v;
    r = extended_gcd_int(m, a, &u, &v);
    if (r != 1)
    {
        fprintf(stderr,
                "Mod Error: %d has no inverse modulo %d. Exit.\n", a, m);
        exit(EXIT_FAILURE);
    }
    return mod(v, m);
}
integer mi_div(integer a, integer b, int m)
{
    return mi_mul(a, mi_inv(b, m), m);
}
integer extended_gcd_int(integer a, integer b, integer* u, integer* v)
{
    integer r, rp, up, vp, rs, us, vs, q;
    r = a; *u = 1; *v = 0;
    rp = b; up = 0; vp = 1;
    while (rp != 0)
    {
        q = r / rp;
        rs = r - q * rp;
        r = rp;
        rp = rs;
        us = *u - q * up;
        *u = up;
        up = us;
        vs = *v - q * vp;
        *v = vp;
        vp = vs;
    }
    return r;
}

integer print_extended_gcd_int(integer a, integer b, integer* u, integer* v)
{
    integer r, rp, up, vp, rs, us, vs, q;
    int i = 0;
    r = a; *u = 1; *v = 0;
    rp = b; up = 0; vp = 1;
    while (rp != 0)
    {
        printf("== Iteration %d ==\n", i++);
        printf("(r, u, v) = (%d, %d, %d)\n", r, *u, *v);
        q = r / rp;
        rs = r - q * rp;
        r = rp;
        rp = rs;
        us = *u - q * up;
        *u = up;
        up = us;
        vs = *v - q * vp;
        *v = vp;
        vp = vs;
    }
    printf("== Result ==\n");
    printf("(r, u, v) = (%d, %d, %d)\n", r, *u, *v);
    return r;
}
