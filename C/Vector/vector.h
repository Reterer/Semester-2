#pragma once
#include <stdlib.h>
#define TYPE double

typedef struct {
    TYPE* _mass;
    size_t _size;
} Vector;

int VectorInit(Vector** vec, size_t size);
void VectorDestroy(Vector* vec);

TYPE VectorGet(Vector* vec, size_t index);
void VectorSet(Vector* vec, size_t index, TYPE val);

int VectorResize(Vector* vec, size_t size);
size_t VectorSizeGet(Vector* vec);

void VectorFill(Vector* vec, TYPE val);
int VectorCopy(Vector* from, Vector* to);

// PUSH BACK
// POP BACK
