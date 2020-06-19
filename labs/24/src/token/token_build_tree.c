#include "token/token.h"

// Определеяем вектор (стек) указателей на указатель на узел дерева
typedef token_tree *token_tree_p;
#define T token_tree_p
#include "vector/vector_template.h"
#include "vector/vector_template.c"
#undef T

build_token_tree_res build_token_tree(token_tree **tree, token_queue *q_tok){
    token_tree_p_v *s_tree;
    if(!token_tree_p_v_init(&s_tree))
        return BTR_ERR_INIT;

    token tok;
    token_tree *left;
    token_tree *right;
    token_tree *node;
    while(!token_queue_is_empty(q_tok)){
        tok = token_queue_pop(q_tok);

        switch (tok.type){
        case TOK_VAR:
        case TOK_CONST:
            left = NULL;
            right = NULL;
            break;
        case TOK_OP:
            // Если операция унарная, если унарных операций будет больше,
            // Можно написать функцию bool is_unary_op(opeartion)
            if(tok.op == OP_UN_MINUS){
                left = NULL;
                // Если нет аргумента операции, то есть вектор узлов пустой
                if (token_tree_p_v_is_empty(s_tree)){
                    token_tree_p_v_deinit(&s_tree);
                    return BTR_ERR_ARGS;
                }
                // Иначе берем аргумент
                right = token_tree_p_v_top(s_tree);
            } else {
                // Если недостаточно аргументов
                if (token_tree_p_v_size(s_tree) < 2){
                    if(!token_tree_p_v_is_empty(s_tree)){
                        node = token_tree_p_v_top(s_tree);
                        token_tree_deinit(&node);
                    }
                    token_tree_p_v_deinit(&s_tree);
                    return BTR_ERR_ARGS;
                }

                right = token_tree_p_v_top(s_tree);
                left = token_tree_p_v_top(s_tree);
            }
            break;

        default:
            token_tree_p_v_deinit(&s_tree);
            return BTR_ERR_TOK;
        }
        node = token_tree_make();
        if(node == NULL){
            LOG_ERR("Can't make node");
            token_tree_deinit(&left);
            token_tree_deinit(&right);
            while(!token_tree_p_v_is_empty(s_tree)){
                node = token_tree_p_v_top(s_tree);
                token_tree_deinit(&node);
            }
            token_tree_p_v_deinit(&s_tree);
            return BTR_ERR_INIT;
        }

        node->l = left;
        node->r = right;
        node->val = tok;
        token_tree_p_v_push_back(s_tree, node);
    }

    // Если стек пустой, то это может быть только из-за пустой входной очереди
    if(token_tree_p_v_is_empty(s_tree)){
        *tree = NULL;
        return BTR_OK;
    }
    // Если же в стеке несколько узлов, то значит в очереди были лишние аргументы
    if(token_tree_p_v_size(s_tree) > 1){
        while(!token_tree_p_v_is_empty(s_tree)){
            node = token_tree_p_v_top(s_tree);
            token_tree_deinit(&node);
        }
        token_tree_p_v_deinit(&s_tree);
        return BTR_ERR_ARGS;
    }

    *tree = token_tree_p_v_top(s_tree);
    token_tree_p_v_deinit(&s_tree);
    return BTR_OK;
}