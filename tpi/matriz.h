#ifndef MATRIX_MAT_H
#define MATRIX_MAT_H  1

#include <stdio.h>
#include "list_t.h"
#include "error_mat.h"

#define N_BUF_LENGTH   2048
#define C_COMMENT       '#' 


#define T_TYPE         double
#define V_NULL         0.0
#define V_ONE          1.0
#define INIT_C_R	   -5

typedef enum matrix_fmt {M1 = 1 , M2 , INVALID} matrix_fmt_t;

typedef struct matrix {
            matrix_fmt_t  fmt;
            unsigned int rows,cols;
            T_TYPE **matriz;
         }  matrix_t;

matrix_t *matrix_create(int n, int m, matrix_fmt_t c);
/***
 * Carga la matriz desde un archivo. El resultado queda en "m".
 */

error_t read_matrix(char *filename,FILE *fp, matrix_t **m);

/***
 * Almacena la matriz en un archivo. El origen es "m".
 */
error_t write_matrix(char *filename,FILE *fp, const matrix_t *m);

/***
 * Imprime la matriz recibida como parametro
 */

void matrix_print(matrix_t *M);

/***
 * Setea el formato de la matriz, (M1, M2, ...).
 */
error_t set_ffmt_matrix(matrix_t *m, matrix_fmt_t fmt);

/***
 * Obtiene el formato de la matriz, (M1, M2, ...).
 */
error_t get_ffmt_matrix(matrix_t *m, matrix_fmt_t  *fmt);

/***
 * Duplica (copia) la matriz en memoria. La copia queda en "m_dst".
 * Se hace la reserva de la memoria dentro de la funcion.
 */
error_t dup_matrix(const matrix_t *m_src, matrix_t **m_dst);

/***
 * Realiza la suma algebraica de matrices. El resultado queda
 * en "mc" que se crea dentro de la funcion. , "mc = ma + mb".
 * Debe chequear que las dimensiones sean compatibles para
 * la operacion. Sino retornar un error que indique el mismo.
 */
error_t sum(const matrix_t *ma, const matrix_t *mb, matrix_t **mc);

/***
 * Realiza la suma algebraica de matrices. El resultado queda
 * en "mb", "mb = ma + mb".
 * Debe chequear que las dimensiones sean compatibles para
 * la operacion. Sino retornar un error que indique el mismo.
 */
error_t sum_inplace(const matrix_t *m_src, matrix_t **m_dst);

/***
 * Realiza la multiplicacion algebraica de una matriz por
 * un escalar. El resultado queda en "mc", "mc = a * mb".
 * Debe chequear que las dimensiones sean compatibles para
 * la operacion. Sino retornar un error que indique el mismo.
 */
error_t mult_scalar(T_TYPE a, const matrix_t *mb, matrix_t **mc);


error_t mult_scalar_inplace(T_TYPE a, matrix_t **m_dst);

/***
 * Realiza la multiplicacion algebraica entre matrices.
 * El resultado queda en "mc", "mc = ma * mb".
 * Debe chequear que las dimensiones sean compatibles para
 * la operacion. Sino retornar un error que indique el mismo.
 */
error_t mult(const matrix_t *ma, const matrix_t *mb, matrix_t **mc);

/***
 * Genera una matriz nueva de "rows*cols" cargando en todos las
 * posiciones el valor escalar "a". 
 */
error_t create_and_fill_matrix(unsigned int rows, unsigned int cols, T_TYPE a, matrix_t **mb);

/***
 * Genera la matriz nula de "n*n" en "mc".
 * El resultado queda en "mc".
 */
error_t null_matrix(unsigned int rows,unsigned int cols, matrix_t **mc);

/***
 * Genera la matriz identidad de "n*n" en "mc".
 * El resultado queda en "mc".
 */
error_t idty_matrix(unsigned int n, matrix_t **m);

/***
 * Obtiene la cantidad de filas de la matriz "ma"
 */
unsigned int get_rows(const matrix_t *ma);

/***
 * Obtiene la cantidad de columnas de la matriz "ma"
 */
unsigned int get_cols(const matrix_t *ma);

/***
 * Coloca el valor "value" en la "pos=(row,col)" en la matriz "mc".
 * Debe chequear las dimensiones.
 */
error_t set_elem_matrix(unsigned int row, unsigned int col, T_TYPE value, matrix_t **m);

/***
 * Obtiene el valor de la "pos=(row,col)" de la matriz "mc" y
 * lo coloca en "value".
 * Debe chequear las dimensiones.
 */
error_t get_elem_matrix(unsigned int row, unsigned int col, T_TYPE *value, const matrix_t *m);

/***
 * Compara las matrices "ma" y "mb". Si son iguales retorna
 * distinto de cero o true y sino cero o false
 */
error_t cmp_matrix(const matrix_t *ma, const matrix_t *mb);

/***
 * Libera la memoria usada por la matriz "m".
 * Asigna NULL a m.
 */
error_t free_matrix(matrix_t **m);

/***
 * Limpia una matrix dejandola en 0
 */
error_t clear_matrix(matrix_t *m);

/***
 * Carga la fila "pos" de la matriz ma en la lista "l"
 */
error_t get_row(unsigned int pos, const matrix_t *ma, tpuntero *l);

/***
 * Carga la columna "pos" de la matriz "ma" en la lista "l"
 */
error_t get_col(unsigned int pos, const matrix_t *ma, tpuntero *l);

/***
 * Pasa la matriz "ma" a la lista "l"
 */
error_t matrix2list(const matrix_t *ma, tpuntero *l);

/***
 * Redimensiona la matriz "ma" a las dimensiones "newrows*newcols"
 * Si es mas grande la nueva matriz queda con cualquier valor
 * en las nuevas posiciones. Si es mas chica se descartan.
 */
error_t resize_matrix(unsigned int newrows, unsigned int newcols, matrix_t **ma);

#endif /*** mat.h ***/
