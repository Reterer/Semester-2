#include <string.h>
#include "enum.h"

void unit_to_string(unit unt, char* str){
    switch (unt)
    {
    case UNIT_STUDENT:
        strcpy(str,"Студент");
        break;
    case UNIT_TEACHER:
        strcpy(str,"Учитель");
        break;
    case UNIT_PROFESSOR:
        strcpy(str,"Профессор");
        break;
    case UNIT_DEAN:
        strcpy(str,"Декан");
        break;
    default:
        strcpy(str,"ошб. знач.");
        break;
    }
}

unit  sritng_to_unit(char* str){
    unit res = UNIT_NONE;
    if(strcmp(str, "Student") == 0){
        res = UNIT_STUDENT;
    }
    else if(strcmp(str, "Teacher") == 0){
        res = UNIT_TEACHER;
    }
    else if(strcmp(str, "Professor") == 0){
        res = UNIT_PROFESSOR;
    }
    else if(strcmp(str, "Dean") == 0){
        res = UNIT_DEAN;
    }
    
    return res;
}