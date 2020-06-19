#include "record/record.h"

int rcd_bin_read(FILE* f, record* rcd){
    int read_code = fread(rcd, sizeof(record), 1, f);
    return read_code == 1;
}

int rcd_bin_write(FILE* f, record rcd){
    int write_code = fwrite(&rcd, sizeof(record), 1, f);
    return write_code == 1;
}

int rcd_read(FILE* f, record* rcd){
    int read_code = fscanf(f, "%d,%12[0-9-],%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%32[a-zA-Z],%d,%64[a-zA-Z]%*c",
        &rcd->id, rcd->date, &rcd->average_price, &rcd->total_volume, &rcd->PLU_4046,
        &rcd->PLU_4225, &rcd->PLU_4770, &rcd->total_bags, &rcd->small_bags, 
        &rcd->large_bags, &rcd->xlarge_bags, rcd->type, &rcd->year, rcd->region);
    return read_code == 14;
}

int rcd_write(FILE* f, record rcd){
    int write_code = fprintf(f, "%d,%s,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%s,%d,%s\n",
        rcd.id, rcd.date, rcd.average_price, rcd.total_volume, rcd.PLU_4046,
        rcd.PLU_4225, rcd.PLU_4770, rcd.total_bags, rcd.small_bags, 
        rcd.large_bags, rcd.xlarge_bags, rcd.type, rcd.year, rcd.region);
    return write_code == 14;
}