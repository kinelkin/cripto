#!/bin/bash

echo 'We will be using the novel 1984 for these experiments'

gcc -g -o d decypher.c funciones_alt.c

./v -C -k NAVYSEALSARECOMING -i 1984.txt -o c_1984.txt
./d -i c_1984.txt
./v -D -k NAVYSEALSARECOMING -i c_1984.txt -o r_1984.txt
./v -D -k TRGKGAIUEFGICKS -i c_1984.txt -o r_1984.txt




diff cap_1984.txt r_1984.txt
echo '\nNo Output Means All OK'

echo 'All Finished'
