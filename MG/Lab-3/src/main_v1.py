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

			if (direction):
				if matrix[row][j] < matrix[i][col]:
					min = matrix[row][j]
				else:
					min = matrix[i][col]
				value = randint(0, int(min * eps))
				value = float(float(value) / float(eps))
				matrix[i][j] += value
				matrix[row][j] -= value
				matrix[i][col] -= value
				matrix[row][col] += value
			else:
				if matrix[i][j] < matrix[row][col]:
					min = matrix[i][j]
				else:
					min = matrix[row][col]
				value = randint(0, int(min * eps))
				value = float(float(value) / float(eps))
				matrix[i][j] -= value
				matrix[row][j] += value
				matrix[i][col] += value
				matrix[row][col] -= value
	for i in range(n):
		for j in range(n):
			print(round(matrix[i][j],2), end="\t")
		print()

i = 0
j = 0
n = 10
step = 0
state = 0
prob = 0.0
eps = 100.0
repeats = 10000
tmp_double = 0.0
filename = "matrix.dat"
vector = [-1 for cnt in range(repeats)]
matrix = [[ 0.0 for cnt in range(n)] for cnt in range(n)]
matrix = [
	[0.4, 0.5, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
	[0.0, 0.4, 0.5, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
	[0.0, 0.0, 0.4, 0.5, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0],
	[0.0, 0.0, 0.0, 0.4, 0.5, 0.1, 0.0, 0.0, 0.0, 0.0],
	[0.0, 0.0, 0.0, 0.0, 0.4, 0.5, 0.1, 0.0, 0.0, 0.0],
	[0.0, 0.0, 0.0, 0.0, 0.0, 0.4, 0.5, 0.1, 0.0, 0.0],
	[0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4, 0.5, 0.1, 0.0],
	[0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4, 0.5, 0.1],
	[0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4, 0.5],
	[0.5, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4]]
# generator(matrix)
while (step < repeats):
	vector[step] = state
	prob = randint(0, eps) / eps
	tmp_double = 0.0
	for i in range(n):
		tmp_double += matrix[state][i];
		if (prob < tmp_double):
			state = i
			break
	step += 1

pyplot.hist(vector,bins=70, label="Вероятностное распределение", color='cyan')
pyplot.xlabel("Кол-во вхождений")
pyplot.ylabel("Номер состояния")
pyplot.legend()
pyplot.show()
