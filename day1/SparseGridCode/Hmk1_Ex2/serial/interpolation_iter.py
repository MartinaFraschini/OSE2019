#======================================================================
#
#     This routine interfaces with the TASMANIAN Sparse grid
#     The crucial part is 
#
#     aVals[iI]=solveriter.iterate(aPoints[iI], n_agents)[0]  
#     => at every gridpoint, we solve an optimization problem
#
#     Simon Scheidegger, 11/16 ; 07/17
#======================================================================

import TasmanianSG
import numpy as np
from parameters import *
import nonlinear_solver_iterate as solveriter

#======================================================================

def sparse_grid_iter(n_agents, iDepth, valold):
    
    grid  = TasmanianSG.TasmanianSparseGrid()

    k_range=np.array([k_bar, k_up])

    ranges=np.empty((n_agents, 2))


    for i in range(n_agents):
        ranges[i]=k_range

    iDim=n_agents
    iOut=1

    grid.makeLocalPolynomialGrid(iDim, iOut, iDepth, which_basis, "localp")
    grid.setDomainTransform(ranges)

    aPoints=grid.getPoints()
    iNumP1=aPoints.shape[0]
    aVals=np.empty([iNumP1, n_shocks])
    EV = np.empty([iNumP1, 1])
    for iI in range(iNumP1):
        for sS in range(n_shocks):
            aVals[iI,sS]=solveriter.iterate(aPoints[iI], n_agents, theta[sS], valold)[0]
        EV[iI] = sum(prob * aVals[iI,:])
    grid.loadNeededPoints(EV)
    
    #for iK in range(refinement_level):
        #file=open("comparison1.txt", 'w')
    #    grid.setSurplusRefinement(fTol, 1, "fds")
    #    aPoints=grid.getNeededPoints()
    #    aVals = np.empty([aPoints.shape[0], n_shocks])
    #    EV = np.empty([aPoints.shape[0], 1])
    #    for iI in range(aPoints.shape[0]):
    #        for sS in range(n_shocks):
    #            aVals[iI][sS]=solveriter.iterate(aPoints[iI], n_agents, theta[sS], valold)[0]
    #        EV[iI] = sum(prob * aVals[iI][:])
            #v=aVals[iI]*np.ones((1,1))
            #to_print=np.hstack((aPoints[iI].reshape(1,n_agents), v))
            #np.savetxt(file, to_print, fmt='%2.16f')
        #file.close()
    #grid.loadNeededPoints(EV)
    
    f=open("grid_iter.txt", 'w')
    np.savetxt(f, aPoints, fmt='% 2.16f')
    f.close()
    
    return grid, aPoints, aVals

#======================================================================
