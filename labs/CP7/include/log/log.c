#include <stdio.h>
#include <log/log.h>

void _log(const char* level, const char* message, const char* file, const char* func, const char* line){
    fprintf(stderr,"%s %s %s %s %s\n", level, message, file, line, func);
}