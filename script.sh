#!/bin/bash
rm outputbino.txt
rm outputavl.txt
rm outputvb.txt

g++  AVL.cpp -o AVL
g++  vEB.cpp -o vEB
g++ BINOMIAL.cpp -o BINOMIAL
for i in {0..149}
do
    echo file_$i.txt
    ./AVL < file_$i.txt
    ./BINOMIAL < file_$i.txt
    ./vEB < file_$i.txt
done
