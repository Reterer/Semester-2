#include <stdio.h>
#include "log/log.h"

void _log(const char* level, const char* message, const char* file, const char* func, const int line){
    if(line == -1)
        fprintf(stderr,"%s %s %s %s\n", level, message, file, func);
    else
        fprintf(stderr,"%s %s %s %s : %i\n", level, message, file, func, line);
}