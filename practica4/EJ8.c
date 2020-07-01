#ifndef ST_T
#define ST_T



#include <stdio.h>
#include <string.h>

struct r_alumno {

char nombre[10];
char apellido[15];
int fecha[15];
char legajo[15];
char dni[3];
int n_dni;


};


typedef struct r_alumno alumno;



int main(){

alumno alumno1,alumno2;

strcpy( alumno1.nombre, "Micael" );
strcpy( alumno1.apellido, "Jotar" );
strcpy( alumno1.fecha, "30/12/1998");
strcpy( alumno1.legajo, "15388/6");
strcpy( alumno1.dni, "dni");
alumno1.n_dni='41665458';


alumno2=alumno1;


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

strcpy( alumno1.nombre, "Joaquin" );

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

}

#endif