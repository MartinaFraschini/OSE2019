#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

#include <mpi.h>
 
int main(int argc, char *argv[])
{
    int niter = 10000000;
    double x,y;
    int i, rank, size;
    int count=0, count_tot;
    double z;
    double pi;
    double time = 0.;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    time -= MPI_Wtime();

    int nitnode = niter/size;
    int rmd = niter % size;
    if (rank<rmd)
    {
        nitnode += 1;
    }

    //set seed
    srand((rank+1)*2);

    //main loop
    for (int i=0; i<nitnode; ++i)
    {
        //get random points
        x = (double)random()/RAND_MAX;
        y = (double)random()/RAND_MAX;
        z = sqrt((x*x)+(y*y));
        //check to see if point is in unit circle
        if (z<=1)
        {
            ++count;
        }
    }

    MPI_Reduce(&count, &count_tot, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        pi = ((double)count_tot/(double)niter)*4.0;          //p = 4(m/n)
        time += MPI_Wtime();
        std::cout << "Pi: " << pi << std::endl;
        std::cout << "time : " << time << " seconds" << std::endl;
    }

    MPI_Finalize();

    return 0;
}
