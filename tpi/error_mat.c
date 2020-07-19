#include "error_mat.h"

int output_error(FILE *fp, error_t e)
{
  fp = fopen ( "errors.txt", "a" ); 
  switch (e)
    {
  case -E_OK:
    fprintf(fp, "NO hay error (OK)");
    return E_OK;
  case -E_READ_ERROR:
    fprintf(fp, "Error de lectura (READ)");
    return E_READ_ERROR;
  case -E_FORMAT_ERROR:
    fprintf(fp, "Error de formato (FORMAT)");
    return -E_FORMAT_ERROR;
  case -E_ALLOC_ERROR:
    fprintf(fp, "Error de memoria (ALLOC)");
    return E_ALLOC_ERROR;
  case -E_SIZE_ERROR:
    fprintf(fp, "Error de dimension (SIZE)");
    return E_SIZE_ERROR;
  case -E_WRITE_ERROR:
    fprintf(fp, "Error de escritura (WRITE)");
    return E_WRITE_ERROR;
  case -E_NOTIMPL_ERROR:
    fprintf(fp, "No implementado aun (NOTIMPL)");
    return E_NOTIMPL_ERROR;
  case -E_FILE_ERROR:
    fprintf(fp, "Error de archivo (FILE)");
    return E_FILE_ERROR;
  case -E_INVALID_ERROR:
    fprintf(fp, "Error de parametro (PARAMETER)");   
    return E_INVALID_ERROR;
  case -ERROR_INCOMPATIBLE_MATRICES:
    fprintf(fp, "Error de matrices (INCOMPATIBLES)");   
    return ERROR_INCOMPATIBLE_MATRICES;
  default:
    fprintf(fp, "Error desconocido (UNKNOWN)");
    return E_NOTIMPL_ERROR;
    }
  fclose(fp);
}

/*** EOF ***/
