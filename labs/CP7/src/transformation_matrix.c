#include "matrix.h"

#define EPS_DIV 1e-10

#define T m_iter
#define T_COMPARE(X,Y) (mi_equals(X, Y))
#include <vector/vector_template.c>
#undef T_COMPARE
#undef T

matrix* m;

double abs_double(double x){
    return (x < 0)?-x:x;
}

void find_elems(vector_m_iter* vec, double val){
    v_resize_m_iter(vec, 0);
    
    m_iter curr_el = m_begin(m);
    m_iter end = m_end(m);
    if(mi_equals(curr_el, end))
        return;

    double found_el = mi_get(curr_el);
    while(!mi_equals(curr_el, end)){
        double new_found_el = mi_get(curr_el);
        if(new_found_el == found_el){
            v_push_back_m_iter(vec, curr_el);
        }
        else if(abs_double(new_found_el-val) < abs_double(found_el-val)){
            found_el = new_found_el;
            v_resize_m_iter(vec, 0);
            v_push_back_m_iter(vec, curr_el);
        }
        mi_next_col(&curr_el);
    }
}

void _divide_row(m_iter it, double val){
    size_t row   = mi_get_row(it);
    m_iter curr  = m_begin_row(m, row);
    m_iter end   = m_end_row(m, row);
    
    while(!mi_equals(curr, end)){
        mi_set(curr, mi_get(curr)/val);
        mi_next_col(&curr);
    }
}

void _divide_col_without_it_el(m_iter it, double val){
    m_iter curr;
    m_iter end = m_end(m);

    curr = it;
    mi_prev_row(&curr);
    while(!mi_equals(curr, end)){
        mi_set(curr, mi_get(curr)/val);
        mi_prev_row(&curr);
    }

    curr = it;
    mi_next_row(&curr);
    while(!mi_equals(curr, end)){
        mi_set(curr, mi_get(curr)/val);
        mi_next_row(&curr);
    }
}

void divide(m_iter it, double val){    
    _divide_row(it, val);
    _divide_col_without_it_el(it, val);
}

void transformation_matrix(matrix* mat, double value){
    m = mat;
    vector_m_iter* found_elems;
    
    v_init_m_iter(&found_elems);
    find_elems(found_elems, value);

    if(!v_is_empty_m_iter(found_elems)){
        double found_value = mi_get(v_get_m_iter(found_elems, 0));
        for(int i = 0; i < v_size_m_iter(found_elems); ++i)
            divide(v_get_m_iter(found_elems, i), found_value);
    }

    v_deinit_m_iter(&found_elems);
}
