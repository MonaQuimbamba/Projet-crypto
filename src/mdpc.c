#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <setjmp.h>
#include <string.h>
#include <sys/random.h>
#include "include/matrice.h"
#include "include/polynome.h"
#include "include/md5.h"

#include "LATEST/libsodium-stable/src/libsodium/include/sodium.h"

#define T 5



int sumPoidsCols(Matrix *m,int nbcol)
{
	 int sum=0;
	 for(int i = 0 ; i < m->nb_rows; i++) sum+=getElt(m,i,nbcol);
	 return sum;
}


void updateU_V(Matrix *u,Matrix *v, Matrix *m)
{
		int i,j;
		int k;
		for (i=0; i<u->nb_columns; i++)
		{
			k=0;
			for (j=0; j<u->nb_rows*2; j++)
			{
					if(j<u->nb_rows) setElt(u,i,j,(getElt(u,i,j)+getElt(m,i,j))%2);
					else {
						 setElt(v,i,k,(getElt(v,i,k)+getElt(m,i,j))%2);
					k++;
				}
			}
		}

}



Matrix bitFlipping(Matrix *ho, Matrix *h1,Matrix *s,int weight_h)
{
		int n = s->nb_rows;
		Matrix u = newMatrix(n,1);
		Matrix v = newMatrix(n,1);
    Matrix u_v = newMatrix(n*2,1);
		u_v.valide=false;
    Matrix rot_h1 = rot(h1);
    Matrix h_neg = mult_scalar(-1,ho);
    Matrix rot_ho_neg = rot(&h_neg);
    Matrix trans_rot_ho=transpose(&rot_ho_neg);
    Matrix trans_rot_h1=transpose(&rot_h1);
    Matrix H = concatenationMatrix(&trans_rot_ho,&trans_rot_h1);
    Matrix syndrome= transpose(s);
		Matrix flipped_positions ;
		Matrix sum =newMatrix(1,2*n);
		Elt elt;
		//printf("\nmatrice H est  [%d][%d] =\n", H.nb_rows, H.nb_columns);
		//printMatrix(&H);
		//printf(" le syndrome est \n");
		//printMatrix(&syndrome);
	  while( (poidHamming(&u)!=weight_h || poidHamming(&v)!=weight_h) & (poidHamming(&syndrome) !=0))
		{


				printf(" ||u||  %d  et || v || %d  et weight_h %d et syndrome poids %d \n",poidHamming(&u),poidHamming(&v) ,weight_h,poidHamming(&syndrome));
				for (int i = 0 ; i < n*2 ; i++) {
            for (int j = 0 ; j < n ; j++)
						{
							elt = getElt(&syndrome,0,j) * getElt(&H,j,i);
							setElt(&sum,0,i,getElt(&sum,0,i) + elt);
            }

        }

			//	printf("\nmatrice sum la matrice creuse  est  [%d][%d] =\n", sum.nb_rows, sum.nb_columns);
			//	printMatrix(&sum);
			  flipped_positions =  newMatrix(1,2*n);
				for(int i =0 ; i < 2*n ; i++) {
						if(getElt(&sum,0,i)>=T)
							setElt(&flipped_positions,0,i,getElt(&flipped_positions,0,i)+1);
				}

				//printf(" le flipped_positions est \n");
				//printMatrix(&flipped_positions);
				u_v= transpose(&u_v);
				u_v = addition(&u_v,&flipped_positions);


				//printf(" le u_v est \n");
				//printMatrix(&u_v);
				updateU_V(&u,&v,&u_v);
				Matrix transpose_flipped_pos = transpose(&flipped_positions);
				Matrix HFptrans = multiplication(&H,&transpose_flipped_pos);
				//printf(" le avant   syndrome est \n");
				//printMatrix(&syndrome);
				syndrome =  subraction_Polynome(&syndrome,&HFptrans);
				syndrome =  transpose(&syndrome);
				u_v =  transpose(&u_v);
				//printf(" le s est syndorm - HFptrans  est \n");
				//printMatrix(&HFptrans);
				//printf(" le apres  syndrome est \n");
			//	printMatrix(&syndrome);

		}

		Matrix H_uv = multiplication(&H,&u_v);
	  Matrix res= subraction_Polynome(&syndrome,&H_uv);
    if(poidHamming(&res)!=0) return;
		else return u_v;
		//return flipped_positions;

}


int chiffrement(int m , Matrix *eo,Matrix *e1)
{

	int res=0;
	int n =eo->nb_rows;
	int k=0;
	unsigned char ma_chaine[n*2];
	for(int j =0 ; j < 2 ; j++)
	{
		k=0;
		for(int i=0 ; i < n*2;i++){

			if( i < n){
				ma_chaine[i]+= getElt(eo,0,i) ;
			}else{
				ma_chaine[i]+= getElt(e1,0,k);
				k++;
			}
		}
	}


		unsigned char mon_hash[MD5_HASHBYTES];
		calcul_md5(ma_chaine,n*2,mon_hash);
		printf("le hash de %s est ", ma_chaine);
		for(int i=0; i < MD5_HASHBYTES;i++)
		printf("%2.2x ", mon_hash[i]);
		printf("\n");

		for(int i=0 ; i < MD5_HASHBYTES;i++) res=res^mon_hash[i];

		printf(" le message est %d\n",res);
		return res;

}

/*
poids de x et y : w=39,
longueur de x et y : n= 4813
poids total de l'erreur e : 78,
 seuil T pour l'algo bitflip= 26
*/

int main(int argc, char const *argv[]) {
  int n=481;
  int weight_h=39;
  int weight_e=78;
	bool goIfnotInverse=true;
	Matrix ho ;
	Matrix h1;
	Matrix Ho;
	Matrix inverse_ho;
	Matrix h;
  Matrix H;
	Matrix eo;
	Matrix e1;
	Matrix c1;
	Matrix c;
	Matrix s;
	int m=25;


while(goIfnotInverse){

	ho= createPolynome(n,weight_h);
	h1 = createPolynome(n,weight_h);
	Ho = rot(&ho);
	inverse_ho = pivotGaus(&Ho);
	if(inverse_ho.valide==true){

		goIfnotInverse=false;
		h = multiplication(&inverse_ho,&h1);
		H = rot(&h);
		// Bob
		eo = createPolynome(n,weight_e);
		e1 = createPolynome(n,weight_e);
		c1 = multiplication(&H,&e1);
		c = addition(&eo,&c1);
		s = multiplication(&Ho,&c);


		//printf("\nmatrice s est  [%d][%d] =\n", s.nb_rows, s.nb_columns);
		//printMatrix(&s);
	//	Matrix eo_e1 = bitFlipping(&ho,&h1,&s,weight_h);

		//if(eo_e1.valide==true)   printMatrix(&eo_e1);

	}


}

  deleteM(&eo);
  deleteM(&e1);
  deleteM(&ho);
  deleteM(&h1);
  deleteM(&h);
  deleteM(&inverse_ho);
  deleteM(&c1);
  deleteM(&s);
  deleteM(&H);
  deleteM(&Ho);


  return 0;
}
