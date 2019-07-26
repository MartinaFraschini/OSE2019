#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

#include <omp.h>
 
int main()
{
    int niter = 10000000;
    double x,y;
    int i;
    int count=0;
    double z;
    double pi;
    int max_threads = omp_get_max_threads();
    double time = -omp_get_wtime();
    //srand(time(NULL));
    //main loop
    #pragma omp parallel private(x,y,z) reduction(+:count)
    {   
        unsigned int myseed = omp_get_thread_num();
        #pragma omp for
        for (int i=0; i<niter; ++i)
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
    pi = ((double)count/(double)niter)*4.0;          //p = 4(m/n)
    time += omp_get_wtime();
    std::cout << "Pi: " << pi << std::endl;
    std::cout << max_threads     << " threads" << std::endl;
    std::cout << "time : " << time << " seconds" << std::endl;
    return 0;
}
