#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

struct nodo {

	double dato;
	struct nodo *siguiente;

};

typedef struct nodo nodo_t;
typedef nodo_t *list_t;

void list_new(list_t l);

list_t list_append(list_t l, int dato);

void destroy_list(list_t l);

bool is_Void(list_t l);

list_t remove_List(list_t l, int dato);

bool exist(list_t l, int dato);


#endif
