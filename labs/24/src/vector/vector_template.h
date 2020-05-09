#ifdef T
#include "template/template.h"
#include <stdlib.h>
#include <stdbool.h>
#define VECTOR TEMPLATE(T,v)

typedef struct { 
    T* buf;
    size_t cap;
    size_t size;
} VECTOR;

// Initializes a vector so that it can be used
bool TEMPLATE(T, v_init)(VECTOR **v);
//  After using the vector, call this function 
void TEMPLATE(T, v_deinit)(VECTOR **v);

//  Returns size of the vector
size_t TEMPLATE(T, v_size)(VECTOR *v);
//  Returns true if vector is empty 
bool   TEMPLATE(T, v_is_empty)(VECTOR *v);

//  Changes size of the vector 
bool TEMPLATE(T, v_resize)(VECTOR *v, size_t new_size);
//  Adds val to the end of the vector 
bool TEMPLATE(T, v_push_back)(VECTOR *v, T val);

//  Changes value of the i-th element 
void TEMPLATE(T, v_set)(VECTOR *v, size_t i, T val);
//  Returns value of the i-th element
T    TEMPLATE(T, v_get)(VECTOR *v, size_t i);

//  Stack implementation 
T    TEMPLATE(T, v_pop_top)(VECTOR *v);

#undef VECTOR
#endif