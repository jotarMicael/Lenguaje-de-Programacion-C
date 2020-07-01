#include <stdlib.h>
#include "matriz.h"

error_t set_ffmt_matrix(matrix_t *m,matrix_fmt_t  fmt)
{
  return -E_NOTIMPL_ERROR;      
}

error_t get_ffmt_matrix(matrix_t *m, matrix_fmt_t  *fmt)
{
  return -E_NOTIMPL_ERROR;      
}

error_t read_matrix(FILE *fp, matrix_t *m)
{
  fp = fopen ("M1.txt", "r");
  if (fp==NULL)
  	return -E_FILE_ERROR;

  int cont = 0;
  char temp = 50;

  while(! feof(fp)){
  	if (strcmp(fgets(temp,50,fp), "M1") == 0) 

  }
  return -E_NOTIMPL_ERROR;      
}

error_t write_matrix(FILE *fp, const matrix_t *m)
{
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
