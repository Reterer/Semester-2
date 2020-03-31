#include "matrix.h"
#include <stdio.h>
#include <limits.h>

#define NOT_AT_INDEX SIZE_MAX

bool m_init(matrix** m) {
    *m = malloc(sizeof(matrix));
    if(*m == NULL)
        return false;

    v_init_int((*m)->a);
    v_init_int((*m)->b);
    v_init_int((*m)->c);
    (*m)->columns = 0;

    return true;
}

void m_deinit(matrix** m) {
    if(*m == NULL)
        return;
    
    v_deinit_int((*m)->a);
    v_deinit_int((*m)->b);
    v_deinit_int((*m)->c);
    free(*m);
}

bool m_read(matrix* m, FILE* file){
    size_t rows;
    size_t cols;
    
    if(fscanf(file, "%zu %zu", &rows, &cols) != 2)
        return false;
    m->columns = cols;
    v_resize_int(m->a, rows+1);

    int curr_element;
    for(size_t i = 0; i < rows; ++i){
        v_set_int(m->a, i, v_size_int(m->b));
        for(size_t j = 0; j < cols; ++j){
            if(fscanf(file, "%i", &curr_element) != 1)
                return false;
            if(curr_element != 0){
                v_push_back_int(m->b, j);
                v_push_back_int(m->c, curr_element);
            }
        }
    }
    v_set_int(m->a, rows, v_size_int(m->b));
    return true;
}

static bool _print_v_int(FILE* file, vector_int* v, const char* ch) {
    if(fprtinf(file, "%s", ch) == 0)
            return false;
    for(size_t i = 0; i < v_size_int(v); ++i)
        if(fprintf(file, "%i ", v_get_int(v, i)) == 0)
            return false;
    if(fprtinf(file, "%c", '\n') == 0)
            return false;

    return true;
}

bool m_print(matrix*m, FILE* file, matrix_io_mode mode){
    size_t rows = v_size(m->a) - 1;
    size_t size_b = v_size(m->b);

    if(mode == HUMAN) {
        size_t index_b = 0;
        for(size_t i = 0; i < rows; ++i){
            for(size_t j = 0; j < m->columns; ++j){
                if(index_b < v_get_int(m->a, i + 1)\
                  && v_get_int(m->b, index_b) == j){
                    if(fprintf(file, "%i ", v_get_int(m->c, index_b)) == 0)
                        return false;
                    index_b++;
                }
                else {
                    if(fprintf(file, "%i ", 0) == 0)
                        return false;
                }
            }
            if(fprintf(file, "%c", '\n') == 0)
                return false;
        }    
    }
    else if(mode == INTERNAL) {
        _print_v_int(file, m->a, "a");
        _print_v_int(file, m->b, "b");
        _print_v_int(file, m->c, "c");

    }

    return true;
}

static size_t _find_col_idx_b(matrix* m, size_t row, size_t col){
    size_t index_b = v_get_int(m->a, row);
    size_t index_b_end = v_get_int(m->a, row + 1);
    
    for(; index_b < index_b_end; ++index_b){
        if(v_get_int(m->b, index_b) == col)
            return index_b;
    }

    return NOT_AT_INDEX;
}

int m_get(matrix* m, size_t row, size_t col){
    size_t index_b = _find_col_idx_b(m, row, col);

    if(index_b == NOT_AT_INDEX)
        return 0;
    return v_get_int(m->c, index_b);
}

void m_set(matrix* m, size_t row, size_t col, int  val){
    size_t index_b = _find_col_idx_b(m, row, col);

    if(index_b == NOT_AT_INDEX)
        return;
    v_set_int(m->c, index_b, val);
}

m_iter m_begin(matrix* m){
    m_iter iter;

    iter.m = m;
    iter.row = 0;
    iter.index_b = 0;

    return iter;
}

m_iter m_begin_by_row(matrix* m, size_t row){
    m_iter iter;

    iter.m = m;
    iter.row = row;
    iter.index_b = v_get_int(m->a, row);

    return iter;
}

//TODO
m_iter m_begin_by_col(matrix* m, size_t col){
    m_iter iter;

    iter.m = NULL;

    return iter;
}


m_iter m_end(matrix* m){
    m_iter iter;

    iter.m = m;
    iter.row = v_size_int(m->a)-1;
    iter.index_b = v_get_int(m->a, iter.row);

    return iter;
}

m_iter m_end_by_row(matrix* m, size_t row){
    m_iter iter;

    iter.m = m;
    iter.row = row+1;
    iter.index_b = v_get_int(m->a, row+1);

    return iter;
}

//TODO
m_iter m_end_by_col(matrix* m, size_t col){
    m_iter iter;

    iter.m = NULL;

    return iter;
}