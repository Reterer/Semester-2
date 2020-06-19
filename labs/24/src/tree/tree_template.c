#include <stdlib.h>
#include <stdbool.h>

#define TREE TEMPLATE(T,tree)

bool TEMPLATE(T,tree_init)(TREE **tree) {
    *tree = NULL;
    return true;
}

TREE *TEMPLATE(T,tree_make)(){
    TREE *node = malloc(sizeof(TREE));
    if(node == NULL)
        return node;
        
    node->l = NULL;
    node->r = NULL;
    return malloc(sizeof(TREE));
}

void TEMPLATE(T,tree_deinit)(TREE **tree) {
    if(*tree == NULL)
        return;
    TEMPLATE(T,tree_remove)(tree);
}

void TEMPLATE(T,tree_remove)(TREE **tree){
    if(*tree == NULL)
        return;
    TEMPLATE(T,tree_remove)(&(*tree)->l);
    TEMPLATE(T,tree_remove)(&(*tree)->r);
    free(*tree);
    *tree = NULL;
}

bool TEMPLATE(T,tree_insert)(TREE **tree, tree_ins mod, T val){
    TREE *node = malloc(sizeof(TREE));
    if(node == NULL)
        return false;

    node->val = val;
    node->l = NULL;
    node->r = NULL;

    if(*tree == NULL){
        *tree = node;
        return true;
    }

    if(mod == INS_LEFT)
        node->l = *tree;
    else if(mod == INS_RIGH)
        node->r = *tree;
    
    *tree = node;
    return true;
}

#undef TREE