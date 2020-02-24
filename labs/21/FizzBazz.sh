#! /usr/bin/env bash

for ((I=0; I<100;I++))
do 
    if !((I%3)) && !((I%5)) 
    then
        echo "FIZZBUZZ"
    elif !((I%3)) 
    then
        echo "FIZZ"
    elif !((I%5)) 
    then
        echo "BUZZ"
    else
        echo "$I"
    fi
done