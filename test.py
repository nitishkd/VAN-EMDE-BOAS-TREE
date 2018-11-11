import math
import matplotlib.pyplot as plt
import random
import os

fd = open("outputbino.txt", 'r')
data= fd.readlines()
fd.close()
fd1 = open("outputvb.txt", 'r')
data1= fd1.readlines()

fd3 = open("outputavl.txt", 'r')
data3= fd3.readlines()


x1 = []
N = 100
n = 0
for i in range(150):
    n += (5*N)
    k = n
    x1.append(n+1+k)

ls1 = []
ls2 = []

ls3 = []
for t in data:
    ls1.append(int(t))  

for t in data1:
    ls2.append(int(t))

for t in data3:
    ls3.append(int(t))

plt.plot(x1,ls1 ,'r', label='BINOMIAL HEAP')
plt.plot(x1,ls2, 'b', label='vBE TREE')
plt.plot(x1,ls3 ,'g', label='AVL TREE')

plt.xlabel('NUMBER OF EDGES')
plt.ylabel('TIME OF EXECUTION (MICROSECONDS)')


legend = plt.legend(loc='upper center')
legend.get_frame().set_facecolor('C0')

plt.show()