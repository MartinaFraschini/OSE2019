#######################################################################	

all: BS.exec BSasian.exec

#######################################################################	


## European option
BS.exec: BS.cpp
	g++ BS.cpp -fopenmp -o BS.exec		
	
## Asian option
BSasian.exec: BSasian.cpp
	g++ BSasian.cpp -fopenmp -o BSasian.exec	

	
clean :
	rm -f *.exec
