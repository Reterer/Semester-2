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

// is_token_equal - равны ли токены
bool is_token_equal(token a, token b);

#define T token
// Объявления очереди типа token
#include "queue/queue_template.h"
// Объявления вектора типа token
#include "vector/vector_template.h"
// Объявление дерева типа token
#include "tree/tree_template.h"
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
void print_expr(FILE *f, token_queue *q_tok);

typedef enum {
    PT_PN,      // Печать в польской нотации
    PT_IN,      // В инфиксной
    PT_RPN,     // В обратной польской
    PT_TREE,    // Как есть в виде иерархии дерева
} print_tree_mod;
// Вывод дерева токенов
void print_token_tree(FILE *f, token_tree *tree, const print_tree_mod mod);

typedef enum {
    SSR_OK,             // Всё хорошо
    SSR_ERR_INIT,       // Ошибка init vector
    SSR_ERR_BR_BALANCE, // Ошибка баланса скобок
} sort_station_res;
// Переводит инфиксную запись токенов q_src в обратную польскую q_dest
// Очищает q_src!!
sort_station_res sort_station(token_queue *q_dest, token_queue *q_src);

typedef enum {
    BTR_OK,         // Всё хорошо
    BTR_ERR_ARGS,   // Ошибка кол-ва аргументов (операция имеет недостаточно аргументов / слишком большое кол-во)
    BTR_ERR_TOK,    // В очереди содержался токен, которого здесь не должно быть
    BTR_ERR_INIT,   // Ошибка init vector
} build_token_tree_res;
// Строит дерево выражений из обратной польской записи
// Очищает q_tok!!
build_token_tree_res build_token_tree(token_tree **tree, token_queue *q_tok);