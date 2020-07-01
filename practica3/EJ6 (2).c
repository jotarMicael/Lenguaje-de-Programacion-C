#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char cadena[200];
    int i = 0;
    printf("Introduce una cadena de texto: \n");
    fgets(cadena, 200, stdin);
    printf("\nLa cadena introducida es: %s\n\n", cadena);
    printf("La cadena al rev\x82s es:\n\t");
    for (i=strlen(cadena); i>=0; i--){
        printf("%c", cadena[i]);
    }
    puts("");
    return 0;
}