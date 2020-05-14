#include <stdio.h>
#include <stdlib.h>


int main()
{

	int car;
    int cant=0;
    int lineas=0;


    printf("Ingrese la cadena de caracteres y cuando desee terminar pulse Ctrl+d.\n");
    (car= getchar());

	while ( car != EOF){
            if ((car)== '\n') 
            	lineas++;
            else
            {
			cant++;

			putchar(car);

		}
		(car= getchar());
	}
	lineas++;
	printf("\n la cantidad de caracteres es: %d\n", cant);
	printf("\n la cantidad de lineas es: %d\n", lineas);

}