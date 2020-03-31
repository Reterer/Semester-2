#ifndef MIN_CAP
#define MIN_CAP 4
#endif

#ifdef T

#include <stdlib.h>
#include <vector/vector_template.h>
#include <log/log.h>

#define VECTOR TEMPLATE(vector, T)

bool TEMPLATE(v_init, T)(VECTOR** v){
    *v = malloc(sizeof(VECTOR));
    if(*v == NULL)
        return false;

    (*v)->buf  = NULL;
    (*v)->cap  = 0;
    (*v)->size = 0;
    return true;
}

void TEMPLATE(v_deinit, T)(VECTOR** v){
    if(*v != NULL){
        free((*v)->buf);
        free(*v);
    }
}

size_t TEMPLATE(v_size, T)(VECTOR* v){
    return v->size;
}

bool TEMPLATE(v_is_empty, T)(VECTOR* v){
    return v->size == 0;
}

static bool TEMPLATE(_v_grow_cap, T)(VECTOR* v, size_t new_size){
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

static void TEMPLATE(_v_reduce_cap, T)(VECTOR* v, size_t new_size){
    size_t new_cap = new_size * 3 / 2;
    if(new_cap > v->cap)
        new_cap = v->cap;
    if(new_cap < MIN_CAP)
        new_cap = MIN_CAP;

    T* new_buf = realloc(v->buf, sizeof(T)*new_cap);
    v->buf = new_buf;
    v->cap = new_cap;
}

bool TEMPLATE(v_resize, T)(VECTOR* v, size_t new_size){
    if(new_size > v->cap){
        if(TEMPLATE(_v_grow_cap, T)(v, new_size) == false)
            return false;
    }
    else if(new_size < v->size){
        TEMPLATE(_v_reduce_cap, T)(v, new_size);
    }
    v->size = new_size;
    return true;
}

bool TEMPLATE(v_push_back, T)(VECTOR* v, T val){
    if(v->size == v->cap)
        if(TEMPLATE(_v_grow_cap, T)(v, v->size+1) == false)
            return false;
    
    v->buf[v->size] = val;
    v->size++;
    return true;
}

void TEMPLATE(v_set, T)(VECTOR* v, size_t i, T val){
    if(v->size <= i){
        LOG_ERR("Array index out of bounds");
        exit(1);
    }

    v->buf[i] = val;
}

T TEMPLATE(v_get, T)(VECTOR* v, size_t i){
    if(v->size <= i){
        LOG_ERR("Array index out of bounds");
        exit(1);
    }

    return v->buf[i];
}

bool TEMPLATE(v_equals,T)(VECTOR* a, VECTOR* b){
    if(a->size != b->size)
        return false;
    
    for(size_t i = 0; i < a->size; ++i){
        if(a->buf[i] != b->buf[i])
            return false;
    }

    return true;
}

#undef vector
#endif