import time

def main():
    N = 10000  # Modify as needed
    output_file = "data/time_output.txt"

    start_time = time.time()

    # Simulate a loop doing computations
    total = sum(range(N))

    end_time = time.time()
    run_time = end_time - start_time

    # Write to a file
    with open(output_file, "w") as f:
        f.write(f"Time taken for N={N}: {run_time:.6f} seconds\n")

if __name__ == "__main__":
    main()
