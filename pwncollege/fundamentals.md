# Fundamentals
1. [Program Misuse](#program-misuse)
2. [Program Interaction](#program-interaction)
    - [Binary Files](#binary-files)
    - [Command Line](#command-line)
    - [Process](#process)
    - [File System](#file-system)
    - [Environment Variables](#environment-variables)
    - [Links](#links)
3. [Assembly Crash Course](#assembly-crash-course)
    - [Computer Architecture](#computer-architecture)
    - [Assembly](#assembly)
    - [Data](#data)
    - [Registers](#registers)
    - [Memory](#memory)
    - [Control Flow](#control-flow)

## Program Misuse


## Program Interaction
###  Binary Files
- **ELF** files allow compilers to *create* and *define* a program
- All ELFs start with `7f 45 4C 46`
- **ELF program headers**
    - the *source of information* when loading an ELF file
    - specify information needed to prepare program for execution
    - ELF program headers define *segments*
        - **segments** are part of ELF files loaded into memory when a program is executed
- **Section headers** are information for debugging
    - they are just metadata
    - not a necessary part of ELF files

    | Section headers | Description |
    | --------------- | ----------- |
    | .text | executable code |
    | .plt and .got | used to resolve and dispatch library calls |
    | .data | initialized global writable data (global arrays with initial values) |
    | .rodata | global read-only data (string const) |
    | .bss | uninitialized global writable data |

***Question***: What are dynamically loaded libraries?

- binaries that use dynamically loaded libraries rely on **symbols** to find libraries
- Interacting with ELFs
    | Program       | Description |
    | -------       | ----------- |
    | `gcc`         | make your ELF file |
    | `readelf`     | parse ELF header |
    | `objdump`     | parse ELF header and disassemble source code |
    | `nm`          | view ELF's symbols |
    | `patchelf`    | change some ELF properties |
    | `objcopy`     | swap out ELF sections |
    | `strip`       | remove helpful information (like symbols) |

### Command Line
- Linux facilitates the safe interaction of processes with each other and with the file system, the network, and computer.
- The command line (AKA shell) is an interface to the computer.
- **Interface** 
    - a device or program enabling a user to communicate with a computer. 
    - a device or program for connecting two items of hardware of software so that they can be operated together or communicate with each other.

### Process
- A **process** is a *running program*
    - a **program** is a *file* on your computer
        - **files** live in a *file system*
- Programs like your web browser, shell, and text editor, are all files on the file system and become processes when they are executed.
- Each Linux process has **virtual memory space** containing:
    - the binary
    - the libraries
    - heap
    - stack
    - any memory specifically mapped by program
    - some helper regions
    - kernal code
- **Virtual memory** is dedicated to the process.
- **Physical memory** is shared among the whole system.

### The Life of a Process
1. A process is [created](#a-process-is-created).
2. A process is [loaded](#a-process-is-loaded).
3. A process is [initialized](#a-process-is-initialized).
4. A process is [launched](#a-process-is-launched).
5. A process reads its arguments and environment.
6. A process [does what it's meant to do](#a-process-does-its-thing).
7. A process [terminates](#a-process-terminates).

### A Process is Created
- Every Linux process has 
    - state
    - priority
    - parent, siblings, children
    - shared resources
    - virtual memory space
    - security context
        - effective uid and gid
        - saved uid and gid
        - capabilities
- Processes clone themselves forming a child and parent process. The child will then replace itself with the `execve` syscall with another process.
    - EXAMPLE: 
        1. type `/bin/cat` in bash
        2. bash forks itself
        3. the child process `execve` `/bin/cat` and becomes `/bin/cat`

### A Process is Loaded
- The kernal first checks for executable permissions.
- If executable, the kernal reads the beginning of the ELF file:
    1. `#!` - script file, kernal extracts interpreter from the rest of that line and executes this interpreter with the original file as an argument.
    2. If the file matches a format in `/proc/sys/fs/binfmt_misc`, the kernal executes the interpreter specificied for that format with the original file as an argument.
    3. If the file is **dynamically-linked** ELF, the kernal reads the interpreter defined in the ELF file and loads it and the original file. Then it lets the interpreter take control.
        - **Dynamically-linked** means the file relies on libraries that also need to be loaded.
        - The loading process of a dynamically-linked ELF:
            1. The program and its interpreter are loaded by the kernal.
            2. The interpreter locates the libraries.
            3. The interpreter loads the libraries.
    4. If the file is **statically-linked** ELF, the kernal loads it.
        - These files are **way bigger** in file size than dynamically-linked one.
        
### A Process is Initialized
- Every ELF binary can call *constructors* which are functions that run before the program is launched.

### A Process is Launched
- A normal ELF calls `__libc_start_main()` in `libc` which calls the programs `main` function.

### A Process Reads Arguments and Environment

### A Process Does Its Thing
- *System calls* are a way for processes to talk to the OS.
- *Signals* are a way for the OS to talk to processes.
    - Signals pause process execution and invoke the handler
        - The handler is a function that takes one argument: the signal number
        - Without a handler for a signal, the default is ignore or kill.
- Processes can share memory with other processes.
    - An easy way to do this is to use the `/dev/shm` directory.

### A Process Terminates
- Processes can only exit in one of two ways:
    1. Recieve an unhandled signal
    2. Call the `exit` system call
- After termination, processes remain in a *zombie* state
    - If the parent process `wait` on the child, then the exit code is return to the parent and the child process is freed
    - If the parent process dies without `wait`, the child process gets adopted by process with `PID 1` and stay there until it is cleaned up.

## File System
| Path          | Description
| ----          | ----------- 
| `/`           | root
| `/usr`        | Unix System Resource, contains system files
| `/usr/bin`    | executable files for programs installed on computer
| `/usr/share`  | program resources
| `/usr/lib`    | shared libraries for use by programs on computer
| `/etc`        | system configurations
| `/var`        | logs, caches, etc.
| `/home`       | user-owned data
| `/proc`       | runtime process data
| `/tmp`        | temporary data storage

### Environment Variables
- a set of key:value pairs passed into every process when it is launched
    - processes will pass them onto their child processes
- If the first word of the command has no `/` characters, the shell will search for the word in either its builtins or a set of directories specified in the `PATH` environment variable.
- `which <command>` searches through directories in `PATH` and returns the path to the `<command>` file

### Links
- `ln -s` symbolic links are a type of file that references a path to another file
    - symbolic links to a relative path are relative to the directory containing the symbolic link
- `ln` hard links are a type of file that references the data of another file
    - we can view any normal files as hard links
- modifying one file (original or linking file) changes the other 

### Problems

I learned how to use pipes to interact with programs in python with the subprocess module. I learned how to use named pipes to interact with processes (shell to python, C to python) and about when they block and how to prevent it. I learned about how processes are started -- with fork and execve. I learned how to use dup2. 

This was a very challenging module and therefore a very rewarding one. 

## Assembly Crash Course

### Computer Architecture
- Every program will become binary instructions executed on the CPU.
    - At the center of the CPU is a lot of logic gates.
    - It is all about logic gates.
![computer architecture](/pwncollege/images/computer_architecture.png)
- Accessing Network + Others is slow, accessing the disk is slightly faster, accessing memory is faster, accessing the register is much faster.
    - The faster the access, the smaller the space
- Memory goes to cache, then to registers
- This is called the **Jon Von Neumann architecture**.

### Assembly
- A direct text representation of binary code. 
- Binary code and assembly code are equivalent:
    - One assembly instruction is one CPU instruction.
- CPUs interact with 3 types of data:
    1. Data directly given to CPU
    2. Data in registers
    3. Data in memory

### Data
| Name | Size
| ---- | ----
| Nibble | 4 bits
| BYTE | 8 bits
| WORD | 2 bytes
| DWORD | 4 bytes
| QWORD | 8 bytes

Numbers are represented using **two's complement**:
- Negative numbers are represented as the large positive number they would correlate to.
- Leftmost bit represent negative number.

### Registers
- CPUs need fast access to the data it is working on.
- Registers are very fast, temporary storage for data.
- `movsx` - sign-extending move

### Memory
- Used to store lots of data with fairly fast access.
- Processes use memory for everything.
- Addresses range from 0x10000 to 0x7fffffffffff (11 f's).
- Each memory address is one byte
    - This means there are 127 terabytes of addressable RAM.
- A process has virtual memeory which is partially filled by OS.
- The **stack** starts in high memory and grows towards smaller addresses.
    - `rsp` points to the top of the stack (most recently added)
    - `push rcx` = `sub rsp, 8` `mov [rsp], rcx`
    - An 8 byte write at address 0x1000 will write from 0x1000 to 0x1007.
- Address calculations: `reg + reg * c_1 + c_2`
- Write immediate values: `mov DWORD PTR [rax], 0x1337`

### Control Flow
- `jmp` adds to RIP
- `eb fe` represents jump back by 2 bytes
    - `fe` is -2 in two's complement
    - this is an infinite loop
- Condition jumps check conditions stored in `rflags` register
- Flags are updated by:
    1. Most arithmetic operations
    2. `cmp` (`sub` but discards result)
    3. `test` (`and` but discards result)
- `call` pushes RIP and jumps to instruction
- `ret` pops RIP and jumps to it