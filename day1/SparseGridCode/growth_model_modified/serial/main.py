#======================================================================
#
#     This routine solves an infinite horizon growth model 
#     with dynamic programming and sparse grids
#
#     The model is described in Scheidegger & Bilionis (2017)
#     https://papers.ssrn.com/sol3/papers.cfm?abstract_id=2927400
#
#     external libraries needed:
#     - IPOPT (https://projects.coin-or.org/Ipopt)
#     - PYIPOPT (https://github.com/xuy/pyipopt)
#     - TASMANIAN (http://tasmanian.ornl.gov/)
#
#     Simon Scheidegger, 11/16 ; 07/17
#     Modified by Martina Fraschini
#======================================================================

import nonlinear_solver_initial as solver     #solves opt. problems for terminal VF
import nonlinear_solver_iterate as solviter   #solves opt. problems during VFI
from parameters import *                      #parameters of model
import interpolation as interpol              #interface to sparse grid library/terminal VF
import interpolation_iter as interpol_iter    #interface to sparse grid library/iteration
import postprocessing as post                 #computes the L2 and Linfinity error of the model

import TasmanianSG                            #sparse grid library
import numpy as np
from matplotlib import pyplot as plt


#======================================================================
# Start with Value Function Iteration

value = []
for sS in range(n_shocks):
    # terminal value function
    valnew=TasmanianSG.TasmanianSparseGrid()
    if (numstart==0):
        valnew=interpol.sparse_grid(n_agents, iDepth, theta[sS])
        valnew.write("valnew_1." + str(numstart) + ".txt") #write file to disk for restart

    # value function during iteration
    else:
        valnew.read("valnew_1." + str(numstart) + ".txt")  #write file to disk for restart
        
    value = value.append(valnew)

valold=TasmanianSG.TasmanianSparseGrid()
valold=valnew

for i in range(numstart, numits):
    print(i)
    value = []
    for sS in range(n_shocks):
        valnew=TasmanianSG.TasmanianSparseGrid()
        valnew=interpol_iter.sparse_grid_iter(n_agents, iDepth, valold, theta[sS])
        valold=TasmanianSG.TasmanianSparseGrid()
        valold=valnew
        valnew.write("valnew_1." + str(i+1) + ".txt")
        
    value = value.append(valnew)
    
#======================================================================
print( "===============================================================")
print( " " )
print( " Computation of a growth model of dimension ", n_agents ," finished after ", numits, " steps")
print( " " )
print( "===============================================================")
#======================================================================

# compute errors   
avg_err=post.ls_error(n_agents, numstart, numits, No_samples)

#======================================================================
print( "===============================================================")
print( " ")
print( " Errors are computed -- see errors.txt")
print( " ")
print( "===============================================================")
#======================================================================