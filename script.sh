#!/bin/bash

g++  Avl.cpp -o Avl
g++  vb.cpp -o vb

for i in {0..149}
do
    echo file_$i.txt
    ./Avl < file_$i.txt
    ./vb < file_$i.txt
done
