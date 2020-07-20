#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
typedef struct snodo{ //snodo es el nombre de la estructura
    double valor;
    struct snodo *sig; //El puntero siguiente para recorrer la lista enlazada
}tnodo; //tnodo es el tipo de dato para declarar la estructura
 
typedef tnodo *tpuntero; //Puntero al tipo de dato tnodo para no utilizar punteros de punteros
 
void insertarEnLista (tpuntero *cabeza, int e);
void imprimirLista (tpuntero cabeza);
void borrarLista (tpuntero *cabeza);
void list_new(tpuntero *cabeza);
bool is_Void(tpuntero l);


#endif
