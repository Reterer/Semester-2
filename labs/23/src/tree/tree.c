#include <stdlib.h>
#include "tree/tree.h"

#define T treenodeptr
#include "template/template.h"
#include "queue/queue_template.c"
#undef T

bool t_init(treenodeptr* tree){
    *tree = NULL;
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

bool t_insert_before(treenodeptr* tree, unit val){
    treenodeptr new_node = malloc(sizeof(treenode));
    if(new_node == NULL)
        return false;

    new_node->val = val;
    new_node->brother = *tree;
    new_node->child = NULL;

    *tree = new_node;
    return true;
}

void t_remove(treenodeptr* root, char* path){
    treenodeptr* tree = t_find_node_by_path(root, path);
    if(tree == NULL || *tree == NULL)
        return;

    treenodeptr  curr_node = *tree;
    *tree = (*tree)->brother;
    curr_node->brother = NULL;
    t_deinit(&curr_node);
}

bool t_add(treenodeptr* root, char* path, unit val){
    treenodeptr* select_node = t_find_node_by_path(root, path);
    if(select_node == NULL)
        return false;

    if(t_insert_before(select_node, val) == false){
        fprintf(stderr, "Can't malloc\n");
        return false;
    }
    return true;
}

void _t_print(FILE* f, treenodeptr tree, int level){
    if(tree == NULL)
        return;

    for(int i = 0; i < level; i++)
        fprintf(f, "|\t");

    char str_unit[MAX_UNIT_STR_LEN];
    unit_to_string(tree->val, str_unit);
    fprintf(f, "[%s]\n", str_unit);

    _t_print(f, tree->child, level+1);
    _t_print(f, tree->brother, level);
}

void t_print(FILE* f, treenodeptr* tree){
    _t_print(f, *tree, 0);
    fprintf(f, "\n");
}

void _psuh_brothers_to_queue(treenodeptr_queue *q, treenodeptr node){
    while(node != NULL){
        treenodeptr_queue_push_back(q, node);
        node = node->brother;
    }
}

bool t_func(FILE* f, treenodeptr* root){
    if(*root == NULL)
        return true;
    
    int width_prev_lvl = -1;
    int width_curr_lvl = 0;
    bool is_monotonous = true;
    
    treenodeptr_queue *curr_q;
    treenodeptr_queue *next_q;
    treenodeptr_queue_init(&curr_q);
    treenodeptr_queue_init(&next_q);

    _psuh_brothers_to_queue(curr_q, *root);
    while(!treenodeptr_queue_is_empty(curr_q)){
        treenodeptr node = treenodeptr_queue_pop(curr_q);
        width_curr_lvl++;

        node = node->child;
        _psuh_brothers_to_queue(next_q, node);

        if(treenodeptr_queue_is_empty(curr_q)){
            treenodeptr_queue *temp = next_q;
            next_q = curr_q;
            curr_q = temp;

            printf("width lvl: %i\n", width_curr_lvl);
            if(width_prev_lvl == -1)
                width_prev_lvl = width_curr_lvl;
            
            if(width_prev_lvl < width_curr_lvl){
                is_monotonous = false;
                break;
            }

            width_prev_lvl = width_curr_lvl;
            width_curr_lvl = 0;
        }
    }

    treenodeptr_queue_deinit(&curr_q);
    treenodeptr_queue_deinit(&next_q);

    return is_monotonous;
}

treenodeptr* t_find_node_by_path(treenodeptr* root, char* path){
    if(*path == '\0')
        return root;
    else if(*root == NULL){
        fprintf(stderr, "Invalid path\n");
        return NULL;
    }

    if(*path == 'c'){
        return t_find_node_by_path(&(*root)->child, path+1);
    }
    else if(*path == 'b'){
        return t_find_node_by_path(&(*root)->brother, path+1);
    }
    else{
        fprintf(stderr, "Invalid path\n");
        return NULL;    
    }
}