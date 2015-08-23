#!/usr/bin/env python
# -*- coding: utf-8 -*-
################################################################################
#
#   Generates adjacency matrices of any size
#
#   Author: Cs4r
#
################################################################################

import sys
from random import randint

def main(argv):
	numberOfVertices = 0
	try:
		numberOfVertices = abs(int(argv[1]))
	except:
		print "Wrong execution!"
		print "Syntax:\t%s: <number_of_vertices>" % argv[0] 
		return sys.exit(1) 	

	fileName = "matrix_%dx%d.txt" % (numberOfVertices, numberOfVertices)

	file = open(fileName, 'w')

	file.write("%d\n" % (numberOfVertices))

	upperLimit = numberOfVertices*2

	for i in range(numberOfVertices):
		for j in range(numberOfVertices):
			randomNumber = randint(1,upperLimit)

			if randomNumber > upperLimit*3/4.:
				randomNumber = 0
		
			file.write( "%d %d %d\n" % (i,j,randomNumber))

	file.close()

	return sys.exit(0) 


if __name__ == "__main__":
   main(sys.argv[0:2])	


