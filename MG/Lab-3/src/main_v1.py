#!/usr/bin/env python3
import sys
from random import randint
from matplotlib import pyplot

def rowsum(row, matrix):
	i = 0
	result = 0.0
	for i in range(n):
		result += matrix[row][i]
	return result

def colsum(col, matrix):
	i = 0
	result = 0.0
	for i in range(n):
		result += matrix[i][col]
	return result

def generator(matrix):
	i = 0
	j = 0
	row = 0
	col = 0
	direction = 0
	value = 0.0

	for i in range(n):
		for j in range(n):
			matrix[i][j] = 1.0 / n

	for i in range(n):
		for j in range(n):
			direction = randint(0, 2)

			row = randint(0, n-1)
			col = randint(0, n-1)
			while (row == i):
				row = randint(0, n-1)
			while (col == j):
				col = randint(0, n-1)

			print(i,j, row, col)
			if (direction):
				if matrix[row][j] < matrix[i][col]:
					min = matrix[row][j]
				else:
					min = matrix[i][col]
				value = randint(0, min * eps) / eps
				matrix[i][j] += value
				matrix[row][j] -= value
				matrix[i][col] -= value
				matrix[row][col] += value
			else:
				if matrix[i][j] < matrix[row][col]:
					min = matrix[i][j]
				else:
					min = matrix[row][col]
				value = randint(0, min * eps) / eps
				matrix[i][j] -= value
				matrix[row][j] += value
				matrix[i][col] += value
				matrix[row][col] -= value

	for i in range(n):
		for j in range(n):
			print(matrix[i][j])
	print()

def drawGraph(y_arr):
	x_arr = [cnt for cnt in range(n)]
	pyplot.plot(x_arr, y_arr, label="Не совсем, но цепь Маркова")
	pyplot.ylabel("Количество входов")
	pyplot.xlabel("Номер состояния")
	pyplot.legend()
	pyplot.show()

n = 5
i = 0
j = 0
step = 0
state = 0
prob = 0.0
eps = 100.0
repeats = 1000
tmp_double = 0.0
filename = "matrix.dat"
vector = [0 for cnt in range(n)]
matrix = [[ 0.0 for cnt in range(n)] for cnt in range(n)]

generator(matrix)
while (step < repeats):
	vector[state] += 1
	prob = randint(0, eps) / eps
	tmp_double = 0.0
	for i in range(n):
		tmp_double += matrix[state][i];
		if (prob < tmp_double):
			state = i
			break
	step += 1
drawGraph(vector)
