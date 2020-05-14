#include <stdio.h>
#include <ctype.h>


int main(){



unsigned int c,numeros,vocales,signos;
numeros=0;
vocales=0;
signos=0;


printf("Ingrese un texto\n");

c= getchar();

while (c != EOF){
		if ((48 <= c) && (c<= 59))
			numeros++;
		else {

			if ( (ispunct(c)) != 0)
				signos++;


			else {

				 if ((c == 'a')||(c=='e')||(c=='i')||(c=='o')||(c=='u')||(c=='A')||(c=='E')||(c=='I')||(c=='O')||(c=='U'))
					vocales++;


		}
			}

        c=getchar();

}

 	printf("Numeros %d\n", numeros);
    printf("Signos de puntuacion %d\n", signos);
    printf("Vocales %d\n", vocales);
}