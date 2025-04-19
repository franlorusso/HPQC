#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define VECTOR_SIZE 8

int main(int argc, char **argv) 
{
    int rank, size, i;
    int local_sum = 0, total_sum = 0;
    int vector[VECTOR_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunk_size = VECTOR_SIZE / size;

    if (rank == 0) {
        printf("Original vector: ");
        for (i = 0; i < VECTOR_SIZE; i++) {
            vector[i] = i + 1;
            printf("%d ", vector[i]);
        }
        printf("\n");
    }

    // Broadcast full vector to all processes
    MPI_Bcast(vector, VECTOR_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process computes partial sum from their assigned section
    int start = rank * chunk_size;
    int end = start + chunk_size;
    for (i = start; i < end; i++) {
        local_sum += vector[i];
    }

    // Collect results to rank 0
    if (rank != 0) {
    MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
} else {
    total_sum = local_sum;
    int temp;
    for (int i = 1; i < size; i++) {
        MPI_Recv(&temp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        total_sum += temp;
    }
}


    if (rank == 0) {
        printf("Total sum: %d\n", total_sum);
    }

    MPI_Finalize();
    return 0;
}

