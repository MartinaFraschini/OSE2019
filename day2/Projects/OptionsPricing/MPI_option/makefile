### CPP compiler wrapper
CXX=mpicxx

### Optimization flags
FFLAGS=-O3

#######################################################################	

all: BS.exec BSasian.exec

#######################################################################	

## European option
BS.exec: BS.cpp
	$(CXX) $(FFLAGS) BS.cpp -o BS.exec

## Asian option
BSasian.exec: BSasian.cpp
	$(CXX) $(FFLAGS) BSasian.cpp -o BSasian.exec
	
#######################################################################	

clean :
	rm -f *.exec

#######################################################################	
