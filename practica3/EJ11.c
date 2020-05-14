#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool es_palindromo(char *palabra, int tamanio, int cantP){
	

for (i=1, i<=cantP, i++){
	int p_i= 0;
	int p_f= tamanio-1;
	while ((p_i< p_f) && (palabra[p_i] == palabra[p_f])){

		p_i++;
		p_f--;
	}

	if (p_i == p_f)
			return true;
	else

			return false;

}


}
int main(){
bool resul;
char cadena[] = "somos los pibes chorros";
char *p_cadena = cadena; 
int tamanio = 0,cantP = 0;

printf("El inicio de la cadena es: %c\n", *(p_cadena));
printf("El final de la cadena es: %c\n", *(p_cadena+4));
printf("la cadena completa es: %s\n", p_cadena);

while(*(p_cadena+tamanio) != '\0')
	if (*(p_cadena+tamanio) = ' ')
		cantP++
	tamanio++;

printf("el tamaño es: %d\n", tamanio);

resul = es_palindromo(p_cadena, tamanio);

if (resul)	
	printf("Es palindromo\n");
else
	printf("No es palindromo\n");


}


