# Portfolio Project Part One

## Overview
This is a C++ multithreading application that demonstrates thread synchronization using mutexes. The program spawns two threads that perform counting operations (up and down) and writes the results to a file.

## Project Details
- **Course**: CSC 450
- **School**: Colorado State University (CSU)
- **Language**: C++

## Features
- **Multithreading**: Uses two separate threads to perform concurrent operations
- **Thread Synchronization**: Implements mutex locks to ensure mutually exclusive access to shared resources
- **Dynamic Memory Management**: Allocates memory on the heap for storing results
- **File I/O**: Writes counting results to an output file
- **Exception Handling**: Comprehensive try-catch blocks for error handling

## How It Works

### Main Components

1. **count_up()**: Thread function that counts from 0 to 20 and stores values in an array
   - Uses `std::lock_guard` for mutual exclusion
   - Displays count progression to console

2. **count_down()**: Thread function that counts from 20 to 0 and stores values in an array
   - Uses `std::lock_guard` for mutual exclusion
   - Displays count progression to console

3. **File Operations**:
   - `open_file()`: Opens or creates a file for appending results
   - `write_file()`: Writes the counting results to the file
   - `close_file()`: Properly closes the file stream

### Program Flow
1. Allocates dynamic memory for two integer arrays (21 elements each)
2. Creates two threads: one for counting up, one for counting down
3. Uses mutex locks to ensure threads don't interfere with each other
4. Waits for both threads to complete (join)
5. Opens output file and writes results
6. Frees allocated memory

## Output
The program generates a file named `results.txt` containing:
- Two sections labeled with IDs (1 for up count, 2 for down count)
- Corresponding counting sequences

## Thread Safety
The implementation uses `std::mutex` and `std::lock_guard` to ensure thread-safe access to shared resources, preventing race conditions when multiple threads access the same data.

## Error Handling
The program includes exception handling for:
- Memory allocation failures
- File operations (open, write, close)
- Thread operations

## Compilation
```bash
g++ -std=c++11 -pthread PortfolioProjectPartOne.cpp -o portfolio
```

## Execution
```bash
./portfolio
```

## Notes
- Results are appended to `results.txt`, preserving previous execution results
- The program uses `std::nothrow` for safe memory allocation
- Mutex is preferred over atomic operations for stricter ordering guarantees
