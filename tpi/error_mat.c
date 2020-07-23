#include "error_mat.h"

int output_error(FILE *fp, error_t e)
{
  fp = fopen ( "errors.txt", "w" ); 
  switch (e)
    {
  case E_OK:
    fprintf(fp, "NO hay error (OK)");
    fclose(fp);
    return E_OK;
  case E_READ_ERROR:
    fprintf(fp, "Error de lectura (READ)");
    fclose(fp);
    return E_READ_ERROR;
  case E_FORMAT_ERROR:
    fprintf(fp, "Error de formato (FORMAT)");
    fclose(fp);
    return -E_FORMAT_ERROR;
  case E_ALLOC_ERROR:
    fprintf(fp, "Error de memoria (ALLOC)");
    fclose(fp);
    return E_ALLOC_ERROR;
  case E_SIZE_ERROR:
    fprintf(fp, "Error de dimension (SIZE)");
    fclose(fp);
    return E_SIZE_ERROR;
  case E_WRITE_ERROR:
    fprintf(fp, "Error de escritura (WRITE)");
    fclose(fp);
    return E_WRITE_ERROR;
  case E_NOTIMPL_ERROR:
    fprintf(fp, "No implementado aun (NOTIMPL)");
    fclose(fp);
    return E_NOTIMPL_ERROR;
  case E_FILE_ERROR:
    fprintf(fp, "Error de archivo (FILE)");
    fclose(fp);
    return E_FILE_ERROR;
  case E_INVALID_ERROR:
    fprintf(fp, "Error de parametro (PARAMETER)"); 
    fclose(fp);  
    return E_INVALID_ERROR;
  case ERROR_INCOMPATIBLE_MATRICES:
    fprintf(fp, "Error de matrices (INCOMPATIBLES)"); 
    fclose(fp);  
    return ERROR_INCOMPATIBLE_MATRICES;
  default:
    fprintf(fp, "Error desconocido (UNKNOWN)");
    fclose(fp);
    return E_NOTIMPL_ERROR;
    }
  fclose(fp);
}

/*** EOF ***/
