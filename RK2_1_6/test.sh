#!/bin/bash

./main.bin
for i in {0..7}; do
    ./main.bin in_$i.txt
done

exit 0

