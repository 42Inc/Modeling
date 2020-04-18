#!/usr/bin/env python3

filePath = "data/matrix.dat"
firstString = [0.4, 0.5, 0.1, 0, 0]
matrixSize = len(firstString)

def genDist():
	probCon = 0
	pathArray = [[-255 for cnt in range(matrixSize)]\
				for cnt in range(matrixSize)]
	pathArray[0] = firstString
	# Generating distances for pathArray
	for i in range(1, matrixSize):
		for j in range(matrixSize):
			if (i == 0):
				pathArray[i][j] = pathArray[matrixSize-1][j-1]
			else:
				pathArray[i][j] = pathArray[i-1][j-1]
	print(pathArray)
	saveData(pathArray)

def saveData(pathData):
	with open(filePath, 'w', encoding='utf-8') as graphFile:
		for row in pathData:
			for path in row:
				graphFile.write("%.1f\t" % path)
			graphFile.write("\n")


if __name__ == '__main__':
	try:
		import sys
		import numpy as np
		from random import randint as rnd, seed
		from datetime import datetime as dt
	except Exception as err:
		print("Error while loading dependencies:", err)
		exit(-1)
	genDist()
