#ifdef T
#include <template.h>
#include <stdlib.h>
#include <stdbool.h>
#define VECTOR TEMPLATE(vector, T)

typedef struct { 
    T* buf;
    size_t cap;
    size_t size;
} VECTOR;

/* Initializes a vector so that it can be used */
bool TEMPLATE(v_init, T)(VECTOR** v);
/* After using the vector, call this function */
void TEMPLATE(v_deinit, T)(VECTOR** v);

/* Returns size of the vector*/
size_t TEMPLATE(v_size, T)(VECTOR* v);
/* Returns true if vector is empty */
bool   TEMPLATE(v_is_empty, T)(VECTOR* v);

/* Changes size of the vector */
bool TEMPLATE(v_resize, T)(VECTOR* v, size_t new_size);
/* Adds val to the end of the vector */
bool TEMPLATE(v_push_back, T)(VECTOR* v, T val);

/* Changes value of the i-th element */
void TEMPLATE(v_set, T)(VECTOR* v, size_t i, T val);
/* Returns value of the i-th element*/
T    TEMPLATE(v_get, T)(VECTOR* v, size_t i);

/* Returns true if a and b are equal */
bool TEMPLATE(v_equals,T)(VECTOR* a, VECTOR* b);

#undef VECTOR
#endif