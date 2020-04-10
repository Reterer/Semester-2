#include <stdlib.h>
#include "tree.h"

bool t_init(treenodeptr* tree){
    *tree = malloc(sizeof(treenode));
    if(*tree == NULL)
        return false;

    (*tree)->brother = NULL;
    (*tree)->child   = NULL;
    return true;
}

void t_deinit(treenodeptr* tree){
    if((*tree) == NULL)
        return;
    t_deinit(&(*tree)->child);
    t_deinit(&(*tree)->brother);
    free(*tree);
    *tree = NULL;
}

bool t_insert_before(treenodeptr* tree, T val){
    treenodeptr new_node = malloc(sizeof(treenode));
    if(new_node == NULL)
        return false;
    new_node->val = val;
    new_node->brother = *tree;

    *tree = new_node;
    return true;
}

void t_remove(treenodeptr* tree){
    treenodeptr curr_node = *tree;
    if(*tree != NULL)
        *tree = (*tree)->brother;
    
    curr_node->brother = NULL;
    t_deinit(&curr_node);
}

bool t_add(treenodeptr root, int idx, T val){
    treenodeptr father = t_find_node_by_idx(root, idx);
    if(father == NULL)
        return false;
    if(t_insert_before(&(father->child), val) == false){
        fprintf(stderr, "Can't malloc\n");
        return false;
    }
    return true;
}

void _t_print(FILE* f, treenodeptr tree, int level, int* idx_vertix_ptr){
    if(tree == NULL)
        return;
    (*idx_vertix_ptr)++;

    for(int i = 0; i < level; i++)
        fprintf(f, "|\t");

    char str_unit[MAX_UNIT_STR_LEN];
    unit_to_string(tree->val, str_unit);
    fprintf(f, "id:%-2i [%s]\n", *idx_vertix_ptr, str_unit);

    _t_print(f, tree->child, level+1, idx_vertix_ptr);
    _t_print(f, tree->brother, level, idx_vertix_ptr);
}

void t_print(FILE* f, treenodeptr tree){
    int idx_vertix = -1;
    _t_print(f, tree, 0, &idx_vertix);
}


treenodeptr _t_find_node_by_idx(treenodeptr tree, int* curr_idx_ptr, const int idx){
    if(tree == NULL)
        return NULL;
    (*curr_idx_ptr)++;

    if(*curr_idx_ptr == idx){
        return tree;
    }
    treenodeptr child   = _t_find_node_by_idx(tree->child, curr_idx_ptr, idx);
    treenodeptr brother = _t_find_node_by_idx(tree->brother, curr_idx_ptr, idx);

    if(child != NULL)
        return child;
    else
        return brother;
}

treenodeptr t_find_node_by_idx(treenodeptr root, const int idx){
    int curr_idx = -1;
    return _t_find_node_by_idx(root, &curr_idx, idx);
}