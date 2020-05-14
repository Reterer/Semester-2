#include "token/token.h"
#include "log/log.h"
// Сортировочная станция Дейкстры
sort_station_res sort_station(token_queue *q_dest, token_queue *q_src){
    token_v *s_tok;
    if(!token_v_init(&s_tok)){
        return SSR_ERR_INIT;
    }
    while(!token_queue_is_empty(q_src)){
        token tok = token_queue_pop(q_src);
        token curr_tok;
        switch (tok.type)
        {
        case TOK_CONST:
        case TOK_VAR:
            token_queue_push_back(q_dest, tok);
            break;
        case TOK_LBR:
            token_v_push_back(s_tok, tok);
            break;
        case TOK_RBR:
            // Если мы считали закрывающую скобку, а стек пуст => не хватает открывающий скобки
            if(token_v_is_empty(s_tok)){
                token_v_deinit(&s_tok);
                return SSR_ERR_BR_BALANCE;
            }
            // Выталкиваем операторы, пока не встретим открывающую скобку
            while(!token_v_is_empty(s_tok) && (curr_tok = token_v_top(s_tok)).type != TOK_LBR){
                token_queue_push_back(q_dest, curr_tok);
            }
            // Если мы так и не встретили открывающую скобку => её не хватает 
            if(curr_tok.type != TOK_LBR){
                token_v_deinit(&s_tok);
                return SSR_ERR_BR_BALANCE;
            }
            break;
        case TOK_OP:
            curr_tok.type = TOK_NONE;
            // Выталкиваем более приоритетные операции из стека, 
            // до открывающий скобки или первого оператора, чей приоритет ниже curr_tok
            while(!token_v_is_empty(s_tok) && (curr_tok = token_v_top(s_tok)).type != TOK_LBR){
                if(!should_pop_out(tok.op, curr_tok.op)){
                    token_v_push_back(s_tok, curr_tok);
                    break;
                }
                token_queue_push_back(q_dest, curr_tok);
            }
            // Если мы считали открывающую скобку, то её нужно вернуть боратно в стек
            if(curr_tok.type == TOK_LBR)
                token_v_push_back(s_tok, curr_tok);
            token_v_push_back(s_tok, tok);
            break;
        default:
            token_v_deinit(&s_tok);
            return SSR_ERR_INIT;
        }
 
    }
    // Когда воходная очередь станет пустой - выталкиваем оставшиеся операции в выходную очередь
    while(!token_v_is_empty(s_tok)){
        token curr_tok = token_v_top(s_tok);
        if(curr_tok.type == TOK_LBR){
            token_v_deinit(&s_tok);
            return SSR_ERR_BR_BALANCE;
        }
        token_queue_push_back(q_dest, curr_tok);
    }
    token_v_deinit(&s_tok);
    return SSR_OK;
}