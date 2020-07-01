
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct r_alumno {

char* nombre;
char* apellido;
char* fecha;
char* legajo;
char* dni;
int* n_dni;


};


typedef struct r_alumno alumno;

alumno set_alumno(alumno alumno1) {

alumno1.nombre= malloc(sizeof(char)*20);
alumno1.apellido= malloc(sizeof(char)*20);
alumno1.fecha= malloc(sizeof(char)*20);
alumno1.legajo= malloc(sizeof(char)*20);
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

int main(){

alumno alumno1,alumno2;

alumno1= set_alumno(alumno1);

printf("%s\n", alumno1.nombre);
printf("%s\n", alumno1.apellido);
printf("%s\n", alumno1.fecha);
printf("%s\n", alumno1.legajo);
printf("%s\n", alumno1.dni);
printf("%d\n", alumno1.n_dni);


alumno2=alumno1;
printf("%s\n", alumno2.nombre);
printf("%s\n", alumno2.apellido);
printf("%s\n", alumno2.fecha);
printf("%s\n", alumno2.legajo);
printf("%s\n", alumno2.dni);
printf("%d\n", alumno2.n_dni);

strcpy( alumno1.nombre, "DOILA");

printf("%s\n", alumno1.nombre);
printf("%s\n", alumno1.apellido);
printf("%s\n", alumno1.fecha);
printf("%s\n", alumno1.legajo);
printf("%s\n", alumno1.dni);
printf("%d\n", alumno1.n_dni);

printf("%s\n", alumno2.nombre);
printf("%s\n", alumno2.apellido);
printf("%s\n", alumno2.fecha);
printf("%s\n", alumno2.legajo);
printf("%s\n", alumno2.dni);
printf("%d\n", alumno2.n_dni);

free(alumno1);
free(alumno2);

}

