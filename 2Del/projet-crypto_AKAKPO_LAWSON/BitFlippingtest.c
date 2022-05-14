#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define n 48
#define w_x 10
#define w_e 78
//#define T 26
#define minvalue 0.0005

/*int **x_y(int ** u , int ** v , int ** xy)
{
	for (int i = 0; i < n ; i++)
		for(int j= 0 ; j < n ; j++)
		{
			xy[i][j] = u[j][0];
		}
		for(int j= n ; j < 2*n ; j++)
		{
			xy[i][j] = v[j%n][0];
		}
  return 
}*/

int ** allocation (int **temp,int lig,int col)
{
    temp=(int **)malloc(lig*sizeof(int*));

    int row;

    for(row=0; row < lig; row++)
    {

        temp[row]=(int *)malloc(col*sizeof(int));
    }

    return temp;
}

float **allocationf (float **temp,int lig,int col)
{
    temp=(float **)malloc(lig*sizeof(float*));

    int row;

    for(row=0; row < lig; row++)
    {

        temp[row]=(float *)malloc(col*sizeof(float));
    }

    return temp;
}

int **rot(int **polynome)
{
	int **sortie;
	sortie = allocation(sortie,n,n);
	int k = 0;
	for (int i = 0 ; i < n ; i ++ )
	{
		k = k + 1 ;
		for(int j = 0 ; j < 2*n ; j ++ )
		{
			sortie[i][j] = polynome[0][k%n];
			k = k + 1 ;
		}
	}
	return sortie;
}
int **rots(int **polynome,int **sortie)
{
	int k = 0;
	for (int i = 0 ; i < n ; i ++ )
	{
		k = k + 1 ;
		for(int j = 0 ; j < 2*n ; j ++ )
		{
			sortie[i][j] = polynome[0][k%n];
			k = k + 1 ;
		}
	}
	return sortie;
}
void afficherMatrice(int **matrice,int t)
{
    int i,j;
    for(i=0;i<t;i++)
    {
        for(j=0;j<t;j++){
            printf("\t %5d",matrice[i][j]);
        }
        printf("\n");
    }
}
int **inversionDouble(int **matrice , float **augmentedmatrix ,int **matriceResult, int dimension)
{
    /*float **augmentedmatrix;
    augmentedmatrix = allocationf(augmentedmatrix,dimension,2*dimension );*/
    afficherMatrice(matrice,dimension);
    printf("\n");
    printf("\n");
    float temporary, r ;
    int i, j, k, temp; 

    for(i=0;i<dimension; i++)
        for(j=0; j< dimension; j++)
                augmentedmatrix[i][j]=matrice[i][j];
    for(i=0;i<dimension; i++)
        for(j=dimension; j<2*dimension; j++)
            if(i==j%dimension)
                augmentedmatrix[i][j]=1;
            else
                augmentedmatrix[i][j]=0;

 /* using gauss-jordan elimination */
    for(i=0; i<dimension; i++)
    {
        for(j=0; j<2*dimension; j++)
                printf("\t %4.1f",augmentedmatrix[i][j]) ;
                printf("\n");
    }
 //

    for(j=0; j<dimension; j++)
    {
      temp=j;
     /* finding maximum jth column element in last (dimension-j) rows */
      for(i=j+1; i<dimension; i++)
        if(augmentedmatrix[i][j]>augmentedmatrix[temp][j])
                            temp=i;
        if(fabs(augmentedmatrix[temp][j])<minvalue)
             {
                printf("\n Elements are too small to deal with !!!");
                //int **matriceResult;
                //matriceResult = allocation(matriceResult,dimension,dimension);
                matriceResult = NULL;
                return matriceResult;
                //exit(0);
                //goto end;
             }
     /* swapping row which has maximum jth column element */
      if(temp!=j)
                for(k=0; k<2*dimension; k++)
                {
                temporary=augmentedmatrix[j][k] ;
                augmentedmatrix[j][k]=augmentedmatrix[temp][k] ;
                augmentedmatrix[temp][k]=temporary ;
                }
    /* performing row operations to form required identity matrix out of the input matrix */
    //TRY{
      for(i=0; i<dimension; i++)
            if(i!=j)
            {
                r=augmentedmatrix[i][j];
                for(k=0; k<2*dimension; k++)
                {
                    if (augmentedmatrix[j][j] != 0)
                    {
                    	 augmentedmatrix[i][k] = abs((int) (augmentedmatrix[i][k] - (augmentedmatrix[j][k]/augmentedmatrix[j][j])*r) % 2) ;

                    }
                }
            }
            else
            {
                r=augmentedmatrix[i][j];
                for(k=0; k<2*dimension; k++)
                {
                    if (r !=0)
                    {
                    	augmentedmatrix[i][k] = abs((int)(augmentedmatrix[i][k]/r)%2);
                    }
                    
                }
            }
    }  
 /* Display augmented matrix */
    printf("\n La matrice augmentée obtenu après la methode de gauss-jordan : \n\n") ;

    for(i=0; i<dimension; i++)
    {
    for(j=0; j<2*dimension; j++)
    printf("\t %4.1f",augmentedmatrix[i][j]) ;
    printf("\t \n");
    }
 /* displaying inverse of the non-singular matrix */
    //int **matriceResult;
    //matriceResult = allocation(matriceResult,dimension,dimension);
    printf("\n\n\n La matrice inverse est : \n\n");
    
    for(i=0; i<dimension; i++)
    {
        for(j=dimension; j<2*dimension; j++)
        {
            matriceResult[i][j%dimension] = abs( (int)augmentedmatrix[i][j]%2);
            //matriceResult[i][j%dimension] = (int)abs(fmod(augmentedmatrix[i][j],2));
            printf("\t %4.1f",augmentedmatrix[i][j]);
        }
        printf("\t\n");
    }

    return matriceResult;
}

