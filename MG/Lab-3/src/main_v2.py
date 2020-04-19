#!/usr/bin/env python3

matrixSize = 10
eps = 100.0
filename = "matrix.dat"

def MIN(x, y):
	return {
		x < y: float(x),
		x >= y: float(y)
	}[1]

def genMatrix(matrix):
	for i in range(matrixSize):
		for j in range(matrixSize):
			matrix[i][j] = 1.0 / matrixSize
	for i in range(matrixSize):
		for j in range(matrixSize):
			direction = rnd(0, 2)

			row = rnd(0, matrixSize-1)
			col = rnd(0, matrixSize-1)
			while (row == i):
				row = rnd(0, matrixSize-1)
			while (col == j):
				col = rnd(0, matrixSize-1)

			if (direction):
				value = rnd(0, int(MIN(matrix[row][j], matrix[i][col]) * eps))
				value = float(float(value) / float(eps))
				matrix[i][j] += value
				matrix[row][j] -= value
				matrix[i][col] -= value
				matrix[row][col] += value
			else:
				value = rnd(0, int(MIN(matrix[i][j], matrix[row][col]) * eps))
				value = float(float(value) / float(eps))
				matrix[i][j] -= value
				matrix[row][j] += value
				matrix[i][col] += value
				matrix[row][col] -= value
	for i in range(matrixSize):
		for j in range(matrixSize):
			print(round(matrix[i][j],2), end="\t")
		print()

def drawGraph(data_arr, lgnd_vect):
	plt.hist(data_arr, bins=30, alpha=0.5, label="Entries distribution")
	plt.xlabel("Amount of entries")
	plt.ylabel("Number of state")
	plt.legend()
	for width in range(len(lgnd_vect)):
		plt.text(width, lgnd_vect[width], lgnd_vect[width], ha='center', va='bottom')
	plt.show()

def main():
	iter = 0
	state = 0
	matrix = [[ 0.0 for cnt in range(matrixSize)] for cnt in range(matrixSize)]
	vector = [-1 for cnt in range(10000)]
	lgnd_vect = [0 for cnt in range(matrixSize)]

	# matrix = [
	# [0.4, 0.5, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
	# [0.0, 0.4, 0.5, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
	# [0.0, 0.0, 0.4, 0.5, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0],
	# [0.0, 0.0, 0.0, 0.4, 0.5, 0.1, 0.0, 0.0, 0.0, 0.0],
	# [0.0, 0.0, 0.0, 0.0, 0.4, 0.5, 0.1, 0.0, 0.0, 0.0],
	# [0.0, 0.0, 0.0, 0.0, 0.0, 0.4, 0.5, 0.1, 0.0, 0.0],
	# [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4, 0.5, 0.1, 0.0],
	# [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4, 0.5, 0.1],
	# [0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4, 0.5],
	# [0.5, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4]]

	genMatrix(matrix)
	while (iter < 10000):
		lgnd_vect[state] += 1
		vector[iter] = state
		prob = rnd(0, eps) / eps
		tmp = 0.0
		for i in range(matrixSize):
			tmp += matrix[state][i];
			if (prob < tmp):
				state = i
				break
		iter += 1
	drawGraph(vector, lgnd_vect)

if __name__ == '__main__':
	try:
		from random import randint as rnd
		from matplotlib import pyplot as plt
	except Exception as e:
		exit(e)
	main()
