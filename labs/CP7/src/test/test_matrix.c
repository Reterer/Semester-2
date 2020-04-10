#include <log/log.h>
#include <stdio.h>
#include "../matrix.h"

#define MATRIX_PATH "test_files/test/matrix.txt"
#define MATRIX_EMPTY_PATH "test_files/test/empty_matrix.txt"

static matrix* _make_matrix(char* path){
    matrix* m;
    FILE* file = fopen(path, "r");
    if(!file){
        char errmsg[100];
        sprintf(errmsg, "file %s missing", path);
        LOG_ERR(errmsg);
        exit(1);
    }
    m_init(&m);
    m_read(m, file);
    fclose(file);

    return m;
}

void test_print_and_read(){
    matrix* m = _make_matrix(MATRIX_EMPTY_PATH);
    m_print(m, stdout, HUMAN);
    m_print(m, stdout, INTERNAL);
    m_deinit(&m);
    
    m = _make_matrix(MATRIX_PATH);
    m_print(m, stdout, HUMAN);
    m_print(m, stdout, INTERNAL);
    m_deinit(&m);
}

void test_get_set(){
    matrix* m = _make_matrix(MATRIX_PATH);
    
    TEST(m_get(m, 0, 0) == 0.\
      && m_get(m, 1, 3) == 4.\
      && m_get(m, 5, 9) == 9.);
    
    m_set(m, 0, 0, 42.);
    m_set(m, 1, 5, 42.);
    m_set(m, 5, 9, 42.);

    TEST(m_get(m, 0, 0) == 0.\
      && m_get(m, 1, 5) == 42.\
      && m_get(m, 5, 9) == 42.);
    
    m_deinit(&m);
}

void  test_begin(){
    matrix* m = _make_matrix(MATRIX_PATH);
    
    m_iter begin = m_begin(m);

    TEST(begin.row == 1 && begin.index_b == 0);
    m_deinit(&m);
}

void test_end(){
    matrix* m = _make_matrix(MATRIX_PATH);
    
    m_iter end = m_end(m);

    TEST(end.row == 6 && end.index_b == 13);

    m_deinit(&m);
}

void test_mi_get_set(){
    matrix* m = _make_matrix(MATRIX_PATH);
    m_iter iter = m_begin(m);

    mi_set(iter, 10.);
    TEST(mi_get(iter) == 10.);
    m_deinit(&m);
}

void test_mi_next_prev_col(){
    matrix* m = _make_matrix(MATRIX_PATH);
    
    m_iter it = m_begin(m);

    mi_prew_col(&it);
    TEST(mi_equals(it, m_end(m)));

    it = m_begin(m);
    mi_next_col(&it);
    mi_prew_col(&it);
    TEST(mi_equals(it, m_begin(m)));

    it = m_end(m);
    mi_prew_col(&it);
    mi_next_col(&it);
    TEST(mi_equals(it, m_end(m)));

    it = m_begin(m);
    for(int i = 0; i < 5; i++)
        mi_next_col(&it);
    TEST(mi_get(it) == 2.);

    mi_prew_col(&it);
    TEST(mi_get(it) == 9.);

    m_deinit(&m);
}

void test_mi_next_prev_row(){
    matrix* m = _make_matrix(MATRIX_PATH);

    m_iter it = m_begin(m);
    mi_prev_row(&it);
    TEST(mi_equals(it, m_end(m)));

    it = m_begin(m);
    mi_next_col(&it);
    mi_next_row(&it);
    TEST(mi_get(it) == 3.0);

    mi_prev_row(&it);
    TEST(mi_get(it) == 4.0);

    mi_next_row(&it);
    mi_next_row(&it);
    TEST(mi_equals(it, m_end(m)));

}

void test_matrix(){
    TEST_START();
    // test_print_and_read();
    test_get_set();
    test_begin();
    test_end();

    test_mi_get_set();
    test_mi_next_prev_col();
    test_mi_next_prev_row();
}