#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int ierror = 0, my_rank, uni_size, counter = 0;
    double start_time, end_time, elapsed_time, avg_time;

    // Initialize MPI
    ierror = MPI_Init(&argc, &argv);
    if (ierror != MPI_SUCCESS) {
        printf("MPI_Init failed\n");
        MPI_Abort(MPI_COMM_WORLD, ierror);
    }

    ierror = MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    ierror = MPI_Comm_size(MPI_COMM_WORLD, &uni_size);

    // Check if we have exactly 2 processes
    if (uni_size != 2) {
        if (my_rank == 0) {
            printf("This program requires exactly 2 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    // Check arguments for the array size
    if (argc != 3) {
        if (my_rank == 0) {
            printf("Usage: mpirun -np 2 ./pingpong <num_pings> <array_size_in_bytes>\n");
        }
        MPI_Finalize();
        return 1;
    }

    int num_pings = atoi(argv[1]);  // Number of ping-pong cycles
    int array_size = atoi(argv[2]); // Size of the array in bytes

    if (num_pings <= 0 || array_size <= 0) {
        if (my_rank == 0) {
            printf("Both num_pings and array_size must be greater than 0.\n");
        }
        MPI_Finalize();
        return 1;
    }

    // Calculate the number of elements in the array
    int num_elements = array_size / sizeof(int);

    // Dynamically allocate memory for the array
    int *data = (int *)malloc(array_size);
    if (data == NULL) {
        if (my_rank == 0) {
            printf("Memory allocation failed.\n");
        }
        MPI_Finalize();
        return 1;
    }

    // Set up the initial value of the counter (first element of the array)
    data[0] = counter;

    // Start the timer
    if (my_rank == 0) {
        start_time = MPI_Wtime();  // Start time for ping-pong cycles
    }

    for (int i = 0; i < num_pings; i++) {
        // Root sends ping (counter value in first element)
        if (my_rank == 0) {
            MPI_Send(data, num_elements, MPI_INT, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(data, num_elements, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        // Client receives and increments counter, then sends pong back
        else if (my_rank == 1) {
            MPI_Recv(data, num_elements, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            data[0]++; // Increment the counter
            MPI_Send(data, num_elements, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    // Stop the timer and calculate the elapsed time
    if (my_rank == 0) {
        end_time = MPI_Wtime();  // End time for ping-pong cycles
        elapsed_time = end_time - start_time;
        avg_time = elapsed_time / num_pings;

        printf("Root process completed %d pings with array size %d bytes.\n", num_pings, array_size);
        printf("Total time: %f seconds, Average time per ping-pong: %f seconds\n", elapsed_time, avg_time);
        
        // Calculate and print the bandwidth (in MB/s)
        double bandwidth = (array_size * num_pings) / elapsed_time / (1024 * 1024);  // In MB/s
        printf("Measured bandwidth: %f MB/s\n", bandwidth);
    }

    // Clean up
    free(data);
    MPI_Finalize();
    return 0;
}

