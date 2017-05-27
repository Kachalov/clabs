#!/bin/bash

./main.bin
for i in {0..6}; do
    ./main.bin in_$i.txt
done

exit 0

