### CPP compiler wrapper
CXX=mpicxx

### Optimization flags
FFLAGS=-O3

#######################################################################	

all: broadcast.exec allreduce.exec scatter.exec MCpi.exec

#######################################################################	

## Exercise 1: broadcast
broadcast.exec: broadcast.cpp
	$(CXX) $(FFLAGS) broadcast.cpp -o broadcast.exec

## Exercise 2: allreduce
allreduce.exec: allreduce.cpp
	$(CXX) $(FFLAGS) allreduce.cpp -o allreduce.exec

## Exercise 3: scatter
scatter.exec: scatter.cpp
	$(CXX) $(FFLAGS) scatter.cpp -o scatter.exec

## Exercise 4: estimate pi with Monte Carlo
MCpi.exec: MCpi.cpp
	$(CXX) $(FFLAGS) MCpi.cpp -o MCpi.exec
	
#######################################################################	

clean :
	rm -f *.exec

#######################################################################	
