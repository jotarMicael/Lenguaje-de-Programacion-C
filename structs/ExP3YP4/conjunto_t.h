#ifndef CONJUNTO_H
#define CONJUNTO_H

int v;

typedef int conjunto_t;


conjunto_t *conjunto_create();

int conjunto_add(conjunto_t *v, int dato);

int conjunto_in(conjunto_t *v, int dato);

conjunto_t *conjunto_intersection(conjunto_t *v, conjunto_t *c);

void conjunto_remove(conjunto_t *v, int);

void conjunto_print(conjunto_t *v);

void conjunto_free(conjunto_t *v);




#endif