#include "help/help.h"

void print_help(FILE* f){
    static const char help[] = "COMMADS:\tSTANDART\t|\tSINONYM\n\
    \tquit\t\t\t| q\n\
    \t\tQuits this program.\n\
    \n\
    \tprint\t\t\t| p\n\
    \t\tPrints the list.\n\
    \n\
    \tinsert [id] <val>\t| i [id] <val>\n\
    \t\tInserts an element before the id.\n\
    \t\tIf the id is not specified,\n\
    \t\tthe command uses the current iterator.\n\
    \n\
    \tremove [id]\t\t| rm [id]\n\
    \t\tDeletes an element with the specified id.\n\
    \t\tIf the id is not specified,\n\
    \t\tthe command uses the current iterator.\n\
    \n\
    \treverse\t\t\t| rv\n\
    \t\tReverses the list.\n\
    \t\tDeletes the current iterator!\n\
    \n\
    \tget-size-list\t\t| size\n\
    \t\tPrints the size of the list.\n\
    \n\
    \tnext-iter\t\t| n\n\
    \t\tMoves the current iterator forward.\n\
    \n\
    \thelp\t\t\t| h\n\
    \t\tShows the program help.\n\
    \n\
    \tget-first-iter\t\t| f\n\
    \t\tSets the current iterator to the top of the list.\n\
    \n\
    \tget-end-iter\t\t| e\n\
    \t\tSets the current iterator to the end of the list.\n\
    \n\
    \tget-iter <id>\t\t|\n\
    \t\tSets the current iterator to an element with the id number.\n\
    \n\
    \tget-val [id]\t\t| get [id]\n\
    \t\tGets the value of the element with the id number.\n\
    \t\tIf the id is not specified,\n\
    \t\tthe command uses the current iterator.\n\
    \n\
    \tset-val [id] <val>\t| set [id] <val>\n\
    \t\tSets the value of the element under the id number.\n\
    \t\tIf the id is not specified,\n\
    \t\tthe command uses the current iterator.\n\
    \n\
    \tfree-iter\t\t| free\n\
    \t\tDeletes the current iterator.\n\
    \n";
    fprintf(f, help);
}