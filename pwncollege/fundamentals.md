# Fundamentals
- [Program Interaction](#program-interaction)
    - [Binary Files](#binary-files)

## Program Interaction

### Binary Files
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
