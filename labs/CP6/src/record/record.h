#pragma once
#include <stdio.h>

typedef struct {
    int     id;
    char    date[12];
    double  average_price;
    double  total_volume;
    double  PLU_4046;
    double  PLU_4225;
    double  PLU_4770;
    double  total_bags;
    double  small_bags;
    double  large_bags;
    double  xlarge_bags;
    char    type[32];
    int     year;
    char    region[64];
} record;

int rcd_bin_read(FILE* f, record* rcd);
int rcd_bin_write(FILE* f, record rcd);

int rcd_read(FILE* f, record* rcd);
int rcd_write(FILE* f, record rcd);