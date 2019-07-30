#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

#include <omp.h>
#include <mpi.h>
 
int main(int argc, char *argv[])
{
    int niter = 10000000;
    double x,y;
    int i;
    int count=0, count_tot;
    double z;
    double pi;
    int max_threads = omp_get_max_threads();
    double time = 0.;

    int numprocs, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    time -= MPI_Wtime();

    int nitnode = niter/numprocs;
    int rmd = niter % numprocs;
    if (rank<rmd)
    {
        nitnode += 1;
    }

    //srand(time(NULL));
    //main loop
    #pragma omp parallel private(x,y,z) reduction(+:count)
    {   
        unsigned int myseed = 25234 + 17 * omp_get_thread_num() * (rank+1)*2;
        #pragma omp for
        for (int i=0; i<nitnode; ++i)
        {
            //get random points
            x = (double)rand_r(&myseed)/RAND_MAX;
            y = (double)rand_r(&myseed)/RAND_MAX;
            z = sqrt((x*x)+(y*y));
            //check to see if point is in unit circle
            if (z<=1)
            {
                ++count;
            }
        }
    }

    MPI_Reduce(&count, &count_tot, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        pi = ((double)count_tot/(double)niter)*4.0;        //p = 4(m/n)
        time += MPI_Wtime();

        std::cout << "Pi: " << pi << std::endl;
        std::cout << max_threads     << " threads" << std::endl;
        std::cout << numprocs     << " processors" << std::endl;
        std::cout << "time : " << time << " seconds" << std::endl;
    }

    MPI_Finalize();
    
    return 0;
}
