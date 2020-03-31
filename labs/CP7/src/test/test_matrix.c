#include <log/log.h>
#include <stdio.h>
#include "../matrix.h"

#define MATRIX_PATH "test_files/matrix.txt"
#define MATRIX_EMPTY_PATH "test_files/empty_matrix.txt"

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

void test_get_set_correct(){
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
    m_iter begin_row = m_begin_by_row(m, 5);

    TEST(begin.row == 0 && begin.index_b == 0\
      && begin_row.row == 5 && begin_row.index_b == 6);

    m_deinit(&m);
}

void test_end(){
    matrix* m = _make_matrix(MATRIX_PATH);
    
    m_iter end = m_end(m);
    m_iter end_row = m_end_by_row(m, 0);

    TEST(end.row == 6 && end.index_b == 13\
      && end_row.row == 1 && end_row.index_b == 0);

    m_deinit(&m);
}

void test_matrix(){
    TEST_START();
    test_print_and_read();
    test_get_set_correct();
    test_begin();
    test_end();
}