int **multiplication(int **matrice1 ,int  **matrice2 , int **matrice3 , int no , int m , int p)
 {
  int i , j , k ;

 for (i=0; i< no; i++)
     for (j=0; j<p; j++)
         {
         	printf("%d\n", j);
          matrice3[i][j]=0;
          exit(0);
          for (k=0; k< m; k++)			 			
               matrice3[i][j] += matrice1[i][k] * matrice2[k][j];
           matrice3[i][j] = abs(matrice3[i][j]%2);
         }
 return matrice3;
}

int **transposer(int **matrice , int **matrice_T , int ligne , int colonne)
{
	for(int i=0;i< ligne ;i++){
        for(int j=0;j< colonne ;j++){
             matrice_T[colonne][ligne]= matrice[ligne][colonne];
        }
    }

    return matrice_T ;
}

int poidHamming(int **matrice,int no ,int m)
{
    int poidHamming = 0 , i , j;

    for (i=0; i<no; i++)
        {
         for (j=0; j< m; j++)
              if (matrice[i][j] == 1)
              {
                poidHamming+=1;
              }
        }
        return poidHamming;
}

int ** generation_aleatoire(int we)
{
	int ** x ;
	int c ;
	x = allocation(x , 1, n);
	for (int i = 0 ; i < n ; i ++)
		x[0][i] = 0 ;
	for(int r=0;r<we;r++)
	{
		c = (rand() % (n));
		x[0][c] = 1;
    }
    int w = poidHamming(x,1,n);

    while(w < we)
	{
		c = (rand() % (n));
		x[0][c] = 1;
		w = poidHamming(x,1,n);
    }

    return x ; 
}



void afficherMatriceXY(int **matrice,int lig , int col)
{
    int i,j;
    for(i=0;i<lig;i++)
    {
        for(j=0;j<col;j++){
            //printf("%d",*(matrice+i*t+j));
            printf("\t %5d",matrice[i][j]);
        }
        printf("\n");
    }
}

