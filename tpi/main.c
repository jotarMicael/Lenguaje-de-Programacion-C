#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "list_t.h"
#include "error_mat.h"

void
formato()
{
    printf("Â¿Necesita ayuda?\n");
    printf("Ingrese '--help' para obtener ayuda sobre los comandos disponibles a ingresar:\n");

};

void help(){

    printf("--in1|-1 â€‹nombre_archivo - Indica la primera matriz a cargar en memoria. (Obligatorio)\n");
    printf("--in2|-2 â€‹nombre_archivo - Indica la segunda matriz a cargar enmemoria.(Obligatorio,excepto que se useâ€‹ dupâ€‹,idtyâ€‹ o â€‹mult_scalar)\n");
    printf("--out|-o â€‹nombre_archivo - Nombre del archivo donde se guardarÃ¡ el resultado\n");
    printf("--scalar|-s â€‹nÃºmero - NÃºmero en punto flotante por el que se multiplicarÃ¡n los elementos de la matriz cargada con â€‹--in1â€‹. (Obligatorio si se usa â€‹mult_scalarâ€‹).\n");
    printf("--op|-p â€‹(dup|sum|mult_scalar|mult|idty|null|cmp) Indica la operaciÃ³n a realizar, que puede ser una de las siguientes:\n");
    printf("dupâ€‹: Genera un duplicado de la matriz indicada conâ€‹ --in1â€‹ ,en el archivo indicado con â€‹--outâ€‹.\n");
    printf("sum: Suma elemento a elemento las matrices indicadas con --in1 y --in2, almacenando el resultado en el archivo indicado con --out. Si las matrices no tienen el mismo tamaÃ±o, el programa debe retornar el error: ERROR_INCOMPATIBLE_MATRICES.\n");
    printf("mult_scalar: Multiplica cada elemento de la matriz indicada con --in1 por el nÃºmero indicado con --scalar. El resultado queda en el valor del parÃ¡metro--out.\n");
    printf("mult: Multiplicar la matriz indicada con --in1 por la indicada con --in2, guardando el resultado en --out. Si las matrices no son multiplicables por su tamaÃ±o el programa debe retornar el error: ERROR_INCOMPATIBLE_MATRICES\n");
    printf("idty: genera la matriz identidad compatible con las dimensiones de la matriz indicada con el parÃ¡metro --in1. Resultado en el parÃ¡metro --out. La matriz identidad es una matriz cuadrada de NxN donde solo en su diagonal tiene valores â€œ1â€� y el resto es â€œ0â€�. Por ejemplo si la matriz de entrada es de 2x3 la identidad serÃ¡ de 3x3 dando como resultado el producto una matriz de 2x3 idÃ©ntica a la de entrada.\n");
    printf("null: genera la matriz nula compatible con las dimensiones de la matriz indicada con el parÃ¡metro --in1. Resultado en el parÃ¡metro de --out. La matriz cuadrada serÃ¡ de NxN y todos sus valores serÃ¡n nulos (â€œ0â€�).\n");
    printf("cmp: compara la matriz indicada con --in1 con la indicada en --in2. Almacena el resultado de la operaciÃ³n en una matriz de 1*1 indicado en el parÃ¡metro --out.\n");
    printf("--help Imprime la ayuda que indica cÃ³mo utilizar el programa en salida estÃ¡ndar y termina.\n");
}


