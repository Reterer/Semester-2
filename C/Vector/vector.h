#pragma once
#include <stdlib.h>

typedef struct { 
    int* _currmass;
    int size;
} VectorInt;


VectorInt* makeVectorInt(int size);
void delVectorInt(VectorInt* vec);
int VectorIntGet(VectorInt* vec, int index);
int VectorIntEq(VectorInt* A, VectorInt* B);
int VectorIntIsEmpty(VectorInt* vec);
int VectorIntLen(VectorInt* vec);
void VectorIntSet(VectorInt* vec, int index, int value);
void VectorIntResize(VectorInt* vec, int size);
