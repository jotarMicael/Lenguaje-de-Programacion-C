#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"
#include "list_t.h"
#include "error_mat.h"



int main(int argc, char *argv[])
{
    FILE *fp=NULL;
    matrix_t **m1;
    *(m1)=matrix_create(2,2,M1);
    printf("Tipo: M");
    for(int i=0; i<2; i++ ){ 
          for(int j=0; j<2; j++ ){
            (*m1)->matriz[i][j]=i;
          }
        }

    write_matrix(argv[1],fp,*m1);
    matrix_print(*m1);
    return 1;

 }
