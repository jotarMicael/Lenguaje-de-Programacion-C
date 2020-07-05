#ifndef LIST_H
#define LIST_H

struct nodo {

	void *dato;
	struct nodo *siguiente;

};

typedef struct nodo nodo_t;
typedef nodo_t lista_t;


void list_new(lista_t *l);

lista_t *lista_append(lista_t *l, int dato);

void destroy_list(lista_t *l);

bool is_Void(lista_t *l);

lista_t *remove_List(lista_t *l, int dato);

bool exist(lista_t *l, int dato);


#endif