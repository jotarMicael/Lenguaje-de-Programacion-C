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

#define OP_SCA            's'
#define OP_SCA_LONG       "scalar"


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
    char* out_name;
    char* operation_name;
    char* ptr2;

     while (1) {
         /*Este while parsea todos los argumentos de argv con la función getopt_long()*/
         //int this_option_optind = optind ? optind : 1;
         int option_index = 0;
         
         static struct option long_options[] = {
             {OP_ARG_1_LONG,required_argument, 0,(int) OP_ARG_1},
             {OP_ARG_2_LONG,required_argument, 0,(int) OP_ARG_2 },
             {OP_CALC_LONG,required_argument, 0,OP_CALC},
             {OP_ARG_O_LONG ,required_argument, 0, OP_ARG_O},
             {OP_ARG_OPS_LONG,required_argument, 0,OP_ARG_OPS},
             {OP_HLP_LONG,no_argument,0,OP_HLP},
             {OP_SCA_LONG,required_argument, 0, (T_TYPE) OP_SCA},
             {0, 0, 0, 0}
         };
         c = getopt_long (argc, argv, "1:p:2:s:c:o:h:",
         long_options, &option_index);
         if (c == -1)
         /*c es -1 cuando se terminan todos los argumentos, entonces sale del while*/
         break; 
         switch (c) { 
             case OP_ARG_1:
                 printf("\n");
                 printf ("Opcion: leer matriz de archivo\n");
                 if (0 != optarg){
                    printf("Se ha leido el archivo: %s", optarg);
                    error=output_error(errors,read_matrix(optarg,fp,&m1));
                    printf("\n");
                    if(error != 0){
                        printf ("%d",error);
                        printf ("Error en la lectura de la matriz\n");
                        return E_READ_ERROR;
                    }
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
                    if(error != 0){
                        printf ("Ha ocurrido un error en al lectura del archivo\n");
                        return error;
                    }
                    matrix_print(m1);
                    printf ("Matriz cargada correctamente\n"); 
                    printf("\n");
                    operation_name= argv[3];
                 }
                 else{
                    printf ("Debe ingresar un archivo de matriz (M1,M2)\n");      
                    return E_READ_ERROR;
                 }
                 break;    
             case OP_ARG_2: 
                 printf("\n");
                 printf ("Opcion: leer segunda matriz de archivo\n");
                 if (0 != optarg){
                    printf("Se ha leido el archivo: %s", optarg);
                    error=output_error(errors,read_matrix(optarg,fp,&m2));
                    printf("\n");
                    if(error != 0){
                        printf ("Ha ocurrido un error en al lectura del archivo\n");
                        return error;
                    }
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
             case OP_ARG_O:
                out_name = optarg;
                break;
             case OP_ARG_OPS:
                operation_name = optarg; 
                break;
             case OP_SCA:
               if (0 != optarg){
                 num=strtod(optarg, &ptr2);
                 if(num==0.0){
                    printf ("Debe ingresar un numero para realizar la multiplicacion\n");  
                    return error;
                 }
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
             default:
                 /*Si el argumento no machea con ninguna opción conocida, debería ser un error en los
                 parámetros...*/
                 printf ("La función getopt_long ha retornado un carácter desconocido. El carácter es = %c\n", c);
                 formato();
                 break;
             }
         }



         if ((operation_name) && (out_name) && (m1)){
            if((strcmp(operation_name,"+") == 0)){

                 printf("\n");
                 printf ("Opcion: leer segunda matriz de archivo\n");
                 printf("Se ha leido el archivo: %s", argv[2]);
                 error=output_error(errors,read_matrix(argv[2],fp,&m2));
                 printf("\n");
                 if(error != 0){
                    printf ("Ha ocurrido un error en al lectura del archivo\n");
                    return error;
                 }
                 else {
                    matrix_print(m2);
                    printf ("Matriz cargada correctamente\n");
                    printf("\n");
                 }                 

                printf ("Opcion: M1 + M2 \n");
                 error=output_error(errors,sum(m1,m2,&m3));
                 if(error != 0){
                    printf ("Ocurrio un error en la suma\n");
                    return error;
                 }
                 else {
                    matrix_print(m3);
                    free_matrix(&m2);
                    free_matrix(&m1);
                    printf ("Matriz sumada correctamente \n");
                    printf("\n");
                    printf ("Opcion: Escribir en el archivo\n");
                    printf("Se va a escribir en el archivo: '%s'", out_name);
                    error=output_error(errors,write_matrix(out_name,fp,m3));
                    free_matrix(&m3);
                    printf("\n");
                    if(error != 0){
                        printf ("Ha ocurrido un error en al escritura del archivo\n");
                        return E_WRITE_ERROR;
                    }
                    else{
                        printf ("Matriz cargada en el archivo '%s' correctamente\n",out_name);
                        printf("\n");          
                        return E_OK;
                    }
                 
                 } 

            }

            if((strcmp(operation_name,"*") == 0)){

                 printf("\n");
                 printf ("Opcion: leer segunda matriz de archivo\n");
                 printf("Se ha leido el archivo: %s", argv[6]);
                 error=output_error(errors,read_matrix(argv[6],fp,&m2));
                 printf("\n");
                 if(error != 0){
                    printf ("Ha ocurrido un error en al lectura del archivo\n");
                    return error;
                 }
                 else {
                    matrix_print(m2);
                    printf ("Matriz cargada correctamente\n");
                    printf("\n");
                 }                 
                printf ("Opcion: multiplicar 2 matrices\n");
                error=output_error(errors,mult(m1,m2,&m3));
                if(error != 0){
                    printf ("Ocurrio un error en la multiplicacion\n");
                    return error;
                }
                else {
                    matrix_print(m3);
                    free_matrix(&m1);
                    free_matrix(&m2);
                    printf ("Matriz multiplicada correctamente \n");
                    printf("\n");
                }

            }

            if((strcmp(operation_name,".*") == 0)){

                 printf("\n");
                 if (argv[6]!=NULL){
                 num=strtod(argv[6], &ptr2);
                 if(num==0.0){
                    printf ("Debe ingresar un numero para realizar la multiplicacion\n");  
                    return error;
                 }
                 printf ("El numero a multiplicar es: %s\n", argv[6]);
                 printf("\n");
                 error=output_error(errors,mult_scalar(num,m1,&m2));
                 free_matrix(&m1);
                 if(error != 0){
                    printf ("Error en la multiplicacion\n");
                    return error;
                 }
                 else {
                    matrix_print(m2);
                    printf ("Matriz multiplicada correctamente \n");
                    printf("\n");
                 }
                 }
                 else{
                    printf ("Debe ingresar como parametro un numero para multiplicar\n");      
                    return E_READ_ERROR; 
                 }

            }

            if((strcmp(operation_name,"id") == 0)){

                printf ("Opcion: matriz identidad\n");
                if(get_cols(m1)>=get_rows(m1)){
                    error=output_error(errors,idty_matrix(get_cols(m1),&m2));
                }
                else{
                    error=output_error(errors,idty_matrix(get_rows(m1),&m2));
                }
                printf("\n");
                if(error != 0){
                    printf ("Ha ocurrido un error en la identidad\n"); 
                    return error;
                }
                matrix_print(m2);
                free_matrix(&m1);
                printf ("Matriz identidad generada correctamente\n"); 
                printf("\n");
                error=output_error(errors,write_matrix(out_name,fp,m2));
                free_matrix(&m2);
                printf("\n");
                if(error != 0){
                    printf ("Ha ocurrido un error en al escritura del archivo\n");
                    return E_WRITE_ERROR;
                }
                else{
                    printf ("Matriz cargada en el archivo '%s' correctamente\n",out_name);
                    printf("\n");          
                    return E_OK;
                }    

            }

            if((strcmp(operation_name,"dup") == 0)){

                printf ("Opcion: duplicar matriz\n");
                dup_matrix(m1,&m2);
                free_matrix(&m1);
                error=output_error(errors,write_matrix(out_name,fp,m2));
                free_matrix(&m2);
                printf("\n");
                if(error != 0){
                    printf ("Ha ocurrido un error en al escritura del archivo\n");
                    return E_WRITE_ERROR;
                }
                else{
                    printf ("Matriz cargada en el archivo '%s' correctamente\n",out_name);
                    printf("\n");          
                    return E_OK;
                }

            }

            if((strcmp(operation_name,"idty") == 0)){

                printf ("Opcion: matriz identidad\n");
                if(get_cols(m1)>=get_rows(m1)){   
                    error=output_error(errors,idty_matrix(get_cols(m1),&m2));
                }
                else{
                    error=output_error(errors,idty_matrix(get_rows(m1),&m2));
                }
                printf("\n");
                if(error != 0){
                    printf ("Ha ocurrido un error en la identidad\n"); 
                    return error;
                }
                matrix_print(m2);
                free_matrix(&m1);
                printf ("Matriz identidad generada correctamente\n"); 
                printf("\n");
                error=output_error(errors,write_matrix(out_name,fp,m2));
                free_matrix(&m2);
                printf("\n");
                if(error != 0){
                    printf ("Ha ocurrido un error en al escritura del archivo\n");
                    return E_WRITE_ERROR;
                }
                else{
                    printf ("Matriz cargada en el archivo '%s' correctamente\n",out_name);
                    printf("\n");          
                    return E_OK;
                }
            

            }

            if((strcmp(operation_name,"mult_scalar") == 0) && (num)){

                printf ("Opcion: multiplicar matriz por un scalar \n");
                error=output_error(errors,mult_scalar(num,m1,&m2));
                if(error != 0){
                    printf ("ERROR!\n");
                }
                else {
                    matrix_print(m2);
                    free_matrix(&m1);
                    printf ("Matriz multiplicada correctamente \n");
                    printf("\n");
                    error=output_error(errors,write_matrix(out_name,fp,m2));
                    free_matrix(&m2);
                    printf("\n");
                    if(error != 0){
                        printf ("Ha ocurrido un error en al escritura del archivo\n");
                        return E_WRITE_ERROR;
                    }
                    else{
                        printf ("Matriz cargada en el archivo '%s' correctamente\n",out_name);
                        printf("\n");          
                        return E_OK;
                    }
                }
                  
            }              

            

            if((strcmp(operation_name,"null") == 0)){

                printf ("Opcion: matriz nula\n");
                error=output_error(errors,null_matrix(get_rows(m1),get_cols(m1),&m2));
                printf("\n");
                if(error != 0){
                    printf ("ERROR!\n");
                    return error;
                }
                matrix_print(m2);
                free_matrix(&m1);
                printf ("Matriz nula generada correctamente\n"); 
                printf("\n");                
                error=output_error(errors,write_matrix(out_name,fp,m2));
                free_matrix(&m2);
                printf("\n");
                if(error != 0){
                    printf ("Ha ocurrido un error en al escritura del archivo\n");
                    return E_WRITE_ERROR;
                }
                else{
                    printf ("Matriz cargada en el archivo '%s' correctamente\n",out_name);
                    printf("\n");          
                    return E_OK;
                }


            }

            if((strcmp(operation_name,"sum") == 0) && (m2)){

                 printf ("Opcion: M1 + M2 \n");
                 error=output_error(errors,sum(m1,m2,&m3));
                 if(error != 0){
                    printf ("Ocurrio un error en la suma\n");
                    return error;
                 }
                 else {
                    matrix_print(m3);
                    free_matrix(&m2);
                    free_matrix(&m1);
                    printf ("Matriz sumada correctamente \n");
                    printf("\n");
                    printf ("Opcion: Escribir en el archivo\n");
                    printf("Se va a escribir en el archivo: '%s'", out_name);
                    error=output_error(errors,write_matrix(out_name,fp,m3));
                    free_matrix(&m3);
                    printf("\n");
                    if(error != 0){
                        printf ("Ha ocurrido un error en al escritura del archivo\n");
                        return E_WRITE_ERROR;
                    }
                    else{
                        printf ("Matriz cargada en el archivo '%s' correctamente\n",out_name);
                        printf("\n");          
                        return E_OK;
                    }
                 
                 }          
            }

            if((strcmp(operation_name,"mult") == 0) && (m2)){

                printf ("Opcion: multiplicar 2 matrices\n");
                error=output_error(errors,mult(m1,m2,&m3));
                if(error != 0){
                    printf ("Ocurrio un error en la multiplicacion\n");
                    return error;
                }
                else {
                    matrix_print(m3);
                    free_matrix(&m1);
                    free_matrix(&m2);
                    printf ("Matriz multiplicada correctamente \n");
                    printf("\n");
                }

            } 

            if((strcmp(operation_name,"cmp") == 0) && (m2)){

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
                free_matrix(&m1);
                free_matrix(&m2);
                printf ("Las matrices son iguales \n");
                printf("\n");     
                }

            }
          
        free_matrix(&m1);free_matrix(&m2);free_matrix(&m3);     
    }
    else{
        printf("No se han ingresado los argumentos de forma correcta\n");
    }
    exit(0);
}
     
        
 

