#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"matriz.h"

//carga de un register
void cargarMatriz(char matriz_t[DIM] [DIM]){

	for(int i=0; i<=DIM; i++){
		for(int j=0; j<=DIM; j++){
			matriz_t[i][j]=i+j;
		}
	}


}
//getter correcto de un campo del register

void imprimirMatriz(char matriz_t[DIM] [DIM]){

	for(int i=0; i<=DIM; i++){
		for(int j=0; j<=DIM; j++){
			printf("La posicion [%d][%d] , tiene almacenado: (%d) \n",i,j, matriz_t[i][j]);
		}
	}


}