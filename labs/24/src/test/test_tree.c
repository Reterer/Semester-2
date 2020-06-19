#include "log/log.h"

// Само дерево
#define T int
#include "tree/tree_template.h"
#include "tree/tree_template.c"
#undef T

// Тестирует возможность инцилизации и деинцилизации дерева
void test_init_deinit(){
    int_tree *tr;
    TEST(int_tree_init(&tr));
    int_tree_deinit(&tr);
}

// Тестируется функции insert
void test_insert(){
    int_tree *tr;
    int_tree_init(&tr);

    int_tree_insert(&tr, INS_LEFT, 42);
    TEST(tr->val == 42);

    int_tree_insert(&tr, INS_LEFT, 7);
    TEST(tr->val == 7 && tr->l->val == 42);

    int_tree_insert(&tr, INS_RIGH, 6);
    TEST(tr->val == 6 && tr->r->val == 7);

    int_tree_insert(&tr->l, INS_LEFT, -42);
    TEST(tr->l->val == -42);

    int_tree_deinit(&tr);
}

void tree_test(){
    test_init_deinit();
    test_insert();
}