# Pintos-Projects

## Overview

This repository contains the implementation of two significant projects for the Pintos operating system: **Project 1 - Threads** and **Project 2 - User Programs**. Both projects aim to deepen our understanding of operating systems' concepts such as threading, synchronization, scheduling, and system calls.

## Importance of the Projects

### Real-World Application

These projects simulate essential components of an operating system, providing hands-on experience with thread management, process scheduling, and system call handling. This experience is crucial for understanding how modern operating systems work and prepares us for tackling similar challenges in real-world systems.

### Concepts Learned

1. **Thread Management**: Understanding how threads are created, managed, and synchronized.
2. **Scheduling**: Implementing various scheduling algorithms to ensure fair and efficient CPU utilization.
3. **Synchronization**: Using locks, semaphores, and condition variables to manage access to shared resources.
4. **System Calls**: Handling user program interactions with the kernel through system calls.

### Usage and Outcomes

-   **Project 1**: Enhanced the thread scheduler to support priority scheduling and implemented an alarm clock that puts threads to sleep and wakes them up after a specified time.
-   **Project 2**: Implemented argument passing to user programs, handled system calls, and ensured safe memory access from user programs.

---

## Project 1 - Threads

### Alarm Clock

#### Highlights

-   **Data Structures**:

    -   `int64_t wakeup_after`: Stores the ticks the thread should sleep.
    -   `struct list_elem sleepelem`: List element for sleeping threads.
    -   `void set_thread_sleeping_time(int64_t ticks)`: Sets the thread's sleeping time.

-   **Algorithms**:

    -   `timer_sleep()`: Puts the current thread to sleep without busy waiting, allowing other threads to run. Uses interrupt disabling to ensure atomic operations and prevent race conditions.

-   **Synchronization**:
    -   Race conditions are avoided by disabling interrupts before modifying shared data and using `thread_block()` and `thread_unblock()` to manage thread states atomically.

### Priority Scheduling

#### Highlights

-   **Data Structures**:

    -   `struct lock` with `struct list_elem elem` and `int max_priority`: Used to manage locks and their priority levels.
    -   `int priority_r`, `struct list locks_held`, `struct lock *current_lock`: Used in thread management for handling original priorities and locks held by the thread.

-   **Algorithms**:
    -   Priority donation ensures the highest priority thread gets the CPU by recursively updating priorities through `lock_acquire()` and `lock_release()`.
    -   Ordered lists for waiters in semaphores, locks, and condition variables ensure that the highest priority thread wakes up first.

### Advanced Scheduler

#### Highlights

-   **Data Structures**:

    -   `int nice`, `fixed_point_t r_cpu`, `static fixed_point_t mlfqs_average_load`: Used to calculate thread priorities and manage scheduling in the Multi-Level Feedback Queue Scheduler (MLFQS).

-   **Algorithms**:
    -   Scheduling decisions are based on `nice` values and `recent_cpu` usage, ensuring fair CPU allocation.
    -   Priority and `recent_cpu` values are updated regularly to reflect the system's load and thread activity.

---

## Project 2 - User Programs

### Argument Passing

#### Highlights

-   **Data Structures**:

    -   `args_pushing_func`: Prepares the stack with arguments for process execution.
    -   `syscall_handler`: Handles system calls by parsing the system call number and executing corresponding functionality.
    -   `my_user`: Reads user memory into kernel space while ensuring memory access validity.
    -   `userspace_memo`: Performs memory read from user space to kernel space, ensuring validity of memory access.

-   **Algorithms**:
    -   Argument parsing implemented using `strtok_r` to tokenize input strings. Arguments are pushed onto the stack in reverse order to avoid overflow and ensure correct alignment.

### System Calls

#### Highlights

-   **Data Structures**:

    -   `process_execute`: Tokenizes the command line input and calls `start_process` with the correct arguments.
    -   `start_process`: Loads and creates a user process, pushing arguments onto the stack using `args_pushing_func`.
    -   `syscall_handler`: Handles system calls, including `SYS_EXIT` and `SYS_WRITE`.

-   **Algorithms**:
    -   `sys_write`: Writes data to a file descriptor, handling standard output. Uses `my_user` to check buffer accessibility.
    -   Error handling strategies ensure safe memory access and resource cleanup in case of failures.

### Synchronization

#### Highlights

-   **Synchronization Mechanisms**:
    -   Ensures that system calls are atomic and thread-safe.
    -   Uses semaphores and condition variables to manage process synchronization and prevent race conditions.

### Rationale

-   **Design Choices**:
    -   Implemented argument passing and system calls to ensure robust and efficient user program execution.
    -   Chose thread-safe functions and atomic operations to maintain system integrity and performance.

## Usage

### Running Tests

To run the provided tests for each project:

1. **Project 1**:

    ```sh
    cd pintos/src/threads
    make check
    ```

2. **Project 2**:
    ```sh
    cd pintos/src/userprog
    make check
    ```

### Debugging

-   Use `hex_dump()` to dump the stack contents for debugging argument passing issues.
-   Use GDB for more complex debugging needs.

## Conclusion

These projects provide a comprehensive understanding of operating system concepts through practical implementation. The hands-on experience gained is invaluable for grasping the complexities of modern OS design and preparing for real-world challenges in systems programming.

🚨Academic Integrity Disclaimer🚨
This project in this repository is intended solely as an inspiration for your future projects and should be referenced accordingly. It is not meant for students to fulfill their academic project requirements. If a student uses this project for such purposes, the creators are not responsible. The student will be solely accountable for violating academic integrity. We explicitly state that this repository should not be used to meet academic requirements. Therefore, any academic integrity issues should be addressed with the student, not the creators.