int **bitFlipping(int **ho,int **h1,int **s,int T,int t)
{
	int **u ;
	int **v ;
	int **u_v;
	// variable u et v conformement a celui décrit dans l'algo
	u = allocation(u,1,n);
	v = allocation(v,1,n);
	// variable qui contient la concatenation de u et v
	u_v = allocation(u_v,1 , 2*n);
	// initialisation de u et v
	for (int i = 0 ; i < n ; i ++)
	{
		u[0][i] = 0;
		v[0][i] = 0;
	}
	// partie de la concacténation (u,v)
	for (int i = 0; i < 1 ; i++){
		for(int j= 0 ; j < n ; j++)
			{
				u_v[i][j] = u[0][j];
			}
			for(int j= n ; j < 2*n ; j++)
			{
				u_v[i][j] = v[0][j];
			}
		}
	
	//declaration de la matrice H comme dans l'algo
	int **H ;
	// allocation de H
	H = allocation(H,n,2*n);
	// variable dont nous allons nous servir pour avoir -ho
	int ** negative_ho;
	negative_ho = allocation(negative_ho, 1 , n );

	// calcul de -ho
	for(int i = 0 ; i < n ; i ++ )
		negative_ho[0][i] = -1 * ho[0][i];

	//Partage du calcul de h en composante pour pouvoir l'implémenter.
	// Calcul de composante 1 : on fait rot (- ho)
	int **composante_H_1 = rot(negative_ho);
	// Calcul de composante 1  On fait aussi rot(h1) affin de pouvoir multiplier les 2 matrices
	int **composante_H_2 = rot(h1);

	int **T_composante_H_1 ;
	int  **T_composante_H_2;
	T_composante_H_1 = allocation(T_composante_H_1, n ,n );
	T_composante_H_2 = allocation(T_composante_H_2, n ,n );

	// transposer des 2 composantes conformement à l'algo
	T_composante_H_1 = transposer(composante_H_1,T_composante_H_1 , n , n);
	T_composante_H_2 = transposer(composante_H_2, T_composante_H_2 , n , n);

// concaténation de H (rot(−h 0 ) , rot(h 1 )^T)
	for (int i = 0; i < n ; i++)
	{
		for(int j= 0 ; j < n ; j++)
		{
			H[i][j] = T_composante_H_1[j][0];
		}
		for(int j= n ; j < 2*n ; j++)
		{
			H[i][j] = T_composante_H_1[j%n][0];
		}
	}
		
// calcul du syndrome 
	int **syndrome ;
	syndrome = allocation(syndrome, 1 ,  n );

// allocation du syndrome avec S
	syndrome = s;
	int **sum;
	sum = allocation(sum,1,2*n);

// declaration de flipped_positions

	int **flipped_positions ;
	flipped_positions = allocation(flipped_positions , 1 , 2*n);
	int ** result ;
	result = allocation(result,1,2*n);

	while((poidHamming(u, 1 , n ) != t || poidHamming(v , 1, n) != t) & poidHamming(syndrome,1,n) != 0 )
	{
		
		sum = multiplication(syndrome,H,result,1,n,2*n);
		for (int i = 0 ; i < n ; i ++)
			flipped_positions[0][i] = 0;

		for(int i = 0; i < 2*n ; i++)
		{
			if (sum[0][i]>= T )
				{
					// XOR de flipped_positions avec 1 
					flipped_positions[0][i] = (flipped_positions[0][i] + 1)%2;

				}
		}
		// XOR de u_v et de flipped_positions
		for (int j = 0 ; j < 2*n ; j ++)
			u_v[0][j] = (u_v[0][j] + flipped_positions[0][j])%2;

		int **T_flipped_positions;

		T_flipped_positions = allocation(T_flipped_positions , 2*n , 1);
		T_flipped_positions = transposer(flipped_positions, T_flipped_positions , 1 , 2*n );
		int **resu ;
		resu = allocation(resu, n , 1);

		// multiplication de H et la Transposer de flipped_positions
		int **Hflipped_positions = multiplication(H , T_flipped_positions , resu , n , 2*n , 1 );
		
		// Soustraction du syndrome et de Hflipped_positions
		for (int j = 0 ; j < 2*n ; j ++)
			syndrome[0][j] = syndrome[0][j] - Hflipped_positions[j][0];

	}
	//  Les parties qui viennent on été decoupé en plusieurs parties pour donner le resultat voulu par l'algorithme.
	int ** T_u_v;

	T_u_v = allocation(T_u_v , 2*n , 1); 

	T_u_v = transposer(u_v , T_u_v , 1 , 2*n);

	int ** multiply ;

	multiply = allocation(multiply, n , 1);

	int **res;
	int **resume;
	resume = allocation(resume,1 , n);
	res = allocation(res , n , 1);

// multiplication entre H et Transpioser de u et v
	multiply = multiplication(H , T_u_v , res , n , 2*n , 1 );

	// soustration entre S et la partie précédente
	for (int j = 0 ; j < n ; j++ )
		resume[0][j] = s[0][j] - multiply[j][0];
	// a cette etape , on retourne le resultat.  
	if (resume != 0)
	{
		return NULL;
	}
	else
	{
		return u_v;
	}
	
}

/*int ** partage_h(int **ho, int **h1)
{	
	printf("\n");

	while(1)
	{
		afficherMatriceXY(ho,1,n);
		printf("matrice de ho \n");
		float **mat;
		mat = allocationf(mat,n,2*n);
		int **matrice_ho = rot(ho);
		int **inverse_matrice_ho = inversionDouble(matrice_ho,mat,n);
		if (inverse_matrice_ho != NULL)
			break;

	}

	

	afficherMatriceXY(h1,1,n);
	printf("matrice de h1 \n");
	int ** result;
	result = allocation(result, n , n );
	afficherMatrice(matrice_ho,n);
	printf("\n");
	printf("matrice_ho\n");
	int **matrice_h1 = rot(h1);

	int **h = multiplication(matrice_h1,inverse_matrice_ho,result , n , n , n);

	afficherMatrice(h,n);
// quand il n'ya pas d"inversion , regénerer 
	return h ;
}*/

