#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"
#include "list_t.h"



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
    int i;
    matrix_t *M;
    
    M = malloc(sizeof(matrix_t));
    if(M == NULL)
    {
        return NULL;
    }

    M->rows = m; //filas  
    M->cols = n; //columnas

    if (c==1)
      set_ffmt_matrix(M,1);
    else
      set_ffmt_matrix(M,2);

    M->matriz = malloc(n * sizeof(float *));
    if(M->matriz== NULL)
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

error_t get_ffmt_matrix(matrix_t *m, matrix_fmt_t  *fmt)
{
  if(m!=NULL){
    fmt=malloc(sizeof(matrix_fmt_t));
    *fmt=m->fmt;
    return -E_OK;
  }
  return -E_NOTIMPL_ERROR;      
}

error_t read_matrix(char *filename,FILE *fp, matrix_t *m){

 T_TYPE dvalue;
 char buf[N_BUF_LENGTH];
 char num[1000];
 int rows,cols,i,j,ni,mj;
 matrix_fmt_t fmt;
 fmt=1;
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
if ((buf[0]=='M')&&(buf[1]=='1'))
    set_ffmt_matrix(m,M1);//fmt=M1
else
    set_ffmt_matrix(m,M2);//fmt=M2;
 /****** 
 //Skip comments checking
 // discard_comments(fp);
 ******/
 if (fgets(buf, sizeof(buf), fp)!=NULL)
    {
      fprintf(stderr, "Error al leer header format\n");
      return -E_FORMAT_ERROR;      
    }
if(buf[0]==C_COMMENT)
     fgets(buf, sizeof(buf), fp); //Buscar forma de volver para atras

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

  rows=get_rows(m);
  cols=get_cols(m);

 if (fscanf(fp, "%d %d",&rows,&cols) != 2) {
   fprintf(stderr, "Error en dimensiones \n");
   return -E_SIZE_ERROR;
 }
  

 if(m->fmt==M1){ //proceso M1
  
      for(ni = 0; ni < get_rows(m); ni++){

          fgets(buf, 100000, fp); 
          i = 0;
          mj = 0;

          while(mj < get_cols(m)) {
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
      while (fread((T_TYPE*)&dvalue, sizeof(T_TYPE), 1, fp) == sizeof(T_TYPE)){
        for(int i=0; i<(get_rows(m)); i++ ){ //Asigno valores al archivo , cant de filas y columnas exactas que posee la matriz
          for(int j=0; j<(get_cols(m)); j++ ){
            m->matriz[i][j]=dvalue;
            fread((T_TYPE*)&dvalue, sizeof(T_TYPE), 1, fp);
        }
      }
        
      }
      fclose(fp); 
      return -E_OK;
 }
}


error_t write_matrix(char *filename,FILE *fp, const matrix_t *m)
{
  if(m!=NULL){
     if (! (fp = fopen(filename,"w")) ){
        perror("Error al abrir archivo de escritura");
        exit(EXIT_FAILURE);  
      }
      //check the matrix header format

    if ((m->fmt!=1)||(m->fmt!=2)) {
      fprintf(stderr, "Error al leer header format\n");
      fclose(fp); 
      return -E_FORMAT_ERROR;      
    }
     if ((m->fmt!=1))
        fprintf(fp, "%c\n",1);
     else
        fprintf(fp, "%c\n",2);  //escribo el formato de la matriz

    
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
                  if(fprintf(fp,"%f",m->matriz[i][j])!=1){
                    fclose(fp); 
                    return -E_WRITE_ERROR;
                  }
                  fprintf(fp,"%c",' ');
                }
              } 

      }

      else{ int *res;
		    res=NULL;
          if(m->fmt==2){ //proceso M2
              for(int i=0; i<(get_rows(m)); i++ ){ //Asigno valores al archivo , cant de filas y columnas exactas que posee la matriz
                for(int j=0; j<(get_cols(m)); j++ ){
                    *res=fwrite(&m->matriz[i][j], sizeof(int), 1, fp);
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
  matrix_t **mb;
  mb=NULL;
  *mb=matrix_create(get_rows(m_src),get_cols(m_src),m_src->fmt);
  if((*mb!=NULL)&&(m_src!=NULL)){
     for(int i=0; i<(get_rows(m_src)); i++ ){ //Asigno valores al archivo , cant de filas y columnas exactas que posee la matriz
        for(int j=0; j<(get_cols(m_src)); j++ ){
           (*mb)->matriz[i][j]=m_src->matriz[i][j];
        }
      }
     m_dst=mb;
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

error_t sum_inplace(const matrix_t *m_src, matrix_t *m_dst)
{
  if((m_src!=NULL)&&(m_dst!=NULL)){
  if(get_rows(m_src)==get_rows(m_dst)){
    if(get_cols(m_src)==get_cols(m_dst)){
        for(int i=0; i<(get_rows(m_src)); i++ ){ 
          for(int j=0; j<get_cols(m_src); j++ ){
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
    if(mb!=NULL){
        *mc=matrix_create(get_rows(mb),get_cols(mb),mb->fmt);
        for(int i=0; i<(get_rows(mb)); i++ ){ 
          for(int j=0; j<(get_cols(mb)); j++ ){
            (*mc)->matriz[i][j]=(mb->matriz[i][j])+a;
          }
        }
          return -E_OK;
    }
    return -E_ALLOC_ERROR; 
  
 }
      

error_t mult_scalar_inplace(T_TYPE a, matrix_t *m_dst)
{
  if (m_dst!=NULL){
  for(int i=0; i<(get_rows(m_dst)); i++ ){ 
    for(int j=0; j<(get_cols(m_dst)); j++ ){
      m_dst->matriz[i][j]=(m_dst->matriz[i][j]+a);
    }
  }
     return -E_OK;
  }
  else
    return -E_ALLOC_ERROR;
          
}

error_t create_and_fill_matrix(unsigned int rows, unsigned int cols, T_TYPE a, matrix_t **mb)
{
  *mb=matrix_create(rows,cols,(*mb)->fmt);
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


error_t null_matrix(unsigned int n, matrix_t **mc)
{

  return create_and_fill_matrix(n, n, V_NULL, mc);
}


error_t idty_matrix(unsigned int n, matrix_t **m)
{
  (*m)=matrix_create(n,n,(*m)->fmt);
  if(*m!=NULL){
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
  

    if(ma->cols != mb->rows)
    {
        printf("Las matrices deben ser columna ma = fila mb");
        return -E_SIZE_ERROR;
    }

    *mc=matrix_create(get_cols(ma),get_rows(mb),ma->fmt);
    if((*mc) == NULL)
    {
        return -E_ALLOC_ERROR;
    }

    (*mc)->cols=ma->cols;
    (*mc)->rows=mb->rows;

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

int cmp_matrix(const matrix_t *ma, const matrix_t *mb){
  if ( (get_rows(mb) != get_rows(ma)) || (get_cols(mb) != get_cols(mb)) ){
      return -E_SIZE_ERROR;
  }

  else{
     // for(int i=0;i<(mb->matriz)*(mb->cols);i++){
	  //if ( mb->contents[i] !=  ma->contents[i])
	  //if ((mb->contents[i] - ma->contents[i]) >=  V_DELTA_PRECS)
    for (int i = 0; i < get_rows(ma); i++) {
      for (int j = 0; j <get_cols(ma); j++) {
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
    for(i = 0; i < get_rows(*m); i++){
        free((*m)->matriz[i]);
    }

    free((*m)->matriz);
    free(*m);
    return -E_OK;
  }
  return -E_NOTIMPL_ERROR;      
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
  
error_t get_row(unsigned int pos, const matrix_t *ma, list_t *l)
{
  list_t aux;
  aux=NULL;
  if((pos<get_rows(ma))&&(pos>=0)){
    if((ma!=NULL)&&(l!=NULL)){
    list_new(aux);
    for(int j=0; j<(get_rows(ma)); j++ ){
      (*l)=list_append(aux,ma->matriz[pos][j]);
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
  list_t aux;
  aux=NULL;
  if((pos<ma->cols)&&(pos>=0)){
    if((ma!=NULL)&&(l!=NULL)){
    list_new(aux);
    for(int i=0; i<(get_rows(ma)); i++ ){
      (*l)=list_append(aux,ma->matriz[i][pos]);
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
    list_t aux;
    aux=NULL;
    if ((ma!=NULL)&&(l!=NULL)){
      list_new(aux);
      for(int i=0; i<(get_rows(ma)); i++ ){ 
        for(int j=0; j<(get_cols(ma)); j++ ){
          (*l)=list_append(aux,ma->matriz[i][j]);
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




   




