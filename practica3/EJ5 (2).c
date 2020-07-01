#include <stdio.h>

int main() {

int arr1[5];
int arr2[5];
int arr3[5];
int num;
int i;

for (i=0; i<6; i++){

printf("Ingrese un numero\n");
scanf ("%d\n", &num);
arr1[i]= num;

printf("Ingrese un numero\n");
scanf ("%d\n",&num );
arr2[i]= num;

}

for (i=0; i<6; i++){

arr3[i]= arr1[i]+arr2[i];
printf("La suma de la posicion %d es: %d\n",i, arr3[i] );

}





}