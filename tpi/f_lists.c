#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list_t.h"

void list_new(list_t *l){

	l=NULL;

}


list_t lista_append(list_t l, int dato){

	nodo_t *nuevoNodo, *aux,*ant;
	nuevoNodo=malloc(sizeof(nodo_t));
	nuevoNodo->dato=dato;
	nuevoNodo->siguiente=NULL;
	if(l==NULL){
		l=nuevoNodo;
	}
	else{
		aux=l;
		while(aux!=NULL){
			ant=aux;
			aux=aux->siguiente;
		}

		ant->siguiente=nuevoNodo;

	}

	return l;

}

void destroy_list(list_t *l){

	free(l);
	l==NULL;
}

bool is_Void(list_t l){

	if(l==NULL)
		return true;
	else
		return false;

}

list_t remove_List(list_t l, int dato){

	list_t *aux,*ante;

	if((l!=NULL) && (l->dato==dato)){

		aux=l;
		l= l->siguiente;
		free(aux);

	}

	else{
		aux=l;
		while((aux!=NULL) && (aux->dato !=dato)){
			ante=aux;
			aux=aux->siguiente;

		}

		if(aux!=NULL){

			ante->siguiente=aux->siguiente;
			free(aux);
		}
	}

	return l;
}

bool exist(list_t l, int dato){

list_t *aux;

aux=l;

	while((aux!=NULL)&&(aux->dato!=dato)){

		aux=aux->siguiente;
	}

	if((aux!=NULL))
		return true;
	else
		return false;


}