##################################################################################
#
#  Day 1 - Sparse grids
#  Homework 1 - Exercise 1
#  Martina Fraschini
#
##################################################################################

# import packages
import TasmanianSG
import numpy as np
import math
from random import uniform


# define function for interpolation with non-adaptive sparse grids
def nonadaptive():


# define function for interpolation with adaptive sparse grids
def adaptive():


# generate plots #points - error
def plotpterr():


# define parameters
npoints = [1e02, 1e03, 1e04, 1e05, 1e06]


# oscillatory test function
for npts in npoints:
	# 1000 2-dimensional sample points
	aPnts = np.empty([int(npts), 2])
	for iI in range(int(npts)):
    	for iJ in range(2):
        	aPnts[iI][iJ] = uniform(-1.0, 1.0)

    # Result
	aTres = np.empty([int(npts),])
	for iI in range(int(npts)):
    	aTres[iI] = math.cos(0.5 * math.pi * aPnts[iI][0]) * math.cos(0.5 * math.pi * aPnts[iI][1])
