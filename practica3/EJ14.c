#include <stdio.h> // ESTE CODIGO TIENE ERRORES
#include <ctype.h>

void capitalizar(char *cadena){
printf("Forma original: ' %s'\n", cadena);
// Pasamos el primer caracter a mayúsculas
cadena[0] = toupper(cadena[0]); // CREO QUE SE DEBE DE ACCEDER A LA POSICION DEL PUNTERO ASI: *(cadena+0) = toupper(*(cadena+0))
printf("Capitalizado: ' %s'\n", cadena);
puts("--");
}

int main(int argc, char **argv){
char cadena1[] = "foo";
char *cadena2 = "bar";
capitalizar(cadena1);
capitalizar(cadena2);
return 0;
}