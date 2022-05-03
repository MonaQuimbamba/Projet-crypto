#include <stdio.h>
#include <math.h>
#define t 4









int matId[t][t];
int mat1[t][t] = {
  {1, 1, 0},
  {1, 0, 1},
  {0, 0, 0}};

/*{
                    {1, 0, 0, 1, 1, 1, 1, 1, 0, 0 },
                    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
                    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
                    {1, 1, 0, 0, 0, 1, 0, 1, 1, 0 },
                    {1, 1, 0, 1, 0, 0, 0, 1, 1, 0 },
                    {1, 0, 1, 0, 1, 1, 0, 1, 1 ,0 },
                    {1, 0, 1, 1, 0, 0, 0, 1, 0 ,0 },
                    {1, 1, 0, 1, 0, 0, 1, 0, 1 ,0 },
                    {1, 1, 1, 1, 1, 1, 1, 0, 1 ,0 },
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
                  };*/
int NewMat[t][2*t];


void afficherMatrice()
{
    int i,j;
    for (i=0;i<t;i++)
    {
        for (j=0;j<t;j++)
        {
            printf("%d  ",mat1[i][j]);
        }
        printf("\n" );
    }
}

void afficherMatriceIdentite()
{
    int i,j;
    for (i=0;i<t;i++)
    {
        for (j=0;j<t;j++)
        {
            printf("%d  ",matId[i][j]);
        }
        printf("\n" );
    }
}


void afficherMatriceInverse()
{
    int i,j;
    float elem;
    for (i=0;i<t;i++)
    {
        for (j=t;j<2*t;j++)
        {
            printf("%d  ",NewMat[i][j]);
        }
        printf("\n" );
    }
}










void creerMatriceId()
{
    int i,j;
    for (i=0;i<t;i++)
    {
        for (j=0;j<t;j++)
        {
            if (i==j)
            {
                matId[i][j] = 1;
            }
            else
            {
                matId[i][j] = 0;
            }
        }
    }
}


void definirNouvelleMatrice()
{
    int i,j;
    i=j=0;
    for (i=0;i<t;i++)
    {
        for (j=0;j<2*t;j++)
        {
            if (j<t)
            {
                NewMat[i][j] = mat1[i][j];
            }
            else
            {
                NewMat[i][j] = matId[i][j-t];
            }
        }
    }
}

int MethodeGauss()
{
    int inversible = 1;
    int k,i,colonne,colonnebis;
    float var,var1;
    k=0;
    while((inversible == 1)&&(k<t))
    {
            if (NewMat[k][k] != 0)
            {
                var = NewMat[k][k];
                for (colonne=0;colonne<2*t;colonne++)
                {
                    NewMat[k][colonne] = NewMat[k][colonne]/var;  //Normalisation de la ligne contenant l'élément diagonal
                }
                for (i=0;i<t;i++)
                {
                    if (i != k)
                    {
                        var1=NewMat[i][k];
                        for (colonnebis=0;colonnebis<2*t;colonnebis++)
                        {
                            NewMat[i][colonnebis] = NewMat[i][colonnebis] - NewMat[k][colonnebis]*var1;
                        }
                    }
                }
                k++;
            }
            else
            {
                inversible = 0;
            }
    }
    return inversible;
}

void modifierMatrice()
{
    creerMatriceId();
    definirNouvelleMatrice();
}

int main ()
{
    printf("debut\n" );
    afficherMatrice();
    modifierMatrice();
    if (MethodeGauss() == 1)
    {
        printf("Matrice inverse\n" );
        afficherMatriceInverse();
    }
    else
    {
        printf("La matrice n'est pas inversible\n" );
    }

    printf("tout c'est bien termine\n" );
    return 0;
}
