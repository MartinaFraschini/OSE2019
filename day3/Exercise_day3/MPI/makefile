### CPP compiler wrapper
CXX=mpicxx

### Optimization flags
FFLAGS=-O3

#######################################################################	

all: broadcast.exec allreduce.exec

#######################################################################	

## Exercise 1: broadcast
broadcast.exec: broadcast.cpp
	$(CXX) $(FFLAGS) broadcast.cpp -o broadcast.exec

## Exercise 2: allreduce
allreduce.exec: allreduce.cpp
	$(CXX) $(FFLAGS) allreduce.cpp -o allreduce.exec
	
#######################################################################	

clean :
	rm -f *.exec

#######################################################################	
