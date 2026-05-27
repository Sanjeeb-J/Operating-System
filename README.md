# ⚡ Operating Systems in C ⚡

A comprehensive, hands-on learning repository implementing core **Operating System (OS)** concepts, algorithms, and mechanisms from scratch using the **C programming language**.

This project serves as a practical, low-level reference architecture for understanding processes, inter-process communication, thread concurrency, scheduling, synchronization, memory allocation, and storage management.

---

![Operating Systems Architecture Banner](assets/banner.png)

---

## 🗺️ Table of Contents
- [📖 Core Concepts Covered](#-core-concepts-covered)
- [📂 Repository Structure](#-repository-structure)
- [🛠️ Detailed Topic Breakdown](#️-detailed-topic-breakdown)
- [🚀 Getting Started](#-getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation & Execution](#compilation--execution)
- [📘 Algorithms & Pseudo-code](#-algorithms--pseudo-code)
- [🤝 Contributing](#-contributing)
- [📄 License](#-license)

---

## 📖 Core Concepts Covered

This repository implements the fundamental building blocks of modern operating systems, categorized into key architectural areas:

### 1. Process Management & IPC
- **Process Hierarchy**: Visualizing process trees and relationships using `fork()`, identifying parent (`PPID`) and child (`PID`) processes.
- **Inter-Process Communication (IPC)**:
  - **Pipes**: Unidirectional channels for byte stream communication.
  - **Message Queues**: Structured IPC using message boundaries (applied to a Distributed Palindrome Checker).
  - **Shared Memory**: Highly-efficient memory segments shared between isolated addresses (applied to String Concatenation & Case Flipping).

### 2. Thread Concurrency
- **Multi-Threading**: Concurrent operations using POSIX Threads (`pthreads`), demonstrating thread creation, joining, and resource distribution for statistical calculations.

### 3. CPU Scheduling Algorithms
- **First Come First Serve (FCFS)**: Non-preemptive scheduling based on arrival times.
- **Shortest Job First (SJF) & Shortest Remaining Time First (SRTF)**: Minimizing average waiting times preemptively and non-preemptively.
- **Priority Scheduling**: Allocating CPU resources based on process priority (both preemptive and non-preemptive variants).
- **Round Robin (RR)**: Time-sliced fair-share scheduling.

### 4. Process Synchronization & Deadlocks
- **Readers-Writers Problem**: Resolving race conditions and access control using semaphores and mutexes under reader-preference and writer-preference bounds.
- **Banker's Algorithm**: Resource allocation and safety-checking to proactively avoid deadlocks.
- **Deadlock Detection**: Determining deadlock existence using allocation/request/available resource matrices.

### 5. Memory Management (Page Replacement)
- **FIFO (First In First Out)**: Simple page-out queue tracking.
- **LRU (Least Recently Used)**: Evicting pages based on history of access.
- **Optimal Page Replacement**: Theoretical benchmark that replaces the page that will not be used for the longest period of time.

### 6. Disk Scheduling (I/O Management)
- **Shortest Seek Time First (SSTF)**: Selecting requests closest to the current head position.
- **LOOK & SCAN (Elevator Algorithms)**: Simulating elevator movements to sweep disk tracks.
- **C-SCAN & C-LOOK (Circular Variants)**: Providing a more uniform waiting time by resetting sweeps in one direction.

---

## 📂 Repository Structure

The codebase is organized modularly, with directories corresponding to specific topics and a dedicated `Algorithm/` folder housing step-by-step design papers:

```text
Operating System/
├── assets/
│   └── banner.png                                      # Repository visual banner
├── Algorithm/                                          # Detailed pseudocode & design steps
│   ├── 03 Process Creation using Fork().md
│   ├── 04 Sum of two numbers.md
│   └── ... (and all other algorithm walk-throughs)
├── 03 Process Creation using Fork()/
│   └── src.c                                           # Fork implementation
├── 04 Sum of two numbers/
│   ├── add.c
│   └── adder.c
├── 05 Parent-Child Process Communication/
│   └── exp5.c
├── 06 Inter-Process Communication using Pipe/
│   └── pipe.c
├── 07 Message Queue - Palindrome Checker/
│   └── msg_queue.c
├── 08 Shared Memory - String Concatenation and Case Flip/
│   └── shr_mem.c
├── 09 Multi-Threading - Statistical Calculations (Mean, Median, SD)/
│   └── mul_thrd.c
├── 10 FCFS (First Come First Serve) CPU Scheduling/
│   └── fcfs.c
├── 11 Shortest Remaining Time CPU Scheduling/
│   ├── sjf_non_pre.c                                   # SJF Non-Preemptive
│   └── srtf.c                                          # SRTF Preemptive
├── 12 Priority (Preemptive) CPU Scheduling/
│   ├── pre_priority.c                                  # Preemptive Priority
│   └── prior_non_pre.c                                 # Non-Preemptive Priority
├── 13 Round Robin (RR) CPU Scheduling/
│   └── rr.c
├── 14 Readers-Writers Problem/
│   ├── read_write_1_reader.c                           # Reader-Preference
│   └── read_write_2_writer.c                           # Writer-Preference
├── 15 Banker's Algorithm (Safety Check)/
│   └── bankers.c
├── 16 Deadlock Detection Algorithm/
│   └── deadlock.c
├── 17 FIFO (First In First Out) Page Replacement/
│   └── fifo.c
├── 18 LRU (Least Recently Used) Page Replacement/
│   └── lru.c
├── 19 Optimal Page Replacement/
│   └── optimal.c
├── 20 Shortest Seek Time First)/
│   ├── fcfs.c
│   ├── rand_sstf.c
│   └── sstf.c
├── 21 Elevator/
│   ├── look.c
│   └── scan.c
└── 22 Circular SCAN/
    ├── clook.c
    └── cscan.c
```

---

## 🛠️ Detailed Topic Breakdown

| ID | Module Name | Source Files | Description |
| :--- | :--- | :--- | :--- |
| **03** | **Process Forking** | [`src.c`](./03%20Process%20Creation%20using%20Fork()/src.c) | Explores parent/child process spawning using `fork()`, `getpid()`, and `getppid()`. |
| **04** | **Sum of Two Numbers** | [`add.c`](./04%20Sum%20of%20two%20numbers/add.c), [`adder.c`](./04%20Sum%20of%20two%20numbers/adder.c) | Basic binary execution & custom input handling. |
| **05** | **Parent-Child Comm** | [`exp5.c`](./05%20Parent-Child%20Process%20Communication/exp5.c) | Basic variable sharing and exit-status tracking between parent/child. |
| **06** | **IPC Pipes** | [`pipe.c`](./06%20Inter-Process%20Communication%20using%20Pipe/pipe.c) | Implements unidirectional data passing using system `pipe()`. |
| **07** | **Message Queues** | [`msg_queue.c`](./07%20Message%20Queue%20-%20Palindrome%20Checker/msg_queue.c) | Implements client-server IPC using POSIX Message Queues for palindrome checking. |
| **08** | **Shared Memory** | [`shr_mem.c`](./08%20Shared%20Memory%20-%20String%20Concatenation%20and%20Case%20Flip/shr_mem.c) | Shares a memory segment between processes to concatenate and change text cases. |
| **09** | **Pthreads Stats** | [`mul_thrd.c`](./09%20Multi-Threading%20-%20Statistical%20Calculations%20(Mean,%20Median,%20SD)/mul_thrd.c) | Computes Mean, Median, and Standard Deviation concurrently using POSIX Threads. |
| **10** | **FCFS CPU Scheduling** | [`fcfs.c`](./10%20FCFS%20(First%20Come%20First%20Serve)%20CPU%20Scheduling/fcfs.c) | Simulates First-Come-First-Serve scheduling, computing waiting/turnaround times. |
| **11** | **SRTF / SJF Scheduling** | [`sjf_non_pre.c`](./11%20Shortest%20Remaining%20Time%20CPU%20Scheduling/sjf_non_pre.c), [`srtf.c`](./11%20Shortest%20Remaining%20Time%20CPU%20Scheduling/srtf.c) | Implements SJF (Non-preemptive) and SRTF (Preemptive Shortest Remaining Time). |
| **12** | **Priority CPU Scheduling** | [`pre_priority.c`](./12%20Priority%20(Preemptive)%20CPU%20Scheduling/pre_priority.c), [`prior_non_pre.c`](./12%20Priority%20(Preemptive)%20CPU%20Scheduling/prior_non_pre.c) | Priority-driven task scheduling, comparing preemptive vs. non-preemptive logic. |
| **13** | **Round Robin Scheduling** | [`rr.c`](./13%20Round%20Robin%20(RR)%20CPU%20Scheduling/rr.c) | Time-quantized CPU scheduling supporting dynamic arrival times and context switches. |
| **14** | **Readers-Writers Problem** | [`read_write_1_reader.c`](./14%20Readers-Writers%20Problem/read_write_1_reader.c), [`read_write_2_writer.c`](./14%20Readers-Writers%20Problem/read_write_2_writer.c) | Mutual exclusion using Semaphores (`sem_t`) solving reader/writer starvation limits. |
| **15** | **Banker's Algorithm** | [`bankers.c`](./15%20Banker's%20Algorithm%20(Safety%20Check)/bankers.c) | Simulates resource requests to determine if the state remains safe from deadlock. |
| **16** | **Deadlock Detection** | [`deadlock.c`](./16%20Deadlock%20Detection%20Algorithm/deadlock.c) | Periodically scans resource state matrices to identify deadlocked processes. |
| **17** | **FIFO Page Replacement** | [`fifo.c`](./17%20FIFO%20(First%20In%20First%20Out)%20Page%20Replacement/fifo.c) | Simulates page frame tracking and counts page faults using FIFO queue. |
| **18** | **LRU Page Replacement** | [`lru.c`](./18%20LRU%20(Least%20Recently%20Used)%20Page%20Replacement/lru.c) | Evicts pages by checking historical access timestamps/counters. |
| **19** | **Optimal Page Replacement** | [`optimal.c`](./19%20Optimal%20Page%20Replacement/optimal.c) | Evicts pages by scanning future reference strings (ideal benchmark). |
| **20** | **SSTF Disk Scheduling** | [`fcfs.c`](./20%20Shortest%20Seek%20Time%20First)/fcfs.c), [`sstf.c`](./20%20Shortest%20Seek%20Time%20First)/sstf.c) | Disk seek optimization focusing on minimizing drive arm distance movement. |
| **21** | **Elevator (LOOK/SCAN)** | [`look.c`](./21%20Elevator/look.c), [`scan.c`](./21%20Elevator/scan.c) | Sweeps track requests backwards and forwards across the disk drive tracks. |
| **22** | **Circular Disk Scheduling** | [`clook.c`](./22%20Circular%20SCAN/clook.c), [`cscan.c`](./22%20Circular%20SCAN/cscan.c) | Circles back directly to one side of the disk to minimize waiting dispersion. |

---

## 🚀 Getting Started

### Prerequisites

Many of the scripts utilize POSIX system libraries (`unistd.h`, `sys/ipc.h`, `sys/shm.h`, `sys/msg.h`, `pthread.h`, `semaphore.h`). Because of this, it is recommended to compile and run these on a UNIX-like environment:
- **Linux** (Debian, Ubuntu, Fedora, etc.)
- **macOS**
- **WSL (Windows Subsystem for Linux)**
- **MinGW / Cygwin** (for some process/math libraries, though pure POSIX APIs like message queues may require full Linux environment/WSL)

Make sure you have `gcc` (GNU Compiler Collection) installed:
```bash
# Verify installation
gcc --version
```

### Compilation & Execution

To compile and run any individual program, navigate to its directory or use the paths directly:

#### Example 1: Multi-Threading Statistical Calculations (Pthreads)
```bash
# Compile with the POSIX threads link flag (-pthread)
gcc "09 Multi-Threading - Statistical Calculations (Mean, Median, SD)/mul_thrd.c" -o mul_thrd -pthread

# Execute the binary
./mul_thrd
```

#### Example 2: Banker's Algorithm (Safety Check)
```bash
# Compile safety checker
gcc "15 Banker's Algorithm (Safety Check)/bankers.c" -o bankers

# Run the program
./bankers
```

#### Example 3: Shared Memory Case Flipping (IPC)
```bash
# Compile shared memory demonstration
gcc "08 Shared Memory - String Concatenation and Case Flip/shr_mem.c" -o shr_mem

# Run program
./shr_mem
```

---

## 📘 Algorithms & Pseudo-code

For detailed step-by-step algorithms, calculations, design patterns, and analysis, please refer to the corresponding markdown files located in the [**`Algorithm/`**](./Algorithm/) folder. 

For instance, you can learn about the logical structures for page replacement, disk sweeps, and thread locks:
- Read [FIFO Page Replacement Algorithm](./Algorithm/17%20FIFO%20(First%20In%20First%20Out)%20Page%20Replacement.md)
- Read [Round Robin CPU Scheduling Algorithm](./Algorithm/13%20Round%20Robin%20(RR)%20CPU%20Scheduling.md)
- Read [Readers-Writers Synchronization Algorithm](./Algorithm/14%20Readers-Writers%20Problem%20(Reader-Preference%20Solution).md)

---

## 🤝 Contributing

Contributions, bug fixes, or optimizations to the scheduling models or synchronization algorithms are welcome! Feel free to:
1. Fork the Repository.
2. Create a feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a Pull Request.

---

## 📄 License

This repository is licensed under the [MIT License](https://opensource.org/licenses/MIT). You are free to use, modify, and distribute this codebase for educational and learning purposes.
