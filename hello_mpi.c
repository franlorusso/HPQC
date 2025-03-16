#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int myRank, uniSize, ierror;

    // Initialize MPI
    ierror = MPI_Init(&argc, &argv);

    // Get the rank of the process
    ierror = MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    // Get the number of processes
    ierror = MPI_Comm_size(MPI_COMM_WORLD, &uniSize);

    // Print message from each process
    printf("Hello, I am %d of %d\n", myRank, uniSize);

    // Finalize MPI
    ierror = MPI_Finalize();

    return 0;
}
