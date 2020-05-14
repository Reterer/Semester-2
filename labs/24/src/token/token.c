#include <string.h>
#include "token/token.h"

bool is_token_equal(token a, token b){
    if(a.type != b.type)
        return false;
    switch (a.type){
    case TOK_NONE:
        return true; 
    case TOK_CONST:
        return a.constval == b.constval;
    case TOK_VAR:
        return strcmp(a.varname, b.varname) == 0;
    case TOK_OP:
        return a.op == b.op;
    case TOK_LBR:
        return true;
    case TOK_RBR:
        return true;
    default:
        return false;
    }
}
