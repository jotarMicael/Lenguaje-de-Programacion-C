#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"
#include "list_t.h"


#define FREE(p)   do { free(p); (p) = NULL; } while(0)



error_t set_ffmt_matrix(matrix_t *m, matrix_fmt_t fmt)
{
  if(m!=NULL){
    m->fmt=fmt;
    return -E_OK;
  }
  return -E_NOTIMPL_ERROR;      
}

matrix_t *matrix_create(int n, int m, matrix_fmt_t c)
{
  
    matrix_t *M;
    
    M=malloc(sizeof(matrix_t));

    if(M == NULL)
    {
        return NULL;
    }

    M->rows = n; //filas  
    M->cols = m; //columnas

    if(c==1)
      set_ffmt_matrix(M,1);
    else
      set_ffmt_matrix(M,2);

    M->matriz = malloc(n * sizeof(T_TYPE));
    if(M->matriz== NULL)
        return NULL;

    for(int i = 0; i < n; i++)
    {
        M->matriz[i] = malloc(m * sizeof(T_TYPE));
        if(M->matriz[i] == NULL){
            return NULL;
        }

    }
    
    return M;

}

void matrix_print(matrix_t *M)
{
    printf("Tipo: M%d\n", M->fmt);
    for(int n=0; n < get_rows(M); n++)
    {
        for(int m=0; m< get_cols(M); m++)
        {
            printf("%.2f\t", M->matriz[n][m]);
        }
        printf("\n");
    }
}

unsigned int get_rows(const matrix_t *ma)
{
  if (ma!=NULL)
    return ma->rows;
  else
     return -E_NOTIMPL_ERROR;
}

unsigned int get_cols(const matrix_t *ma)
{
  if (ma!=NULL)
    return ma->cols;
  else
     return -E_NOTIMPL_ERROR;
}

error_t get_ffmt_matrix(matrix_t *m, matrix_fmt_t *fmt)
{
  if(m!=NULL){
    fmt=malloc(sizeof(matrix_fmt_t));
    *(fmt)=m->fmt;
    return -E_OK;
  }
  return -E_NOTIMPL_ERROR;      
}

error_t read_matrix(char *filename,FILE *fp, matrix_t **m){

 T_TYPE dvalue;
 char buf[N_BUF_LENGTH];
 int rows,cols;
 matrix_fmt_t fmt;

 
 // Open file
  
   if (!(fp = fopen(filename,"rb")))
     return E_FILE_ERROR; 

 //check the matrix header format
 
 if ((fgets(buf, N_BUF_LENGTH, fp))==NULL)
    {
      fprintf(stderr, "Error al leer header format \n");
      return E_FORMAT_ERROR;      
    }
 if (buf[0] != 'M')
   {
     fprintf(stderr, "Error de formato, debe ser ('M1 o M2')\n");
     return E_FORMAT_ERROR;
   }
if ((buf[0]=='M')&&(buf[1]=='1'))
    fmt=M1;//fmt=M1
else{
      if((buf[0]=='M')&&(buf[1]=='2'))
        fmt=M2;//fmt=M2
      else
        return E_FORMAT_ERROR;
    }

 /****** 
 //Skip comments checking
 // discard_comments(fp);
 ******/
 if ((fgets(buf, N_BUF_LENGTH, fp))==NULL)
    {
      fprintf(stderr, "Error al leer header format 2\n");
      return E_FORMAT_ERROR;      
    }
while(buf[0]==C_COMMENT){
     fgets(buf, N_BUF_LENGTH, fp); //leo todos los comentarios

}

if(fseek(fp, INIT_C_R, SEEK_CUR)!=0){
  fprintf(stderr, "Error al leer header format 3\n");
  return E_FORMAT_ERROR; 
}

char c;
if(fscanf(fp,"%d",&rows) == 1){
  fscanf(fp,"%c",&c); //leo el espacio
  if(fscanf(fp,"%d",&cols) == 1){
     (*m)=matrix_create(rows,cols,fmt);
  }
}
else{
  fprintf(stderr, "Error al leer las dimensiones 1\n");
  return E_SIZE_ERROR;   
}
if(*m==NULL){
  fprintf(stderr, "Error al crear la matriz\n");
  return E_ALLOC_ERROR;
}

 //read matrix size information

 if((get_rows(*m)==E_NOTIMPL_ERROR)||(get_cols(*m)==E_NOTIMPL_ERROR)){
  fprintf(stderr, "Error en las filas y/o columnas de la matriz \n");
  return E_READ_ERROR;
 }
 
 if (getc(fp) == EOF)
      {
        return E_READ_ERROR;
      }

 
 if((*m)->fmt==1){ //proceso M1

      for(int i=0; i<(get_rows(*m)); i++ ){ //Asigno valores al archivo , cant de filas y columnas exactas que posee la matriz
          for(int j=0; j<(get_cols(*m)); j++ ){
            fscanf(fp,"%lf",&dvalue); 
            (*m)->matriz[i][j]=dvalue;
            fscanf(fp,"%c",&c); //leo el espacio entre cada double
            
          }
        }

 }
 else{

    unsigned int len= get_rows(*m) * get_cols(*m);

    // temporal, para leer los datos todos seguidos
    double *data = (double *) malloc(sizeof(double) * len);

    if (!data){
      return E_ALLOC_ERROR;
    }
  
        if (fread(data, sizeof(double), len, fp) != len)
        {
            free(data);
            return E_ALLOC_ERROR;
        }
        if (ferror(fp) || (!feof(fp) && (getc(fp) != EOF)))
        {
            free(data);
            return E_ALLOC_ERROR;
        } 

        for(int i=0; i<(get_rows(*m)); i++ ){ 
          for(int j=0; j<(get_cols(*m)); j++ ){
              (*m)->matriz[i][j] = data[i * cols + j];
          }
        }

  }

 fclose(fp);
 return E_OK;
}



