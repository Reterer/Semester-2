#include <stdio.h>
#include <stdlib.h>
#include <log/log.h>

#include "matrix.h"
#include "transformation_matrix.h"

typedef struct {
    FILE* in;
    FILE* out;
} config;

void print_help_and_exit(char* name_programm){
    printf("USAGE:\n");
    printf("\t   %s <in file> <out file>\n", name_programm);
    printf("\tor %s \n", name_programm);
    printf("EXAMPLES:\n");
    printf("\t   %s in_matrix.txt out_matrix.txt\n", name_programm);
    printf("\t   %s < in_matrix.txt\n", name_programm);
    exit(1);
}

config handle_args(int argc,char* argv[]){
    config res = { stdin, stdout};
    if(argc == 1)
        return res;
    else if(argc == 3){
        res.in = fopen(argv[1], "r");
        res.out = fopen(argv[2], "w");

        if(res.in == NULL)
            LOG_ERR("can't open input file");
        if(res.out == NULL)
            LOG_ERR("can't open output file");

        if(res.out == NULL || res.in == NULL)
                print_help_and_exit(argv[0]);
    }
    else {
        print_help_and_exit(argv[0]);
    }

    return res;
}

int main(int argc,char* argv[]){
    config cnfg = handle_args(argc, argv);
    
    matrix* m;
    if(m_init(&m) == false){
        LOG_ERR("Can't init matrix");
        fclose(cnfg.in);
        fclose(cnfg.out);
        return 1;
    }

    if(m_read(m, cnfg.in) == false){
        LOG_ERR("Can't read matrix");
        m_deinit(&m);
        fclose(cnfg.in);
        fclose(cnfg.out);
        return 1;
    }

    double value;
    if(fscanf(cnfg.in, "%lf", &value) != 1){
        LOG_ERR("Can't read value");
        m_deinit(&m);
        fclose(cnfg.in);
        fclose(cnfg.out);
        return 1;
    }

    transformation_matrix(m, value);

    if(m_print(m, cnfg.out, HUMAN) == false)
        LOG_ERR("Can't print result matrix");
    m_deinit(&m);
    fclose(cnfg.in);
    fclose(cnfg.out);
    return 0;
}