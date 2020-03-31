#pragma once
#include <stdio.h>
#include "vector/vector.h"

typedef struct {
    vector_int* a;
    vector_int* b;
    vector_int* c;
    size_t columns;
} matrix;

typedef struct {
    matrix* m;
    size_t row;
    size_t index_b; 
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

/* Get value of the element of matrix */
int m_get(matrix* m, size_t row, size_t col);

/* Set value of the element of matrix           */
/* If the element is zero,then it does nothing */
void m_set(matrix* m, size_t row, size_t col, int val);

/* Returns an iterator pointing to the beginning of a row/col */
m_iter m_begin(matrix* m);
m_iter m_begin_by_row(matrix* m, size_t row);
m_iter m_begin_by_col(matrix* m, size_t col);
/* Returns an iterator pointing to the end of a row/col */
m_iter m_end(matrix* m);
m_iter m_end_by_row(matrix* m, size_t row);
m_iter m_end_by_col(matrix* m, size_t col);

/**********************************************************/
void mi_next_col(m_iter* i);
void mi_prew_col(m_iter* i);
void mi_next_row(m_iter* i);
void mi_prew_row(m_iter* i);

bool mi_equals(m_iter* a, m_iter* b);

int  mi_get(m_iter* i);
void mi_set(m_iter* i, int val);