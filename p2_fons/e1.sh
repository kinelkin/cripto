#!/bin/bash
echo 'EX 1 Several Texts for these experiments:'


echo '\nmini.txt: number of words'
wc -c mini.txt
echo 'generating stats_mini_p.txt and stats_mini_i.txt'
./seg-perf -I -i mini.txt -o stats_mini_i.txt
./seg-perf -P -i mini.txt -o stats_mini_p.txt

echo '\nshort.txt: number of words'
wc -c short.txt
echo 'generating stats_short_p.txt and stats_short_i.txt'
./seg-perf -I -i short.txt -o stats_short_i.txt
./seg-perf -P -i short.txt -o stats_short_p.txt

echo '\nmed.txt: number of words'
wc -c med.txt
echo 'generating stats_med_p.txt and stats_med_i.txt'
./seg-perf -I -i med.txt -o stats_med_i.txt
./seg-perf -P -i med.txt -o stats_med_p.txt

echo '\n1984.txt: number of words'
wc -c 1984.txt
echo 'generating stats_1984_p.txt and stats_1984_i.txt'
./seg-perf -I -i 1984.txt -o stats_1984_i.txt
./seg-perf -P -i 1984.txt -o stats_1984_p.txt

echo '\nAll Finished'
