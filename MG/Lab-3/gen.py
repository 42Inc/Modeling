#!/usr/bin/env python3

filePath = "matrix.dat"	
N = 10						

def genDist():
	probCon = 0
	pathArray = [[-255 for cnt in range(citiesNum)]\
				for cnt in range(citiesNum)]

	# Generating distances for pathArray
	for i in range(1, N):
		for j in range(N):

	saveData(pathArray)

def saveData(pathData):
	with open(filePath, 'w', encoding='utf-8') as graphFile:
		for row in pathData:
			for path in row:
				graphFile.write("%d\t" % path)
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
