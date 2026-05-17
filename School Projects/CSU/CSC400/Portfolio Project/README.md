# Customer Order Management System

A Java-based order management application for CSC400 Portfolio Project that demonstrates data structures, sorting algorithms, and object-oriented programming concepts.

## Project Overview

This is a command-line order management system that allows users to add, manage, and organize customer orders. The system utilizes queues for order storage and implements the QuickSort algorithm to organize orders by order number or customer last name.

## Features

- **Add Orders**: Input customer orders with last name, order number, and cost
- **Remove Orders**: Remove orders from the queue (FIFO - First In First Out)
- **Sort Orders**: Sort and display orders by either order number or last name in descending order
- **Queue Management**: Clear all orders from the system and check queue status
- **User-Friendly Menu**: Interactive command-line interface for navigation

## Project Structure

### Core Classes

#### [CustomerOrder.java](CustomerOrder.java)
Represents individual customer order objects with the following attributes:
- `lastName`: Customer's last name (String)
- `orderNumber`: Unique order identifier (int)
- `orderCost`: Cost of the order (double)

**Key Methods:**
- Getters and setters for all attributes
- `assignLastName()`: Input validation for customer last name
- `assignOrderNumber()`: Auto-generates unique order numbers
- `assignCost()`: Input validation for order cost with proper formatting
- `toString()`: Formats order display with 2-decimal precision for currency

#### [Order.java](Order.java)
Manages the order queue and queue operations:
- Static `Queue<CustomerOrder>` to store orders
- `addOrders()`: Creates and adds new order to queue
- `removeItem()`: Removes first order from queue
- `getOrder()`: Polls and removes order from queue
- `addToArray()`: Peeks at next order without removing
- `checkOrderQueue()`: Checks if queue is empty
- `clearQueue()`: Empties all orders from queue

#### [Display.java](Display.java)
Handles sorting and display of orders:
- `arrayID`: ArrayList for orders sorted by order number
- `arrayNames`: ArrayList for orders sorted by last name
- `updateOrder()`: Copies orders from queue to ArrayLists and triggers sorting
- `addOrder()`: Transfers all remaining orders from queue to lists
- `sortID()`: Sorts orders by ID number in descending order
- `sortName()`: Sorts orders by last name in descending order
- `displayOrders()`: Outputs both sorted lists to console

#### [QuickSort.java](QuickSort.java)
Implements QuickSort algorithm with two sorting strategies:

**Sort by Last Name:**
- `partitionName()`: Partitions array using customer last name as pivot
- `sortName()`: Recursively sorts orders by last name in descending order

**Sort by Order Number:**
- `partitionID()`: Partitions array using order number as pivot
- `sortID()`: Recursively sorts orders by order number in descending order

#### [Main.java](Main.java)
Entry point for the application with interactive menu system:
- **A/a**: Add new orders
- **R/r**: Remove first entered order
- **C/c**: Copy queue to arrays and sort
- **D/d**: Display sorted orders
- **Z/z**: Clear all orders
- **E/e**: Exit application

## Data Structures Used

- **Queue**: LinkedList-based queue for managing orders in FIFO order
- **ArrayList**: Used for storing and sorting orders
- **QuickSort**: Efficient sorting algorithm for order organization

## How to Compile and Run

### Compilation
```bash
javac *.java
```

### Execution
```bash
java Main
```

## Usage Example

1. Launch the application
2. Select "A" to add orders
3. Enter customer last name, and order cost
4. Continue adding more orders
5. Select "C" to copy orders to arrays and sort
6. Select "D" to display orders sorted by ID and last name
7. Select "E" to exit

## Algorithm Details

### QuickSort Implementation
- **Time Complexity**: O(n log n) average case, O(n²) worst case
- **Space Complexity**: O(log n) due to recursion
- **Order**: Descending order for both ID and name sorting
- **Pivot Selection**: Last element of partition is used as pivot

## Key Features

- **Input Validation**: Error handling for invalid customer name and cost entries
- **Auto-Incrementing Order Numbers**: Order IDs are automatically assigned
- **Currency Formatting**: Order costs displayed with 2-decimal precision
- **Queue Integration**: Orders processed in FIFO manner
- **Dual Sorting**: View orders sorted by ID or customer name

## Exception Handling

The application includes try-catch blocks to handle:
- Invalid input formats
- Empty queue operations
- General runtime exceptions

## Educational Purpose

This project demonstrates:
- Object-Oriented Programming (OOP) principles
- Use of Java Collections Framework (Queue, ArrayList)
- Sorting algorithms (QuickSort)
- Input validation and error handling
- Menu-driven application design
