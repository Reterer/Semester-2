#pragma once
#include "vector/vector.h"

typedef struct {
    vector_int* CIP;
    vector_int* PI;
    vector_int* YE;
    size_t row;
    size_t col;
} matrix;