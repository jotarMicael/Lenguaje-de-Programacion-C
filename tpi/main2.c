#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"
#include "list_t.h"
#include "error_mat.h"
#define _GNU_SOURCE
#include <getopt.h> /*para getopt_long*/ 

#define OP_ARG_1          '1'
#define OP_ARG_1_LONG     "in1"

#define OP_ARG_2          '2'
#define OP_ARG_2_LONG     "in2"

#define OP_ARG_O          'o'
#define OP_ARG_O_LONG     "out"

#define OP_CALC           'c'
#define OP_CALC_LONG     "calc"

#define OP_ARG_S          's'
#define OP_ARG_S_LONG     "scalar"

#define OP_ARG_OPS        'p'
#define OP_ARG_OPS_LONG   "op"

#define OP_HLP            'h'
#define OP_HLP_LONG       "help"


void
formato()
{
    printf("¿Necesita ayuda?\n");
    printf("Ingrese '--help' para obtener ayuda sobre los comandos disponibles a ingresar:\n");

}

void help(){

    printf("--in1|-1 nombre_archivo - Indica la primera matriz a cargar en memoria. (Obligatorio)\n");
    printf("--in2|-2 nombre_archivo - Indica la segunda matriz a cargar enmemoria.(Obligatorio,excepto que se use? dup?,idty? o ?mult_scalar)\n");
    printf("--out|-o nombre_archivo - Nombre del archivo donde se guardará el resultado\n");
    printf("--scalar|-s número - Número en punto flotante por el que se multiplicarán los elementos de la matriz cargada con ?--in1?. (Obligatorio si se usa ?mult_scalar?).\n");
    printf("--op|-p (dup|sum|mult_scalar|mult|idty|null|cmp) Indica la operación a realizar, que puede ser una de las siguientes:\n");
    printf("dup?: Genera un duplicado de la matriz indicada con? --in1? ,en el archivo indicado con ?--out?.\n");
    printf("sum: Suma elemento a elemento las matrices indicadas con --in1 y --in2, almacenando el resultado en el archivo indicado con --out. Si las matrices no tienen el mismo tamaño, el programa debe retornar el error: ERROR_INCOMPATIBLE_MATRICES.\n");
    printf("mult_scalar: Multiplica cada elemento de la matriz indicada con --in1 por el número indicado con --scalar. El resultado queda en el valor del parámetro--out.\n");
    printf("mult: Multiplicar la matriz indicada con --in1 por la indicada con --in2, guardando el resultado en --out. Si las matrices no son multiplicables por su tamaño el programa debe retornar el error: ERROR_INCOMPATIBLE_MATRICES\n");
    printf("idty: genera la matriz identidad compatible con las dimensiones de la matriz indicada con el parámetro --in1. Resultado en el parámetro --out. La matriz identidad es una matriz cuadrada de NxN donde solo en su diagonal tiene valores 1 y el resto es 0. Por ejemplo si la matriz de entrada es de 2x3 la identidad será de 3x3 dando como resultado el producto una matriz de 2x3 idéntica a la de entrada.\n");
    printf("null: genera la matriz nula compatible con las dimensiones de la matriz indicada con el parámetro --in1. Resultado en el parámetro de --out. La matriz cuadrada será de NxN y todos sus valores serán nulos (0).\n");
    printf("cmp: compara la matriz indicada con --in1 con la indicada en --in2. Almacena el resultado de la operación en una matriz de 1*1 indicado en el parámetro --out.\n");
    printf("--help Imprime la ayuda que indica cómo utilizar el programa en salida estándar y termina.\n");
}

