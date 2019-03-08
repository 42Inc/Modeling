#!/usr/bin/python

import sys
import math
import numpy as np
import random as rnd
from math import exp
from scipy import integrate
from math import cos, pi

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
    rand_dots = np.zeros([1, 20])
    for i in range (len(rand_dots[0])):
        rnd.seed(i, version=2)
        rand_dots[0][i] = rnd.uniform(-6, 0)
    fin_arr = np.zeros([2, 20])

    print(rand_dots)
    print("----------------------")
    print(fin_arr)

    pos = 0
    f = 2

    for i in range (len(rand_dots[0])):
        if not (func(rand_dots[0][i])):
            fin_arr[0, pos] = rand_dots[0, i]
            fin_arr[1, pos] = rand_dots[0, i] * f
            pos += 1

    print("----------------------")
    print(fin_arr)


def main(argv = None):
    rnd.seed(10, version=2)
    mathexp = MathExp_Disper(v, -4, 5*a, n)
    disper = MathExp_Disper(w, -4, 5*a, n)
    print("MathExp", mathexp)
    print("Dispersion", disper - mathexp**2)
    print("Square deviation", pow(disper - mathexp**2, .5))
    gen_ran()

main()
