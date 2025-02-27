#include <stdio.h>

int main() {
    FILE *fptr;
    char buffer[100];

    fptr = fopen("data/time_output.txt", "r"); // Open file for reading

    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Read the file and print its contents
    while (fgets(buffer, 100, fptr)) {
        printf("%s", buffer);
    }

    fclose(fptr);
    return 0;
}
