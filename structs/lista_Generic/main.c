#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

int main()
{
	lista_t *lista,*aux;

	list_new(lista);

	bool v=is_Void(lista);

	if(v){

		printf("esta vacia\n");

	}
	else

		printf("no esta vacia\n");


		int i=3;

		lista=lista_append(lista,i);
	
	

	v=is_Void(lista);
	
	if(v){

		printf("esta vacia\n");

	}
	else

		printf("no esta vacia\n");

	aux=lista;

	while(aux!=NULL){

		printf("Dato: %d \n", aux->dato);

		aux=aux->siguiente;

	}

	v=exist(lista,7);
	if(v){

		printf("existe\n");

	}
	else

		printf("no existe\n");

	lista=remove_List(lista,7);

	v=exist(lista,7);

	if(v){

		printf("existe\n");

	}
	else

		printf("no existe\n");


	aux=lista;


	while(aux!=NULL){

		printf("Dato: %d \n", aux->dato);

		aux=aux->siguiente;

	}



	destroy_list(lista);
}