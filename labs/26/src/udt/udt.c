#include "udt/udt.h"

#define T data_type
#include "vector/vector_template.c"
#undef T

bool udt_init(udt **u){
    *u = malloc(sizeof(udt));
    if(*u == NULL)
        return false;

    if(data_type_v_init(&(*u)->vec) == false){
        free(*u);
        return false;
    }
    return true;
}

void udt_deinit(udt **u){
    if(*u == NULL)
        return;
    
    data_type_v_deinit(&(*u)->vec);
    free(*u);
}

bool udt_is_empty(udt *u){
    return data_type_v_is_empty(u->vec);
}
size_t udt_size(udt *u){
    return data_type_v_size(u->vec);
}

data_type udt_pop(udt *u){
    size_t v_size = data_type_v_size(u->vec);
    data_type res = data_type_v_get(u->vec, v_size-1);
    data_type_v_resize(u->vec, v_size-1);
    return res;
}
bool udt_push(udt *u, data_type data){
    size_t v_size = data_type_v_size(u->vec);
    if(data_type_v_resize(u->vec, v_size+1) == false){
        return false;
    }

    data_type_v_set(u->vec, v_size, data);
    return true;
}