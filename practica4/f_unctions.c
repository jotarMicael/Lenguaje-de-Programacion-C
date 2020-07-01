#ifndef FU_T
#define FU_T

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

typedef struct fecha fecha_t;

fecha_t get_struct(fecha_t fecha1){

fecha1.dia=1;
fecha1.mes=1;
fecha1.anio=1970;


return fecha1;
}

#endif