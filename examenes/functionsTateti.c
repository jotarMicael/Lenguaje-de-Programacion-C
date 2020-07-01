
#include <stdio.h>
#include "matriz.h"

void intro_Primer(char p[5][5]){
	int i,j;
	char aux='V';

	for(i=0; i<=4;i++){
		for(j=0; j<=4;j++){

			p[i][j]=aux;
		}}
}


void pintar_Tateti(char p[5][5]){
	int i,j;

	for(i=0; i<=4;i++){
		for(j=0; j<=4;j++){

			printf(" %c |", p[i][j]);
		}

		printf("\n--------------------\n");


	}
}

void loop(char p[5][5]){


	intro_Primer(p);
	pintar_Tateti(p);
}

void colocar(char tateti[5][5]){
	char aux,i,j;
	int k;
	do{

		do{
			printf("Coloca una ficha: ");
			fflush(stdin);
			scanf("%c",&aux);

		}while (aux <1 || aux > 25);

	k = 1;

	for (i=1; i<=25; i++){
		if(i==aux){
			if( tateti[i][j] == 'X' || tateti[i][j] == 'O' ){

				K=0
				printf("la casilla esta ocupada!\n");
			}


		}

	}

	}while (k==1)




}


