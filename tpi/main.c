#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "list_t.h"
#include "error_mat.h"

void
formato()
{
    printf("¿Necesita ayuda?\n");
    printf("Ingrese '--help' para obtener ayuda sobre los comandos disponibles a ingresar:\n");

};

void help(){

    printf("--in1|-1 ​nombre_archivo - Indica la primera matriz a cargar en memoria. (Obligatorio)\n");
    printf("--in2|-2 ​nombre_archivo - Indica la segunda matriz a cargar enmemoria.(Obligatorio,excepto que se use​ dup​,idty​ o ​mult_scalar)\n");
    printf("--out|-o ​nombre_archivo - Nombre del archivo donde se guardará el resultado\n");
    printf("--scalar|-s ​número - Número en punto flotante por el que se multiplicarán los elementos de la matriz cargada con ​--in1​. (Obligatorio si se usa ​mult_scalar​).\n");
    printf("--op|-p ​(dup|sum|mult_scalar|mult|idty|null|cmp) Indica la operación a realizar, que puede ser una de las siguientes:\n");
    printf("dup​: Genera un duplicado de la matriz indicada con​ --in1​ ,en el archivo indicado con ​--out​.\n");
    printf("sum: Suma elemento a elemento las matrices indicadas con --in1 y --in2, almacenando el resultado en el archivo indicado con --out. Si las matrices no tienen el mismo tamaño, el programa debe retornar el error: ERROR_INCOMPATIBLE_MATRICES.\n");
    printf("mult_scalar: Multiplica cada elemento de la matriz indicada con --in1 por el número indicado con --scalar. El resultado queda en el valor del parámetro
--out.\n");
    printf("mult: Multiplicar la matriz indicada con --in1 por la indicada con --in2, guardando el resultado en --out. Si las matrices no son multiplicables por su tamaño el programa debe retornar el error: ERROR_INCOMPATIBLE_MATRICES\n");
    printf("idty: genera la matriz identidad compatible con las dimensiones de la matriz indicada con el parámetro --in1. Resultado en el parámetro --out. La matriz identidad es una matriz cuadrada de NxN donde solo en su diagonal tiene valores “1” y el resto es “0”. Por ejemplo si la matriz de entrada es de 2x3 la identidad será de 3x3 dando como resultado el producto una matriz de 2x3 idéntica a la de entrada.\n");
    printf("null: genera la matriz nula compatible con las dimensiones de la matriz indicada con el parámetro --in1. Resultado en el parámetro de --out. La matriz cuadrada será de NxN y todos sus valores serán nulos (“0”).\n");
    printf("cmp: compara la matriz indicada con --in1 con la indicada en --in2. Almacena el resultado de la operación en una matriz de 1*1 indicado en el parámetro --out.\n");
    printf("--help Imprime la ayuda que indica cómo utilizar el programa en salida estándar y termina.
\n");
}


int
main(int argc, char *argv)
{
   // int n1, n2, m1, m2, print;
    //char *f1, *f2;
    matrix_t *m1,*m2
    matrix_t **m3;
    int error;
    FILE *fp,*fp2,*errors;

    // Revisamos si hay suficientes entradas desde terminal
    if (argc >12)
    {
        formato();
        return 0;
    }

    // ¿Queremos impresión en pantalla?
    print = 1;

    /* Asignamos valores de la entrada a variables
    n1 = atoi(argv[1]);
    m1 = atoi(argv[2]);
    f1 = argv[3];
    n2 = atoi(argv[4]);
    m2 = atoi(argv[5]);
    f2 = argv[6]; */

    if(argv[1] == "--help"){
        help();
        return -E_OK;
    }

    if ((argv[1] == "--in1|-1")&&(argv[2]!=NULL)){
        error=output_error(errors,read_matrix(argv[2],fp,m1));
        if(error!=0)
            return error;//Hubo error en carga de 1era matriz
        if ((argv[3] == "--in2|-2")&&(argv[4]!=NULL)){
            error=output_error(errors,read_matrix(argv[4],fp,m2));
            if(error!=0)
                return error; //Hubo error en carga de 2da matriz
            
         }
        else{
             if (argv[3] == "dup"){
                if(argv[4]=="--out|-o")&&(argv[5]!=NULL)){
                    error=output_error(errors,dup_matrix(m1,&m2)); //realizo copia de la matriz en m2
                    if(error!=0)
                        return error; //Hubo error en copia de matriz
                    error=output_error(errors,write_matrix((argv[5],fp2,m2)); //cargo m2 en el archivo
                }

            }
             if (argv[3] == "idty"){
                 if((argv[4]=="--out|-o")&&(argv[5]!=NULL)){
                    if(m1.rows>=m1.cols)
                        error=output_error(errors,idty_matrix(m1->rows,&m2)); //genero matriz identidad en m2 con rows
                    else
                        error=output_error(errors,idty_matrix(m1->cols,&m2)); //genero matriz identidad en m2 con cols
                    if(error!=0)
                        return error;
                    error=output_error(errors,write_matrix((argv[5],fp2,m2)); //cargo m2 en el archivo
                }


             }
             if (argv[3] == "mult_scalar"){
                if((argv[4]=="--scalar|-s")&&(argv[5]!=NULL)&&(argv[6]=="--out|-o")&&(argv[7]!=NULL)){
                    error=output_error(errors,mult_scalar(argv[5],m1,m3)); //genero mult_scalar en m3
                    if(error==0) //si no hay error
                        error=output_error(errors,write_matrix((argv[7],fp2,*m3)); //escribo en el archivo la matriz escalar
                }

            }
            matrix_free(m1);matrix_free(m2);matrix_free(*m3);
            return errors; //retorna cualquier otro error, o si salio bien.
        }
    }
        else
            return output_error(errors,7);

 


    // Se crea la primera matriz
    M1 = matrix_load_file(f1 ,n1, m1);
    if (M1 == NULL)
    {
        printf("Error al crear matríz\n");
        return 1;
    }

    if(print)
    {
        matrix_print(M1);
        printf("*\n");
    }

    //Se crea la segunda matriz
    M2 = matrix_load_file(f2 ,n2, m2);
    if (M2 == NULL)
    {
        printf("Error al crear matríz\n");
        matrix_free(M1);
        return 1;
    }

    if(print)
    {
        matrix_print(M2);
    }
    
    // Realizamos la multiplicación
    M = matrix_mult(M1, M2);
    if(M == NULL)
    {
        matrix_free(M1);
        matrix_free(M2);
        return 1;
    }
    if(print)
    {
        printf("----------------------\n");
        matrix_print(M);
    }

    // Liberamos memoria
    matrix_free(M1);
    matrix_free(M2);
    matrix_free(M);
    return 0;
}