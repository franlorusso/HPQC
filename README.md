Activity for Topic 2: Performance and Parallelism.

Execution time was monitored as input size increased using inefficient repeat-adder programs written in Python and C. As could be expected given that Python is an interpreted language, it performed these operations far more slowly than C.

Using import time in Python and <time.h> in C, I compared code blocks with internal timers. This helped analyze performance of print-heavy operations vs file I/O.


Activity for Topic 2 : Introduction to MPI

In order to facilitate parallel computing in C programs, we introduced the Message Passing Interface (MPI) in this topic. The main exercises are intended to show off MPI's ability to carry out tasks across several processes.
Created a parallel program hello_mpi.c based on the example in the lecture notes.As the number of processes increased, the user time + sys time became greater than real time.
This indicates true parallel execution: multiple processes running simultaneously, each on a separate core.

Used vector_serial.c as the base for a vector addition program.Modified it to operate on non-trivial data:
Filled the vector with increasing integers or randomized numbers.
Compiled and tested serial version:

Developed vector_parallel.c:
Vector divided among all processes.
Each process computes sum of its portion.
Partial sums are gathered and summed by root.


Topic 4 : MPI communications

Implemented pingpong.c:
Two processes (rank 0 and rank 1) exchanged a counter variable back and forth.
Used MPI_Send() and MPI_Recv(), incremented counter on each pass.
Recorded time using MPI_Wtime() before and after loop.
Varying ping counts: 10, 100, 1,000, 10,000.

Created pingpong_bw.c, which transmits a buffer of size 8B to 2MiB back and forth.
Used malloc() to create dynamic buffers.
Measured total time for N round trips, calculated bandwidth.

Overall, MPI_Scatter() is the fastest (no needless duplication).
For chunk-wise processing, MPI_Bcast() performs better than manual but less well than Scatter.
The prediction was true: Scatter distributes chunked data more effectively.

Final Analysis:
Discovered differences and internal behaviour of different MPI send kinds.
Developed knowledge of the experimental measurement of latency and bandwidth.
discovered that large-scale repetitions are necessary to stabilise findings while timing noise in MPI.
Found that group communication practices are more efficient and manageable than send/receive loops.
