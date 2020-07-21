/*
 * Created by ariel on 20/7/20.
*/
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// El tipo de dato de la matriz
typedef struct
{
    size_t rows; // cantidad de filas
    size_t cols; // cantidad de columnas
    double **data; // datos, se accede data[row][col]
} matrix_t;

// Tipo del archivo
typedef enum
{
    MATRIX_FORMAT_TXT, // archivo de texto
    MATRIX_FORMAT_BIN // archivo binario
} matrix_format_t;

// crea una matriz vacía
bool create_matrix(matrix_t **m)
{
    matrix_t *tmp = (matrix_t *) malloc(sizeof(matrix_t));
    if (!tmp)
    {
        *m = NULL;
        return false;
    }
    tmp->rows = tmp->cols = 0;
    tmp->data = NULL;
    *m = tmp;
    return true;
}

// crea una matriz rows x cols
bool create_and_init_matrix(size_t rows, size_t cols, matrix_t **m)
{
    size_t len = rows * cols;
    if (!len || !m || *m)
    {
        return false;
    }

    matrix_t *tmp = NULL;
    if (!create_matrix(&tmp))
    {
        return false;
    }

    // arreglo de filas == punteros a punteros a double
    double **data = (double **) malloc(sizeof(double *) * rows);
    if (!data)
    {
        free(tmp);
        return false;
    }
    double *p_col;
    for (size_t i = 0; i < rows; i++)
    {
        // cada fila es un arreglo dinámico de double
        p_col = (double *) malloc(sizeof(double) * cols);
        if (!p_col)
        {
            while (i) free(data[i--]); // liberar las columnas que ya se alocaron
            free(data); // liberar el arreglo de filas
            free(tmp); // liberar la matriz
            return false;
        }
        data[i] = p_col;
    }

    tmp->rows = rows;
    tmp->cols = cols;
    tmp->data = data;
    *m = tmp;
    return true;
}

// libera la memoria alocada
void destroy_matrix(matrix_t **m)
{
    // liberar cada fila
    for (size_t i = 0; i < (*m)->rows; i++)
    {
        free((*m)->data[i]);
    }
    free((*m)->data); // libera el arreglo de filas
    free(*m); // libera la matriz
    *m = NULL;
}

// crea una matriz rows x cols y la llena con data
bool create_and_fill_matrix(const double *data, size_t rows, size_t cols, matrix_t **m)
{
    if (!create_and_init_matrix(rows, cols, m))
        return false;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            (*m)->data[i][j] = data[i * cols + j];
        }
    }
    return true;
}

// escribe la matriz en un archivo
bool write_matrix(FILE *out, matrix_format_t format, const matrix_t *m)
{
    // escribir el encabezado M1 o M2
    fprintf(out, "M%c\n", format == MATRIX_FORMAT_TXT ? '1' : '2');
    // escribir las dimensiones
    fprintf(out, "%zu %zu\n", m->rows, m->cols);
    if (format == MATRIX_FORMAT_TXT)
    {
        // los datos como TEXTO se guardan con fprintf uno a uno
        for (size_t i = 0; i < m->rows; i++)
        {
            for (size_t j = 0; j < m->cols; j++)
            {
                fprintf(out, j + 1 == m->cols ? "%f" : "%f\t",
                        m->data[i][j]);
            }
            fputc('\n', out); // final de fila
        }
    }
    else
    {
        // los datos en formato binario se escriben uno a uno
        size_t count = m->rows * m->cols;
        size_t written = 0;
        for (size_t i = 0; i < m->rows; i++)
        {
            for (size_t j = 0; j < m->cols; j++)
            {
                if (fwrite(&m->data[i][j], sizeof(double), 1, out) != 1)
                    return false;
                written++;
            }
        }
        if (count != written)
            return false;
    }
    return true;
}

