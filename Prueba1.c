#include <stdio.h>
#include <stdbool.h>


int main(){

int c,cant,espacios;

cant= 0;
espacios=0;
c=getchar();
while (c != EOF) {
		if (c == '\n')
			espacios++;

		else
		cant++;
		
        putchar(c);
		c=getchar();




}

printf("la cantidad de caracteres es: %d\n", cant);
printf("la cantidad de saltos de lineas es: %d\n", espacios );






}