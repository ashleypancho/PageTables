# PageTables

## To Run:
Compile in the command line with the following command:
`g++ program5.cpp PageTables.cpp -std=c++14`

To run the program with the included input files, type in either of the following:
`./a.out VSWSsystemTrace.txt`
or
`./a.out VSWSsystemTrace2.txt`

## What does this do?
This program will run through an input file of format to simulate the variable-interval sampled working set policy.
The VSWS is designed to minimize thrashing by dynamically adjust the resident set of pages for each process in such a way to maximize the chances of a processes’ working set to be included within its resident set.

### Input File Format:
process ID, operation, page/size.

The process ID states which processes is being used.
The operation will either be n (new process), r (read), w (write), or t (terminate).

Example:
            3          n          22
            3          r           1
            3          w          10
            3          w          10
            3          t          -1
1. Create a new process, process 3, that is 22 virtual pages in length.  That means a page table with 22 entries must be created for process 3.
2. Process 3 wants to read from virtual page 1.  Page 1 needs to be assigned to an available page frame (page fault).  Set use bit for page 1 to 1.
3. Process 3 wants to write to virtual page 10.  Page 10 needs to be assigned to an available page frame (page fault). Set use bit for page 10 to 1.
4. Process 3 wants to write again to virtual page 10.  Page 10 should already occupy a frame. Set use bit for page 10 to 1.
5. Process 3 wants to terminate.  All page frames assigned to process 3 will be released.
