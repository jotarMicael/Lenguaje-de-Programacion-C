#include <stdio.h>

struct integers{

int a;
char b;

};

typedef struct integers ints;


int main(){


ints numbers;

numbers.a= 3;
numbers.b=4;

printf("el tamaño del entero del register es: %ld\n", sizeof(numbers.a) );
printf(" el tamaño del char del register es: %ld\n", sizeof(numbers.b) );

printf("el tamaño del register completo es: %ld\n", sizeof(numbers) );




}