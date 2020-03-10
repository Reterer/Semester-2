#include <stdio.h>
#include "vector.h"

int VectorInit(Vector** vec, size_t size) {
    *vec = (Vector*) malloc(sizeof(Vector)); 
    (*vec)->_mass = (TYPE*)  malloc(sizeof(TYPE)*size);
    if (!(*vec)->_mass) {
        (*vec)->_size = 0;
        return 0;
    }
    (*vec)->_size = size;
    return 1;
}
void VectorDestroy(Vector* vec){
    free(vec->_mass);
    free(vec);
}

TYPE VectorGet(Vector* vec, size_t index){
    if(index >= vec->_size)
        printf("WARNING: OUT OF RANGE index: %lu  size: %lu\n", index, vec->_size);
    return vec->_mass[index];
}

void VectorSet(Vector* vec, size_t index, TYPE val){
    if(index >=  vec->_size)
        printf("WARNING: OUT OF RANGE index: %lu  size: %lu\n", index, vec->_size);
    vec->_mass[index] = val;
}

size_t VectorSizeGet(Vector* vec){
    return vec->_size;
}

int VectorResize(Vector* vec, size_t size){
    TYPE* newMass = (TYPE*) realloc(vec->_mass, sizeof(TYPE)*size);
    if (newMass == NULL  && size != 0)
        return 0;
    vec->_mass = newMass;
    vec->_size = size;
    return 1;
}

void VectorFill(Vector* vec, TYPE val){
    TYPE* end = vec->_mass + vec->_size;
    while( vec->_mass != --end)
        *end = val;
    vec->_mass[0] = val;
}

int VectorCopy(Vector* from, Vector* to){
    if(from->_size != to->_size)
        return 0;
    for(int i = 0; i < from->_size; ++i){
        to->_mass[i] = from->_mass[i];
    }
    return 1;
}

int VectorPushBack(Vector* vec, TYPE val){
    size_t back = VectorSizeGet(vec);
    int res = VectorResize(vec, back+1);
    if(!res)
        return res;
    VectorSet(vec, back, val);
    return res;
}

TYPE VectorBack(Vector* vec){
    size_t size = VectorSizeGet(vec)-1;
    if(size < 0)
        printf("WARNING: Back, vector is empty\n");
    return VectorGet(vec, size);
}

int VectorPopBack(Vector* vec){
    size_t size = VectorSizeGet(vec)-1;
    if(size < 0)
        printf("WARNING: PopBack, vector is empty\n");
    return VectorResize(vec, size);
}
