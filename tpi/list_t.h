#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>


 
typedef struct snodo{ //snodo es el nombre de la estructura
    double valor;
    struct snodo *sig; //El puntero siguiente para recorrer la lista enlazada
}tnodo; //tnodo es el tipo de dato para declarar la estructura
 
typedef tnodo *tpuntero; //Puntero al tipo de dato tnodo para no utilizar punteros de punteros
 
void insert_InList(tpuntero *cabeza, double e);
void print_List (tpuntero cabeza);
void delete_List (tpuntero *cabeza);
void list_new(tpuntero *cabeza);



#endif
