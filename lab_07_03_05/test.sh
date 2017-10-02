#!/bin/bash

for i in $(find functional_tests -name 'in_*.txt'); do
    ./main.exe $i functional_tests/last_test.txt > /dev/null
    diff -su $(echo $i | sed 's/in/out/g') functional_tests/last_test.txt

    ./main.exe - $i functional_tests/last_test.txt > /dev/null
    diff -su $(echo $i | sed 's/in/out_filtered/g') functional_tests/last_test.txt
done

if [ -f functional_tests/last_test.txt ]; then
    rm functional_tests/last_test.txt
fi
