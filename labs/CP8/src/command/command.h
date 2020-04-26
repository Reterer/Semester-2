#pragma once
#include "list/int_list.h"
#include "stdio.h"

typedef enum {
    CMD_QUIT,
    CMD_PRINT,
    CMD_INSERT,
    CMD_REMOVE,
    CMD_REVERSE,
    CMD_SIZE,
    CMD_NEXT,
    CMD_HELP,
    CMD_FIRST,
    CMD_END,
    CMD_GET_ITER,
    CMD_GET_VALUE,
    CMD_SET_VALUE,
    CMD_FREE_ITER,
    CMD_UNKNOWN,
    CMD_ERR,
    CMD_NONE,
} command_type;

typedef struct {
    command_type type;
    int          value;
    int          id;
} command;

//*************************************

#define MAX_LEN_COMMAND_STR 40

typedef enum {
    GET_0_ARG = 1,
    GET_1_ARG = 2,
    GET_2_ARG = 4,
    VAL_CAN_1ST_ARG = 8,
    CANT_WRITE = 16,    
} command_str_flags;

typedef struct
{
    FILE *fout;
    command cmd;
    int_list_iterator *it;
    int_listptr list;
} command_func_args;


typedef struct {
    const char   str[MAX_LEN_COMMAND_STR];
    const char   str_alt[MAX_LEN_COMMAND_STR];
    const command_type type;
    unsigned int flags;
    void (*handle)(command_func_args*);
} command_info;

extern const command_info cmd_info_arr[];