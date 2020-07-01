#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "matriz.h"


int main(){

char *p;

p=&matriz[0][0];

cargarMatriz(p);
imprimirMatriz(p);


}