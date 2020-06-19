#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "record/record.h"

typedef struct {
    FILE* in;
    FILE* out;
    bool filter_by_year;
    int year;
} config;

config handle_flags(int argc, char* argv[]){
    config conf = {stdin, stdout, false};

    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-f") == 0 && i + 1 < argc){
            conf.in = fopen(argv[i+1], "rb");
            i++;
        } else if(strcmp(argv[i], "-p") == 0 && i + 1 < argc){
            conf.filter_by_year = true;
            conf.year = atoi(argv[i+1]);
            i++;
        } else if(strcmp(argv[i], "-h") == 0){
            char help_str[] =
                "                                  _         ______ _           _          \n"
                "     /\\                          | |       |  ____(_)         | |           \n"
                "    /  \\__   _____   ___ __ _  __| | ___   | |__   _ _ __   __| | ___ _ __  \n"
                "   / /\\ \\ \\ / / _ \\ / __/ _` |/ _` |/ _ \\  |  __| | | '_ \\ / _` |/ _ \\ '__| \n"
                "  / ____ \\ V / (_) | (_| (_| | (_| | (_) | | |    | | | | | (_| |  __/ |    \n"
                " /_/    \\_\\_/ \\___/ \\___\\__,_|\\__,_|\\___/  |_|    |_|_| |_|\\__,_|\\___|_|    \n"
                "\n"
                "Avocado-finder Ищет город-мечту любителя авокадо.\n"
                "Выводит записи, где цена авокадо ниже среднего.\n\n"
                "КЛЮЧИ:\n"
                "\t-f <FILE> указывает входной файл.\n"
                "\tПо умодчанию используется поток стандартного ввода.\n\n"
                "\t-p <YEAR> указывает по какому году фильтровать записи.\n"
                "\tПо умолчанию фильтрации не происходит\n\n"
                "\t-h выводит справку о программе\n\n"
                "ПРИМЕРЫ:\n"
                "\t%s < avocado.bin\n"
                "\t%s -f avocado.bin -p 2018 > found_records\n"
                "ЗАМЕЧАНИЕ:\n"
                "\tДля генерации бинарного файла нужно использовать программу avocado-converter\n"
                "\tavocado-converter < avocado.csv > avocado.bin\n";
                fprintf(stderr, help_str, argv[0], argv[0]);
                exit(0);
        } else {
            char err_str[] =
                "Введен ошибочный ключ %s, смотрите справку\n"
                "%s -h\n";
            fprintf(stderr, err_str, argv[i], argv[0]);
            exit(1);
        }
    }

    return conf;
}

void request(config conf){
    // Находим средную цену авкокадо
    double summ_avocado_price = 0;
    int record_count = 0;
    
    record rcd;
    while(rcd_bin_read(conf.in, &rcd) == 1){
        if(!conf.filter_by_year || conf.year == rcd.year){
            summ_avocado_price += rcd.average_price;
            record_count++;
        }
    }
    if(record_count == 0)
        return;
    double average_price = summ_avocado_price/record_count;

    // Выводим подходящие записи
    fseek(conf.in, 0, SEEK_SET);
    while(rcd_bin_read(conf.in, &rcd) == 1){
        if(!conf.filter_by_year || conf.year == rcd.year){
            if(rcd.average_price <= average_price){
                rcd_write(conf.out, rcd);
            }
        }
    }

}

int main(int argc, char* argv[]){
    config conf = handle_flags(argc, argv);
    request(conf);
    return 0;
}