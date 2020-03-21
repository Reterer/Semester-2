#! /bin/bash
# Это вторая весрия этого скрипта, так как первая была безвозратно
# Потеряна, так как я случайно её удалил...

# Данный скрипт меняет в наденных файлах \ на /
# script [OPTION]... [--] [DIR]...
# Краткое описане возможностей ключей:
# -r            reverse, то есть программа будет менять / на \ 
# -l            переходить по  симолическим ссылкам
# -help         справка о программе
# -name [ptrn]  указать шаблон, по которому будет производиться поиск
#               по умолчанию используется -name "Makefile*" 
# -iname [ptrn] то же самое, что и name, но без учета регистра 
# -norecursion  отключает рекурсию, то есть ищет файлы только в
#               указанных директориях
# Смотрите больше в справке 
# (хотя, по сути, это просто копия данного описания, переведенного google)

# Краткое описание работы данного скрипта
# 1) handle options
# 2) find and replace

recursion_key=""
link_key=""

name_key="-name"
name_pattern="Makefile*"

is_help_mode=0
is_reverse_mode=0

# Вывод справки скрипта
function print_help {
    help_text="
    DESCRIPTION
    \n\tThis script replaces \ with / 
    \nUSAGE
    \n\t$0 [OPTION]... [--] [DIR]...
    \nOPTIONS
    \n\t-r\t\treverse: the program will replace / with \ 
    \n\t-l\t\tfollows symbolic links
    \n\t-help\t\tprogram help
    \n\t-name\t[ptrn]\tThe pattern to be searched. By default, the pattern 'Makefile*' is used 
    \n\t-iname\t[ptrn]\tthe same as -name, but case insensitive
    \n\t-norecursion\tdisable recursion
    \n\t--\t\tmarks the end of keys
    \nEXIT CODES
    \n\t0\tit's ok
    \n\t1\tinvalid keys
    \nAUTHOR
    \n\t written by Egor Sukhanov (egor-suhanov2012@ya.ru)
    "
    echo -e $help_text
    exit 1
}

function find_and_replace {
    # set up variables
    command_sed=""
    if (($is_reverse_mode)); then
        command_sed='s!/!\\!g'
    else
        command_sed='s!\\!/!g'
    fi

    find $link_key "$@" -type f $recursion_key $name_key "$name_pattern"\
    -exec sed -i "$command_sed" "{}" \;
}

# handle options
function print_mesage_invalid_option_and_exit {
    echo -e "key $1 is invalid.\nTry $0 -help for more information."
    exit 1
}

was_name_key=0
function handle_name_option {
    if ((was_name_key)); then
        print_mesage_invalid_option_and_exit "$1"
    fi
    
    # Если не существует второй аргумент, то
    if [[ ! "$2" ]]; then
        print_mesage_invalid_option_and_exit "$1"
    fi

    was_name_key=1
    name_key="$1"
    name_pattern="$2"
}

while (($# > 0)); do
    case "$1" in
    -r) 
        is_reverse_mode=1
        ;;
    -l) 
        link_key="-L"
        ;;
    -help)
        is_help_mode=1
        ;;
    -name)
        handle_name_option "$1" "$2"
        shift
        ;;
    -iname)
        handle_name_option "$1" "$2"
        shift
        ;;
    -norecursion)
        recursion_key="-maxdepth 0"
        ;;
    --)
        shift
        break 
        ;;
    -*) 
        print_mesage_invalid_option_and_exit "$1"
        ;;
    *) 
        break
        ;;
    esac
    shift
done

if (($is_help_mode)); then
    print_help
else
    if (($# > 0)); then
        find_and_replace "$@"
    else
        find_and_replace "./"
    fi
fi