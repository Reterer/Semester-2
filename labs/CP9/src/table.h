#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int key1;
    char key2[10];
    char value[10];
} tb_elem;

typedef struct {
    tb_elem* buf;
    int size;
} table;

bool tb_elem_is_smaller(tb_elem a, tb_elem b);
bool tb_elem_is_eq(tb_elem a, tb_elem b);

bool tb_read(table* tb);
void tb_deinit(table* tb);
void tb_print(table tb);
