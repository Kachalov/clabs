#!/bin/bash

for i in {1..5}; do
    ./lab.bin 'in_'$i'.txt' > last_test.txt 2>&1
    diff -su 'out_'$i'.txt' last_test.txt
done

rm last_test.txt
