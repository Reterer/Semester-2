#! /usr/bin/env bash

read TRASH FILES  < <(ls -l | head -n 1)
for ((I=0; I<=FILES; I++)); do
    read R L O G D D D D N < <(ls -l | tail -n $I)
    echo $N
done