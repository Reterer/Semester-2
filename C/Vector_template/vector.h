#ifdef T
#include <stdbool.h>
#include <stdlib.h>
#include "template.h"
#define VECTOR TEMPLATE(vector, T)

typedef struct {
    T* data;
    size_t size;
    size_t capacity;
}  VECTOR;

void    TEMPLATE(v_init,T)(VECTOR* v);
void    TEMPLATE(v_deinit,T)(VECTOR* v);

size_t  TEMPLATE(v_get_size,T)(VECTOR* v);
bool    TEMPLATE(v_set_size,T)(VECTOR* v, size_t size);

T       TEMPLATE(v_get,T)(VECTOR* v, size_t index);
void    TEMPLATE(v_set,T)(VECTOR* v, size_t index, T val);

#undef VECTOR
#endif