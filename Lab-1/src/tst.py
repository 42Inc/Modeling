import sys
import math
import numpy as np
import random as rnd
from math import exp
from scipy import integrate
from math import cos, pi

rnd.seed(10, version=2)
rand_dots = np.zeros([1, 20])
for i in range (len(rand_dots[0])):
    rnd.seed(i, version=2)
    rand_dots[0][i] = rnd.uniform(-6, 6)
fin_arr = np.zeros([2, 20])
print(rand_dots)
print("----------------------")
print(fin_arr)
eps = 0
pos = 0
f = 2
for i in range (len(rand_dots[0])):
    if (rand_dots[0][i] > eps):
        fin_arr[0, pos] = rand_dots[0, i]
        fin_arr[1, pos] = rand_dots[0, i] * f
        pos += 1

print("----------------------")
print(fin_arr)
