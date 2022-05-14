#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#define w_x 20
#define minvalue 0.0005

#define TRY do{ jmp_buf ex_buf; if( !setjmp(ex_buf) ){
#define CATCH } else {
#define ETRY } }while(0)
#define THROW longjmp(ex_buf, 1)



// Fonction qui retourne un entier aléatoire entre [min , max]
int random_val(int min,int max)
{

    int r;
    const unsigned int range=1+max-min;
    const unsigned int buckets=RAND_MAX/range;
    const unsigned int limit = buckets * range;


    do
    {
        r=rand();

    }while(r >= limit);

    return min + (r/buckets);

}
// Fonction qui permet la création de la matrice identité
int **allocation (int **temp,int lig,int col)
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
void createMatriceIdentite(int rows,int cols)
{
    int i,j;
    int *matrice=(int*)malloc(rows*cols*sizeof(int));

    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++){
            if(i==j){

                *(matrice+i*cols+j)=1;
            }
            else{
                *(matrice+i*cols+j)=0;
            }


        }
    }

}
// Fonction pour libérer la matrice de la mémoire ( pour éviter d'engorger ou saturer la mémoire)
void free_matrice(int **matrice,int Rows)
{
    int row;

    for(row=0;row<Rows;row++)
    {
        free(matrice[row]);

    }

    free(matrice);
}
// Fonction qui assure l'affichage d'une matrice
void afficherMatrice(int **matrice,int t)
{
    int i,j;
    for(i=0;i<t;i++)
    {
        for(j=0;j<t;j++){
            //printf("%d",*(matrice+i*t+j));
            printf("\t %5d",matrice[i][j]);
        }
        printf("\n");
    }
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
// Fonction de création d'une nouvelle matrice
void createNewMatrice(int **new_matrice,int** matrice1,int** matrice_iden,int t)
{
    int i,j;
    i=j=0;

    for(i=0;i<t;i++)
    {
        for(j=0;j<2*t;j++)
        {
            if(j<t)
            {
                new_matrice[i][j]=matrice1[i][j];

            }
            else{
                new_matrice[i][j]=matrice_iden[i][j-t];
            }
        }

    }
}
//multiplication retourne une valeur null
// reverifier les différentes valeurs et améliorer ca
int **multiplication(int **matrice1 ,int  **matrice2 , int **matrice3 , int n , int m , int p)
 {

  int i , j , k ;
   // Affectation du résultat de la multiplication à C
 for (i=0; i< n; i++)
     for (j=0; j<p; j++)
         {
          matrice3[i][j]=0;
          for (k=0; k< m; k++)
          {
            //result = allocation(result , n-k , 1);
            matrice3[i][j] += matrice1[i][k] * matrice2[k][j];
          }
           matrice3[i][j] = abs(matrice3[i][j]%2);
         }
 return matrice3;

}
int ** modulo (int **matrice, int row , int col)
{
    for(int i=0;i<row;i++){
        for(int j=0;j<col ;j++){
           matrice[i][j] = abs(matrice[i][j]%2) ;
        }
    }

    return matrice;
}
int **create_binary_matrice(int rows,int cols)
{
    int i,j;
    i=j=0;
    int **matrice=(int**)malloc(rows*cols*sizeof(int));

    printf("#####################");
    printf("\nSAISIE DES VALEURS DE LA MATRICE : \n");
    for(i=0;i<rows;i++)
        for(j=0;j<cols;j++)

            matrice[i][j] =rand() & 1;

    return matrice;
}
//NB : toujours s'assurer que la taille du tableau entrer en paramètre est 2*fois plus grand
// (conforme à l'ajout  de matrice identité )
int **inversionDouble(int **matrice , int dimension)
{

    float ** augmentedmatrix;
    augmentedmatrix = allocationf(augmentedmatrix,dimension,2*dimension );
    //afficherMatrice(matrice,dimension);
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
                int **matriceResult;
                matriceResult = allocation(matriceResult,dimension,dimension);
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
 /* displaying inverse of the non-singular matrix */

    printf("\n\n\n La matrice inverse est : \n\n");
    int **matriceResult;
    matriceResult = allocation(matriceResult,dimension,dimension);
    for(i=0; i<dimension; i++)
    {
        for(j=dimension; j<2*dimension; j++)
        {
            matriceResult[i][j%dimension] = abs( (int)augmentedmatrix[i][j]%2);

        }
        printf("\n");
    }

    return matriceResult;
}
int poidHamming(int **matrice,int n ,int m)
{
    int poidHamming = 0 , i , j;

    for (i=0; i<n; i++)
        {
         for (j=0; j< m; j++)
              if (matrice[i][j] == 1)
              {
                poidHamming+=1;
              }

        }
        return poidHamming;
}
void destroyArray(float** arr)
{
    free(*arr);
    free(arr);
}
int **creerMatriceIdentite(int rows,int cols)
{
    int i,j;
    //int **matrice=(int** )malloc(rows*cols*sizeof(int*));
    int **matrice ;
    matrice = allocation(matrice,rows,cols);

    for(i=0;i<rows;i++){
        for(j=0;j<cols;j++){

            if(i==j){

                matrice[i][j]=1;
            }
            else{
                matrice[i][j]=0;
            }
        }
    }
    return matrice;
}


int main(){

    clock_t start,end;
    double cpu_time_used;
    start=clock();
    srand(time(NULL));
    int n=400;
    int k=200;
    // Paramètres de la matrice H (matrice_H)

    // => row_H et col_H correspondent respectivement au nombre de lignes et de colonnes de la matrice H (matrice_H)

    /////////////////////////////////////////////////// Debut matrice_H //////////////////////////////////////////////////////////////

    // Création de notre matrice 2D H (elle porte le nom matrice_H)
    int **matrice_H;
    matrice_H = allocation(matrice_H , n-k , n);

    // Vérifier si  matrice_H n'est pas vide
    if(matrice_H==NULL)
    {
        printf("Out of Memory\n" );
        //fprintf(stderr,'Out of Memory\n');
        exit(0);
    }

        // Création de notre matrice binaire aléatoire de taille (row*col) .
        // avec row= n-k et col=n
        // matrice représente dans le cas de l'algorithme H (matrice H)

        //*matrice =(int*)malloc(sizeof(int )*row*col);

        // Affectation de valeurs binaires aléatoires à notre matrice H (matrice_H) pour la remplir
        // On a donc à la suite de cette opération notre matrice H de taille (row_H * col_H)
        // avec row_H et col_H défini un peu plus haut( row_H = n-k et col_H=n)

    for(int r=0;r< n-k;r++){
        for(int c=0;c< n;c++){
            matrice_H[r][c]=rand() & 1;
        }
    }
    printf("\n");
    printf("affichage de H juste après sa création \n");
    printf("\n");
    /////////////////////////////////////////////////// Fin matrice_H //////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////// Debut matrice_x //////////////////////////////////////////////////////////////
    // x est : (1,n)
    int **matrice_X ;
    matrice_X = allocation(matrice_X , 1 , n);
    // total1 sert à connaitre le nombre de 1 dans x
    int total1 = 0;
    // generation aléatoire de X avec un nombre de 1 égale au poids cherché
    for(int r=0;r<1;r++){
        for(int c=0;c< n ;c++){
            matrice_X[r][c]=rand() & 1;

            if (matrice_X[r][c] == 1 )
                total1 += 1;
        }
    }
    printf("\n");
    printf("\n");
    printf("affichage de X juste après sa création \n");
    printf("\n");
    int colonnes;
    int ajustement = 0;
    while (total1 < w_x)
    {
        // le nombre de x est inférieur au poids qu'on veut , on change certaine valeur pour avoir le nombre voulu
        // random entre [0 et n[
        ajustement = 0;
        printf("01\n");
        colonnes = rand()%(n) ;
        matrice_X[0][colonnes] = 1;
        printf("\n");
        printf("affichage de X juste après sa création \n");
        printf("\n");
        total1 = ajustement ;
    }

    while (total1 > w_x)
    {
        ajustement = 0;
        printf("02\n");
        // le nombre de x est superieur au poids qu'on veut , on change certaine valeur pour avoir le nombre voulu
        colonnes = rand()%(n);
        matrice_X[0][colonnes] = 0;
        printf("\n");
        printf("\n");
        printf("affichage de X juste après sa création \n");
        printf("\n");

        total1 = ajustement ;
    }
    /////////////////////////////////////////////////// Fin matrice_x //////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////// Debut transposé de matrice_x //////////////////////////////////////////////////////////////
    int **transpose_matrice_X ;
        transpose_matrice_X = allocation(transpose_matrice_X , n , 1);
    // matrice transposé
    for(int i=0;i< 1;i++){
        for(int j=0;j< n;j++){
             transpose_matrice_X[j][i]=matrice_X[i][j];
        }
    }
    /////////////////////////////////////////////////// Fin transposé de matrice_x //////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////// Debut Calcul de H' //////////////////////////////////////////////////////////////
     int **temp_H ;
    temp_H = allocation(temp_H,n,n-k);
    // matrice transposé
    for(int i=0;i<n-k;i++){
        for(int j=0;j<n ;j++){
             temp_H[j][i]=matrice_H[i][j];
        }
    }
    printf("\n");
    printf("\n");
    printf("affichage de la matrice H \n");
    printf("\n");
    printf("\n");
    printf("affichage de la transposé de H \n");
    printf("\n");
    do{
        int ** temp_A;
        temp_A = allocation(temp_A,n-k,n-k);
        int rand_col=0;
        for(int p=0;p<n-k;p++)
        {
            rand_col = (rand() % (n ));
            temp_A[p]=temp_H[rand_col];

        }
        printf("\n");
        printf("Affichage du H (colonnes , lignes) \n");
        printf("\n");
        int ** extrait_H;
        extrait_H = allocation(extrait_H,n-k,n-k);
        // matrice transposé
        for(int i=0;i<(n-k);i++){
            for(int j=0;j<(n-k);j++){
                 extrait_H[j][i]=temp_A[i][j];
            }
        }
        printf("\n");
        printf("Affichage du H (lignes, colonnes) \n");
        /////////////////////////////////////////////////// Fin Calcul de H' //////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////// Debut Calcul de S //////////////////////////////////////////////////////////////
        int ** inter ;
        inter = allocation(inter , n-k , 1 );
        int ** S ;
        inter = allocation(S , n-k , 1 );
         S = multiplication(extrait_H , transpose_matrice_X, inter , n-k , n-k , 1);

        //afficherMatriceXY(S,n-k,1);
        printf("\n");
        printf("Affichage de S \n");
        printf("\n");
        /////////////////////////////////////////////////// Fin Calcul de S //////////////////////////////////////////////////////////////

        /////////////////////////////////////////////////// Debut Calcul de H'^-1 //////////////////////////////////////////////////////////////

        int ** invers_H ;
        invers_H = allocation(invers_H,n-k,n-k);
        //invers_H doit doubler de taille normalement : n-k et 2(n-k)
        invers_H = inversionDouble(extrait_H,n-k);

        if (invers_H == NULL)
        {
            continue ;
        }
        else {
                /////////////////////////////////////////////////// Fin Calcul de H'^-1 //////////////////////////////////////////////////////////////
                /////////////////////////////////////////////////// Debut Calcul de X' //////////////////////////////////////////////////////////////
                //afficherMatrice(invers_H,n-k);
                printf("Affichage de l'inversion \n");
                int matSize = n-k;
                int ** result;
                result = allocation(result , n-k , 1);
                // multiplication entre H' et S
                int ** extrait_X = multiplication(invers_H , S ,result,matSize,matSize,1);
                printf("\n");
                printf("\n");
                //afficherMatriceXY(extrait_X,matSize,1);
                printf("Affichage de x' \n");
                /////////////////////////////////////////////////// Fin Calcul de X' //////////////////////////////////////////////////////////////
                /////////////////////////////////////////////////// Debut Calcul du poid de X et comparaison //////////////////////////////////////////////////////////////
                int w_x_derive = poidHamming(extrait_X,n-k,1);
                if (w_x_derive == w_x)
                {
                    printf("bingo\n");
                    break;
                }
            }

    }
    while(1);
    /////////////////////////////////////////////////// Fin Calcul du poid de X et comparaison //////////////////////////////////////////////////////////////
    end=clock();
    cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
    printf("\t# Temps utilisé  pour l'éxécution est : %f #\n\n\n",cpu_time_used);
    // Pour libérer l'espace mémoire qui contient la matrice
    free(matrice_H);

    return 0;
}
