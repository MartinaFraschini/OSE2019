### CPP compiler wrapper
CXX=mpicxx

### Optimization flags
FFLAGS=-O3 -fopenmp


#######################################################################	

all: BS.exec BSasian.exec

#######################################################################	


## European option
BS.exec: BS.cpp
	$(CXX) $(FFLAGS) BS.cpp -fopenmp -o BS.exec		
	
## Asian option
BSasian.exec: BSasian.cpp
	$(CXX) $(FFLAGS) BSasian.cpp -fopenmp -o BSasian.exec	

	
clean :
	rm -f *.exec
