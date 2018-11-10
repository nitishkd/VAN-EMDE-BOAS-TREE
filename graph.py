import math
import matplotlib.pyplot as plt
import random
import os

# lsl = []
# lsll = []
# ls2 = []
# for i in range(100, 100000, 100):
#     x = random.randint(1,500)
#     lsl.append(math.log(i+ x))
#     lsll.append(math.log(math.log(i+x)))
#     x = random.randint(1,5)
#     ls2.append(math.log(i+x))

# plt.plot(lsl)
# plt.plot(lsll)
# plt.plot(ls2)

# plt.show()
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
    fd.write(str(m+1)+ '\n')

    for i in range(0,n):
        fd.write(str(i) + " " + str( i+1) + " " + str( random.randint(1,10000)) + '\n')

    fd.write(str(n) + " " + str( 0) + " " + str( random.randint(1,10000)) + '\n')
    fd.close()
