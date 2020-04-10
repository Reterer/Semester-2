#!/bin/bash

echo "TEST.OUT"
make test && ./test.out

echo "MAIN.OUT"
make cp7
for file in test_files/main/test*.in; do
    ./main.out $file ${file%.*}.res 
    diff -s ${file%.*}.res ${file%.*}.ans
done