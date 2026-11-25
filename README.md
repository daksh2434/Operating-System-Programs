# Operating System Programs

A collection of C++ programs implementing core Operating System concepts: process management, CPU scheduling, synchronization, memory management, disk scheduling, file allocation, and deadlock handling.

## Contents

### Process Management and System Calls
| File | Description |
|------|-------------|
| `ProcessCreation.cpp` | Creating processes using `fork()`, `exec` and `wait()` |
| `Linux_sytem_calls.cpp` | Demonstration of common Linux system calls |
| `Thread_Creation.cpp` | Creating and joining threads using POSIX threads (`pthread`) |

### CPU Scheduling
| File | Description |
|------|-------------|
| `fcfs.cpp` | First Come First Served scheduling |
| `SJF.cpp` | Shortest Job First scheduling |
| `CPU Scheduling.cpp` | Additional CPU scheduling algorithms |

### Process Synchronization
| File | Description |
|------|-------------|
| `Producer_Consumer.cpp` | Producer-Consumer problem |
| `Dining_Philosopher.cpp` | Dining Philosophers problem |

### Deadlock
| File | Description |
|------|-------------|
| `Banker's_algo.cpp` | Banker's algorithm for deadlock avoidance |

### Memory Management
| File | Description |
|------|-------------|
| `Cont_Memory_Alloc.cpp` | Contiguous memory allocation strategies |
| `Page_Replacement.cpp` | Page replacement algorithms |

### Disk and File Management
| File | Description |
|------|-------------|
| `Disk_Scheduling.cpp` | Disk scheduling algorithms |
| `File_Allocation.cpp` | File allocation methods |

## Requirements

- Linux (or WSL on Windows), since several programs use POSIX system calls
- `g++` compiler

Install the compiler on Ubuntu/Debian:

```bash
sudo apt update
sudo apt install g++
```

## How to Compile and Run

Clone the repository:

```bash
git clone https://github.com/daksh2434/Operating-System-Programs.git
cd Operating-System-Programs
```

Compile and run any program:

```bash
g++ fcfs.cpp -o fcfs
./fcfs
```

Programs that use threads or synchronization need the `-pthread` flag:

```bash
g++ Thread_Creation.cpp -o Thread_Creation -pthread
./Thread_Creation
```

```bash
g++ Producer_Consumer.cpp -o Producer_Consumer -pthread
./Producer_Consumer
```

```bash
g++ Dining_Philosopher.cpp -o Dining_Philosopher -pthread
./Dining_Philosopher
```

Files with spaces or special characters in the name need quotes:

```bash
g++ "CPU Scheduling.cpp" -o cpu_scheduling
./cpu_scheduling
```

```bash
g++ "Banker's_algo.cpp" -o bankers_algo
./bankers_algo
```

## Topics Covered

- Process creation and termination
- Threads and multithreading
- CPU scheduling algorithms
- Process synchronization
- Deadlock avoidance
- Contiguous memory allocation
- Page replacement
- Disk scheduling
- File allocation methods
- Linux system calls

## Author

**Daksh** ([@daksh2434](https://github.com/daksh2434))
