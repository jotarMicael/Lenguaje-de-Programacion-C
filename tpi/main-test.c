#include <stdio.h>
#include "matriz.h"
#include "list_t.h"
#include "stdbool.h"

#define SCALAR (0.5)

int main(int argc, char *argv[])
{

  matrix_t  *m;
  matrix_t  *ma;
  matrix_t  *mb;
  matrix_t  *mc;
  matrix_t  *md;
  matrix_t  *me;
  matrix_t  *mf;  
  matrix_t  *m0;
  matrix_t  *m1;  
  matrix_t  *maux1, *maux2; 
  double     f;
  list_t     l;
  FILE *fp=NULL;
  

  if (read_matrix(argv[1],fp, &ma))
    {
      fprintf(stderr,"Can't read matrix\n");      
      return -1;
    }
  fprintf(stderr,"ma=\n"); matrix_print(ma);
  m=ma;
  fprintf(stderr,"-----------------\n");
  dup_matrix(m,&mb);
  fprintf(stderr,"mb=\n"); matrix_print(mb);
  fprintf(stderr,"-----------------\n");

  //////////// SUM 

  // Conmutativa 
  // A + B = C
  sum(ma,mb,&mc);
  // B + A = D
  sum(mb,ma,&md);
  // C == D , D == C
  fprintf(stderr,"ma + mb == mb + ma :%d %d\n",cmp_matrix(mc,md), cmp_matrix(md,mc));
  fprintf(stderr,"mc=\n"); matrix_print(mc);
  fprintf(stderr,"-----------------\n");
  fprintf(stderr,"md=\n"); matrix_print(md);
  fprintf(stderr,"-----------------\n");
  free_matrix(&md);
  free_matrix(&mc);
  
  // Asociativa
  // A + (B + C) = D
  dup_matrix(m,&mc);
  sum(mb,mc,&maux1);
  sum(ma,maux1,&md);

  // (A + B) + C = E
  free_matrix(&maux1);
  sum(ma,mb,&maux1); 
  sum(maux1,mc,&me);
  // D == E , E == D
  fprintf(stderr,"ma + (mb + mc) == (ma + mb) + mc :%d %d\n",cmp_matrix(md,me), cmp_matrix(me,md));
  fprintf(stderr,"md=\n"); matrix_print(md);
  fprintf(stderr,"-----------------\n");
  fprintf(stderr,"me=\n"); matrix_print(me);
  fprintf(stderr,"-----------------\n");
  free_matrix(&md);
  free_matrix(&me);
  free_matrix(&maux1);  
 
  // Elemento neutro
  // A + 0 = D
  null_matrix(get_rows(ma),get_cols(ma),&m0);
  fprintf(stderr,"m0=\n"); matrix_print(m0);
  fprintf(stderr,"-----------------\n");  
  sum(ma, m0, &md);
  // A == D == A
  fprintf(stderr,"(ma + m0) = ma :%d %d\n",cmp_matrix(ma,md), cmp_matrix(md,ma) );
  fprintf(stderr,"md=\n"); matrix_print(md);
  fprintf(stderr,"-----------------\n"); 
  free_matrix(&md);
  
  //Inverso Aditivo
  // A + -A = 0
  mult_scalar(-1, ma, &md);
  fprintf(stderr,"-ma=\n"); matrix_print(md);
  fprintf(stderr,"-----------------\n");
  // D = A + -A
  printf("(%d)\n",sum_inplace(ma, &md));
  printf("(%d)\n",sum(ma, md, &me));  
  fprintf(stderr,"(ma + -ma) = 0 :%d %d\n",cmp_matrix(m0,md), cmp_matrix(md,m0) );
  fprintf(stderr,"md=\n"); matrix_print(md);
  fprintf(stderr,"me=\n"); matrix_print(me); 
  fprintf(stderr,"-----------------\n");
  free_matrix(&md);
  free_matrix(&me);

  //////////// MULT  SCALAR
  // A + B = F
  sum(ma,mb,&mf);
  // c * F = c * (A + B) = F
  mult_scalar_inplace(SCALAR, &mf);
  fprintf(stderr,"%f * mf=\n",SCALAR); matrix_print(mf);
  fprintf(stderr,"-----------------\n");
  
  // D = c * A
  mult_scalar(SCALAR, ma, &md);
  // E = c * B  
  mult_scalar(SCALAR, mb, &me);
  // E = D + E = c * A + c * B 
  sum_inplace(md,&me);
  fprintf(stderr,"%f * ma +  %f * mb =\n",SCALAR,SCALAR); matrix_print(me);
  fprintf(stderr,"-----------------\n");
  fprintf(stderr,"%f * (ma + mb) = %f * ma + %f * mb :%d %d\n",SCALAR,SCALAR,SCALAR,cmp_matrix(mf,me), cmp_matrix(me,mf) );
  free_matrix(&md);
  free_matrix(&me);
  free_matrix(&mf);  

  // Identidad Multiplicativa
  // D = A * I
  if(get_rows(ma)>=get_cols(ma))
    idty_matrix(get_rows(ma),&m1);
  else
    idty_matrix(get_cols(ma),&m1);  
  mult(ma, m1, &md);
  fprintf(stderr,"md= \n"); matrix_print(md); 
  // E = I
  mult(ma, m1, &me);
  fprintf(stderr,"ma * m1 \n"); matrix_print(me);
  fprintf(stderr,"-----------------\n");
  fprintf(stderr,"(ma * m1) = (m1 * ma) = ma : %d %d %d\n",cmp_matrix(ma,md), cmp_matrix(md,ma), cmp_matrix(md,me));
  free_matrix(&md);
  free_matrix(&me);

  // Nulo Multiplicativo
  // D = A * 0 

  null_matrix(get_rows(ma),get_cols(ma),&m0); 
  fprintf(stderr,"ma = \n"); matrix_print(ma);
  fprintf(stderr,"m0 = \n"); matrix_print(m0);
  mult_scalar(0.0, ma, &md);

  // E = 0 * A
  
  mult_scalar(0.0, ma, &me);
  fprintf(stderr,"md = \n"); matrix_print(md);
  fprintf(stderr,"-----------------\n");
  fprintf(stderr,"(ma * m0) = (m0 * ma) = ma :%d %d\n",cmp_matrix(me,md), cmp_matrix(md,me));
  free_matrix(&md);
  free_matrix(&me);

  // Nulo Multiplicativo escalar
  // D = esc(0) * A  = 0
  mult_scalar(0.0, ma, &md);
  fprintf(stderr,"md = \n"); matrix_print(md);
  fprintf(stderr,"-----------------\n");
  fprintf(stderr,"(0 * ma) = m0 :%d %d\n",cmp_matrix(md,m0), cmp_matrix(md,m0));
  fprintf(stderr,"-----------------\n");
  free_matrix(&md);

  // Asociativa de la mult
  // A * (B * C) = D  
  fprintf(stderr,"mb = \n"); matrix_print(mb);
  fprintf(stderr,"mc = \n"); matrix_print(mc);

  mult(mb,mc,&maux1);
  mult(ma,maux1,&md);

  // (A * B) * C = E
  free_matrix(&maux1);
  mult(ma,mb,&maux1); 
  mult(maux1,mc,&me);
  
  // D == E , E == D
  fprintf(stderr,"ma * (mb * mc) == (ma * mb) * mc :%d %d\n",cmp_matrix(md,me), cmp_matrix(me,md));
  fprintf(stderr,"md=\n"); matrix_print(md);
  fprintf(stderr,"-----------------\n");
  fprintf(stderr,"me=\n"); matrix_print(me);
  fprintf(stderr,"-----------------\n");
  free_matrix(&md);
  free_matrix(&me);
  free_matrix(&maux1);  

   // Dist de la mult con respecto a la suma
  // A * (B + C) = D  
  sum(mb,mc,&maux1);
  mult(ma,maux1,&md);

  // (A * B)  + (A * C)  = E
  // E = E + F
  free_matrix(&maux1);
  mult(ma,mb,&maux1); 
  mult(ma,mc,&maux2);
  sum(maux1,maux2,&me);  
  
  // D == E , E == D
  fprintf(stderr,"ma * (mb + mc) == (ma * mb) + (ma * mc) :%d %d\n",cmp_matrix(md,me), cmp_matrix(me,md));
  fprintf(stderr,"md=\n"); matrix_print(md);
  fprintf(stderr,"-----------------\n");
  fprintf(stderr,"me=\n"); matrix_print(me);
  fprintf(stderr,"-----------------\n");
  free_matrix(&md);
  free_matrix(&me);
  free_matrix(&maux1);  
  free_matrix(&maux2);  
  create_and_fill_matrix(get_rows(ma), get_cols(ma), 3.0, &md);
  set_elem_matrix(2,2,1000.0,&md);
  set_elem_matrix(4,4,2000.0,&md);
  set_elem_matrix(5,5,2000.0,&md);   
  fprintf(stderr,"md=\n"); matrix_print(md);
  printf("-------------\n");
  for(int i=0;i<get_rows(md);i++)
    {
      for(int j=0;j<get_cols(md);j++)
	{
	  get_elem_matrix(i,j,&f,md);
	  printf("%.2lf ",f);
	}
      printf("\n");
    }
  printf("-------------\n");
  list_new(l);
  matrix2list(md, &l);
  while(l!=NULL){
      fprintf(stderr,"dato= %lf\n",l->dato);
      l=l->siguiente;
  }
  printf("\n-------------\n");
  destroy_list(l);
  free_matrix(&md);
  clear_matrix(ma);
  matrix_print(ma);
  free_matrix(&mb);
  free_matrix(&mc);
  free_matrix(&m0);
  free_matrix(&m1);
  return 0;
}


/*** EOF **/
