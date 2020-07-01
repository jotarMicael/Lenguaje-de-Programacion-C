#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "register_struct.h"


int main()
{

register_ty persona;

char *nombre=(char*)malloc(10*sizeof(char));

char *apellido=(char*)malloc(10*sizeof(char));

char *dni=(char*)malloc(10*sizeof(char));

char *direccion=(char*)malloc(10*sizeof(char));

printf("Introduzca un nombre:\n");
scanf("%s", nombre);

printf("Introduzca un apellido:\n");
scanf("%s", apellido);

printf("Introduzca un dni:\n");
scanf("%s", dni);

printf("Introduzca un direccion:\n");
scanf("%s", direccion);

create_register(&persona,nombre,apellido,dni,direccion);

nombre=getter_NameRegister(&persona);

puts(nombre);

free(nombre);

puts(nombre);





}