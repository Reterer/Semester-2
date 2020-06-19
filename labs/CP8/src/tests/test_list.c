#include "log/log.h"

#define T int
#include "list/list_template.c"
#undef T

static int_listptr _make_list(){
    int_listptr list;
    int_list_init(&list);
    return list;
}

void test_list_init(){
    int_listptr list = _make_list();
    int_list_deinit(&list);
}


void test_push_front(){
    int_listptr list = _make_list();
    int_list_push_front(list, 42);

    TEST(list->cap == MIN_CAP && list->size == 1 && list->first == MIN_CAP-1);
    TEST(int_list_pop_front(list) == 42);
    TEST(list->cap == MIN_CAP && list->size == 0 && list->first == NOT_AN_INDEX);
    
    int_list_deinit(&list);
}

void test_push_back(){
    int_listptr list = _make_list();

    int_list_push_back(list, 42);
    TEST(int_list_pop_front(list) == 42);


    int_list_push_back(list, 7);
    int_list_push_back(list, 42);
    int_list_pop_front(list);
    TEST(int_list_pop_front(list) == 42);
    
    int_list_deinit(&list);
}

void test_size(){
    int_listptr list = _make_list();
    
    TEST(int_list_is_empty(list) == true && int_list_get_size(list) == 0);

    int_list_push_front(list, 42);
    int_list_push_back(list, 42);
    int_list_push_front(list, 42);
    int_list_push_back(list, 42);
    int_list_pop_front(list);
    int_list_pop_front(list);

    TEST(int_list_is_empty(list) == false && int_list_get_size(list) == 2);

    int_list_deinit(&list);
}

void test_begin(){
    int_listptr list = _make_list();

    int_list_iterator li1 = int_list_begin(list);
    TEST(li1.prev_el == NOT_AN_INDEX);

    int_list_push_front(list, 42);
    int_list_iterator li2 = int_list_begin(list);
    TEST(li2.prev_el == NOT_AN_INDEX\
    && int_list_iterator_get_val(li2) == 42);

    int_list_deinit(&list);
}

void test_end(){
    int_listptr list = _make_list();

    int_list_iterator li1 = int_list_end(list);
    TEST(li1.prev_el = NOT_AN_INDEX);

    int_list_push_front(list, 42);
    int_list_iterator li2 = int_list_end(list);
    TEST(li2.prev_el == 3);

    int_list_deinit(&list);
}

void test_li_get_set(){
    int_listptr list = _make_list();

    int_list_push_back(list, 42);
    int_list_iterator li = int_list_begin(list);
    TEST(int_list_iterator_get_val(li) == 42);

    int_list_iterator_set_val(li, 7);
    TEST(int_list_iterator_get_val(li) == 7);

    int_list_deinit(&list);
}

void test_li_next_and_is_equals(){
    int_listptr list = _make_list();

    bool is_succ = true;

    int from = 0;
    int to   = 100;
    for(int i = from; i < to; ++i){
        int_list_push_back(list, i);
    }

    int curr_el_val = 0;
    int_list_iterator end = int_list_end(list);
    int_list_iterator it  = int_list_begin(list);    
    while(!int_list_iterator_is_equals(it, end)){
        if(int_list_iterator_get_val(it) != curr_el_val)
                is_succ = false;
        int_list_iterator_next(&it);
        curr_el_val++;
    }
    TEST(is_succ == true);
    int_list_deinit(&list);
}

void test_li_insert_before(){
    int_listptr list = _make_list();

    int_list_iterator it = int_list_begin(list);
    int_list_iterator_insert_before(&it, 42);

    int_list_iterator it2 = int_list_begin(list);
    TEST(int_list_iterator_get_val(it2) == 42);
    
    int_list_iterator_insert_before(&it, 7);
    int_list_iterator_next(&it2);
    TEST(int_list_iterator_get_val(it2) == 7\
    && int_list_iterator_is_equals(it, int_list_end(list)));
    
    int_list_deinit(&list);
}

void test_li_remove(){
    int_listptr list = _make_list();

    int_list_iterator it = int_list_begin(list);
    int_list_iterator_insert_before(&it, 42);

    int_list_iterator it2 = int_list_begin(list);
    int_list_iterator_remove(&it2);
    TEST(int_list_iterator_is_equals(int_list_begin(list), int_list_end(list)));
    
    it = int_list_begin(list);
    int_list_iterator_insert_before(&it, 7);
    int_list_iterator_insert_before(&it, 42);

    it2 = int_list_begin(list);
    int_list_iterator_remove(&it2);
    TEST(int_list_iterator_get_val(it2) == 42);
    
    int_list_deinit(&list);
}

void test_list(){
    TEST_START();
    test_list_init();
    test_push_front();
    test_push_back();
    test_size();
    test_begin();
    test_end();
    
    test_li_get_set();
    test_li_next_and_is_equals();
    test_li_insert_before();
    test_li_remove();
}