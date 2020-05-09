#include <math.h>
#include "token/operation/operation.h"

typedef struct{
    int ch;         // Символическое представление
    enum {          
        AS_L,       // Левая ассоциативность
        AS_R        // Правая ассоциативность
    } assoc;
    int priority;   // Приоритет
    double (*calc)(double, double); // Функция операции
} op;

double add(double l, double r){
    return l + r;
}
double minus(double l, double r){
    return l - r;
}
double mult(double l, double r){
    return l * r;
}
double divide(double l, double r){
    return l / r;
}

double unary_minus(double l, double r){
    return -r;
}

// Список операций
static const op op_info[] = {
    {'+', AS_L, 1, add},
    {'-', AS_L, 1, minus},
    {'*', AS_L, 2, mult},
    {'/', AS_L, 2, divide},
    {'^', AS_R, 3, pow},
    {'~', AS_R, 4, unary_minus}
};

operation char_to_op(int ch){
    for(operation op = 0; op < OP_UNK; ++op){
        if(op_info[op].ch == ch)
            return op;
    }
    return OP_UNK;
}

bool isoperator(int ch){
    return char_to_op(ch) != OP_UNK;
}

int op_to_char(operation op){
    if(op == OP_UNK)
        return '?';
    return op_info[op].ch;
}

double calc_op(operation op, double a, double b){
    if (op == OP_UNK) {
        return NANOP;
    }
    return op_info[op].calc(a, b);
}

bool should_pop_out(operation a, operation b){
    if(a == OP_UNK || b == OP_UNK)
        return false;

    if(op_info[a].assoc == AS_L){
       return op_info[b].priority >= op_info[a].priority; 
    } else {
       return op_info[b].priority > op_info[a].priority; 
    }
}