error_t write_matrix(char *filename,FILE *fp, const matrix_t *m)
{
  if(m!=NULL){
     if (!(fp=fopen(filename,"wb")) ){
        fprintf(stderr, "Error abrir archivo de escritura \n");
        return -E_FILE_ERROR;    
      }
      //check the matrix header format
    if ((m->fmt!=1)&&(m->fmt!=2)) { 
      fprintf(stderr, "Error al leer header format 2\n");
      fclose(fp); 
      return -E_FORMAT_ERROR;      
    }
     if ((m->fmt==1))
        fprintf(fp, "%s\n","M1");
     else
        fprintf(fp, "%s\n","M2");  //escribo el formato de la matriz

    
    //read matrix size information
      if(sizeof(get_cols(m))!=sizeof(int)&&(sizeof(get_rows(m))!=sizeof(int))){
        fprintf(stderr, "Error en dimensiones \n");
        fclose(fp); 
        return -E_SIZE_ERROR;
      }
      fprintf(fp, "%d",get_rows(m));
      fprintf(fp, "%c",' ');
      fprintf(fp, "%d\n",get_cols(m)); //escribo filas y columnas en archivo

      

      if(m->fmt==1){ //proceso M1
          for(int i=0; i<get_rows(m); i++ ){ //Asigno valores al archivo , cant de filas y columnas exactas que posee la matriz
                for(int j=0; j<(get_cols(m)); j++ ){
                  fprintf(fp,"%.2f",m->matriz[i][j]);
                  fprintf(fp,"%c",' ');  
                }
                  fprintf(fp,"%c",'\n');
          }
               

      }

      else{ 
        // los datos en formato binario se escriben uno a uno
        unsigned int count = get_rows(m) * get_cols(m);
        unsigned int written = 0;
        for (int i = 0; i < get_rows(m); i++)
        {
            for (int j = 0; j < get_cols(m); j++)
            {
                if (fwrite(&m->matriz[i][j], sizeof(T_TYPE), 1, fp) != 1)
                    return E_READ_ERROR;
                written++;
            }
        }
        if (count != written)
            return E_WRITE_ERROR;
      }
    
    fclose(fp); 
    return -E_OK;
  }
  fprintf(stderr, "la matriz esta vacia\n");
  return -E_ALLOC_ERROR;
}    


error_t dup_matrix(const matrix_t *m_src, matrix_t **m_dst)
{
  *(m_dst)=matrix_create(get_rows(m_src),get_cols(m_src),m_src->fmt);
  if((*(m_dst)!=NULL)&&(m_src!=NULL)){
     for(int i=0; i<(get_rows(m_src)); i++ ){ //Asigno valores al archivo , cant de filas y columnas exactas que posee la matriz
        for(int j=0; j<(get_cols(m_src)); j++ ){
           (*m_dst)->matriz[i][j]=m_src->matriz[i][j];
        }
      }
     return -E_OK;
  }
  return -E_NOTIMPL_ERROR;      
}


