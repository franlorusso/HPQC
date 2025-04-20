Activity for Topic 2: Performance and Parallelism.

Execution time was monitored as input size increased using inefficient repeat-adder programs written in Python and C. As could be expected given that Python is an interpreted language, it performed these operations far more slowly than C.

Using import time in Python and <time.h> in C, I compared code blocks with internal timers. This helped analyze performance of print-heavy operations vs file I/O.
