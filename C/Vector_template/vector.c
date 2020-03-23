#ifndef MIN_CAP
#define MIN_CAP 10
#endif

#ifdef T
#include "template.h"
#include "vector.h"
#define VECTOR TEMPLATE(vector, T)

void TEMPLATE(v_init,T)(VECTOR* v){
    v->size = 0;
    v->capacity = MIN_CAP;
}
void TEMPLATE(v_deinit,T)(VECTOR* v){
    free(v->data);
}

size_t TEMPLATE(v_get_size,T)(VECTOR* v){
    return v->size;
}

bool TEMPLATE(v_set_size,T)(VECTOR* v, size_t size){
    if (size > v->capacity){
        size_t new_c = v->capacity * 3/2;
        if(new_c < MIN_CAP)
            new_c = MIN_CAP;
        if(new_c < size)
            new_c = size;

        T* new_data = realloc(v->data, new_c * sizeof(T));
        if(!new_data)
            return false;

        v->data = new_data;
        v->capacity = new_c;
        v->size = size;
        return true;    
    } else {
        v->size = size;
        return true;
    }
}

T TEMPLATE(v_get,T)(VECTOR* v, size_t index){
    return v->data[index];
}

void TEMPLATE(v_set,T)(VECTOR* v, size_t index, T val){
    v->data[index] = val;
}

#undef VECTOR
#endif