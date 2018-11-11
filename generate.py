import math
import matplotlib.pyplot as plt
import random
import os
N = 100
M = 100
n = 0
m = 0
for i in range(150):
    fname = "file_"+str(i) + ".txt"
    fd = open(fname, 'w+')
    print("***")
    n += (5*N) 
    m += (5*M)
    fd.write(str(n+1) + '\n')
    k = m
    fd.write(str(m+1+k)+ '\n')

    for i in range(0,n):
        fd.write(str(i) + " " + str( i+1) + " " + str( random.randint(1,1000)) + '\n')
    
	
    fd.write(str(n) + " " + str( 0) + " " + str( random.randint(1,1000)) + '\n')

    for i in range(0,k):
        a = random.randint(1,n-1)
        b = random.randint(1,n-1)
        c = random.randint(1,10000)
        fd.write(str(a) + " " + str(b) + " " + str(c) + '\n')
    
    fd.close()
