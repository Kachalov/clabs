#!/bin/bash

for i in $(find . -name 'in_*.txt'); do
    ./lab.bin $i > last_test.txt 2>&1
    diff -su $(echo $i | sed 's/in/out/g') last_test.txt
done

./lab.bin in_6.txt > last_test.txt 2>&1
diff -su out_6.txt last_test.txt

./lab.bin > last_test.txt 2>&1
diff -su out_7.txt last_test.txt

if [ -f last_test.txt ]; then
    rm last_test.txt
fi
