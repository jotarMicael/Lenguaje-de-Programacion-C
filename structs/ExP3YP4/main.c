#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "conjunto_t.h"

//Compilacion: gcc main.c conjunto_t_func.c -o main.out
 


int main(){

conjunto_t *conj1,conj2,nuevo;

conj1=conjunto_create();
conj2=conjunto_create();

nuevo=conjunto_intersection(conj1,conj2);

conjunto_in(conj1,34);
conjunto_in(conj1,46);
conjunto_in(conj1,88);
conjunto_in(conj1,56);
conjunto_in(conj1,13);

conjunto_in(conj2,23);
conjunto_in(conj2,76);
conjunto_in(conj2,75);
conjunto_in(conj2,34);
conjunto_in(conj2,56);

conjunto_remove(conj1,34);
conjunto_remove(conj2,56);

conjunto_print(conj1);
conjunto_print(conj2);

conjunto_free(conj1);
conjunto_free(conj2);
conjunto_free(nuevo);











}