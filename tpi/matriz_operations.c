#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"
#include "list_t.h"

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
        if(M->matriz[i] == NULL){
            return NULL;
        }

    }
    
    return M;
}

error_t set_ffmt_matrix(matrix_t *m,matrix_fmt_t  fmt)
{
  if(m!=NULL){
    m->fmt=fmt;
    return -E_OK;
  }
  return -E_NOTIMPL_ERROR;      
}

error_t get_ffmt_matrix(matrix_t *m, matrix_fmt_t  *fmt)
{
  if(m!=NULL){
    fmt=malloc(n * sizeof(matrix_fmt_t *))
    fmt=m->fmt;
    return -E_OK;
  }
  return -E_NOTIMPL_ERROR;      
}

error_t read_matrix(char *filename,FILE *fp, matrix_t *m){

 double dvalue;
 char buf[N_BUF_LENGTH];
 char num[1000];
 int rows,cols,i,j,ni,mj;
 matrix_fmt_t fmt;
 // Open file
  
   if (!(fp = fopen(filename,"r")) )
   {
     return -E_FILE_ERROR;
     
   }
 
 //check the matrix header format
 buf[0] = buf[1] = 0;
 if (fgets(buf, sizeof(buf), fp)!=NULL)
    {
      fprintf(stderr, "Error al leer header format\n");
      return -E_FORMAT_ERROR;      
    }
 if (buf[0] != 'M' || (buf[1] != '1' && buf[1] != '2'))
   {
     fprintf(stderr, "Error de formato, debe ser ('M1 o M2')\n");
     return -E_FORMAT_ERROR;
   }
if ((buf[0] == 'M') && (buf[1] == '1'))
    fmt=M1;
else
    fmt=M2;
 /****** 
 //Skip comments checking
 // discard_comments(fp);
 ******/
 if (fgets(buf, sizeof(buf), fp)!=NULL)
    {
      fprintf(stderr, "Error al leer header format\n");
      return -E_FORMAT_ERROR;      
    }
if (buf[0] == '#')
     fgets(buf, sizeof(buf), fp) //Buscar forma de volver para atras

if(fscanf(fp,"%d",&rows) == 1){
  if(fscanf(fp,"%d",&cols) == 1)
     m = matrix_create(rows, cols,fmt);
}
else{
  fprintf(stderr, "Error al leer las dimensiones\n");
  return -E_SIZE_ERROR;   
}
if(m==NULL){
  return -E_ALLOC_ERROR;
}

 //read matrix size information
 if (fscanf(fp, "%d %d", m->rows, m->cols) != 2) {
   fprintf(stderr, "Error en dimensiones \n");
   return -E_SIZE_ERROR
 }
  

    if(m->fmt==M1){ //proceso M1
  
        for(ni = 0; ni < m->rows; ni++){

          fgets(buf, 100000, fp); 
          i = 0;
          mj = 0;

          while(mj < m->cols) {
            j = 0;

            while(buf[i] != ' ' && buf[i] != '\n') {
                num[j] = buf[i];
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

 }
 else{ //proceso M2
      while (fread((double*)&dvalue, sizeof(double), 1, fp) == sizeof(double)){
        for(int i=0; i<(m->rows); i++ ){ //Asigno valores al archivo , cant de filas y columnas exactas que posee la matriz
          for(int j=0; i<(m->cols); j++ ){
            m.matriz[i][j]=dvalue;
            fread((double*)&dvalue, sizeof(double), 1, fp);
        }
      }
        
      }
      fclose(fp); 
      return -E_OK;
 }
}  

error_t write_matrix(char *filename,FILE *fp, const matrix_t *m)
{
  /*int i,j;
  int c; //para leer de a caracteres
 
  if(m != NULL){
    fp = fopen (filename, "a");
    if(fp==NULL)
     return 1; //error desconocido
    else{
      if(m->fmt==M1){
        fwrite(fp, "M1" . PHP_EOL);
        fprintf(fp,"%d",m.rows);
        fputc (" ",fp);
        fprintf(fp,"%d\n",m.cols);
        for(int i=0; i<(m->rows); i++ ){ //Asigno valores al archivo , cant de filas y columnas exactas que posee la matriz
          for(int j=0; i<(m->cols); j++ ){
            fprintf(fp,"%lf",m.matriz[i][j]);
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
    return -E_NOTIMPL_ERROR;  */
  char buf[N_BUF_LENGTH];
  int rows,cols,res;

  if(m!=NULL){
     if (! (fp = fopen(filename,"w")) ){
        perror("Error al abrir archivo de escritura");
        exit(EXIT_FAILURE);  
      }
      //check the matrix header format

    if ((m->fmt!='M1')||(m->fmt!='M2')) {
      fprintf(stderr, "Error al leer header format\n");
      fclose(fp); 
      return -E_FORMAT_ERROR;      
    }
     if ((m->fmt!='M1'))
        fprintf(fp, "%c\n",'M1')
     else
        fprintf(fp, "%c\n",'M2')  //escribo el formato de la matriz

    
    //read matrix size information
      if(sizeof(m->cols)!=sizeof(int)&&(sizeof(m->rows)!=sizeof(int))){
        fprintf(stderr, "Error en dimensiones \n");
        fclose(fp); 
        return -E_SIZE_ERROR;
      }
      fprintf(fp, "%d",m->rows);
      fprintf(fp, "%c",' ');
      fprintf(fp, "%d\n",m->cols); //escribo filas y columnas en archivo

      

      if(m->fmt=='M1'){ //proceso M1
          for(int i=0; i<(m->rows); i++ ){ //Asigno valores al archivo , cant de filas y columnas exactas que posee la matriz
                for(int j=0; i<(m->cols); j++ ){
                  if(printf(fp,"%d",m->matriz[i][j])!=1){
                    fclose(fp); 
                    return -E_WRITE_ERROR;
                  }
                  fprintf(fp,"%c",' ');
                }
              } 

      }

      else{
          if(m->fmt=='M2'){ //proceso M2
              for(int i=0; i<(m->rows); i++ ){ //Asigno valores al archivo , cant de filas y columnas exactas que posee la matriz
                for(int j=0; i<(m->cols); j++ ){
                  res=fwrite(&m->matriz[i][j], sizeof(int), 1, fp);
                  if(res==NULL){
                    fclose(fp); 
                    return -E_READ_ERROR;
                  }
                }
              }  

          }
          else{
              fclose(fp); 
              return -E_SIZE_ERROR;
          }
      }
    
    fclose(fp); 
    return -E_OK;
  }
}    


error_t dup_matrix(const matrix_t *m_src, matrix_t **m_dst)
{
  m_dst=matrix_create(m_src->rows,m_src->cols,m_src->fmt);
  if((*m_dst!=NULL)&&(*m_src!=NULL){
     m_dst=&m_src;
     return -E_OK;
  }
  return -E_NOTIMPL_ERROR;      
}


error_t sum(const matrix_t *ma, const matrix_t *mb, matrix_t **mc)
{
  int i,j;
  if(ma->rows==mb->rows){
    if(ma->cols==mb->cols){
        mc=matrix_create(ma->rows,ma->cols,ma->fmt);
        for(int i=0; i<(ma->rows); i++ ){ 
          for(int j=0; j<(ma->cols); j++ ){
            *mc->matriz[i][j]=(ma->matriz[i][j])+(mb->matriz[i][j]);
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
  int i,j;
  if((m_src!=NULL)&&(m_dst!=NULL)){
  if(m_src->rows==m_dst->rows){
    if(m_src->cols==m_dst->cols){
        for(int i=0; i<(m_src->rows); i++ ){ 
          for(int j=0; j<(m_src->cols); j++ ){
            m_dst->matriz[i][j]=(m_src->matriz[i][j])+(m_dst->matriz[i][j]);
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
else
    return -E_ALLOC_ERROR;
}

error_t mult_scalar(T_TYPE a, const matrix_t *mb, matrix_t **mc)
{
  int i,j;
    if(mb!=NULL){
        *mc=matrix_create(mb->rows,mb->cols,mb->fmt);
        for(int i=0; i<(mb->rows); i++ ){ 
          for(int j=0; j<(mb->cols); j++ ){
            *mc->matriz[i][j]=(mb->matriz[i][j])+a;
          }
        }
          return -E_OK;
    }
    return -E_ALLOC_ERROR; 
  
 }
      

error_t mult_scalar_inplace(T_TYPE a, matrix_t *m_dst)
{
  int i,j;
  if (m_dst!=NULL){
  for(int i=0; i<(m_dst->rows); i++ ){ 
    for(int j=0; j<(m_dst->cols); j++ ){
      m_dst->matriz[i][j]=(m_dst->matriz[i][j])+a);
    }
  }
     return -E_OK;
  }
  else
    return -E_ALLOC_ERROR;
          
}

error_t create_and_fill_matrix(unsigned int rows, unsigned int cols, T_TYPE a, matrix_t **mb)
{
  int i,j;
  *mb=matrix_create(rows,cols,*mb->fmt);
  if(*mb!=NULL){
    for(int i=0; i<(*mb->rows);i++){ 
          for(int j=0; j<(*mb->cols);j++){
            *mb->matriz[i][j]=a;
          }
    }
    return -E_OK;
  }

  return -E_ALLOC_ERROR;

}

unsigned int get_rows(const matrix_t *ma)
{
  if (ma!=NULL)
    return ma->rows;
  else
    return 0;
}

unsigned int get_cols(const matrix_t *ma)
{
  if (ma!=NULL)
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
  int i,j;
  m=matrix_create(n,n,*m->fmt);
  if(m!=NULL){
    for(int i=0; i<(*m->matriz); i++ ){ 
          for(int j=0; j<(*m->cols); j++ ){
            *m->matriz[i][j]=n*n;
          }
    }
    return -E_OK;
  }

  return -E_ALLOC_ERROR;     
}

error_t mult(const matrix_t *ma, const matrix_t *mb, matrix_t **mc)
{
  int n,m,i;
  float fsum;
    
    if((ma == NULL)&&(mb == NULL)){

       return -E_ALLOC_ERROR;
    }
  

    if(ma->cols != mb->rows)
    {
        printf("Las matrices deben ser columna ma = fila mb");
        return -E_SIZE_ERROR;
    }

    *mc=matrix_create(ma->cols,mb->rows,ma->fmt);
    if(*mc == NULL)
    {
        return -E_ALLOC_ERROR;
    }

    *mc->cols = ma->cols;
    *mc->rows = mb->rows;

    for(n = 0; n < *mc->rows; n++)
    {
        for(m = 0; m < *mc->cols; m++)
        {
            fsum = 0;
            for(i=0; i<*mc->cols; i++)
            {
                fsum = fsum + (ma->cols[n][i] * mb->cols[i][m]);
            }
            *mc->cols[n][m] = fsum;
        }
    }
    
    return -E_OK;    
}

error_t set_elem_matrix(unsigned int row, unsigned int col, T_TYPE value, matrix_t **m)
{
  if (*m!=NULL){
      if(row<=*m->rows)&&(col<=*m->cols){
        *m->matriz[row][col]=value;
        return -E_OK;
      }
      else
        return -E_SIZE_ERROR;
  }
  return -E_NOTIMPL_ERROR;      
}

error_t get_elem_matrix(unsigned int row, unsigned int col, T_TYPE *value, const matrix_t *m)
{
  if (m!=NULL){
      if(row<=m->rows)&&(col<=m->cols){
        value=m->matriz[row][col];
        return -E_OK;
      }
      else
        return -E_SIZE_ERROR;
  }
  return -E_NOTIMPL_ERROR;   
    
}

int cmp_matrix(const matrix_t *ma, const matrix_t *mb){
  int complete_me= 1;
  if ( (mb->rows != ma->rows) || (mb->cols != ma->cols) ){
      return -E_SIZE_ERROR;
  }

  else{
     // for(int i=0;i<(mb->matriz)*(mb->cols);i++){
	  //if ( mb->contents[i] !=  ma->contents[i])
	  //if ((mb->contents[i] - ma->contents[i]) >=  V_DELTA_PRECS)
    for (int i = 0; i < ma->rows; x++) {
      for (int j = 0; j < ma->cols; y++) {
        if (ma->matriz[i][j] != mb->matriz[i][j]){
          return -E_SIZE_ERROR;
        } //retorna 0 si son diferentes
      }
    }
	  
      return -E_OK; //retorna 1 si son iguales
	  }
}


error_t free_matrix(matrix_t **m)
{
  if(m!=NULL){
  int i;
    for(i = 0; i < *m->rows; i++)
        FREE(*m->cols[i]);
    FREE(*m->cols);
    FREE(*m);
    return -E_OK;
  }
  return -E_NOTIMPL_ERROR;      
}

error_t clear_matrix(matrix_t *m)
{
  int i,j;
  if (m!=NULL){
  for(int i=0; i<(m->rows); i++ ){ 
    for(int j=0; j<(m->cols); j++ ){
      m->matriz[i][j]=0;
    }
  }
     return -E_OK;
  }
  else
    return -E_ALLOC_ERROR;

  return -E_NOTIMPL_ERROR;      
}
  
error_t get_row(unsigned int pos, const matrix_t *ma, list_t *l)
{
  int j;
  list_t aux;
  if((pos<ma.rows)&&(pos>=0)){
    if(ma!=NULL)&&(l!=NULL){
    list_new(aux);
    for(int j=0; j<(ma->cols); j++ ){
      l=list_append(aux,m->matriz[pos][j]);
    }
    destroy_list(aux);
    return -E_OK;
    }
    return -E_NOTIMPL_ERROR;  
  }
  return -E_SIZE_ERROR;

      
}

error_t get_col(unsigned int pos, const matrix_t *ma, list_t *l)
{
  int i;
  list_t aux;
  if((pos<ma.cols)&&(pos>=0)){
    if(ma!=NULL)&&(l!=NULL){
    list_new(aux);
    for(int i=0; i<(ma->rows); j++ ){
      l=list_append(aux,m->matriz[i][pos]);
    }
    destroy_list(aux);
    return -E_OK;
    }
    return -E_NOTIMPL_ERROR;  
  }
  return -E_SIZE_ERROR;
  
}

error_t matrix2list(const matrix_t *ma, list_t *l)
{
    int i,j;
    list_t aux;
    if (ma!=NULL)&&(l!=NULL){ 
      list_new(aux);
      for(int i=0; i<(ma->rows); i++ ){ 
        for(int j=0; j<(ma->cols); j++ ){
          l=list_append(aux,ma->matriz[i][j]);
        }
      }
      destroy_list(aux);
      return -E_OK;
    }

  return -E_NOTIMPL_ERROR;      
}

error_t resize_matrix(unsigned int newmatriz, unsigned int newcols, matrix_t **ma)
{
  return -E_NOTIMPL_ERROR;  
}



void redimensionar(int **ma, int newrows,int newcols){


int n=newrows; 
int m=newcols;
int *aux = matriz_create (n, m, *ma-> fmt );//creo la matriz nueva
if(newrows=<*ma->rows)&&(newcols=<*ma->cols){// en caso de que la nueva dimension sea mas grande que la actual
    
    for(int i = 0; i <newrows; i++){ 
      for(int j = 0; j <newcols; j++){
            aux[i][j] = *ma[i][j];
      }
    }
}

else{
      if(newrows>*ma->rows)
        newrows=newrows-*ma->rows;


}
    free_matrix(ma);//deberia eliminar y liberar la memoria de la vieja matriz 

   ma=&aux; //y actualizar la matriz que devuelvo

   
}

void redimensionar(int vectord, int &longitud)/ Incrementamos en 5 el tamaño del array dinamico */
{
    longitud = longitud + 5;

    int *aux = new int[longitud];

    for(int i = 0; i < longitud - 5 ; i++)
    {
        aux[i] = vectord[i];
    }

    delete[] vectord;

    vectord = aux;
}
