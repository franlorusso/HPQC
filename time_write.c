#include <stdio.h>
#include <time.h>

int main() {
    FILE *fptr;
    fptr = fopen("data/time_output.txt", "w"); // Open file for writing

    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    clock_t start_time, end_time;
    start_time = clock();  // Start time

    // Simulate a loop doing computations
    long total = 0;
    for (long i = 0; i < 1000000; i++) {
        total += i;
    }

    end_time = clock();  // End time
    double run_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Write execution time to file
    fprintf(fptr, "Time taken: %f seconds\n", run_time);
    fclose(fptr);

    printf("Execution time written to file!\n");
    return 0;
}
