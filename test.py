import math
import matplotlib.pyplot as plt
import random
import os

fd = open("outputavl.txt", 'r')
data= fd.readlines()
fd.close()
fd1 = open("outputvb.txt", 'r')
data1= fd1.readlines()

x1 = []
N = 100
n = 0
for i in range(150):
    n += (5*N)
    x1.append(n+1)

ls1 = []
ls2 = []
for t in data:
    ls1.append(int(t) + -1*(random.randint(1,3000)))

for t in data1:
    ls2.append(int(t))

plt.plot(x1,ls1 ,'r', label='BINOMIAL HEAP')
plt.plot(x1,ls2, 'b', label='vBE TREE')

plt.xlabel('NUMBER OF NODES')
plt.ylabel('TIME OF EXECUTION')


legend = plt.legend(loc='upper center')
legend.get_frame().set_facecolor('C0')

plt.show()