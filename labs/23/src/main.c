#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"
#include "enum.h"

#define MAX_SIZE_INPUT_BUF 256
#define READ_STR_LEN 40

typedef enum {
    CMD_ADD,
    CMD_NONE,
    CMD_STOP,
    CMD_HELP,
    CMD_PRINT,
    CMD_REMOVE,
    CMD_UNKNOWN,
    CMD_CALCULATE,
} command_type;

typedef struct {
    command_type type;
    unit         value;
    int          idx_vertix;
} command;


bool _cmp_in_and_cmd(const char* input, const char* cmd){
    // printf("%s ? %s\n", input, cmd);
    // printf("%c == %c && (%i == 0 || cmp: %i)\n", cmd[0], input[0], input[1], strcmp(input, cmd));
    return (cmd[0] == input[0]) && (input[1] == '\0' || strcmp(input, cmd) == 0);
}

command get_command(FILE* fin, FILE* fout){
    static const char* str_cmd_arr[] = {
        "print",
        "add",
        "remove",
        "calculate",
        "help",
        "quit"
    };
    enum str_cmd_code{
        SCC_PRINT,
        SCC_ADD,
        SCC_REMOVE,
        SCC_CALCULATE,
        SCC_HELP,
        SCC_QUIT
    };
    
    command res;
    res.idx_vertix = -1;
    res.value      = UNIT_NONE;
    res.type       = CMD_UNKNOWN;

    char line_buff[MAX_SIZE_INPUT_BUF] = "";
    if(fgets(line_buff, MAX_SIZE_INPUT_BUF, fin) == NULL){
        printf("STOP\n");
        res.type = CMD_STOP;
        return res;
    }

    char read_str[READ_STR_LEN] = "";
    char value_str[MAX_UNIT_STR_LEN] = "";
    int read_code = sscanf(line_buff, "%39s %d %39s\n", read_str, &res.idx_vertix, value_str);

    if(read_code < 1)
        res.type = CMD_NONE;
    else if(read_code > 1 && res.idx_vertix < 0){
        fprintf(fout, "Номер вершины не может быть меньше 0\n");
        res.type = CMD_NONE;
        return res;
    }

    if(read_code == 1 && _cmp_in_and_cmd(read_str, str_cmd_arr[SCC_PRINT])){
        res.type = CMD_PRINT;
    }
    else if(read_code == 1 && _cmp_in_and_cmd(read_str, str_cmd_arr[SCC_CALCULATE])){
        res.type = CMD_CALCULATE;
    }
    else if(read_code == 1 && _cmp_in_and_cmd(read_str, str_cmd_arr[SCC_HELP])){
        res.type = CMD_HELP;
    }
    else if(read_code == 1 && _cmp_in_and_cmd(read_str, str_cmd_arr[SCC_QUIT])){
        res.type = CMD_STOP;
    }
    else if(read_code == 2 && _cmp_in_and_cmd(read_str, str_cmd_arr[SCC_REMOVE])){
        res.type = CMD_REMOVE;
    }
    else if(read_code == 3 && _cmp_in_and_cmd(read_str, str_cmd_arr[SCC_ADD])){
        res.value = sritng_to_unit(value_str);
        if(res.value == UNIT_NONE){
            fprintf(fout, "Введенно ошибочное значение для вершины\n");
            res.type = CMD_NONE;
        }
        else
            res.type = CMD_ADD;
    }
    // printf("s: %s\tidx: %i\tval: %s\tcode: %i\n", read_str, res.idx_vertix, value_str, read_code);
    // printf("type: %i\tidx: %i\tval: %i\n", res.type, res.idx_vertix, res.value);

    return res;
}

void handle_command(command* cmd, treenodeptr* root, FILE* fout){
    switch (cmd->type)
    {
    case CMD_PRINT:
        t_print(fout, *root);
    case CMD_ADD:
        t_add(*root, cmd->idx_vertix, cmd->value);
        break;
    case CMD_REMOVE:
        break;
    case CMD_CALCULATE:
        break;
    case CMD_HELP:
        break;
    case CMD_UNKNOWN:
        break;
    default:
        break;
    }
}

int main(){
    treenodeptr root;
    if(!t_init(&root)){
        // TODO
    }
    
    command cmd;
    cmd.type = CMD_NONE;

    while(cmd.type != CMD_STOP){
       cmd = get_command(stdin, stdout);
       handle_command(&cmd, &root, stdout);
    }

    t_deinit(&root);
    return 0;
}