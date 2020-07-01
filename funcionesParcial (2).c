#include <stdio.h>
#include <stdbool.h>

bool divisible (int a, int b){

	if (a%b == 0)
		return true;

	return false;

}

bool par(int a){


 if (a%2== 0)
 	return true;

 return false;

}

bool impar(int a){


    if(a%2 == 1)

    	return true;
    return false;

}


int main(){



int num1,num2;
bool resultado;

printf("Ingrese un numero: ");

scanf("%d", &num1);

printf("Ingrese otro numero: ");

scanf("%d", &num2);


resultado = divisible(num1,num2);

if(resultado)
	printf("El numero %d es divisible por el numero %d\n",num1,num2);
else

	printf("El numero %d no es divisible por el numero %d\n",num1,num2);

resultado= par(num1);

if(resultado)
	printf("El numero %d es par \n", num1);
else
	printf("El numero %d no es par \n", num1);


resultado= impar(num1);

if(resultado)

	printf("El numero %d es impar \n", num1);
else
	printf("El numero %d no es impar \n", num1);

}