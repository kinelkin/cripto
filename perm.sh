#!/bin/bash
echo 'We will be using the novel 1984 for these experiments'

echo 'Showing the first lines of the mini text'
head mini.txt --lines=10

echo '\n\nEXP 1:\n Encrypting with perms: -k1 [ 1 3 2 4 0 ] -k2 [ 1 3 2 0 ] to c_mini'
./p -C -k1 [ 1 3 2 4 0 ] -k2 [ 1 3 2 0 ] -i mini.txt -o c_mini.txt
echo 'Showing the first lines of the encrypted text'
head c_mini.txt --lines=10

echo '\n\nEXP 1:\n Decrypting with perms: -k1 [ 1 3 2 4 0 ] -k2 [ 1 3 2 0 ] r_mini'
./p -D -k1 [ 1 3 2 4 0 ] -k2 [ 1 3 2 0 ] -i c_mini.txt -o r_mini.txt
echo 'Showing the first lines of the decrypted text'
head r_mini.txt --lines=10
echo '\nDifferences between original text (padded) and deciphered:'
diff cap_mini.txt r_mini.txt
echo '\nNo Output Means All OK'

echo 'Showing the first lines of the short text'
head short.txt --lines=10

echo '\n\nEXP 1:\n Encrypting with perms: -k1 [ 7 2 0 1 3 5 4 6 ] -k2 [ 4 0 2 3 1 ] to c_short'
./p -C -k1 [ 7 2 0 1 3 5 4 6 ] -k2 [ 4 0 2 3 1 ] -i short.txt -o c_short.txt
echo 'Showing the first lines of the encrypted text'
head c_short.txt -c 100

echo '\n\nEXP 1:\n Decrypting with perms: -k1 [ 7 2 0 1 3 5 4 6 ] -k2 [ 4 0 2 3 1 ] r_short'
./p -D -k1 [ 7 2 0 1 3 5 4 6 ] -k2 [ 4 0 2 3 1 ] -i c_short.txt -o r_short.txt
echo 'Showing the first lines of the decrypted text'
head r_short.txt -c 100
echo '\nDifferences between original text (padded) and deciphered:'
diff cap_short.txt r_short.txt
echo '\nNo Output Means All OK'

echo '\n\nEXP 2: '
echo 'Showing the first lines of the 1984 text'
head 1984.txt --lines=10
echo 'Encrypting with perms: -k1 [ 7 2 0 1 3 5 4 6 ] -k2 [ 4 0 2 3 1 ] to c_1984'
./p -C -k1 [ 7 2 0 1 3 5 4 6 ] -k2 [ 4 0 2 3 1 ] -i 1984.txt -o c_1984.txt
echo 'Showing the first line of the encrypted text'
head c_1984.txt -c 100

echo '\n\nEXP 2:\n Decrypting with perms: -k1 [ 7 2 0 1 3 5 4 6 ] -k2 [ 4 0 2 3 1 ] r_1984'
./p -D -k1 [ 7 2 0 1 3 5 4 6 ] -k2 [ 4 0 2 3 1 ] -i c_1984.txt -o r_1984.txt
echo 'Showing the first lines of the decrypted text'
head r_1984.txt -c 100
echo '\nDifferences between original text (padded) and deciphered:'
diff cap_1984.txt r_1984.txt
echo '\nNo Output Means All OK'

echo 'All Finished'
