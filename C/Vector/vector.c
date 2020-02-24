#include "vector.h"

VectorInt* makeVectorInt(int size){
    VectorInt* res = (VectorInt*) malloc(sizeof(VectorInt));
    res->_currmass = NULL;
    VectorIntResize(res, size);
    return res;
}

void delVectorInt(VectorInt* vec){
    free(vec->_currmass);
    free(vec);
}

int VectorIntIsEmpty(VectorInt* vec){
    if (vec->size)
        return 0;
    else
        return 1;
}
int VectorIntLen(VectorInt* vec){
    return vec->size;
}

void VectorIntSet(VectorInt* vec, int index, int value){
    vec->_currmass[index] = value;    
}

int VectorIntGet(VectorInt* vec, int index){
    return vec->_currmass[index];
}

void VectorIntResize(VectorInt* vec, int size){
    vec->size = size;
    vec->_currmass = (int*) realloc(vec->_currmass, sizeof(int)*size);
}

int VectorIntEq(VectorInt* A, VectorInt* B){
    if(A->size != B->size) return 0;
    for(int i = 0 ; i < A->size; ++i){
        if(A->_currmass[i] != B->_currmass[i])
            return 0;
    }
    return 1;
}
