#include <stdio.h>
#include <string.h>

#include "alumno_operations.c"



int main()
{
	
alumno alumno1;


alumno1= set_alumno(alumno1);

char v[sizeof(alumno1)];

char* cadena=v;

printf("%d\n", strlen(cadena));

convert_String(alumno1,cadena);

print_alumno(alumno1);



printf("%s\n", cadena);

}