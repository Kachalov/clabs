#!/bin/bash

for i in $(find functional_tests -name 'in_slae_*.txt'); do
    out=$(echo $i | sed 's/in/out/g')
    ./main.exe $i functional_tests/last_test.txt > /dev/null
    diff -su $out functional_tests/last_test.txt
done

for t in sum mul; do
    for i in $(find functional_tests -name 'in1_'$t'_*.txt'); do
        out=$(echo $i | sed 's/in1/out/g')
        j=$(echo $i | sed 's/in1/in2/g')
        ./main.exe $t $i $j functional_tests/last_test.txt > /dev/null
        diff -su $out functional_tests/last_test.txt
    done
done

if [ -f functional_tests/last_test.txt ]; then
    rm functional_tests/last_test.txt
fi