int
main(int argc, char *argv[])
{
   // int n1, n2, m1, m2, print;
    //char *f1, *f2;
    matrix_t *m1,*m2;
    matrix_t **m3;
    int error;
    FILE *fp,*fp2,*errors;

    // Revisamos si hay suficientes entradas desde terminal
    if (argc >7)
    {
        formato();
        return 0;
    }

    if(argv[1] == "--help"){
        help();
        return -E_OK;
    }

    if ((argv[1] == "--in1|-1")&&(argv[2]!=NULL)){
        error=output_error(errors,read_matrix(argv[2],fp,m1));
        if(error!=0)
            return error;//Hubo error en carga de 1era matriz
        if ((argv[3] == "--op|-p")&&(argv[4]!="null")&&(argv[5]!="--out|-o")&&(argv[6]!=NULL)){
            error=output_error(errors,null_matrix(m1->rows,m3));
            if(error!=0)
                return error; //Hubo error en null
            error=output_error(errors,write_matrix(argv[6],fp2,m2)); //cargo m3 en el archivo
            return error; //salgo del programa bien, o mal
        }
        if ((argv[3] == "--in2|-2")&&(argv[4]!=NULL)){
            error=output_error(errors,read_matrix(argv[4],fp,m2));
            if(error!=0)
                return error; //Hubo error en carga de 2da matriz
            if(argv[5]=="--op|-p"){
                if((argv[6]=="sum")&&(argv[7]!=NULL)){
                    error=output_error(errors,sum(m1,m2,m3));
                    if(error!=0)
                        return error; //Hubo error en la suma
                    error=output_error(errors,write_matrix(argv[7],fp2,(*m3))); //cargo m3 en el archivo
                    if(error!=0)
                        return error; //Hubo error en escritura de matriz
                }
                if((argv[6]=="mult")&&(argv[7]!=NULL)){
                    error=output_error(errors,mult(m1,m2,m3));
                    if(error!=0)
                        return error; //Hubo error en la multiplicacion
                    error=output_error(errors,write_matrix(argv[7],fp2,(*m3))); //cargo m3 en el archivo
                    if(error!=0)
                        return error; //Hubo error en escritura de matriz
                }
                if((argv[6]=="cmp")&&(argv[7]!=NULL)){
                    error=output_error(errors,cmp_matrix(m1,m2));
                    if(error!=0)
                        return error; //Hubo error en la comparacion
                    error=output_error(errors,write_matrix(argv[7],fp2,m2)); //cargo m2 en el archivo
                    if(error!=0)
                        return error; //Hubo error en escritura de matriz
                }

                return output_error(errors,7);

            }
            else
                return output_error(errors,7);
            
         }
        else{
             if (argv[3] == "dup"){
                if((argv[4]=="--out|-o")&&(argv[5]!=NULL)){
                    error=output_error(errors,dup_matrix(m1,&m2)); //realizo copia de la matriz en m2
                    if(error!=0)
                        return error; //Hubo error en copia de matriz
                    error=output_error(errors,write_matrix(argv[5],fp2,m2)); //cargo m2 en el archivo
                }

            }
             if (argv[3] == "idty"){
                 if((argv[4]=="--out|-o")&&(argv[5]!=NULL)){
                    if(m1->rows>=m1->cols)
                        error=output_error(errors,idty_matrix(m1->rows,&m2)); //genero matriz identidad en m2 con rows
                    else
                        error=output_error(errors,idty_matrix(m1->cols,&m2)); //genero matriz identidad en m2 con cols
                    if(error!=0)
                        return error;
                    error=output_error(errors,write_matrix(argv[5],fp2,m2)); //cargo m2 en el archivo
                }


             }
             if (argv[3] == "mult_scalar"){
                if((argv[4]=="--scalar|-s")&&(argv[5]!=NULL)&&(argv[6]=="--out|-o")&&(argv[7]!=NULL)){ 
                    int ia = *(argv[5]) - '0';
                    error=output_error(errors,mult_scalar(ia,m1,m3)); //genero mult_scalar en m3
                    if(error==0) //si no hay error
                        error=output_error(errors,write_matrix(argv[7],fp2,*m3)); //escribo en el archivo la matriz escalar
                }

            }
            free_matrix(&m1);free_matrix(&m2);free_matrix(m3);
            return error; //retorna cualquier otro error, o si salio bien.
        }
    }
        else
            return output_error(errors,7);

 
}
