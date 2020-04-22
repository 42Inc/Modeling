#!/usr/bin/python

import sys
import math
import numpy as np
import random as rnd
from scipy import integrate
import matplotlib.pyplot as plt

a = -0.5379
n = 100
v = lambda x: x*(x + 4)**(0.5)

def MathExp_Disper(f, a, b, n):
    h = float(b - a)/n
    result = 0.5*(f(a) + f(b))
    for i in range(1, n):
        result += f(a + i*h)
    result *= h
    return result

w = lambda x: x**2 * (x + 4)**(0.5)

def func(x):
    y = 0.0
    if x > -4 and x <= 5*a:
        y = math.sqrt(x + 4)
    elif x <= -4 or x > 5*a:
        y = 0
    return y

def gen_ran():
    rand_dots = np.zeros([1, 1000])
    for i in range (len(rand_dots[0])):
        rnd.seed(i, version=2)
        rand_dots[0][i] = rnd.uniform(-10, 10)
    fin_arr = np.zeros([3, 1000])
    pos = 0

    for i in range (len(rand_dots[0])):
        fin_arr[0, pos] = rand_dots[0, i]
        fin_arr[1, pos] = func(rand_dots[0, i])
        pos += 1
    fin_arr[2, 0] = pos
    return fin_arr

def main(argv = None):
    rnd.seed(10, version=2)
    mathexp = MathExp_Disper(v, -4, 5*a, n)
    disper = MathExp_Disper(w, -4, 5*a, n)

    print("MathExp", mathexp)
    print("Dispersion", disper - mathexp**2)
    print("Square deviation", pow(disper - mathexp**2, .5))

    rnd_arr = np.zeros([2, 1000])
    rnd_arr = gen_ran()
    cnt = rnd_arr[2][0]
    rnd_arr_x = np.zeros([1, int(cnt)])
    rnd_arr_y = np.zeros([1, int(cnt)])
    for i in range(int(cnt)):
        rnd_arr_x[0][i] = rnd_arr[0][i]
        rnd_arr_y[0][i] = rnd_arr[1][i]

    x2 = np.arange(-4, 4*np.pi + 0.1, 0.1)
    y2 = np.sqrt(x2+4)

    fig = plt.figure()
    plt.plot(x2, y2, color='red', linewidth=4.0)
    plt.plot(rnd_arr_x[0], rnd_arr_y[0], 'bo', color='blue')
    plt.grid(True)
    plt.show()

main()