error_t sum(const matrix_t *ma, const matrix_t *mb, matrix_t **mc)
{
  if(get_rows(ma)==get_rows(mb)){
    if(get_cols(ma)==get_cols(mb)){
        *mc=matrix_create(get_rows(ma),get_cols(ma),ma->fmt);
        for(int i=0; i<(get_rows(ma)); i++ ){ 
          for(int j=0; j<(get_cols(ma)); j++ ){
            (*mc)->matriz[i][j]=(ma->matriz[i][j])+(mb->matriz[i][j]);
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

error_t sum_inplace(const matrix_t *m_src, matrix_t **m_dst)
{
  if((m_src!=NULL)&&(*m_dst!=NULL)){
  if(get_rows(m_src)==get_rows(*m_dst)){
    if(get_cols(m_src)==get_cols(*m_dst)){
        for(int i=0; i<(get_rows(m_src)); i++ ){ 
          for(int j=0; j<get_cols(m_src); j++ ){
            (*m_dst)->matriz[i][j]=(m_src->matriz[i][j])+((*m_dst)->matriz[i][j]);
          }
        }
        return E_OK;
    }
    else
      return E_SIZE_ERROR;
  }
  else
    return E_SIZE_ERROR;     
}
else
    return E_ALLOC_ERROR;
}

error_t mult_scalar(T_TYPE a, const matrix_t *mb, matrix_t **mc)
{
    if(mb!=NULL){
        (*mc)=matrix_create(get_rows(mb),get_cols(mb),mb->fmt);
        for(int i=0; i<(get_rows(mb)); i++ ){ 
          for(int j=0; j<(get_cols(mb)); j++ ){
            (*mc)->matriz[i][j]=(mb->matriz[i][j])*a;
          }
        }
          return -E_OK;
    }
    return -E_ALLOC_ERROR; 
  
 }
      

error_t mult_scalar_inplace(T_TYPE a, matrix_t **m_dst)
{
  if ((*m_dst)!=NULL){
  for(int i=0; i<(get_rows(*m_dst)); i++ ){ 
    for(int j=0; j<(get_cols(*m_dst)); j++ ){
      (*m_dst)->matriz[i][j]=((*m_dst)->matriz[i][j]*(a));
    }
  }
     return -E_OK;
  }
  else
    return -E_ALLOC_ERROR;
          
}

error_t create_and_fill_matrix(unsigned int rows, unsigned int cols, T_TYPE a, matrix_t **mb)
{
  *(mb)=matrix_create(rows,cols,M1);
  if((*mb)!=NULL){
    for(int i=0; i<(get_rows(*mb));i++){ 
          for(int j=0; j<(get_cols(*mb));j++){
            (*mb)->matriz[i][j]=a;
          }
    }
    return -E_OK;
  }

  return -E_ALLOC_ERROR;

}


error_t null_matrix(unsigned int rows,unsigned int cols, matrix_t **mc)
{

  return create_and_fill_matrix(rows, cols, V_NULL, mc);
}


error_t idty_matrix(unsigned int n, matrix_t **m)
{
  *(m)=matrix_create(n,n,M1);
  if((*m)!=NULL){
    for(int i=0; i<(get_rows(*m)); i++ ){ 
          for(int j=0; j<(get_cols(*m)); j++ ){
            if(i==j)
              (*m)->matriz[i][j]=V_ONE;
            else
              (*m)->matriz[i][j]=V_NULL;  
          }
    }
    return -E_OK;
  }

  return -E_ALLOC_ERROR;     
}

error_t mult(const matrix_t *ma, const matrix_t *mb, matrix_t **mc)
{
  float fsum;
    
    if((ma==NULL)&&(mb==NULL)){

       return -E_ALLOC_ERROR;
    }
  

    if(get_cols(ma) != get_rows(mb))
    {
        printf("Las matrices deben ser --> columnas ma == filas mb\n");
        return -E_SIZE_ERROR;
    }

    *mc=matrix_create(get_rows(ma),get_cols(mb),ma->fmt);
    if((*mc) == NULL)
    {
        return -E_ALLOC_ERROR;
    }
    for(int n = 0; n < get_rows(*mc); n++)
    {
        for(int  m = 0; m < get_cols(*mc); m++)
        {
            fsum = 0;
            for(int i=0; i<get_cols(*mc); i++)
            {
                fsum = fsum + ((ma->matriz[n][i]) * (mb->matriz[i][m]));
            }
            (*mc)->matriz[n][m] = fsum;
        }
    }
    
    return -E_OK;    
}

error_t set_elem_matrix(unsigned int row, unsigned int col, T_TYPE value, matrix_t **m)
{
  if (*m!=NULL){
      if((row<=get_rows(*m))&&(col<=get_cols(*m))){
        (*m)->matriz[row][col]=value;
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
      if((row<=get_rows(m))&&(col<=get_cols(m))){
        (*value)=m->matriz[row][col];
        return -E_OK;
      }
      else
        return -E_SIZE_ERROR;
  }
  return -E_NOTIMPL_ERROR;   
    
}

error_t cmp_matrix(const matrix_t *ma, const matrix_t *mb){

  if ( (get_rows(mb) != get_rows(ma)) || (get_cols(mb) != get_cols(ma)) ){
      return -E_SIZE_ERROR;
  }

  else{
    for (int i = 0; i < get_rows(mb); i++) {
      for (int j = 0; j <get_cols(mb); j++) {
        if ((ma->matriz[i][j])!=(mb->matriz[i][j])){
          return ERROR_INCOMPATIBLE_MATRICES;
        } //retorna 8 si son diferentes
      }
    }
      return E_OK; //retorna 1 si son iguales
	  }
}


error_t free_matrix(matrix_t **m)
{
    if(*m!=NULL){
    for(int i = 0; i < get_rows(*m); i++){ 
       FREE((*m)->matriz[i]);
       
    }
    FREE((*m)->matriz);
    FREE(*m);
    *m=NULL;
  }
 return E_OK;

  
}

error_t clear_matrix(matrix_t *m)
{
  if (m!=NULL){
  for(int i=0; i<(get_rows(m)); i++ ){ 
    for(int j=0; j<(get_cols(m)); j++ ){
      m->matriz[i][j]=V_NULL;
    }
  }
     return -E_OK;
  }
  else
    return -E_ALLOC_ERROR;

  return -E_NOTIMPL_ERROR;      
}
  
error_t get_row(unsigned int pos, const matrix_t *ma, tpuntero *l)
{
  if((pos<get_rows(ma))&&(pos>=0)){
    if((ma!=NULL)&&(l!=NULL)){
    for(int j=0; j<(get_rows(ma)); j++ ){
      insert_InList(l,ma->matriz[pos][j]);
    }
    return -E_OK;
    }
    return -E_NOTIMPL_ERROR;  
  }
  return -E_SIZE_ERROR;

      
}

error_t get_col(unsigned int pos, const matrix_t *ma, tpuntero *l)
{
  if((pos<ma->cols)&&(pos>=0)){
    if((ma!=NULL)&&(l!=NULL)){
    for(int i=0; i<(get_rows(ma)); i++ ){
      insert_InList(l,ma->matriz[i][pos]);
    }
    return -E_OK;
    }
    return -E_NOTIMPL_ERROR;  
  }
  return -E_SIZE_ERROR;
  
}

error_t matrix2list(const matrix_t *ma, tpuntero *l)
{
   
    if ((ma!=NULL)&&(l!=NULL)){
      
      for(int i=0; i<(get_rows(ma)); i++ ){ 
        for(int j=0; j<(get_cols(ma)); j++ ){
          insert_InList(l,ma->matriz[i][j]);
        }
      }
      return -E_OK;
    }

  return -E_NOTIMPL_ERROR;      
}

error_t resize_matrix(unsigned int newrows, unsigned int newcols, matrix_t **ma)
{
  matrix_t **mb=NULL;
  error_t ok;


  if(*(ma)!=NULL){
    if((newrows<get_rows(*ma)) || (newcols<get_cols(*ma))){
      if(newrows<get_rows(*ma))
          (*ma)->rows=newrows;
      if(newcols<get_cols(*ma))
          (*ma)->cols=newcols;       
    }
    ok=create_and_fill_matrix(newrows,newcols,V_NULL,mb);
    if(ok==0){
    for(int i=0; i<(get_rows(*ma)); i++ ){ 
          for(int j=0; j<(get_cols(*ma)); j++ ){
          (*mb)->matriz[i][j]=(*ma)->matriz[i][j];
          }
    }

    free_matrix(ma); ma=mb;
    return -E_OK;

    }
    return -E_ALLOC_ERROR; 
  }

  return -E_NOTIMPL_ERROR;  

}



   




