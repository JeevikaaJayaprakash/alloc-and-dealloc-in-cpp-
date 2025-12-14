# OPERATING SYSTEM PRINCIPLES - PROJECT 2
The program has 2 files - firstfit.cpp and besstfit.cpp which implements first fit and best fit memory allocation strategies respectively.

## Task 1 - Solution Design 
- Implemented global tracking of memory allocations and free chunks using two linked lists - `allocatedList` and `freeList`.
- Defined a struct `Allocation` to encapsulate chunk metadata (size and pointer).
- global variables are only accessed within `alloc()` and `dealloc()`.

## Task 2 - Memory Allocation 
- iplemented `alloc(size_t chunk_size)` to allocate memory in fixed partition sizes (32, 64, 128, 256, 512 bytes).
- used `sbrk()` system call to grow heap when no suitable free chunk is found.

## Task 3 - Allocation Strategies
- Implemented First-Fit strategy: returns the first chunk large enough to satisfy the request.
- Implemented Best-Fit strategy: returns the smallest chunk that fits the request to minimize internal fragmentation.
- Strategy selection is based on terminal commands (`firstfit` or `bestfit`).

## Task 4 - Memory Deallocation
- Implemented `dealloc(void* chunk)` to remove the chunk from the allocated list and append it to the free list.
- Validates pointer existence in allocated list; terminates if no memory is available to be deallocated.

## Makefile, Arguments, and Output
- Created a Makefile with `make all` and `make clean` commands.
- Program accepts `firstfit datafile` or `bestfit datafile` on termianl
- Final output includes:
  - Allocated list: address, total size, used size
  - Free list: address, total size

## Compilation and Execution


1. Connect to server via SSH:
   ssh username@jupiter.csit.rmit.edu.au

2. Navigate to project directory:
   cd ~/project_directory_name

3. Compile the programs:
   make all

4. Generate a test data file : #(optional)
   1)chmod +x p2_gen.sh
   2)./p2_gen.sh 20 > datafile

5. Run the code with the required strategy:
   ./firstfit datafile      # For First-Fit strategy
   ./bestfit datafile       # For Best-Fit strategy
