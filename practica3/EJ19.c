#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *crear_vector_int(int n){

int *vector;


vector=malloc(n);
 if (vector == NULL) {    
     fprintf(stderr, "La aplicacion no pudo reservar memoria y se va a cerrar!\n");
     exit(EXIT_FAILURE);

}
else

	return vector;


}

int *reasignar_memoria(int* vector, int n){

vector = realloc (vector,sizeof(int)*n);
return vector;



}


int main(){


int* ptr;
int n=1;
ptr = crear_vector_int(n);
printf("Direccion del Puntero: %i\n", ptr );
*ptr= 535;
printf("Contenido de la memoria: %d\n", *(ptr) );
n=3;
ptr= reasignar_memoria(ptr,n);
printf("Direccion del Puntero: %i\n", ptr );
*ptr= 345;
printf("Contenido de la memoria: %d\n", *(ptr) );


free(ptr);
}
