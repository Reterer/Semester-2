#pragma once
#include <stdio.h>
#include "vector/vector.h"

#define NOT_AT_INDEX ULLONG_MAX

typedef struct {
    vector_int* a;
    vector_int* b;
    vector_double* c;
    size_t columns;
} matrix;
typedef struct {
    matrix* m;
    size_t index_b; 
    size_t row;
    // size_t col;
} m_iter;

typedef enum {
    HUMAN,      // Человеческий формат (в виде матрицы)
    INTERNAL    // Внутреннее представленее (в виде 3-ех векторов)
} matrix_io_mode;

/* Initializes a matrix so that it can be used */
bool m_init(matrix** m);
/* After using the matrix, call this function */
void m_deinit(matrix** m);

/* Read matrix from file */
bool m_read(matrix* m, FILE* file);
/* Print matrix to file */
bool m_print(matrix*m, FILE* file, matrix_io_mode mode);


size_t m_get_count_rows(matrix* m);

size_t m_get_count_cols(matrix* m);

/* Get value of the element of matrix */
double m_get(matrix* m, size_t row, size_t col);

/* Set value of the element of matrix           */
/* If the element is zero,then it does nothing  */
void m_set(matrix* m, size_t row, size_t col, double val);

/* Returns an iterator pointing to the first not empty elment of matrix*/
m_iter m_begin(matrix* m);
m_iter m_begin_row(matrix* m, size_t row);

/* Returns an iterator pointing to the end of matrix*/
m_iter m_end(matrix* m);
m_iter m_end_row(matrix* m, size_t row);

/**********************************************************/
void mi_next_col(m_iter* i);
void mi_prew_col(m_iter* i);
void mi_next_row(m_iter* i);
void mi_prev_row(m_iter* i);

bool mi_equals(m_iter a, m_iter b);

double  mi_get(m_iter i);
void    mi_set(m_iter i, double val);

size_t mi_get_col(m_iter i);
size_t mi_get_row(m_iter i);