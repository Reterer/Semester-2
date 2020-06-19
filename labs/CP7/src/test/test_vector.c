#include <log/log.h>
#include "../vector/vector.h"

static void test_init(){
    vector_int* v;
    v_init_int(&v);

    TEST(v->buf == NULL && v->cap == 0 && v->size == 0);
    v_deinit_int(&v);
}

static vector_int* _make_not_empty_vector(){
    vector_int* v;
    v_init_int(&v);
    v_push_back_int(v, 10);
    v_push_back_int(v, 42);
    v_push_back_int(v, 503);
    return v;
}

static void test_size_and_push_back(){
    vector_int* v_not_empty = _make_not_empty_vector();
    vector_int* v_empty; v_init_int(&v_empty);

    TEST(v_is_empty_int(v_empty) == true\
      && v_is_empty_int(v_not_empty) == false\
      && v_size_int(v_empty) == 0\
      && v_size_int(v_not_empty) == 3);
    TEST(v_get_int(v_not_empty, 1) == 42);
    v_deinit_int(&v_empty);
    v_deinit_int(&v_not_empty);
}

static void test_resize(){
    vector_int* v;
    v_init_int(&v);

    bool f = true;
    v_resize_int(v, 2);
    f &= v->size == 2 && v->cap == 4;
    v_resize_int(v, 100);
    f &= v->size == 100 && v->cap == 100;
    v_resize_int(v, 80);
    f &= v->size == 80 && v->cap == 100;
    v_resize_int(v, 100);
    f &= v->size == 100 && v->cap == 100;
    v_resize_int(v, 1);
    f &= v->size == 1 && v->cap == 4;

    TEST(f);
    v_deinit_int(&v);
}

static void test_get_set(){
    vector_int* v = _make_not_empty_vector();

    v_set_int(v, 0, 15);

    TEST(v_get_int(v, 0) == 15);
    v_deinit_int(&v);
}

void test_vector(){
    TEST_START();
    test_init();
    test_size_and_push_back();
    test_resize();
    test_get_set();
}
