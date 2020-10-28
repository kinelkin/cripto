#!/bin/bash
echo 'We will be using the novel 1984 for these experiments'

gcc -g -o v vigenere.c funciones_alt.c


echo 'Showing the first lines of the book'
head 1984.txt --lines=10

echo '\n\nEXP 1:\n Encrypting with key TRICKS to c_1984'
./v -C -k TRICKS -i 1984.txt -o c_1984.txt
echo 'Showing the first lines of the encrypted book'
head c_1984.txt --lines=10

echo '\nEXP 1: Decrypting with key TRICKS to r_1984'
./v -D -k TRICKS -i c_1984.txt -o r_1984.txt
echo 'Comparing the decrypted version with the original'
diff cap_1984.txt r_1984.txt
echo 'No Output Means All OK'

echo '\n\n\nEXP 2:\n Encrypting with key TRICKTOR to c_1984'
./v -C -k TRICKTOR -i 1984.txt -o c_1984.txt
echo 'Showing the first lines of the encrypted book'
head c_1984.txt --lines=10

echo '\nEXP 2: Decrypting with key TRICKTOR to r_1984'
./v -D -k TRICKTOR -i c_1984.txt -o r_1984.txt
echo 'Comparing the decrypted version with the original'
diff cap_1984.txt r_1984.txt
echo 'No Output Means All OK'

echo '\n\n\nEXP 3: Encrypting with key NAVYSEALSARECOMING to c_1984'
./v -C -k NAVYSEALSARECOMING -i 1984.txt -o c_1984.txt
echo 'Showing the first lines of the encrypted book'
head c_1984.txt --lines=10

echo '\nEXP 3: Decrypting with key NAVYSEALSARECOMING to r_1984'
./v -D -k NAVYSEALSARECOMING -i c_1984.txt -o r_1984.txt
echo 'Comparing the decrypted version with the original'
diff cap_1984.txt r_1984.txt
echo 'No Output Means All OK'

echo 'All Finished'
