#include <stdio.h>
#include <stdlib.h>

#include "token/token.h"
#include "log/log.h"

void log_err_and_exit(const char *str){
    LOG_ERR(str);
    exit(1);
}

void clean_queue(token_queue *q){
    while(!token_queue_is_empty(q))
        token_queue_pop(q);
}

bool tok_is_op(token tok, operation op){
    return tok.type == TOK_OP && tok.op == op;
}

// Своравчивает множители в разность кубов
void    tranform_token_tree(token_tree **node){
    if(*node == NULL)
        return;

    // Обоходим дерево, начинаем работать снизу вверх
    // Что бы изменить все вхождения за один обход
    tranform_token_tree(&(*node)->l);
    tranform_token_tree(&(*node)->r);

    // Проверяем первый уровень, если node не операция *, то выходим  
    if(!tok_is_op((*node)->val, OP_MULT))
        return;

    // Находим множители и выделяем a и b, основываясь на first
    token_tree *first  = NULL; // (a-b) или (~b+a)
    token_tree *second = NULL; // (a^2 + a*b + b^2)
    token_tree *node_a;
    token_tree *node_b;

    // Проверяем второй уровень на операции + и +
    if(tok_is_op((*node)->l->val, OP_ADD) && tok_is_op((*node)->r->val, OP_ADD)){
        if(tok_is_op((*node)->l->l->val, OP_UN_MINUS)){
            first = (*node)->l;
            second = (*node)->r;
        }
        else if(tok_is_op((*node)->r->l->val, OP_UN_MINUS)){
            first = (*node)->r;
            second = (*node)->l;    
        }else{
            return;
        }
        node_a = first->r;
        node_b = first->l->r; // правый аргумент унарного минуса
    }
    // Иначе находим вершину с операцией -
    else{
        if(tok_is_op((*node)->l->val, OP_MINUS) && tok_is_op((*node)->r->val, OP_ADD)){
            first = (*node)->l;
            second = (*node)->r;
        }else if(tok_is_op((*node)->l->val, OP_ADD) && tok_is_op((*node)->r->val, OP_MINUS)){
            first = (*node)->r;
            second = (*node)->l;
        }else{
            return;
        }
        node_a = first->l;    
        node_b = first->r;
    }

    // Проверяем на то, что a и b - константы либо переменные
    if(!(node_a->val.type == TOK_VAR || node_a->val.type == TOK_CONST))
        return;
    if(!(node_b->val.type == TOK_VAR || node_b->val.type == TOK_CONST))
        return;

    // Поддерево first считаем проверенным. Проверям поддерево second
    token_tree *node_second_pow_or_mul = NULL;   // ab или c^2    
    token_tree *node_second_add = NULL; // сын second, имеющей операцию +

    token_tree *node_mul   = NULL;
    token_tree *node_pow_1 = NULL;
    token_tree *node_pow_2 = NULL;

    if(tok_is_op(second->l->val, OP_ADD)){
        node_second_add = second->l;
        node_second_pow_or_mul = second->r;
    } else if(tok_is_op(second->r->val, OP_ADD)){
        node_second_add = second->r;
        node_second_pow_or_mul = second->l;
    } else {
        return;
    }
    // Проверим node_second_pow_or_mul и определеим node_mul pow_1 и pow_2
    if(tok_is_op(node_second_pow_or_mul->val, OP_MULT)){
        node_mul = node_second_pow_or_mul;

        if(!(tok_is_op(node_second_add->l->val, OP_POW) && tok_is_op(node_second_add->r->val, OP_POW))){
            return;
        }
        node_pow_1 = node_second_add->l;
        node_pow_2 = node_second_add->r;
    } else if(tok_is_op(node_second_pow_or_mul->val, OP_POW)){
        node_pow_1 = node_second_pow_or_mul;
        
        if(tok_is_op(node_second_add->l->val, OP_MULT) && tok_is_op(node_second_add->r->val, OP_POW)){
            node_pow_2 = node_second_add->r;
            node_mul = node_second_add->l;
        } else if(tok_is_op(node_second_add->l->val, OP_POW) && tok_is_op(node_second_add->r->val, OP_MULT)){
            node_pow_2 = node_second_add->l;
            node_mul = node_second_add->r;
        } else {
            return;
        }
    }

    // Проверим на совпадение a и b node_mul
    if(is_token_equal(node_a->val, node_mul->l->val)\
    && is_token_equal(node_b->val, node_mul->r->val)){
        // node_a == левому сыну, а node_b == правому
    }else if(is_token_equal(node_a->val, node_mul->r->val)\
            && is_token_equal(node_b->val, node_mul->l->val)){
        // node_a == правому сыну, а node_b == левому
    } else {
        return;
    }
    // Проверим на совпадение pow_1 и pow_2
    if(!(node_pow_1->r->val.type == TOK_CONST && node_pow_1->r->val.constval == 2.0)){
        return;
    }
    if(!(node_pow_2->r->val.type == TOK_CONST && node_pow_2->r->val.constval == 2.0)){
        return;
    }

    if(is_token_equal(node_a->val, node_pow_1->l->val) && is_token_equal(node_b->val, node_pow_2->l->val)){
        // pow_1 - a^2 | pow_2 - b^2
    } else if(is_token_equal(node_a->val, node_pow_2->l->val) && is_token_equal(node_b->val, node_pow_1->l->val)){
        // pow_1 - b^2 | pow_2 - a^2
    } else {
        return;
    }

    // Если мы дошли до сюда, то значит мы нашли поддерево, которое надо свернуть
    token a = node_a->val;
    token b = node_b->val;
    token const3 = {TOK_CONST, "", 3.0, OP_UNK};

    // Перестраиваем дерево
    (*node)->val.op = OP_MINUS;
    
    (*node)->l->val.op = OP_POW;
    (*node)->l->l->val = a;
    (*node)->l->r->val = const3;
    token_tree_remove(&(*node)->l->l->l);
    token_tree_remove(&(*node)->l->l->r);
    token_tree_remove(&(*node)->l->r->l);
    token_tree_remove(&(*node)->l->r->r);

    (*node)->r->val.op = OP_POW;
    (*node)->r->l->val = b;
    (*node)->r->r->val = const3;
    token_tree_remove(&(*node)->r->l->l);
    token_tree_remove(&(*node)->r->l->r);
    token_tree_remove(&(*node)->r->r->l);
    token_tree_remove(&(*node)->r->r->r);
}