int **partage_c1(int **h)
{

	///////////////////////////////////////////////////////////////////////////////////////////////
	
	int ** eo;
	int ** e1 ;
	int **res ;
	res = allocation(res , n ,n );
	eo = allocation(eo, 1 , n);
	e1 = allocation(e1,1,n);

	// generation aléatoire de e0 et e1 
	eo = generation_aleatoire(w_x);
	e1 = generation_aleatoire(w_x);

	//mettre e0 et e1 sous forme matricielle pour pouvoir faire la multiplication
	int **matrice_eo = rot(eo);
	int **matrice_e1 = rot(e1);
	
	int **he1 = multiplication(h , matrice_e1 , res , n , n ,n );

	int ** c1;

	// calcul de c1 
	c1 = allocation(c1 ,n , n );
	
	for(int i = 0; i < n ; i++)
		for(int j = 0; j < n ; j++)
			c1[i][j] = matrice_eo[i][j] + he1[i][j];

	return c1;

	///////////////////////////////////////////////////////////////////////////////////////////////

}

int **chiffrement(int **m, int **eo, int **e1)
{
	/*int ** eo;
	int ** e1 ;

	eo = allocation(eo, 1 , n);
	e1 = allocation(e1,1,n);

	eo = generation_aleatoire(w_x);
	e1 = generation_aleatoire(w_x);*/

	int ** co;
	co = allocation(co ,n , n );
	Hash_eo_e1 = Hash(eo,e1);
	for (int i = 0 ; i < n ; i++)
	{
		co = (m[0][i] + Hash_eo_e1)%2;
	}

	return co;
}

int **dechiffrement(int **c)
{
	int ** m;
	m = allocation(m ,n , n );
	int **Hash_eo_e1 = Hash(eo,e1);
	for(int i = 0 ; i < n ; i ++ )
	{
		m = (c[0][i] + Hash_eo_e1)%2;
	}

	return m;
}

int **getS(int **ho,int **c1)
{
 	int **s ;
	s = allocation(s , n , n );
	int **matrice_ho = rot(ho);
	s = multiplication(matrice_ho , c1 , s ,n,n,n);
	return s;
}

///////////////////////////////////////////////////
int  main(int argc, char const *argv[])
{
	clock_t start,end;
    double cpu_time_used;
    start=clock();
    srand(time(NULL));


///////////////////////////////////////////////////////////////////////////////////////////////
	int t =  7 ;
	int T = 6;
	int w = 10;
	int ** h1;
	int ** ho ;
	float **mat = NULL;
	//int **h ;
	//h = allocation(h , n , n );
	int **matrice_ho = NULL;
	int **matrice_result = NULL;
	matrice_result = allocation(matrice_result,n,n);
	int **result = NULL;
	result = allocation(result, n , n );
	int **inverse_matrice_ho = NULL;
	int **matrice_h1 = allocation(matrice_h1,n,n);
	h1 = allocation(h1,1,n);
	h1 = generation_aleatoire(w_x);
	
	mat = allocationf(mat,n,2*n);
	ho = allocation(ho,1,n);

	printf("\n");
	afficherMatriceXY(h1,1,n);
	printf("matrice de h1 \n");
	while(1)
	{
		
		ho = generation_aleatoire(w_x);
		afficherMatriceXY(ho,1,n);
		printf("matrice de ho \n");
		matrice_ho = rot(ho);
		inverse_matrice_ho = inversionDouble(matrice_ho,mat,matrice_result,n);
		if (inverse_matrice_ho != NULL)
			break;
	}
	afficherMatrice(inverse_matrice_ho,n);
	//exit(0);
	afficherMatrice(matrice_ho,n);
	printf("\n");
	printf("matrice_ho\n");
	matrice_h1 =rots(h1,matrice_h1);
	int **h = multiplication(matrice_h1,inverse_matrice_ho,result , n , n , n);
	afficherMatrice(h,n);

/////////////////////// Création de h1 et h0 //////////////////////////////////////////////////




/////////////////////////// Envoie du h ///////////////////////////////////////////////////////

//int **h = partage_h(ho,h1);

//////////////////////////////// Envoie de c1 /////////////////////////////////////////////////

int **c1 = partage_c1(h);

//////////////////////// recuperation de s /////////////////////////////////////////////////////

int **s = getS(ho,c1);
///////////////// S , c'est s sous forme polynomiale
int **S;
S[0] = s[0];
printf("\n");
printf("###############################################################################################\n");
afficherMatrice(s,n);
printf("Affichage de s \n" );
///////////////////////////////////////////////////////////////////////////////////////////////

int ** eoe1 = bitFlipping(ho,h1,S, t , w );

///////////////////////////////////////////////////////////////////////////////////////////////

	end=clock();
    cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
    printf("\t# Temps utilisé  pour l'éxécution est : %f #\n\n\n",cpu_time_used);    
    
	return 0;
}
