#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"register_struct.h"


//carga de un register
void create_register(register_ty *registro, char *nombre,char *apellido, char *dni, char *domicilio){

	strcpy(registro->nombre,nombre);
	strcpy(registro->apellido,apellido);
	strcpy(registro->domicilio,domicilio);
	strcpy(registro->dni,dni);
}

//getter correcto de un campo del register

const char *getter_NameRegister(register_ty *registro){

	char *nombre=malloc(strlen(registro->nombre)+1);
	strcpy(nombre,registro->nombre);
	return nombre;


}