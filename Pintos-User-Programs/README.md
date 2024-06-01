# Pintos Project 2: User Programs

## Argument Passing

### Data Structures

**A1**: Declaration of new or changed structures, members, global or static variables, typedefs, or enumerations.

```c
1. args_pushing_func: static function prototype for pushing arguments onto the stack during process creation.
2. syscall_handler: static function handling system calls, parsing system call number and its functionality.
3. my_user: function for reading user memory into kernel space, for valid memory access.
4. userspace_memo: function for performing memory read from user space to kernel space, ensuring validity of memory access.
```

-   **args_pushing_func**: Prepares the stack with arguments for process execution.
-   **syscall_handler**: Handles system calls by parsing the system call number and executing corresponding functionality.
-   **my_user**: Reads user memory into kernel space while ensuring memory access validity.
-   **userspace_memo**: Performs memory read from user space to kernel space, ensuring validity of memory access.

### Algorithms

**A2**: Argument parsing implementation.

Argument parsing was implemented using a `strtok_r` function to tokenize the input string by spaces. Tokens were stored in an array in the correct order. To avoid stack overflow, the stack pointer was aligned to a 4-byte boundary, and arguments were pushed onto the stack in reverse order, decrementing the stack pointer for each argument. Additionally, a NULL pointer and the address of arguments were pushed onto the stack, and the stack pointer was aligned again.

### Rationale

**A3**: Why does Pintos implement `strtok_r` but not `strtok`?

Pintos implements `strtok_r` instead of `strtok` because `strtok_r` is thread-safe, allowing for safe use in a multi-threaded environment.

**A4**: Advantages of Unix-like systems where the shell separates commands into an executable name and arguments.

1. **Flexibility**: Allows for dynamic handling of commands by the shell, enabling features like command substitution, piping, and redirection.
2. **Extensibility**: Facilitates the implementation of custom shells with varying functionalities, enhancing user experience and system versatility.

## System Calls

### Data Structures

**B1**: Declaration of new or changed structures, members, global or static variables, typedefs, or enumerations.

```c
1. args_pushing_func: Static function to push arguments onto stack while process creation.
2. process_execute: Updated to tokenize the command line input and call start_process with the correct arguments.
3. start_process: Load and create a user process, push arguments onto the stack using args_pushing_func.
4. syscall_handler: This handle the sys calls, including SYS_EXIT and SYS_WRITE.
5. userspace_memo: Performs memory read from user space to kernel space, ensuring validity.
6. sys_exit: Exit the current thread.
7. sys_write: Write the data to a file descriptor, handling standard output.
```

### File Descriptors

**B2**: Association of file descriptors with open files and their uniqueness.

No file descriptors were implemented.

### Algorithms

**B3**: Reading and writing user data from the Kernel.

For writing data to user space through the `sys_write` system call, the `my_user` function checks the accessibility of the buffer in the user space. If the file descriptor is for standard output (fd == 1), it writes the data using `putbuf`.

**B4**: Inspections of the page table for system calls.

Not Applicable (NA).

**B5**: Implementation of the "wait" system call and its interaction with process termination.

Not Applicable (NA).

### Error Handling

**B6**: Managing user program memory access failures and resource cleanup.

System calls with error handling can be designed with error checking at critical points like user memory access, with cleanups to release resources upon error detection. In the `write` system call, pointers are validated before accessing user memory, and cleanup routines release resources if errors occur. The process is terminated while logging errors.

### Synchronization

**B7**: Ensuring "exec" system call returns -1 if loading the new executable fails.

Not Applicable (NA).

**B8**: Synchronization and race condition avoidance when parent process P calls wait(C) before C exits.

Contains a loop that iterates a large number of times, consuming CPU cycles. The loop includes an assertion (ASSERT(d!=0)) to ensure a certain condition (d not becoming zero) holds true. If fully implemented, this function would have synchronization mechanisms such as semaphores or condition variables to wait for the child process to terminate and properly handle its exit status.

### Rationale

**B9**: Implementation of access to user memory from the kernel.

Implemented access to user memory from the kernel using explicit memory access functions, allowing the kernel to directly read and write user memory while checking for valid memory access, preventing potential security vulnerabilities like buffer overflows or unauthorized memory access.

**B10**: Design for file descriptors.

Not implemented.

**B11**: Mapping between tid_t and pid_t.

No mapping between tid_t (thread ID) and pid_t (process ID). The tid_t is used as a unique identifier for threads created by the `thread_create` function, while the pid_t is used to identify processes.

```

This README file covers the key points from the provided design document for the Pintos Project 2: User Programs, providing a comprehensive overview of the project's data structures, algorithms, rationale, and synchronization mechanisms.

## FAQ
**How do I run the Phase 1 test?**
* Navigate to Pintos' root directory (the directory that contains `src`), and run:
```

python pa2_arg_test/arg_test.py

```

**How can I debug my work for Phase 1?**
* You can use `hex_dump ()` to dump the contents of your stack. If you're not sure how to use it, see `pa2_arg_test/test_arg_passing.sh` for an example. I'll include it here for reference:
```

// An example of hex_dump you can use to debug
hex_dump( (uintptr_t) *esp, *esp, PHYS_BASE-\*esp, true);

```
* You will also need GDB for the harder to diagnose issues.
```
