#include "matrix.h"
#include "config.h"

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

// double max_double(double a, double b){
//     return (a > b)?a:b;
// }

// double get_eps(double a){
//     return a/EPS_DIV;
// }

// bool eq_double(double a, double b){
//     double eps = get_eps(max_double(a,b));
//     return abs_double(a-b) < eps;
// }

// bool less_double(double a, double b){
//     double eps = get_eps(max_double(a,b));
//     //TODO??
// }

void find_elems(vector_m_iter* vec, double val){
    double found_el;
    m_iter curr_el = m_begin(m);
    v_resize_m_iter(vec, 0);

    double new_found_el;
    m_iter end = m_end(m);

    found_el = mi_get(curr_el);
    while(!mi_equals(curr_el, end)){
        new_found_el = mi_get(curr_el);
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

void divide(m_iter it, double found_value){    
    size_t row = mi_get_row(it);
    m_iter curr  = m_begin_row(m, row);
    m_iter end   = m_end_row(m, row);

    while(!mi_equals(curr, end)){
        mi_set(curr, mi_get(curr)/found_value);
        mi_next_col(&curr);
    }
    
    curr = it;
    end  = m_end(m);
    mi_prev_row(&curr);
    while(!mi_equals(curr, end)){
        mi_set(curr, mi_get(curr)/found_value);
        mi_prev_row(&curr);
    }

    curr = it;
    mi_next_row(&curr);
    while(!mi_equals(curr, end)){
        mi_set(curr, mi_get(curr)/found_value);
        mi_next_row(&curr);
    }
}

void transformation_matrix(config cnfg){
    m_init(&m);
    m_read(m, cnfg.in);
    if(m_get_count_cols(m) == 0 || m_get_count_rows(m) == 0){
        LOG_ERR("The matrix is irregular in shape");
        exit(1);
    }
    double value;
    fscanf(cnfg.in, "%lf", &value);
    
    vector_m_iter* found_elems;
    v_init_m_iter(&found_elems);
    find_elems(found_elems, value);

    m_print(m, cnfg.out, INTERNAL);
    printf("Найденны следующие элементы:\n");
    for(int i = 0; i < v_size_m_iter(found_elems); ++i){
        m_iter it = v_get_m_iter(found_elems, i);
        printf("%zu\t%zu\t%-4.2lf\n", it.row, it.index_b, mi_get(it));
    }

    double found_value = mi_get(v_get_m_iter(found_elems, 0));
    for(int i = 0; i < v_size_m_iter(found_elems); ++i){
        divide(v_get_m_iter(found_elems, i), found_value);
    }

    v_deinit_m_iter(&found_elems);
    m_print(m, cnfg.out, HUMAN);
    m_deinit(&m);
}
