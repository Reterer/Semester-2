#pragma once
#include <stdbool.h>
#define NANOP -1

// Список операций, операции должны быть сопоставлены с op_info
typedef enum {
    OP_ADD,
    OP_MINUS,
    OP_MULT,
    OP_DIV,
    OP_POW,
    OP_UN_MINUS,
    OP_UNK
} operation;

// Возвращает true, если есть такая операция
bool isoperator(int ch);

// Возвращает код операции ch,
// если такой операции нет вернет OP_UNK
operation char_to_op(int ch);

// Возвращает символическое представление операции
// Если op = OP_UNK, то вернет NANOP
int op_to_char(operation op);

// Выоплняет операцию op, a - левый аргумент, b - правый
double calc_op(operation op, double a, double b);

// Должен ли a вытеснить b?
bool should_pop_out(operation a, operation b); 