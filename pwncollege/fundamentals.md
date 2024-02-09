# Fundamentals

- [Program Interaction](#binary-files)
    - [Binary Files](#binary-files)
    - [Command Line](#command-line)
    - [Process](#process)
    - [File System](#file-system)
    - [Environment Variables](#environment-variables)
    - [Links](#links)

## Binary Files
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

## Command Line
- Linux facilitates the safe interaction of processes with each other and with the file system, the network, and computer.
- The command line (AKA shell) is an interface to the computer.
- **Interface** 
    - a device or program enabling a user to communicate with a computer. 
    - a device or program for connecting two items of hardware of software so that they can be operated together or communicate with each other.

## Process
- A **process** is a *running program*
    - a **program** is a *file* on your computer
        - **files** live in a *file system*
- Programs like your web browser, shell, and text editor, are all files on the file system and become processes when they are executed.

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

## Environment Variables
- a set of key:value pairs passed into every process when it is launched
    - processes will pass them onto their child processes
- If the first word of the command has no `/` characters, the shell will search for the word in either its builtins or a set of directories specified in the `PATH` environment variable.
- `which <command>` searches through directories in `PATH` and returns the path to the `<command>` file

## Links
- `ln -s` symbolic links are a type of file that references a path to another file
    - symbolic links to a relative path are relative to the directory containing the symbolic link
- `ln` hard links are a type of file that references the data of another file
    - we can view any normal files as hard links
- modifying one file (original or linking file) changes the other