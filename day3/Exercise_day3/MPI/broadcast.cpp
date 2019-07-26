#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank=0;
    double data=0.;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank==0) {
        data = 0.8;
    }

    /* broadcast the value of data of rank 0 to all ranks */
    MPI_Bcast(&data, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    std::cout << "I am rank " << rank << " and the value is " << data << std::endl;
    MPI_Finalize();
    return 0;
}
