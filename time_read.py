def main():
    input_file = "data/time_output.txt"

    # Read from the file
    with open(input_file, "r") as f:
        contents = f.read()
        print("File Contents:\n", contents)

if __name__ == "__main__":
    main()
