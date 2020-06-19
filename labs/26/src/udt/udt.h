#pragma once
#include <stdbool.h>

typedef struct {
    int val;
    int key;
} data_type;

#define T data_type
#include "vector/vector_template.h"
#undef T

typedef struct {
    data_type_v *vec;
} udt;

bool udt_init(udt **u);
void udt_deinit(udt **u);

bool udt_is_empty(udt *u);
size_t udt_size(udt *u);

data_type udt_pop(udt *u);
bool udt_push(udt *u, data_type data);
