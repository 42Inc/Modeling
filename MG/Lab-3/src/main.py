#!/usr/bin/env python3
import sys
from random import randint as rnd

eps = 100.0
n = 5

def MIN(x, y):
	return {
		x < y : x,
		x > y : y
	}[1]

def rowsum(row, matrix):
	i = 0
	result = 0.0
	for i in range(n):
		result += matrix[row][i]
	return result

def colsum(col, matrix):
	int i = 0
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
			direction = rnd(0, 2)

			while ((row = rnd(0, n)) == i)
			while ((col = rnd(0, n)) == j)

			if (direction):
				value = rnd(0, MIN(matrix[row][j], matrix[i][col]) * eps) / eps
				matrix[i][j] += value
				matrix[row][j] -= value
				matrix[i][col] -= value
				matrix[row][col] += value
			else:
				value = rnd(0, MIN(matrix[i][j], matrix[row][col]) * eps) / eps
				matrix[i][j] -= value
				matrix[row][j] += value
				matrix[i][col] += value
				matrix[row][col] -= value

	for i in range(n):
		for j in range(n):
			print(matrix[i][j])
	print()

def main():
	i = 0
	j = 0
	tmp_double = 0.0
	filename = "matrix.dat"
	matrix = NULL
	repeats = 10000
	step = 0
	state = 0
	prob = 0.0

	matrix = [[ 0.0 for cnt in range(n)] for cnt in range(n)]
	generator(matrix)

	do {
		prob = rnd(0, eps) / eps;
		print(step, state)
		tmp_double = 0.0;
		for (i = 0; i < n; ++i) {
			tmp_double += matrix[state][i];
			if (prob < tmp_double) {
				state = i;
				break;
			}
		}
		++step;
	} while (step < repeats);
	return EXIT_SUCCESS;
}
