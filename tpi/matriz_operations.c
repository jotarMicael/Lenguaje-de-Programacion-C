#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"

error_t set_ffmt_matrix(matrix_t *m,matrix_fmt_t  fmt)
{
  return -E_NOTIMPL_ERROR;      
}

error_t get_ffmt_matrix(matrix_t *m, matrix_fmt_t  *fmt)
{
  return -E_NOTIMPL_ERROR;      
}

error_t read_matrix(FILE *fp, matrix_t *m){

  char temp = 50; //para leer de a lineas
  int c; //para leer de a caracteres
  char *p; //puntero para utilizar en la funcion strtol
  int num; //entero para almacenar el entero devuelto por strtool
  double num2; //double para cargar a la matriz

  m=(m*)malloc(sizeof(matrix_t)); //asigno memoria al puntero que contiene el registro.
  fp = fopen ("M1.txt", "r"); //abro el archivo de texto
  if (fp==NULL){  // si no es de texto, me fijo si es binario
    fp = fopen ("M2.bin", "rb"); //abro el binario
    if (fp==NULL)
  	  return -E_FORMAT_ERROR; //retorna error si no abre ni el archivo binario ni texto
    //procesando archivo binario
  }
  //procesando archivo de texto

  if(!feof(fp)){ //mientras no termine el archivo
  	if (strcmp(fgets(temp,50,fp), "M1") == 0) { //leo la primera linea, y me fijo si dice M1
      m=(m*)malloc(sizeof(matrix_t)); //reservo memoria para el puntero al struct matrix
      if(m==NULL)
        return -E_SIZE_ERROR;
      *m->fmt = M1; // coloco el valor M1 , al formato de matriz
      while ((strcmp(c = fgetc(fp), "#") == 0)&&(!feof(fp))); // si el caracter es "#", descarto la linea completa, si salgo es porque leo el numero de la fila
        fgets(temp,50,fp);
      if (feof(fp))
        return -E_SIZE_ERROR;
      else{
        p=&c; //almaceno direccion del caracter
        num = (int) strtol(p,NULL,10); //convierto la fila a entero
        *m->rows=num; //almaceno fila en la var fila del struct
        c = fgetc(fp);c = fgetc(fp);
        num = (int) strtol(p,NULL,10); //convierto la columna a entero
        *m->cols=c; // almaceno columna en la var cols del struct
        *m->matriz=malloc(sizeof(double)*(*m->rows)); //Asigno memoria para la matriz
        for(int i=0; i<(*m->cols); i++ ){ // ----
          *m->matriz[i]=malloc(sizeof(double)*(*m->cols)); // .
        }
      for(int i=0; i<(*m->rows); i++ ){ //Asigno valores a la matriz , cant de filas y columnas exactas que poseia el archivo
        for(int j=0; i<(*m->cols); j++ ){
          fscanf(fichero, "%lf", &num2);
          *m.matriz[i][j]=num2;
        }
      }
    }
    fclose(fp);  
    return E_OK; 
    }  
    else
     {fclose(fp); return E_FORMAT_ERROR; }
  }
  fclose(fp);
  return -E_OK;   
}

error_t write_matrix(FILE *fp, const matrix_t *m)
{
  char temp = 50; //para leer de a lineas
  int c; //para leer de a caracteres
  char *p; //puntero para utilizar en la funcion strtol
  int num; //entero para almacenar el entero devuelto por strtool
  double num2; //double para cargar a la matriz

  fp = fopen ("M1.txt", "a");
  if(fp==NULL)
    return 1; //error desconocido
  else{
    if(*m->fmt==1){
      fwrite(fp, "M1" . PHP_EOL);

    }
    else{

    }
  }
  

  return -E_NOTIMPL_ERROR;      
}

error_t dup_matrix(const matrix_t *m_src, matrix_t **m_dst)
{
  return -E_NOTIMPL_ERROR;      
}

error_t sum(const matrix_t *ma, const matrix_t *mb, matrix_t **mc)
{
  return -E_NOTIMPL_ERROR;      
}

error_t sum_inplace(const matrix_t *m_src, matrix_t *m_dst)
{
  return -E_NOTIMPL_ERROR;      
}

error_t mult_scalar(T_TYPE a, const matrix_t *mb, matrix_t **mc)
{
  return -E_NOTIMPL_ERROR;      
}

error_t mult_scalar_inplace(T_TYPE a, matrix_t *m_dst)
{
  return -E_NOTIMPL_ERROR;      
}

error_t create_and_fill_matrix(unsigned int rows, unsigned int cols, T_TYPE a, matrix_t **mb)
{
  return -E_NOTIMPL_ERROR;      
}

unsigned int get_rows(const matrix_t *ma)
{
  if (ma !=NULL)
    return ma->rows;
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
  if ( (mb->rows != ma->rows) || (mb->cols != ma->cols) )
    {
      return 0;
    }
  else
    {
      for(int i=0;i<(mb->rows)*(mb->cols);i++)
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

error_t resize_matrix(unsigned int newrows, unsigned int newcols, matrix_t **ma)
{
  return -E_NOTIMPL_ERROR;  
}
