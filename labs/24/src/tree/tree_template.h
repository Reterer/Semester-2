#include <stdbool.h>
#include "template/template.h"

#define TREE TEMPLATE(T,tree)

#ifndef TREE_INS
#define TREE_INS
typedef enum {
    INS_LEFT,
    INS_RIGH,
    INS_NONE,
} tree_ins;
#endif

typedef struct TREE TREE;
struct TREE{
    T val;
    TREE *l;
    TREE *r;
};

// init - инцилизируйте дерево перед его использованием
bool TEMPLATE(T,tree_init)(TREE **tree);
// make - возвращает указатель на новую ноду
TREE *TEMPLATE(T,tree_make)();

// deinit - освобождает память, уничтожает дерево
void TEMPLATE(T,tree_deinit)(TREE **tree);

// remove - удаляет поддерево tree
void TEMPLATE(T,tree_remove)(TREE **tree);

// insert - вставляет новую ноду в сыновья tree 
// mod - куда вставится новая нода INS_LEFT || INS_RIGH || INS_NONE
bool TEMPLATE(T,tree_insert)(TREE **tree, tree_ins mod, T val);


#undef TREE