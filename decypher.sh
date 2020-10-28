#!/bin/bash

echo 'We will be using the novel 1984 for these experiments'

echo '\n\nEXP 1: Encrypting using KEY: NAVYSEALSARECOMING'
./v -C -k NAVYSEALSARECOMING -i 1984.txt -o c_1984.txt
echo '\nObtaining KEY:'
./d -i c_1984.txt

echo '\n\nEXP 2: Encrypting using KEY: WINTER'
./v -C -k WINTER -i 1984.txt -o c_1984.txt
echo '\nObtaining KEY:'
./d -i c_1984.txt

echo '\n\nEXP 2: Encrypting using KEY: BOTTLE'
./v -C -k BOTTLE -i 1984.txt -o c_1984.txt
echo '\nObtaining KEY:'
./d -i c_1984.txt

echo '\n\nEXP 2: Encrypting using KEY: KITCHEN'
./v -C -k KITCHEN -i 1984.txt -o c_1984.txt
echo '\nObtaining KEY:'
./d -i c_1984.txt

echo '\n\nEXP 2: Encrypting using KEY: SHARKNADO'
./v -C -k SHARKNADO -i 1984.txt -o c_1984.txt
echo '\nObtaining KEY:'
./d -i c_1984.txt

echo 'All Finished'
