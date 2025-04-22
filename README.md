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


Program your own Quantum Computer Part 1

My primary objective for this portion of the assignment was to use `numpy` to simulate a simple quantum computer from scratch, without the need of quantum libraries like Qiskit.  The tutorials approach to viewing a quantum computer as a stack machine made it much easier for me to understand what goes on inside as qubits are moved, adjusted, and measured.The dimensionality (and complexity) of the state space doubles with each qubit, which is why the author compares the quantum state to a high-dimensional Rubik's Cube.
In this state, each cube contains an amplitude, which is a real or complex weight.The state vector is a superposition of all conceivable bit combinations made up of these amplitudes. A state vector with three qubits, for instance, would include eight complex numbers (2³ = 8), each of which would indicate a probability amplitude for states such as |000⟩, |001⟩, … |111⟩.Thinking of the quantum state as a stack where pushing a qubit changes the entire memory helped me visualize what was happening.

I proceeded to the next step, which was to execute gate operations, after constructing the basic framework to push qubits onto the stack.  As reversible changes to the quantum state, these gates are the essential components of quantum computation.  The system felt alive at this point since I was actively changing quantum information rather than merely stacking bits.You flip a bit in classical computing.  A vector in complex space is rotated in quantum computing.  This function applies the gate using matrix multiplication after reshaping the workspace so that the final dimension matches the gate's size.The X-gate flips the state |0⟩ ↔ |1⟩, just like a classical NOT gate. The input state [1, 0] represents |0⟩, and the output [0, 1] represents |1⟩. It did exactly what I expected.

Measuring a qubit in quantum physics results in the collapse of its superposition.  This implies that we only obtain one clear conclusion, either 0 or 1, rather than several options. Based on the weights (α) in the quantum state (shown as little cubes in the workspace), each qubit has a probability of being either 0 or 1.
Knowing the odds of 0 and 1 allows us to:

Using those probabilities, a value is chosen at random from 0 to 1.
Any components of the workspace that don't contribute to the final result are thrown away.
To make the probabilities add up to one once more, the remaining portion is normalised.

