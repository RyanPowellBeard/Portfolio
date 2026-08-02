# Concurrency Concepts

## Overview
This project demonstrates Java concurrency concepts using multithreading. The `ConcurrencyConcepts` class serves as the main entry point that manages concurrent thread execution.

## Project Structure
- **ConcurrencyConcepts.java**: Main driver class that orchestrates thread execution
- **ConcurrencyThreads.java**: Thread implementation class (referenced in the main code)

## Key Features

### Thread Management
- Creates and starts custom `ConcurrencyThreads` objects
- Uses thread joining to synchronize execution and wait for worker threads to complete

### Error Handling
The program implements comprehensive exception handling for:
- **IllegalAccessError**: Caught when attempting to invoke inaccessible methods
- **InterruptedException**: Caught when thread joining is interrupted
- **General Exceptions**: Catches any unexpected errors during execution

### Core Operations
1. Instantiates a `ConcurrencyThreads` object
2. Starts the thread with the `start()` method
3. Joins threads to pause the main thread until all worker threads finish
4. Writes thread execution results to a file via `write_threads()` method

## Usage
```bash
javac ConcurrencyConcepts.java
java ConcurrencyConcepts
```

## Notes
- Thread execution follows the producer-consumer or task distribution pattern
- Results from thread operations are persisted to a file
- The program ensures proper synchronization using thread joins before writing output
