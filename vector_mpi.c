#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define VECTOR_SIZE 8  // Defining the size of the vector

int main(int argc, char **argv) 
{
    int rank, size, i;
    int local_sum = 0, total_sum = 0;
    int vector[VECTOR_SIZE];

    MPI_Init(&argc, &argv);  // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get number of processes

    int chunk_size = VECTOR_SIZE / size;  // Divide work among processes
    int local_vector[chunk_size];  // Each process gets part of the vector

    if (rank == 0) 
    {
        // Root process initializes the vector
        printf("Original vector: ");
        for (i = 0; i < VECTOR_SIZE; i++) 
        {
            vector[i] = i + 1;  // Example: {1, 2, 3, ..., 8}
            printf("%d ", vector[i]);
        }
        printf("\n");
    }

    // Distribute vector to all processes
    MPI_Scatter(vector, chunk_size, MPI_INT, local_vector, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process computes partial sum
    for (i = 0; i < chunk_size; i++) 
    {
        local_sum += local_vector[i];
    }

    // Root process gathers and sums results
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) 
    {
        printf("Total sum: %d\n", total_sum);
    }

    MPI_Finalize();  // Finalize MPI
    return 0;
}