int main(){
    token_queue *q_read; // Считанные токены
    token_queue *q_rpn;  // Токены в обратной польской записи
    if (!token_queue_init(&q_read)) 
        log_err_and_exit("Can't init queue");
    if (!token_queue_init(&q_rpn))
        log_err_and_exit("Can't init queue");

    read_expr_res rer;
    while((rer = read_expr(q_read, stdin)) != RER_EOF){
        if(rer == RER_ERR)
            printf("Token %d is unknown.\n", token_queue_get_size(q_read)+1);
        else {
            sort_station_res ssr = sort_station(q_rpn, q_read);
            if(ssr == SSR_ERR_BR_BALANCE)
                printf("Err bracket balance.\n");
            else if(ssr == SSR_ERR_INIT)
                LOG_ERR("Can't init token stack. Try later.");
            else {
                token_tree *t_tok = NULL;
                build_token_tree_res btr = build_token_tree(&t_tok, q_rpn);
                if(btr == BTR_ERR_INIT)
                    LOG_ERR("Can't init tree. Try later.");
                else if(btr == BTR_ERR_ARGS)
                    printf("Err agrs count.\n");
                else if(btr == BTR_OK){
                    tranform_token_tree(&t_tok);
                    print_token_tree(stdout, t_tok, PT_IN);
                    print_token_tree(stdout, t_tok, PT_TREE);
                }
                token_tree_deinit(&t_tok);
            }
        }

        clean_queue(q_read);
        clean_queue(q_rpn);
    }
    token_queue_deinit(&q_rpn);
    token_queue_deinit(&q_read);
}