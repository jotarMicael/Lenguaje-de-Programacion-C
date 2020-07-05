#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"

matrix_t *matrix_create(int n, int m, matrix_fmt_t c)
{
    int i;
    matrix_t *M;
    
    M = malloc(sizeof(matrix_t));
    if(M == NULL)
    {
        return NULL;
    }

    M->rows = m; //filas  
    M->cols = n; //columnas
    if (c==M1)
      M->fmt = M1;
    else
      M->fmt = M2;

    M->matriz = malloc(n * sizeof(float *));
    if(M->matriz== NULL)
    {
        return NULL;

    for(i = 0; i < n; i++)
    {
        M->matriz[i] = malloc(m * sizeof(float));
        if(M->matriz[i] == NULL)
        {
            return NULL;
        }
    }
    
    return M;
}

error_t set_ffmt_matrix(matrix_t *m,matrix_fmt_t  fmt)
{
  return -E_NOTIMPL_ERROR;      
}

error_t get_ffmt_matrix(matrix_t *m, matrix_fmt_t  *fmt)
{
  return -E_NOTIMPL_ERROR;      
}

error_t read_matrix(char *filename,FILE *fp, matrix_t *m){
{
    int c,ni, mj, i, j,rows,cols;
    char line[100000];
    char num[1000];
    char *p;

    fp = fopen(filename,"r");
    if(fp == NULL)
    {
        printf("Error al abrir archivo");
        return -E_FILE_ERROR:
    }
    if (strcmp(fgets(temp,50,fp), "M1") == 0){ //PROCESO MATRIZ M1
        while ((strcmp(c = fgetc(fp), "#") == 0)&&(!feof(fp))); // si el caracter es "#", descarto la linea completa, si salgo es porque leo el numero de la fila
          fgets(temp,50,fp);
        if (feof(fp))
          return -E_FORMAT_ERROR;
        p=&c; //almaceno direccion del caracter
        n= (int) strtol(p,NULL,10); //convierto la fila a entero
        rows=n; //almaceno fila en la var fila del struct
        c = fgetc(fp);c = fgetc(fp);
        n= (int) strtol(p,NULL,10); //convierto la columna a entero
        cols=n;
        m = matrix_create(rows, cols,*m->fmt);
        if(m == NULL){
          return -E_ALLOC_ERROR;
        }
        for(ni = 0; ni < rows; ni++){

          fgets(line, 100000, fp); 
          i = 0;
          mj = 0;

          while(mj < cols) {
            j = 0;

            while(line[i] != ' ' && line[i] != '\n') {
                num[j] = line[i];
                j++;
                i++;
            }

            i++;
            num[j] = '\0';
            m->matriz[ni][mj] = atof(num);
            mj++;
            j = 0;
          }
        }
                
    fclose(fp);
    return -E_OK;
      
    }

    else { //Procesar matriz M2


    }

    

error_t write_matrix(char *filename,FILE *fp, const matrix_t *m)
{
  int i,j;
  int c; //para leer de a caracteres
 
  if(m != NULL){
    fp = fopen (filename, "a");
    if(fp==NULL)
     return 1; //error desconocido
    else{
      if(*m->fmt==M1){
        fwrite(fp, "M1" . PHP_EOL);
        fprintf(fp,"%d",*m.rows);
        fputc (" ",fp);
        fprintf(fp,"%d\n",*m.cols);
        for(int i=0; i<(*m->rows); i++ ){ //Asigno valores al archivo , cant de filas y columnas exactas que posee la matriz
          for(int j=0; i<(*m->cols); j++ ){
            fprintf(fp,"%lf",*m.matriz[i][j]);
            fputc(" ",fp);
        }
      }
      fclose(fp); return -E_OK;
    }
    else{
        //procesar matriz tipo2
    }
  }
  }
    return -E_NOTIMPL_ERROR;  
}    


error_t dup_matrix(const matrix_t *m_src, matrix_t **m_dst)
{
  m_dst=matrix_create(*m_src->rows,*m_src->cols,*m_src->fmt);
  if((m_dst!=NULL)&&(m_src!=NULL){
    *m_dst=&msrc;
     return -E_OK;
  }
  return -E_NOTIMPL_ERROR;      
}


error_t sum(const matrix_t *ma, const matrix_t *mb, matrix_t **mc)
{

  if(*ma->rows==*mb->rows){
    if(*ma->cols==*mb->cols){
        mc=matrix_create(*ma->rows,*ma->cols,*ma->fmt);
        for(int i=0; i<(*ma->matriz); i++ ){ //Asigno valores a la matriz , cant de filas y columnas exactas que poseia el archivo
          for(int j=0; i<(*ma->cols); j++ ){
            **mc->matriz[i][j]=(*ma->matriz[i][j])+(*mb->matriz[i][j]);
          }
        }
        return -E_OK;
    }
    else
      return -E_SIZE_ERROR;
  }
  else
    return -E_SIZE_ERROR;
    
}

error_t sum_inplace(const matrix_t *m_src, matrix_t *m_dst)
{
  if(*m_src->matriz==*m_dst->matriz){
    if(*m_src->cols==*m_dst->cols){
        for(int i=0; i<(*m_src->matriz); i++ ){ //Asigno valores a la matriz , cant de filas y columnas exactas que poseia el archivo
          for(int j=0; i<(*m_src->cols); j++ ){
            *m_dst->matriz[i][j]=(*m_src->matriz[i][j])+(*m_dst->matriz[i][j]);
          }
        }
        return -E_OK;
    }
    else
      return -E_SIZE_ERROR;
  }
  else
    return -E_SIZE_ERROR;     
}

error_t mult_scalar(T_TYPE a, const matrix_t *mb, matrix_t **mc)
{
    if(mb!=NULL){
      **mc->matriz=malloc(sizeof(double)*(**mb->matriz)); //Asigno memoria para la matriz
       for(int i=0; i<(**mb->cols); i++ )// ----
        **mc->matriz[i]=malloc(sizeof(double)*(**mb->cols)); // .
        for(int i=0; i<(*mb->matriz); i++ ){ //Asigno valores a la matriz , cant de filas y columnas exactas que poseia el archivo
          for(int j=0; i<(*mb->cols); j++ ){
            **mc->matriz[i][j]=(*mb->matriz[i][j])+a;
          }
        }
          return -E_OK;
    }
    return -E_NOTIMPL_ERROR; 
  
 }
      

error_t mult_scalar_inplace(T_TYPE a, matrix_t *m_dst)
{
  return -E_NOTIMPL_ERROR;      
}

error_t create_and_fill_matrix(unsigned int matriz, unsigned int cols, T_TYPE a, matrix_t **mb)
{
  return -E_NOTIMPL_ERROR;      
}

unsigned int get_matriz(const matrix_t *ma)
{
  if (ma !=NULL)
    return ma->matriz;
  else
    return 0;
}

unsigned int get_cols(const matrix_t *ma)
{
  if (ma !=NULL)
    return ma->cols;
  else
    return 0;
}

error_t null_matrix(unsigned int n, matrix_t **mc)
{
  return create_and_fill_matrix(n, n, V_NULL, mc);
}


error_t idty_matrix(unsigned int n, matrix_t **m)
{
  return -E_NOTIMPL_ERROR;      
}

error_t mult(const matrix_t *ma, const matrix_t *mb, matrix_t **mc)
{
  return -E_NOTIMPL_ERROR;      
}

error_t set_elem_matrix(unsigned int row, unsigned int col, T_TYPE value, matrix_t **m)
{
  return -E_NOTIMPL_ERROR;      
}

error_t get_elem_matrix(unsigned int row, unsigned int col, T_TYPE *value, const matrix_t *m)
{
  return -E_NOTIMPL_ERROR;      
}

int cmp_matrix(const matrix_t *ma, const matrix_t *mb)
{
  int complete_me = 1;
  if ( (mb->matriz != ma->matriz) || (mb->cols != ma->cols) )
    {
      return 0;
    }
  else
    {
      for(int i=0;i<(mb->matriz)*(mb->cols);i++)
	{
	  //if ( mb->contents[i] !=  ma->contents[i])
	  //if ((mb->contents[i] - ma->contents[i]) >=  V_DELTA_PRECS)
	  if (complete_me)
	    {
	      return 0;
	    }
	}
      return 1;
    }
}

error_t free_matrix(matrix_t **m)
{
  return -E_NOTIMPL_ERROR;      
}

error_t clear_matrix(matrix_t *m)
{
  return -E_NOTIMPL_ERROR;      
}
  
error_t get_row(unsigned int pos, const matrix_t *ma, list_t *l)
{
  return -E_NOTIMPL_ERROR;      
}

error_t get_col(unsigned int pos, const matrix_t *ma, list_t *l)
{
  return -E_NOTIMPL_ERROR;  
}

error_t matrix2list(const matrix_t *ma, list_t *l)
{
  return -E_NOTIMPL_ERROR;      
}

error_t resize_matrix(unsigned int newmatriz, unsigned int newcols, matrix_t **ma)
{
  return -E_NOTIMPL_ERROR;  
}
