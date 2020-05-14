#pragma once
#include "list/int_list.h"
#include "stdio.h"

// Да, не все ENUM нужны для работы программы, но для простоты
// Каждая команда имеет свой coommand_type
// коды команд в ДОЛЖНЫ соотвествовать соотвествующим командам в cmd_info_arr
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
    CMD_NEGATIVE_ID,
    CMD_NONE,
} command_type;
// А CMD_NONE ДОЛЖНА быть последней командой (нужно для итерирования по cmd_info_arr)

typedef struct {
    command_type type;
    int          value;
    int          id;
} command;

//*************************************

#define MAX_LEN_COMMAND_STR 40

// Флаги для указания аргументов для команд
typedef enum {
    GET_0_ARG = 1,          // Команда может принять 0 аргументов
    GET_1_ARG = 2,
    GET_2_ARG = 4,
    VAL_CAN_1ST_ARG = 8,    // Если был введен только 1 аргумент, то им является value
    CANT_WRITE = 16,        // Пользователь не может ввести эту команду
} command_str_flags;

// Аргументы команд, возможно тут содержится излишняя информация,
// Но зато, все обработчики команд имеют одинаковый прототип
typedef struct{
    FILE *fout;
    command cmd;           // текущая команда
    int_list_iterator *it; // текущий итератор
    int_listptr list;      
} command_func_args;

// Служит для обявления команды
typedef struct {
    const char   str[MAX_LEN_COMMAND_STR];
    const char   str_alt[MAX_LEN_COMMAND_STR];
    const command_type type;
    unsigned int flags;
    void (*handle)(command_func_args*);
} command_info;

// Массив всех команд
extern const command_info cmd_info_arr[];