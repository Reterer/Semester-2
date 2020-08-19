#pragma once
#include "table.h"

void tb_sort(table tb);
int  tb_binsearch(table tb, tb_elem key);
bool tb_is_sorted(table tb);