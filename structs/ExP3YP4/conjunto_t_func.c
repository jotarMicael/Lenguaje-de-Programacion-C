#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"conjunto_t.h"

#define INT_MAX 10;

conjunto_t *conjunto_create(){
int n;
conjunto_t *v;
printf("Ingrese la dimension del arreglo\n");
scanf("%d", &n);

v=malloc((n*sizeof(int))+1);

v[n+1]='\0';

return v;

}


int conjunto_add(conjunto_t *v, int num){
	int i=0;
	while(v[i]!='\0'){

		if(v[i]==num){
			return 0;
		}
		i++;

	}

	if(v[i+1]!='\0'){

		v[i+1]=num;
		return 1;

	}

	return 0;

}

int conjunto_in(conjunto_t *v, int dato){
	int i=0;
	while(v[i]!='\0'){

		if(v[i]==dato){
			return 1;
		}
	}

	return 0;
}

conjunto_t *conjunto_intersection(conjunto_t *v, conjunto_t *c){

conjunto_t *nuevo;


nuevo=malloc(sizeof(v)*sizeof(c));
    int i=0;
	while(v[i]!='\0'){

		nuevo[i]=v[i];	
		i++;
	}
	int j=0;
	i++;
	while(c[j]!='\0'){

		if(c[j]!=nuevo[i]){

			nuevo[i]=c[j];	
		}
		i++;
		j++;
	}

	return nuevo;
}

void conjunto_remove(conjunto_t *v, int num){
	int i=0;
	while(v[i]!='\0'){

		if(v[i]==num){
			v[i]==INT_MAX;
		}
		i++;
	}


}

void conjunto_print(conjunto_t *v){

	int i=0;
	while(v[i]!='\0'){

		printf("El numero en la posicion [%d] es: %d \n",i,v[i] );
		i++;

	}


}

void conjunto_free(conjunto_t *v){

free(v);


}