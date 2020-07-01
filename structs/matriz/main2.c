#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "matriz.h"


int main(int argc, char const *argv[])
{

if((argc==2)&&(strcmp(argv[1], "ok") == 0)){

char *p;

p=&matriz[0][0];

cargarMatriz(p);
imprimirMatriz(p);

return 0;
}

else
	printf("Debe presionar ok para que el programa funcione de manera correcta\n");
	printf("%d\n", argc);
	printf("%s\n", argv [1] );
	return 1;
}