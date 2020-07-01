#include <stdio.h>

int main(){
        int c;

        while((c = getchar()) != EOF){             //Leemos caracteres hasta Ctrl+D
                  if(c == ' '){                                   //Solo imprimiremos el primer blanco
                          putchar(c);
                          c = getchar();                     //Leemos el siguiente por si fuera otro blanco                     //Podemos introducir los
                               while(c == ' '){    //blancos que nos de la gana seguidos
                                       c = '\0';
                                       c = getchar();  //omitiremos la escritura
                                }
                           
                    }
                       putchar(c);     //Imprimimos la cadena sin espacios
          }
          
          return 0;
}

