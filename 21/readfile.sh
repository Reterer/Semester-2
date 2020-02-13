#! /usr/bin/env bash

I=1
while read
do
    ((I=I+1))
done < "$1"
echo $I