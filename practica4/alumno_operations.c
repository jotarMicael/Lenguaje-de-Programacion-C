#ifndef A0_T
#define AO_T


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#include "alumno_t.h"

alumno set_alumno(alumno alumno1) {

alumno1.nombre= malloc(sizeof(char)*20);
alumno1.apellido= malloc(sizeof(char)*20);
alumno1.fecha= malloc(sizeof(char)*15);
alumno1.legajo= malloc(sizeof(char)*15);
alumno1.dni= malloc(sizeof(char)*20);
alumno1.n_dni= malloc(sizeof(int)*20);

strcpy( alumno1.nombre, "Micael");
strcpy( alumno1.apellido, "Jotar" );
strcpy( alumno1.fecha, "30/12/1998");
strcpy( alumno1.legajo, "15388/6");
strcpy( alumno1.dni, "dni");

alumno1.n_dni=41665458;

return alumno1;

}

void print_alumno(alumno alumno1){

printf("%s\n", alumno1.nombre);
printf("%s\n", alumno1.apellido);
printf("%s\n", alumno1.fecha);
printf("%s\n", alumno1.legajo);
printf("%s\n", alumno1.dni);
printf("%d\n", alumno1.n_dni);



}

void convert_String(alumno alumno1, char* p){



strcpy(p, alumno1.nombre);
strcat(p, " ");
strcat(p, alumno1.apellido);
strcat(p, " ");

}

#endif

