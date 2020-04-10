#pragma once
#include <stdio.h>
#include <stdbool.h>

#include "enum.h"
#define T unit

typedef struct treenode treenode;
typedef treenode* treenodeptr;

struct treenode{
    unit val;
    treenodeptr brother;
    treenodeptr child;
};

bool t_init(treenodeptr* tree);
void t_deinit(treenodeptr* tree);

bool t_insert_before(treenodeptr* tree, T val);
void t_remove(treenodeptr* tree);
bool t_add(treenodeptr root, int idx, T val);

void t_print(FILE* f, treenodeptr tree);

treenodeptr t_find_node_by_idx(treenodeptr root, const int idx);