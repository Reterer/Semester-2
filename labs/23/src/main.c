#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "tree/tree.h"
#include "enum/enum.h"
#include "log/log.h"

#define MAX_SIZE_INPUT_BUF 256
#define READ_STR_LEN 40
#define MAX_LEN_PATH 64

#define INVITATION_CHAR '>'

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
    char         path[MAX_LEN_PATH];
} command;


bool _cmp_in_and_cmd(const char* input, const char* cmd){
    return (cmd[0] == input[0]) && (input[1] == '\0' || strcmp(input, cmd) == 0);
}

int _split_line(char* line_buff, char* command, char* path, char* value){
    path[0]   = '\0';
    value[0]  = '\0';

    int read_code = sscanf(line_buff, "%39s %63[cbCB] %39s\n", command, path, value);
    if(read_code == 1){
        read_code = sscanf(line_buff, "%39s %39s\n", command, value);
        path[0] = '\0';
    }
    
    for(char* ch = path; *ch != '\0'; ++ch){
        *ch = tolower(*ch);
    }
    for(char* ch = value; *ch != '\0'; ++ch){
        *ch = tolower(*ch);
    }

    return read_code;
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
    res.path[0]    = '\0';
    res.value      = UNIT_NONE;
    res.type       = CMD_UNKNOWN;

    char line_buff[MAX_SIZE_INPUT_BUF] = "";
    if(fprintf(fout, "%c ", INVITATION_CHAR));
    if(fgets(line_buff, MAX_SIZE_INPUT_BUF, fin) == NULL){
        printf("End of the file\n");
        res.type = CMD_STOP;
        return res;
    }

    char read_str[READ_STR_LEN] = "";
    char value_str[MAX_UNIT_STR_LEN] = "";

    int read_code = _split_line(line_buff, read_str, res.path, value_str);

    if(read_code < 1)
        res.type = CMD_NONE;

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
    else if((read_code == 1  || read_code == 2) && _cmp_in_and_cmd(read_str, str_cmd_arr[SCC_REMOVE])){
        res.type = CMD_REMOVE;
    }
    else if((read_code == 2 || read_code == 3) && _cmp_in_and_cmd(read_str, str_cmd_arr[SCC_ADD])){
        res.value = sritng_to_unit(value_str);
        if(res.value == UNIT_NONE){
            fprintf(fout, "Erroneous value entered\n");
            res.type = CMD_NONE;
        }
        else
            res.type = CMD_ADD;
    }
    return res;
}

void print_help(FILE* f){
    static const char help[] = "COMMADS:\tSTANDART\t|\tSINONYM\n\
    \tadd <path> <value>\t| a <path> <value>\n\
    \t\tAdds a node.\n\
    \t\tPath - path to a new node.\n\
    \t\tValue - node value.\n\
    \n\
    \tremove <path>\t\t| r <path>\n\
    \t\tRemoves the node and its sons.\n\
    \t\tPath - the node.\n\
    \n\
    \tprint\t\t\t| p\n\
    \t\tPrint the tree.\n\
    \n\
    \tcalculate\t\t| c\n\
    \t\tСomputes function.\n\
    \n\
    \tquit\t\t\t| q\n\
    \t\tQuits this program.\n\
    \n\
    \thelp\t\t\t| h\n\
    \t\tYou're reading it.\n\
    \nPATH:\n\
    \tPath is a sequence of characters 'c' or 'b' ('C' or 'B').\n\
    \tThe path may be empty \"\".\n\
    \tc - child\tb - brother\n\
    \tExamples: \"с\", \"cbc\"\n\
    \nENUM (value of node):\n\
    \tСase insensitive.\n\
    \tUniversity hierarchy:\n\
    \t  Rector, Director, Dean,\n\
    \t  Professor, Teacher,\n\
    \t  Student.\n\n";
    fprintf(f, help);
}

void handle_command(command* cmd, treenodeptr* root, FILE* fout){
    switch (cmd->type){
    case CMD_PRINT:
        t_print(fout, root);
        break;
    case CMD_ADD:
        if(t_add(root, cmd->path, cmd->value) == false)
            printf("Try again.\n");
        break;
    case CMD_REMOVE:
        t_remove(root, cmd->path);
        break;
    case CMD_CALCULATE:
        t_func(fout, root);
        break;
    case CMD_HELP:
        print_help(fout);
        break;
    case CMD_STOP:
        fprintf(fout, "Quite.\n");
        break;
    case CMD_UNKNOWN:
        fprintf(fout, "Unknown command. Try again or typing help.\n");
        break;
    default:
        break;
    }
}

int main(){
    treenodeptr root;
    if(t_init(&root) == false){
        LOG_ERR("Can't init tree");
        return 1;    
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