# Program Security
- [Shellcode Injection](#shellcode-injection)
- [Reverse Engineering](#reverse-engineering)
- [Memory Errors](#memory-errors)
- [Program Exploitation](#program-exploitation)

## Shellcode Injection
Von Neumann architecture sees and stores code as data and vice versa. x86 and ARM are Von Neumann architecture.

Shellcode execution is executing injected binary code under the context of the program. So if the program is SUID root, we can run the injected shellcode as root.

Question: How does shellcode get injected? \
Answer: A simple switching of arguments when calling a function is enough.
```C
void bye() { puts ("Bye!"); }
void hello(char *name, void (*bye_func)()) {
    printf("Hello %s\n", name);
    bye_func();
}
int main() {
    char buf[100];
    fgets(buf, 100);
    hello(bye, buf); // <--- Vuln: Switched args
}
```
The user inputted data in `buf` is executed -- so data is treated as code! When the `bye_func` in `hello` gets called, RIP points to the stack.

The goal of shellcoding is to inject arbitrary data as code into a program. Another name for this is code injection. Most of the time, the goal is to get a shell, hence the name shellcode.

Some common challenges in writing shellcode include:
1. Memory sizes
2. Forbidden bytes
    - Use clever synonyms
    - If the page where shellcode is mapped is writable, remember **data is code.**
        ```
        # Bypass restriction on int3

        inc BYTE PTR [rip]  
        .byte 0xcb  # <-- Data treated as code

        # Make sure .text is writable (gcc -Wl, N)
        ```
    - Multi-stage shellcode
        1. Stage 1: Reads in stage 2 -- read(0, rip, 100)
            - Shellcode pages needs to be writable
        2. Stage 2: Anything
3. Shellcode mangling
    - Shellcode might be sorted, (un)compressed, encrypted, or decrypted.
        - Start at the result and work backwards
    - Parts of the shellcode might be uncontrollable
        - Jump over them

To prevent data execution (shellcoding), by default, the stack and heap are not executable. Normally, all the code is in .text, so there is no point for the stack or heap to be executable. Also .text is not writable.

Because of these prevention, shellcoding is not very prevalent anymore. But ...

Memory can be made executable using `mprotect()` system call.
1. Trick program to `mprotect` (PROT_EXEC) our shellcode.
2. Jump to shellcode.

Question: How to do 1? \
Answer: Code reuse through ROP.

## Reverse Engineering
Forward engineering is the process of building a program.

1. Figure out what to code (Design)
2. Code
3. Compile

At every step, **information is lost.**

Reverse engineer is getting this information back. Every step in the reverse engineering process requires human help. A reverser uses several tools to build up a mental model.

Question: What is lost in the transition between Design and Code? \
Answer: The intent of the code. What does the code do?

Question: What is lost in the compilation process? \
Answer: 
- Comments
- Variable names (becomes memory locations)
- Function names
- Structure data (classes, structs, etc)
- Sometimes, entire algorithms (optimization)
- Type information

The focus of the module is **how do we reverse the design from the binary?**

A program consists of *modules* \
made up of *functions* \
containing *blocks* of *instructions* \
that operate on *variables* and *data structures*. 

Developers rely on *modules* (libraries) to build software. These libraries are well-documented. This means that we can easily look up what the code does, if we recognize a library used.

Most *functions* have one main purpose, so they can be reversed in isolation. Once we understand more *functions* of a program, we build an idea of what the program does. In disassemblers, *functions* are represented as *blocks* of *instructions* connected by edges to other *blocks* of *instructions*.

A *function* prologue sets up the stack frame.
```amd64
push rbp
mov rbp, rsp
sub rsp, 0x__
```

A *function* epilogue tears down the stack frame.
```
mov rsp, rbp
pop rbp
```

The stack is a region of memory used to store **local variables**. It grows *'backwards'* towards smaller memory addresses. 

`push` ---> rsp - 8 \
`pop`  ----> rsp + 8

The stack starts out storing the environment variables and program arguments. When a function is called, the address of the next instruction is pushed onto the stack. This address is popped when the function returns. Every function sets up a stack frame.

Programs operate on data:
```
.data   - initialized global writable data
.bss    - uninitialized global writable data
.rodata - global read-only data
stack   - statically allocated local variables
heap    - dynamically allocated variables
```
Data in `.bss`, `.data`, `.rodata` is stored at **known offsets** from program code. It is accessed via RIP-relative instructions. Code and data are accessed from different areas. Code lives in `.text`.

Static tools analyze a program at rest -- what is in an ELF file. 

Dynamic tools analyze a program at runtime.

`gdb` has timeless debugging with `record`. 

## Memory Errors


## Program Exploitation