int
main(int argc, char *argv[])
{
    matrix_t *m1=NULL,*m2=NULL,*m3=NULL;
    int error;
    T_TYPE num;
    FILE *fp=NULL,*errors=NULL;

    int c;
   // int digit_optind = 0;
 
     while (1) {
         /*Este while parsea todos los argumentos de argv con la función getopt_long()*/
         //int this_option_optind = optind ? optind : 1;
         int option_index = 0;
         
         static struct option long_options[] = {
             {OP_ARG_1_LONG,required_argument, 0,(int) OP_ARG_1},
             {OP_ARG_2_LONG,required_argument, 0,(int) OP_ARG_2 },
             {OP_CALC_LONG,required_argument, 0,OP_CALC},
             {"+",required_argument, 0, '+'},
             {"*",required_argument, 0, '*'},
             {"op",no_argument, 0, 'p'},
             {".*",required_argument, 0, '.'},
             {"dup",no_argument, 0, 'd'},
             {"idty",no_argument, 0, 'i'},
             {"out",required_argument, 0, 'o'},
             {"mult_scalar",no_argument, 0, 'm'},
             {"mult",no_argument, 0, 'x'},
             {"sum",no_argument, 0, 'f'},
             {"null",no_argument, 0, 'e'},
             {"cmp",no_argument, 0, 'z'},
             {OP_HLP_LONG,no_argument,0,OP_HLP},
             {"scalar",required_argument, 0, (T_TYPE) 's'},
             {0, 0, 0, 0}
         };
         c = getopt_long (argc, argv, "OP_ARG_1:OP_ARG_2:s:OP_CALC:+:*:o:.:OP_HLPixzpfdim",
         long_options, &option_index);
         if (c == -1)
         /*c es -1 cuando se terminan todos los argumentos, entonces sale del while*/
         break; 
 
         switch (c) { 
             case '1':
                 printf("\n");
                 printf ("Opcion: leer matriz de archivo\n");
                 if (0 != optarg){
                    printf("Se ha leido el archivo: %s", optarg);
                    error=output_error(errors,read_matrix(optarg,fp,&m1));
                    printf("\n");
                    if(error != 0)
                        printf ("ERROR!\n");
                    matrix_print(m1);
                    printf ("Matriz cargada correctamente\n"); 
                    printf("\n");
                 }
                 else{
                    printf ("Debe ingresar un archivo de matriz (M1,M2)\n");   
                    return E_READ_ERROR;
                 }              
                 break;
             case OP_CALC:
                 printf("\n");
                 printf ("Opcion: calcular matriz de archivo\n");
                 if (0 != optarg){
                    printf("Se ha leido el archivo: %s", optarg);
                    printf("\n");
                    error=output_error(errors,read_matrix(optarg,fp,&m1));
                    printf("\n");
                    if(error != 0)
                        printf ("ERROR!\n");
                    matrix_print(m1);
                    printf ("Matriz cargada correctamente\n"); 
                    printf("\n");
                 }
                 else{
                    printf ("Debe ingresar un archivo de matriz (M1,M2)\n");      
                    return E_READ_ERROR;
                 }                  
                 break;    
             case 'd':
                 printf ("Opcion: duplicar matriz\n");
                 m2=m1;
                 break;
             case 'i':
                 printf ("Opcion: matriz identidad\n");
                    //printf("Se ha leido el archivo: %s", optarg);
                    if(get_cols(m1)>=get_rows(m1))   
                        error=output_error(errors,idty_matrix(get_cols(m1),&m2));
                    else
                        error=output_error(errors,idty_matrix(get_cols(m1),&m2));
                    printf("\n");
                    if(error != 0)
                        printf ("ERROR!\n");
                    matrix_print(m2);
                    printf ("Matriz identidad generada correctamente\n"); 
                    printf("\n");
                 break;
             case '2': 
                 printf("\n");
                 printf ("Opcion: leer segunda matriz de archivo\n");
                 if (0 != optarg){
                    printf("Se ha leido el archivo: %s", optarg);
                    error=output_error(errors,read_matrix(optarg,fp,&m2));
                    printf("\n");
                    if(error != 0)
                        printf ("ERROR!\n");
                    else {
                        matrix_print(m2);
                        printf ("Matriz cargada correctamente\n");
                        printf("\n");
                    }
                 }
                 else{
                    printf ("Debe ingresar un archivo de matriz (M1,M2)\n");      
                    return E_READ_ERROR;
                  }    
                 break;
             case 'o':
                 printf ("Opcion: Escribir en el archivo\n");
                 if (0 != optarg){
                    printf("Se va a escribir en el archivo: '%s'", optarg);
                    error=output_error(errors,write_matrix(optarg,fp,m2));
                    printf("\n");
                    if(error != 0)
                        printf ("ERROR!\n");
                    else{
                        printf ("Matriz cargada en el archivo '%s' correctamente\n",optarg);
                        printf("\n");
                    }
                 }
                 else{
                    printf ("Debe ingresar el nombre de un archivo como salida\n");      
                    return E_WRITE_ERROR;
                  }  
                 break;
             case 'p':
                 printf ("Operacion: ");
                 break;
             case 's':
               if (0 != optarg){
                 printf ("Scalar\n");
                 printf("\n");
                 num=atof(optarg);
                /* printf ("El numero a multiplicar es: %s\n", optarg);
                 if(strcmp(optarg, "0") != 0){
                     printf ("ERROR: Debe ingresar un numero!\n");
                     return error;
                 } */
                 printf ("El numero a multiplicar es: %s\n", optarg);
                 printf("\n");
               }
               else{
                    printf ("Debe ingresar un numero para realizar la multiplicacion\n");      
                    return E_READ_ERROR;
               }  
                 break;
             case OP_HLP:
                 help();
                 break;
             case 'm':
                 if(num!=NULL){
                 printf ("Opcion: multiplicar matriz por un scalar \n");
                 error=output_error(errors,mult_scalar(num,m1,&m2));
                 if(error != 0)
                    printf ("ERROR!\n");
                 else {
                    matrix_print(m2);
                    printf ("Matriz multiplicada correctamente \n");
                    printf("\n");

                 }
                 }
                 else{
                     printf ("Debe ingresar un numero para realizar la multiplicacion\n");      
                    return E_READ_ERROR;
                 }
                 break;
             case 'x':
                 if ((m1!=NULL)&&(m2!=NULL)){
                 printf ("Opcion: multiplicar 2 matrices\n");
                 error=output_error(errors,mult(m1,m2,&m3));
                 if(error != 0){
                    printf ("ERROR!\n");
                    return error;
                }
                 else {
                    matrix_print(m3);
                    printf ("Matriz multiplicada correctamente \n");
                    printf("\n");
                    m2=m3;
                 }
                 }
                 else{
                    printf ("No se encuentran cargadas las matrices m1 o m2\n");      
                    return E_WRITE_ERROR;
                 }
                 break;
             case 'f':
                 if ((m1!=NULL)&&(m2!=NULL)){
                 printf ("Opcion: sumar 2 matrices\n");
                 error=output_error(errors,sum(m1,m2,&m3));
                 if(error != 0){
                    printf ("ERROR!\n");
                    return error;
                 }
                 else {
                    matrix_print(m3);
                    printf ("Matriz sumada correctamente \n");
                    printf("\n");
                    m2=m3;
                 }
                 }
                 else{
                    printf ("No se encuentran cargadas las matrices m1 o m2\n");      
                    return E_WRITE_ERROR;
                 }
                 break;
             case 'e':
                 if (m1!=NULL){
                 printf ("Opcion: matriz nula\n");
                    error=output_error(errors,null_matrix(get_rows(m1),get_cols(m1),&m2));
                    printf("\n");
                    if(error != 0){
                        printf ("ERROR!\n");
                        return error;
                    }
                    matrix_print(m2);
                    printf ("Matriz nula generada correctamente\n"); 
                    printf("\n");
                 }
                 else{
                    printf ("No se encuentran cargada la matriz m1\n");      
                    return E_WRITE_ERROR;
                 }
                 break;
              case 'z':
                 if ((m1!=NULL)&&(m2!=NULL)){
                 printf ("Opcion: comparar 2 matrices\n");
                 error=output_error(errors,cmp_matrix(m1,m2));
                 if(error == 8){
                    printf ("Error incompatibles!\n");
                    return error;
                }
                 else {
                    if(error != 0){
                        printf ("ERROR\n");
                        return error;
                    }
                    printf ("Las matrices son iguales \n");
                    printf("\n");     
                 }
                 }
                 else{
                    printf ("No se encuentran cargadas las matrices m1 o m2\n");      
                    return E_WRITE_ERROR;
                 }
                 break;
              case '+':
                 printf("\n");
                 printf ("leer segunda matriz de archivo\n");
                 if (0 != optarg){
                    printf("Se ha leido el archivo: %s", optarg);
                    error=output_error(errors,read_matrix(optarg,fp,&m2));
                    printf("\n");
                    if(error != 0)
                        printf ("ERROR!\n");
                    else {
                        matrix_print(m2);
                        printf ("Matriz cargada correctamente\n");
                        printf("\n");
                    }
                 }
                
                 printf ("Opcion: M1 + M2 \n");
                 error=output_error(errors,sum(m1,m2,&m3));
                 if(error != 0){
                    printf ("ERROR!\n");
                    return error;
                 }
                 else {
                    matrix_print(m3);
                    printf ("Matriz sumada correctamente \n");
                    printf("\n");
                    m2=m3;
                 }
                 break;
              case '*':
                printf("\n");
                 printf ("Opcion: leer segunda matriz de archivo\n");
                 if (0 != optarg){
                    printf("Se ha leido el archivo: %s", optarg);
                    error=output_error(errors,read_matrix(optarg,fp,&m2));
                    printf("\n");
                    if(error != 0)
                        printf ("ERROR!\n");
                    else {
                        matrix_print(m2);
                        printf ("Matriz cargada correctamente\n");
                        printf("\n");
                    }
                 }
                printf ("Opcion: multiplicar 2 matrices\n");
                 error=output_error(errors,mult(m1,m2,&m3));
                 if(error != 0){
                    printf ("ERROR!\n");
                    return error;
                }
                 else {
                    matrix_print(m3);
                    printf ("Matriz multiplicada correctamente \n");
                    printf("\n");
                    m2=m3;
                 }
                break;
            case '.':
                 printf("\n");
                 num=atof(optarg);
                 /*if((strcmp(optarg, "0") != 0)){
                     printf ("ERROR: Debe ingresar un numero!\n");
                     return error;
                 }*/
                 printf ("El numero a multiplicar es: %s\n", optarg);
                 printf("\n");
                 error=output_error(errors,mult_scalar(num,m1,&m2));
                 if(error != 0)
                    printf ("ERROR!\n");
                 else {
                    matrix_print(m2);
                    printf ("Matriz multiplicada correctamente \n");
                    printf("\n");
                 }
                break;
             default:
                 /*Si el argumento no machea con ninguna opción conocida, debería ser un error en los
                 parámetros...*/
                 printf ("La función getopt_long ha retornado un carácter desconocido. El carácter es = %c\n", c);
                 formato();
             }
         }
         /*Si siguen apareciendo cosas que no son argumentos, se imprimen hasta que se acaben...*/
         if (optind < argc) {
         printf ("No son opciones pero estan en ARGV: ");
         while (optind < argc)
             printf ("%s ", argv[optind++]);
         printf ("\n");
      }
     
        free_matrix(&m1);free_matrix(&m2);free_matrix(&m3);
        free(m1);
        return 0;
      
 }
