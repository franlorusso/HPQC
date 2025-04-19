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
    int *sums = NULL;
if (rank == 0) {
    sums = malloc(size * sizeof(int));
}

MPI_Gather(&local_sum, 1, MPI_INT, sums, 1, MPI_INT, 0, MPI_COMM_WORLD);

if (rank == 0) {
    total_sum = 0;
    for (int i = 0; i < size; i++) {
        total_sum += sums[i];
    }
    free(sums);
}


    if (rank == 0) {
        printf("Total sum: %d\n", total_sum);
    }

    MPI_Finalize();
    return 0;
}

