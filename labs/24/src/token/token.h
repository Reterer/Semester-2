#pragma once
#include <stdio.h>
#include "token/operation/operation.h"

typedef enum {
    TOK_NONE,       // Не знащащий/ошибочный токен
    TOK_CONST,      // Числовая константа
    TOK_VAR,        // Именная переменная 
    TOK_OP,         // Операция
    TOK_LBR,        // Левая скобка
    TOK_RBR         // Правая скобка
} token_type;

typedef struct {
    token_type type;
    char varname[32];
    double constval;
    operation op;
} token;

// Объявления очереди типа token
#define T token
#include "queue/queue_template.h"
// Объявления вектора типа token
#include "vector/vector_template.h"
#undef T

typedef enum {
    RER_OK,  // Успешное считывание выражения
    RER_ERR, // Возникла ошибка при считывании expr
    RER_EOF, // Был достигнут конец файла
} read_expr_res;
// Считывает из f выражение в q_tok
read_expr_res read_expr(token_queue *q_tok, FILE *f);

// Вывод токенов из q_tok в f в текстовом представлении
// Очищает очередь!!
void print_expr(token_queue *q_tok, FILE *f);

typedef enum {
    SSR_OK,             // Всё хорошо
    SSR_ERR_INIT,       // Ошибка init vector
    SSR_ERR_BR_BALANCE, // Ошибка баланса скобок
} sort_station_res;
// Переводит инфиксную запись токенов q_src в обратную польскую q_dest
sort_station_res sort_station(token_queue *q_dest, token_queue *q_src);
