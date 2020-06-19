#pragma once
#include <stdio.h>
#include <stdbool.h>

#include "enum/enum.h"

typedef struct treenode treenode;
typedef treenode* treenodeptr;

struct treenode{
    unit val;
    treenodeptr brother;
    treenodeptr child;
};

bool t_init(treenodeptr* tree);
void t_deinit(treenodeptr* tree);

bool t_insert_before(treenodeptr* tree, unit val);

void t_remove(treenodeptr* root, char* path);
bool t_add(treenodeptr* root, char* path, unit val);

void t_print(FILE* f, treenodeptr* tree);

void t_func(FILE* f, treenodeptr* root);

treenodeptr* t_find_node_by_path(treenodeptr* root, char* path);