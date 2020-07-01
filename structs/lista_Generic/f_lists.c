#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

void list_new(lista_t *l){

	l=NULL;

}


lista_t *lista_append(lista_t *l, int dato){

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

void destroy_list(lista_t *l){

	free(l);
	l==NULL;
}

bool is_Void(lista_t *l){

	if(l==NULL)
		return true;
	else
		return false;

}

lista_t *remove_List(lista_t *l, int dato){

	lista_t *aux,*ante;

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

bool exist(lista_t *l, int dato){

lista_t *aux;

aux=l;

	while((aux!=NULL)&&(aux->dato!=dato)){

		aux=aux->siguiente;
	}

	if((aux!=NULL))
		return true;
	else
		return false;


}