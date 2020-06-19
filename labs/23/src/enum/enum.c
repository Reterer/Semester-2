#include <string.h>
#include "enum/enum.h"

void unit_to_string(unit unt, char* str){
    switch (unt)
    {
    case UNIT_STUDENT:
        strcpy(str,"Студент");
        break;
    case UNIT_TEACHER:
        strcpy(str,"Преподаватель");
        break;
    case UNIT_PROFESSOR:
        strcpy(str,"Профессор");
        break;
    case UNIT_DEAN:
        strcpy(str,"Декан");
        break;
    case UNIT_RECTOR:
        strcpy(str,"Ректор");
        break;
    case UNIT_DIRECTOR:
        strcpy(str,"Директор");
        break;
    case UNIT_ROOT:
        strcpy(str,"Корень");
        break;
    default:
        strcpy(str,"ошб. знач.");
        break;
    }
}

unit  sritng_to_unit(char* str){
    unit res = UNIT_NONE;
    if(strcmp(str, "student") == 0){
        res = UNIT_STUDENT;
    }
    else if(strcmp(str, "teacher") == 0){
        res = UNIT_TEACHER;
    }
    else if(strcmp(str, "professor") == 0){
        res = UNIT_PROFESSOR;
    }
    else if(strcmp(str, "dean") == 0){
        res = UNIT_DEAN;
    }
    else if(strcmp(str, "rector") == 0){
        res = UNIT_RECTOR;
    }
    else if(strcmp(str, "director") == 0){
        res = UNIT_DIRECTOR;
    }
    
    return res;
}