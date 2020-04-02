#include <stdio.h>
#include <limits.h>
#include <log/log.h>
#include "matrix.h"

bool m_init(matrix** m) {
    *m = malloc(sizeof(matrix));
    if(*m == NULL)
        return false;

    v_init_int(&(*m)->a);
    v_init_int(&(*m)->b);
    v_init_double(&(*m)->c);
    (*m)->columns = 0;

    return true;
}

void m_deinit(matrix** m) {
    if(*m == NULL)
        return;
    
    v_deinit_int(&(*m)->a);
    v_deinit_int(&(*m)->b);
    v_deinit_double(&(*m)->c);
    free(*m);
}

bool m_read(matrix* m, FILE* file){
    size_t rows;
    size_t cols;
    
    if(fscanf(file, "%zu %zu", &rows, &cols) != 2)
        return false;
    m->columns = cols;
    v_resize_int(m->a, rows+1);

    double curr_element;
    for(size_t i = 0; i < rows; ++i){
        v_set_int(m->a, i, v_size_int(m->b));
        for(size_t j = 0; j < cols; ++j){
            if(fscanf(file, "%lf", &curr_element) != 1)
                return false;
            if(curr_element != 0){
                v_push_back_int(m->b, j);
                v_push_back_double(m->c, curr_element);
            }
        }
    }
    v_set_int(m->a, rows, v_size_int(m->b));
    return true;
}

static bool _print_v_int(FILE* file, vector_int* v, const char* ch) {
    if(fprintf(file, "%s", ch) == 0)
            return false;
    for(size_t i = 0; i < v_size_int(v); ++i)
        if(fprintf(file, "%i ", v_get_int(v, i)) == 0)
            return false;
    if(fprintf(file, "%c", '\n') == 0)
            return false;

    return true;
}

static bool _print_v_double(FILE* file, vector_double* v, const char* ch) {
    if(fprintf(file, "%s", ch) == 0)
            return false;
    for(size_t i = 0; i < v_size_double(v); ++i)
        if(fprintf(file, "%lf ", v_get_double(v, i)) == 0)
            return false;
    if(fprintf(file, "%c", '\n') == 0)
            return false;

    return true;
}

bool m_print(matrix*m, FILE* file, matrix_io_mode mode){
    size_t rows = v_size_int(m->a) - 1;

    if(mode == HUMAN) {
        size_t index_b = 0;
        for(size_t i = 0; i < rows; ++i){
            for(size_t j = 0; j < m->columns; ++j){
                if(index_b < v_get_int(m->a, i + 1)\
                  && v_get_int(m->b, index_b) == j){
                    if(fprintf(file, "%-4.2lf ", v_get_double(m->c, index_b)) == 0)
                        return false;
                    index_b++;
                }
                else {
                    if(fprintf(file, "%-4c ", '.') == 0)
                        return false;
                }
            }
            if(fprintf(file, "%c", '\n') == 0)
                return false;
        }    
    }
    else if(mode == INTERNAL) {
        _print_v_int(file, m->a, "a ");
        _print_v_int(file, m->b, "b ");
        _print_v_double(file, m->c, "c ");

    }

    return true;
}

size_t m_get_count_rows(matrix* m){
    return v_size_int(m->a)-1;
}

size_t m_get_count_cols(matrix* m){
    return m->columns;
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

double m_get(matrix* m, size_t row, size_t col){
    if(row >= v_size_int(m->a) || col >= m->columns){
        LOG_ERR("Matrix index out of bounds");
        exit(1);
    }

    size_t index_b = _find_col_idx_b(m, row, col);

    if(index_b == NOT_AT_INDEX)
        return 0;
    return v_get_double(m->c, index_b);
}

void m_set(matrix* m, size_t row, size_t col, double  val){
    if(row >= v_size_int(m->a) || col >= m->columns){
        LOG_ERR("Matrix index out of bounds");
        exit(1);
    }
    size_t index_b = _find_col_idx_b(m, row, col);

    if(index_b == NOT_AT_INDEX)
        return;
    v_set_double(m->c, index_b, val);
}

static size_t _find_row_by_index_b(matrix* m, size_t index_b){
    size_t rows = v_size_int(m->a)-1;
    size_t row = 0;

    while(rows != row && v_get_int(m->a, row+1) <= index_b)
        row++;
    
    return row;
}

m_iter m_begin(matrix* m){
    m_iter iter;

    iter.m = m;
    iter.index_b = 0;
    iter.row = _find_row_by_index_b(m, iter.index_b);

    return iter;
}

m_iter m_begin_row(matrix* m, size_t row){
    m_iter iter;

    iter.m = m;
    iter.row = row;
    iter.index_b = v_get_int(m->a, row);
    while(v_get_int(m->a, iter.row+1) <= iter.index_b){
        iter.row++;
    }

    return iter;
}


m_iter m_end(matrix* m){
    m_iter iter;

    iter.m = m;
    iter.row = v_size_int(m->a)-1;
    iter.index_b = v_get_int(m->a, iter.row);

    return iter;
}

m_iter m_end_row(matrix* m, size_t row){
    size_t rows = v_size_int(m->a)-1;
    m_iter iter;

    iter.m = m;
    iter.row = row+1;
    iter.index_b = v_get_int(m->a, row+1);
    while(iter.row != rows && v_get_int(m->a, iter.row+1) <= iter.index_b){
        iter.row++;
    }
    return iter;
}

/*************************************************************/

void mi_next_col(m_iter* i){
    size_t rows = v_size_int(i->m->a)-1;
    i->index_b++;
    while(i->row != rows && v_get_int(i->m->a, i->row+1) <= i->index_b){
        i->row++;
    }
}

void mi_prew_col(m_iter* i){
    if(i->index_b == 0){
        i->row = v_size_int(i->m->a)-1;
        i->index_b = v_get_int(i->m->a, i->row);
        return;
    }

    i->index_b--;
    while(v_get_int(i->m->a, i->row) > i->index_b)
        i->row--;
}   

void mi_next_row(m_iter* i){
    size_t curr_col = v_get_int(i->m->b, i->index_b);
    size_t rows     = v_size_int(i->m->a) - 1;

    if(i->row+1 == rows){
        i->index_b = v_get_int(i->m->a, rows);
        i->row     = rows;
        return;
    }

    while(i->row+1 < rows) {
        i->row++;
        if((i->index_b = _find_col_idx_b(i->m, i->row, curr_col)) != NOT_AT_INDEX)
            return;
    }

    i->index_b = v_get_int(i->m->a, rows);
    i->row     = rows;
}

void mi_prev_row(m_iter* i){
    size_t curr_col = v_get_int(i->m->b, i->index_b);

    while(i->row > 0) {
        i->row--;
        if((i->index_b = _find_col_idx_b(i->m, i->row, curr_col)) != NOT_AT_INDEX)
            return;
    }
    i->row = v_size_int(i->m->a)-1;
    i->index_b = v_get_int(i->m->a, i->row);

}

bool mi_equals(m_iter a, m_iter b){
    return a.m == b.m && a.row == b.row\
        && a.index_b == b.index_b;
}

double  mi_get(m_iter i){
    return v_get_double(i.m->c, i.index_b);
}

void mi_set(m_iter i, double val){
    v_set_double(i.m->c, i.index_b, val);
}

size_t mi_get_col(m_iter i){
    return v_get_int(i.m->b, i.index_b);
}

size_t mi_get_row(m_iter i){
    return i.row;
}