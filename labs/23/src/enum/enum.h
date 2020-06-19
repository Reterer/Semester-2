#pragma once
#define MAX_UNIT_STR_LEN 40

typedef enum {
    UNIT_NONE,
    UNIT_ROOT,
    UNIT_DEAN,
    UNIT_RECTOR,
    UNIT_STUDENT,
    UNIT_TEACHER,
    UNIT_DIRECTOR,
    UNIT_PROFESSOR,
} unit;

void unit_to_string(unit  unt, char* str);
unit  sritng_to_unit(char* str);