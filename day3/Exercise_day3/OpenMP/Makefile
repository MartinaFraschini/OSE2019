#######################################################################	
all: normalize_vec.exec dot_prod.exec MCpi.exec
#######################################################################	

## Exercise 1: normalize a vector
normalize_vec.exec : normalize_vec.cpp
	g++ normalize_vec.cpp -fopenmp -o normalize_vec.exec

## Exercise 2: dot product
dot_prod.exec : dot_prod.cpp
	g++ dot_prod.cpp -fopenmp -o dot_prod.exec

## Exercise 3: estimate pi with Monte Carlo
MCpi.exec : MCpi.cpp
	g++ MCpi.cpp -fopenmp -o MCpi.exec

#######################################################################	
	
clean :
	rm -f *.exec