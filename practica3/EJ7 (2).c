#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

char cadena[50];

printf("Ingrese una cadena:\n");
fgets(cadena,50,stdin);
printf("el tamaño de la cadena es: %ld\n", strlen(cadena) );

}