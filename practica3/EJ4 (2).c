#include <stdio.h>

int main(){

int aux,i,numposiciones,x;
int vector[]= {54,32,67,56,34,87,12,89,34};
numposiciones= 8;
    printf("\nORDENANDO DE FORMA ASCENDENTE: \n\n");

        for(i=0;i<=numposiciones-1;i++){
            for(x=i+1;x<numposiciones;x++){
            	if(vector[i]>vector[x]){
                	aux=vector[i];
                	vector[i]=vector[x];
                	vector[x]=aux;
            }
        }
    }


for(i=0;i<=numposiciones;i++)

	printf("%d\n\n", vector[i] );
}