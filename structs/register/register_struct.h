#ifndef REGISTER_H
#define REGISTER_H


struct regis {

	char nombre[15];
	char apellido[15];
	char domicilio[15];
	char dni[14];
};

typedef struct regis register_ty;

typedef int numero;

void create_register(register_ty *registro, char *nombre,char *apellido, char *dni, char *domicilio);

const char *getter_NameRegister(register_ty *registro);

#endif