// lee la matriz de un archivo
bool read_matrix(FILE *in, matrix_t **m)
{
    // leer el encabezado
    char header[4];
    char *tmp = fgets(header, 4, in);
    if (!tmp || strlen(tmp) != 3 || header[0] != 'M' ||
        (header[1] != '1' && header[1] != '2') || header[2] != '\n')
    {
        return false;
    }
    matrix_format_t format = header[1] == '1' ?
                             MATRIX_FORMAT_TXT :
                             MATRIX_FORMAT_BIN;

    // ignorar comentarios
    int c;
    while ((c = getc(in)) != EOF && c == '#')
    {
        while ((c = getc(in)) != EOF && c != '\n');
    }
    if (c == EOF)
    {
        return false;
    }
    // cuando salimos del loop de arriba sin EOF, leimos un char de más!
    if (ungetc(c, in) == EOF)
    {
        return false;
    }

    // leer la dimensión
    size_t rows, cols;
    int scanned = fscanf(in, "%zu %zu[^\n]", &rows, &cols);
    if (scanned != 2)
        return false;

    // remover el \n que deja fscanf
    if (getc(in) == EOF)
    {
        return false;
    }

    size_t len = rows * cols;
    // temporal, para leer los datos todos seguidos
    double *data = (double *) malloc(sizeof(double) * len);
    if (!data)
        return false;

    if (format == MATRIX_FORMAT_TXT)
    {
        // M1 para otro día...
        free(data);
        return false;
    }
    else
    {
        // es más sencillo leer todos los datos juntos
        // y después iterar la matriz asignando los datos
        if (fread(data, sizeof(double), len, in) != len)
        {
            free(data);
            return false;
        }
        if (ferror(in) || (!feof(in) && (getc(in) != EOF)))
        {
            free(data);
            return false;
        }
    }

    if (!create_matrix(m))
    {
        free(data);
        return false;
    }

    (*m)->data = (double **) malloc(sizeof(double *) * rows);
    if (!(*m)->data)
    {
        free(data);
        free(*m);
        return false;
    }

    for (size_t i = 0; i < rows; i++)
    {
        // alocar memoria para cada columna
        (*m)->data[i] = (double *) malloc(sizeof(double) * cols);
        if (!(*m)->data[i])
        {
            while (i) free((*m)->data[i--]); // liberar las columnas alocadas hasta ahora
            free((*m)->data); // liberar las filas
            free(*m); // liberar la matriz
            return false;
        }
        for (size_t j = 0; j < cols; j++)
        {
            (*m)->data[i][j] = data[i * cols + j];
        }
    }

    free(data);
    (*m)->rows = rows;
    (*m)->cols = cols;
    return true;
}

// imprime la matriz
void print_matrix(const matrix_t *m)
{
    for (size_t i = 0; i < m->rows; i++)
    {
        for (size_t j = 0; j < m->cols; ++j)
        {
            printf(j + 1 == m->cols ? "%f" : "%f\t",
                   m->data[i][j]);
        }
        putchar('\n');
    }
}

int main(void)
{
    // archivo con los datos en formato texto plano
    const char txt_file[] = "test_matrix_2dim.m1";
    // archivo con los datos en formato binario
    const char bin_file[] = "test_matrix_2dim.m2";
    // datos de prueba para crear una matriz en memoria
    double test[] = {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 13, 14, 15
    };

    matrix_t *m = NULL;
    // creamos la matriz y la llenamos con los datos de prueba
    if (!create_and_fill_matrix(test, 3, 5, &m))
        return EXIT_FAILURE;

    FILE *out_bin, *out_txt, *in_bin, *in_txt;

    // escritura de matriz formato binario
    out_bin = fopen(bin_file, "wb");
    if (out_bin)
    {
        write_matrix(out_bin, MATRIX_FORMAT_BIN, m);
        fclose(out_bin);
    }

    // escritura de matriz formato texto plano
    out_txt = fopen(txt_file, "wb");
    if (out_txt)
    {
        write_matrix(out_txt, MATRIX_FORMAT_TXT, m);
        fclose(out_txt);
    }

    // liberar memoria alocada
    destroy_matrix(&m);

    // cargar desde archivo TEXTO PLANO
    in_txt = fopen(txt_file, "rb");
    if (in_txt)
    {
        if (read_matrix(in_txt, &m))
        {
            printf("Matriz M1 leída:\n");
            print_matrix(m);
            destroy_matrix(&m); // liberar memoria alocada
        }
        fclose(in_txt);
    }

    // cargar desde archivo BINARIO
    in_bin = fopen(bin_file, "rb");
    if (in_bin)
    {
        if (read_matrix(in_bin, &m))
        {
            printf("Matriz M2 leida:\n");
            print_matrix(m);
            destroy_matrix(&m); // liberar memoria alocada
        }
        fclose(in_bin);
    }

    return EXIT_SUCCESS;
}