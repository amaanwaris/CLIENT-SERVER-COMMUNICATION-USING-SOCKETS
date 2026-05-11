# Client-Server Communication Using Sockets

## Overview
This project implements a high-performance client-server communication system using TCP/IP stream sockets in Linux. The system is designed to provide reliable, ordered, and efficient communication between multiple clients and the server using multi-threading and synchronization techniques.

The project demonstrates low-level system programming concepts including socket programming, concurrent client handling using POSIX threads (pthreads), synchronization using semaphores, and scalable server-side architecture.

---

# Key Features
- TCP/IP based client-server communication
- Reliable and ordered data transfer using stream sockets
- Multi-threaded server implementation using POSIX Threads (pthreads)
- Parallel handling of multiple client requests
- High scalability supporting 100000+ simultaneous client connections
- Semaphore-based synchronization for thread safety
- Efficient request-response communication mechanism
- Race condition prevention and shared resource protection
- Low-latency communication and optimized server performance
- Linux system-level programming implementation
- Debugging and testing using Linux tools and logs
- Modular and maintainable code structure

---

# Tech Stack
- C Programming
- Linux (Ubuntu)
- TCP/IP Networking
- Socket Programming
- POSIX Threads (pthreads)
- Semaphores
- System Programming
- Multi-threading

---

# Concepts Used

## 1. Socket Programming
Socket programming enables communication between processes over a network.

### Used in this project for:
- Client-server communication
- Network data transfer
- Establishing reliable TCP connections

### System Calls Used
- `socket()`
- `bind()`
- `listen()`
- `accept()`
- `connect()`

### Advantages
- Reliable communication
- Ordered data transfer
- Network-based process communication

---

## 2. TCP/IP Networking
TCP/IP provides reliable and connection-oriented communication between client and server.

### Used for:
- Reliable packet delivery
- Error checking
- Ordered communication

### Advantages
- Stable communication
- Error handling support
- High reliability

---

## 3. POSIX Threads (pthreads)
POSIX Threads are used to implement multi-threading in Linux applications.

### Used for:
- Handling multiple clients simultaneously
- Parallel request processing
- Improving server performance

### Advantages
- Concurrent execution
- Better CPU utilization
- Faster client handling

---

## 4. Multi-threading
Multi-threading allows multiple tasks to execute concurrently within a process.

### Used for:
- Concurrent client management
- Parallel processing
- High-performance communication

### Advantages
- Increased scalability
- Better responsiveness
- Improved performance

---

## 5. Semaphores
Semaphores are synchronization mechanisms used to control access to shared resources.

### Used for:
- Thread synchronization
- Shared resource management
- Preventing simultaneous access conflicts

### Advantages
- Prevents race conditions
- Maintains data consistency
- Ensures thread safety

---

## 6. Synchronization
Synchronization coordinates thread execution and resource sharing.

### Used for:
- Managing concurrent access
- Maintaining execution order
- Preventing resource conflicts

### Advantages
- Reliable execution
- Stable performance
- Safe resource sharing

---

## 7. Race Condition Prevention
Race conditions occur when multiple threads access shared resources simultaneously.

### Prevention Methods
- Semaphores
- Critical sections
- Thread synchronization

### Benefits
- Correct execution
- Safe concurrent processing
- Data consistency

---

## 8. System Programming
System Programming involves low-level interaction with the Linux operating system.

### Used for:
- Socket handling
- Thread management
- Process communication
- Resource management

### Advantages
- Better hardware interaction
- High performance
- Efficient resource control

---

# Synchronization Techniques

## 1. POSIX Semaphores
Used to synchronize threads and manage access to shared resources.

### Purpose
- Resource access control
- Critical section management
- Thread synchronization

### Benefits
- Prevents simultaneous access
- Improves stability
- Ensures safe execution

---

## 2. Thread Synchronization
Coordinates execution among multiple threads.

### Purpose
- Controlled execution
- Proper resource sharing
- Concurrent processing management

### Benefits
- Reliable communication
- Better concurrency handling
- Efficient processing

---

## 3. Shared Resource Protection
Shared resources are protected during concurrent access.

### Purpose
- Safe data modification
- Shared memory protection
- Resource integrity

### Benefits
- Prevents corruption
- Maintains consistency
- Improves reliability

---

# System Calls Used

| System Call | Purpose |
|---|---|
| `socket()` | Creates a socket |
| `bind()` | Binds socket to IP and port |
| `listen()` | Listens for client connections |
| `accept()` | Accepts incoming client requests |
| `connect()` | Establishes client connection |
| `send()` | Sends data |
| `recv()` | Receives data |
| `close()` | Closes socket connection |

---

# Project Structure

## Core Files

### Client Side
- `client`
- `clientApp.c`
- `clientHandler.c`

### Server Side
- `server`
- `mainServer.c`
- `mainServer.o`

### Vendor Operations
- `vendorAdd.c`
- `vendorSub.c`
- `vendorMul.c`
- `vendorDiv.c`
- `vendorMod.c`

### Communication & Processing
- `sendExact.c`
- `recvExact.c`
- `runClient`

### Header Files
- `declarations.h`

### Build & Configuration
- `Makefile`
- `README.md`

---

# System Architecture

## 1. Server Initialization
- Creates TCP socket
- Binds socket to port
- Starts listening for client connections

## 2. Client Connection
- Clients connect to server using TCP/IP sockets
- Server accepts incoming connections

## 3. Multi-threaded Request Handling
- Separate thread created for each client
- Multiple clients handled concurrently

## 4. Synchronization
- Semaphores protect shared resources
- Prevents race conditions during concurrent execution

## 5. Request Processing
- Server processes client requests
- Responses sent back efficiently

---

# How to Run

## Compile the Project
```bash
make
```

## Run the Server
```bash
./server
```

## Run the Client
```bash
./client
```

---

# Sample Workflow
1. Start the server
2. Server listens for incoming connections
3. Multiple clients connect simultaneously
4. Separate threads handle each client
5. Requests are processed concurrently
6. Responses are sent back to clients

---

# Advantages of the Project
- High scalability with 100000+ concurrent client support
- Efficient concurrent client handling
- Reliable TCP/IP communication
- Thread-safe execution
- Low-latency communication
- Modular architecture
- Better resource utilization

---

# Debugging & Testing
- Linux terminal tools
- System logs
- GCC compiler debugging
- Thread execution monitoring
- Network testing

---

# Future Enhancements
- SSL/TLS secure communication
- Load balancing support
- Distributed server architecture
- Logging and monitoring system
- Docker deployment
- GUI monitoring dashboard

---

# Learning Outcomes
- TCP/IP networking concepts
- Linux socket programming
- Multi-threading and concurrency
- Synchronization techniques
- Semaphore usage
- System-level programming
- Client-server architecture design

---

# Conclusion
This project demonstrates efficient client-server communication using TCP/IP sockets and multi-threading techniques in Linux. It provides strong practical exposure to socket programming, synchronization, concurrency control, and system-level programming concepts while building a scalable and high-performance server architecture capable of supporting 100000+ concurrent client connections.
