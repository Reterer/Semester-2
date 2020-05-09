#ifndef MIN_CAP
#define MIN_CAP 4
#endif

#ifdef T

#include <stdlib.h>
#include "template/template.h"
#include "log/log.h"

#define VECTOR TEMPLATE(T, v)

bool TEMPLATE(T, v_init)(VECTOR **v){
    *v = malloc(sizeof(VECTOR));
    if(*v == NULL)
        return false;

    (*v)->buf  = NULL;
    (*v)->cap  = 0;
    (*v)->size = 0;
    return true;
}

void TEMPLATE(T, v_deinit)(VECTOR **v){
    if(*v != NULL){
        free((*v)->buf);
        free(*v);
    }
}

size_t TEMPLATE(T, v_size)(VECTOR *v){
    return v->size;
}

bool TEMPLATE(T, v_is_empty)(VECTOR *v){
    return v->size == 0;
}

static bool TEMPLATE(T, _v_grow_cap)(VECTOR *v, size_t new_size){
    size_t new_cap = v->cap * 3 / 2;
    if(new_cap < new_size)
        new_cap = new_size;
    if(new_cap < MIN_CAP)
        new_cap = MIN_CAP;
    
    T* new_buf = realloc(v->buf, sizeof(T)*new_cap);
    if(new_buf == NULL)
        return false;
    v->buf = new_buf;
    v->cap = new_cap;

    return true;
}

static void TEMPLATE(T, _v_reduce_cap)(VECTOR *v, size_t new_size){
    if(new_size > v->cap * 4 / 9)
        return;
    
    size_t new_cap = new_size * 3 / 2;
    if(new_cap > v->cap)
        new_cap = v->cap;
    if(new_cap < MIN_CAP)
        new_cap = MIN_CAP;

    T* new_buf = realloc(v->buf, sizeof(T)*new_cap);
    v->buf = new_buf;
    v->cap = new_cap;
}

bool TEMPLATE(T, v_resize)(VECTOR *v, size_t new_size){
    if(new_size > v->cap){
        if(TEMPLATE(T, _v_grow_cap)(v, new_size) == false)
            return false;
    }
    else if(new_size < v->size){
        TEMPLATE(T, _v_reduce_cap)(v, new_size);
    }
    v->size = new_size;
    return true;
}

bool TEMPLATE(T, v_push_back)(VECTOR *v, T val){
    if(v->size == v->cap)
        if(TEMPLATE(T, _v_grow_cap)(v, v->size+1) == false)
            return false;
    
    v->buf[v->size] = val;
    v->size++;
    return true;
}

void TEMPLATE(T, v_set)(VECTOR *v, size_t i, T val){
    if(v->size <= i){
        LOG_ERR("Array index out of bounds");
        exit(1);
    }

    v->buf[i] = val;
}

T TEMPLATE(T, v_get)(VECTOR *v, size_t i){
    if(v->size <= i){
        LOG_ERR("Array index out of bounds");
        exit(1);
    }

    return v->buf[i];
}

T    TEMPLATE(T, v_pop_top)(VECTOR *v){
    T res = TEMPLATE(T, v_get)(v, TEMPLATE(T, v_size)(v)-1);
    TEMPLATE(T, v_resize)(v, TEMPLATE(T, v_size)(v)-1);
    return res;
}

#undef vector
#endif