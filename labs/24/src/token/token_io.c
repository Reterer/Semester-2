#include <stdbool.h>
#include <ctype.h>
#include "token/token.h"

typedef enum {
    RTR_OK,     // Успешное считывание
    RTR_ERR,    // Токен не распознан
    RTR_EOF,    // Был достигнут конец файла
    RTR_EOE,    // Был достигнут конец выражения
} read_token_res;

static bool is_unary_minus(int ch, token_type prev_type){
    return ch == '-' && (prev_type == TOK_LBR || prev_type == TOK_NONE || prev_type == TOK_OP);
}

// Считывает tok из f
// Некоторые токены зависят от типа предыдущего prev_type
static read_token_res read_token(FILE *f, token *tok, token_type prev_type){
    read_token_res res = RTR_EOF;
    int ch;
    while((ch = fgetc(f)) != EOF){
        // Если встретился конец строки
        if(ch == '\n'){
            res = RTR_EOE;
            break;
        }
        // Если встретился пробел либо табуляция
        else if(isblank(ch))
            continue;
        // Если мы начали считывать имя переменной
        else if(isalpha(ch) || ch == '_'){
            tok->type = TOK_VAR;
            ungetc(ch, f);
            fscanf(f, "%32[_a-zA-Z0-9]", tok->varname);
            if (tok->varname[31] != '\0'){
                tok->varname[31] = '\0';
                fscanf(f, "%*[_a-zA-Z0-9]");
            }
            res = RTR_OK;
            break;
        }
        // Если мы начали считывать число
        else if(isdigit(ch)){
            tok->type = TOK_CONST;
            ungetc(ch, f);
            fscanf(f, "%lf", &tok->constval);
            res = RTR_OK;
            break;
        }
        // Если мы считали оператор
        else if(isoperator(ch)){
            if(is_unary_minus(ch, prev_type)){
                ch = '~';   
            }
            tok->type = TOK_OP;
            tok->op = char_to_op(ch);
            res = RTR_OK;
            break;
        } 
        // Если мы считали скобки
        else if(ch == '('){
            tok->type = TOK_LBR;
            res = RTR_OK;
            break;
        }
        else if(ch == ')'){
            tok->type = TOK_RBR;
            res = RTR_OK;
            break;
        }
        // Если введен непонятный символ
        else {
            tok->type = TOK_NONE;
            res = RTR_ERR;
            while ((ch = fgetc(f)) != EOF)
                if(ch == '\n')
                    break;
            break;
        }
    }
    return res;
}

read_expr_res read_expr(token_queue *q_tok, FILE *f){
    token tok;
    tok.type = TOK_NONE;

    read_token_res rtr;
    while((rtr = read_token(f,&tok, tok.type)) == RTR_OK){
        token_queue_push_back(q_tok, tok);
    }
    if(rtr == RTR_EOF && !token_queue_is_empty(q_tok))
        rtr = RTR_EOE;
    read_expr_res res = RER_ERR;
    switch (rtr)
    {
    case RTR_OK:
        res = RER_OK;
        break;
    case RTR_EOE:
        res = RER_OK;
        break;
    case RTR_ERR:
        res = RER_ERR;
        break;
    case RTR_EOF:
        res = RER_EOF;
    default:
        break;
    }
    return res;
}

void print_expr(token_queue *q_tok, FILE *f){
    token tok;
    while(!token_queue_is_empty(q_tok)){
        tok = token_queue_pop(q_tok);
        switch (tok.type)
        {
        case TOK_CONST:
            fprintf(f, "%.2lf ", tok.constval);
            break;
        case TOK_VAR:
            fprintf(f, "%s ", tok.varname);
            break;
        case TOK_OP:
            fprintf(f, "%c ",op_to_char(tok.op));
            break;
        case TOK_LBR:
            fprintf(f, "( ");
            break;
        case TOK_RBR:
            fprintf(f, ") ");
            break;
        default:
            break;
        }
    }
    fprintf(f, "\n");
}