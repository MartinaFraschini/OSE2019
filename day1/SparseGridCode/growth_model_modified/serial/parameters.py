#======================================================================
# 
#     sets the parameters for the model
#     "Growth Model"
#
#     The model is described in Scheidegger & Bilionis (2017)
#     https://papers.ssrn.com/sol3/papers.cfm?abstract_id=2927400
#
#     Simon Scheidegger, 11/16 ; 07/17
#     Modiefied by Martina Fraschini
#====================================================================== 

import numpy as np

#====================================================================== 

# Depth of "Classical" Sparse grid
iDepth=3
iOut=1         # how many outputs
which_basis = 1 #linear basis function (2: quadratic local basis)

# Adaptive Sparse grid
fTol = 1.E-5    # tolerance criterion
refinement_level = 3    # refinement level

# control of iterations
numstart = 0   # which is iteration to start (numstart = 0: start from scratch, number=/0: restart)
numits = 10    # which is the iteration to end

# How many random points for computing the errors
No_samples = 1000

#====================================================================== 

# Model Paramters

n_agents=2  # number of continuous dimensions of the model

beta=0.8
rho=0.95
zeta=0.5
psi=0.36
gamma=2.0
delta=0.025
eta=1
big_A=(1.0-beta)/(psi*beta)

theta = np.array([.9, .95, 1., 1.05, 1.1])
theta_inf = 1.    # value of theta at infinity = average of all possible values for theta
n_shocks = len(theta)
prob = .2 * np.ones([n_shocks,])

# Ranges For States
range_cube=1 # range of [0..1]^d in 1D
k_bar=0.2
k_up=3.0

# Ranges for Controls
c_bar=1e-2
c_up=10000.0

l_bar=1e-2
l_up=1.0

inv_bar=1e-2
inv_up=10000.0

#====================================================================== 




