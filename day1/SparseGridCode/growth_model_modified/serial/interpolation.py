#======================================================================
#
#     This routine interfaces with the TASMANIAN Sparse grid
#     The crucial part is 
#
#     aVals[iI]=solver.initial(aPoints[iI], n_agents)[0]  
#     => at every gridpoint, we solve an optimization problem
#
#     Simon Scheidegger, 11/16 ; 07/17
#     Modified by Martina Fraschini
#======================================================================

import TasmanianSG
import numpy as np
from parameters import *
import nonlinear_solver_initial as solver

#======================================================================

def sparse_grid(n_agents, iDepth, curr_theta):
    
    grid  = TasmanianSG.TasmanianSparseGrid()

    k_range=np.array([k_bar, k_up])

    ranges=np.empty((n_agents, 2))


    for i in range(n_agents):
        ranges[i]=k_range

    iDim=n_agents

    grid.makeLocalPolynomialGrid(iDim, iOut, iDepth, which_basis, "localp")
    grid.setDomainTransform(ranges)

    aPoints=grid.getPoints()
    iNumP1=aPoints.shape[0]
    aVals=np.empty([iNumP1, 1])
    for iI in range(iNumP1):
        aVals[iI]=solver.initial(aPoints[iI], n_agents, curr_theta)[0]    
    grid.loadNeededPoints(aVals)
    
    for iK in range(refinement_level):
        #file=open("comparison0.txt", 'w')
        grid.setSurplusRefinement(fTol, 1, "fds")
        aPoints=grid.getNeededPoints()
        iNumP1=aPoints.shape[0]
        aVals = np.empty([iNumP1, 1])
        for iI in range(iNumP1):
            aVals[iI]=solver.initial(aPoints[iI], n_agents, curr_theta)[0]
            #v=aVals[iI,:]*np.ones((1,n_shocks))
            #to_print=np.hstack((aPoints[iI,:].reshape(n_shocks,n_agents), v))
            #np.savetxt(file, to_print, fmt='%2.16f')
        #file.close()
        grid.loadNeededPoints(aVals)
    
    f=open("grid.txt", 'w')
    np.savetxt(f, aPoints, fmt='% 2.16f')
    f.close()
    
    return grid
#======================================================================

