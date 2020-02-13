#! /usr/bin/env bash

# -i dir -o dir2 -n 10

I_DIR=""
O_DIR=""
N=0

IFLAG=false
OFLAG=false
NFLAG=false

while (($# > 1)); do
    echo "$1 $2 $3 $4 $5 $6"

    if [[ "$1" == "-i" ]]; then
        I_DIR="$2"
        IFLAG=true
    elif [[ "$1" == "-o" ]]; then
        O_DIR="$2"
        OFLAG=true
    elif [[ "$1" == "-n" ]]; then
        N="$2"
        NFLAG=true
    fi
    shift
    shift
done

# if [[ "$IFLAG" -eq false || "$OFLAG" -eq false || "$NFLAG" -eq false ]]; then
#     echo "USING: $0 -i <имя dir источника> -o <имя dir назначения> -n <кол-во файлов>"
#     exit
# fi

echo $("$IFLAG" -eq false)
echo $IFLAG
echo $OFLAG
echo $NFLAG