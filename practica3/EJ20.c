#include <stdio.h>
#include <stlib.h>
#include <string.h>


char *crear_pila(){

char *pila;

return pila;

}


int destruir_pila(char *pila){


	free(pila);
	return 1;
}

void apilar(char *pila,char *pilaFin, char caracter, int *cant){

	if(pila!=pilaFin)
		pila = realloc(pila,1+cant);
	
	else
		pila = malloc(sizeof(char)*1);

	pila[cant]= caracter;
	pilaFin = &pila[cant];
	printf("apilado exitosamente\n");
	cant++

}

void desapilar(char*pilaFin,char*){
	if(pila != pilaFin)
		pilaFin= (pilaFin-1);
	else
		printf("No hay elementos en la pila\n");




}