#!/bin/bash

for i in $(find . -name 'in_*.txt'); do
    cat $i | xargs ./main.exe > last_test.txt 2>&1
    if [ -f $(echo $i | sed 's/in/out/g') ]; then
        diff -su $(echo $i | sed 's/in/out/g') last_test.txt
    else
        mv last_test.txt $(echo $i | sed 's/in/out/g')
    fi
done

if [ -f last_test.txt ]; then
    rm last_test.txt
fi
