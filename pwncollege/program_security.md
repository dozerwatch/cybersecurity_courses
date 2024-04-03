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
In the beginning, computers were programmed through **direct input of machine code** (punch cards, writing assembly, etc.).

In 1952, *Grace Hopper* proposed one of the first compilers. However, there were many problems. The compiler created **inefficient code** and early computers were **very slow**. Therefore, early compilers were difficult to use due to its slowness. 

In 1972, *Dennis Ritchie* created C. It was specifically designed to be **portable** across different architectures (could be used in different architectures) and to provide low level control of memory access. 

C is essentially assembly with register allocation done for you. This means that developers have great amount of freedom and power, but with that comes a lot of problems if used irresponsibly.

**Problem 1: Trusting the developer**
```C
int a[3] = {1, 2, 3};
a[10] = 0x41;   // <--- Allowed!
```
Arbitrary array access is allowed. This could leak important data! Developers have to ensure that they don't access elements outside of the index.

**Problem 2: Mixing Control Information and Data** \
User data is stored with control data in C. Think of the stack frame -- local variables are stored with the saved frame pointer and the return address. 

Memory corruption occurs when user-controlled data spreads into data that *shouldn't* be user-controlled through a memory error.

**Problem 3: Mixing data & metadata** \
Think of strings. Strings contain the 'data' and is terminated by a null byte (meta-data). What happens if a user provides a null byte as input? Or completely fills up the input, so there are no null bytes? Developers have to make sure that strings are null-terminated, else information can be leaked!

**Problem 4: Initialization and Cleanup** \
When a function returns, C merely moves the stack pointer up some value. The information from a previous function call is still on the stack! Developers must cleanup after themselves because C won't. 

Likewise when a developer declares a variable without initializing it, the previous information on the memory in which the variable sits can be leak! Developers must make sure to initialize their variables.

**If we are able to memory corrupt, what can we corrupt?**
1. Memory that doesn't influence anything. Useless!
2. Memory that is used in a *value*. Think important variable.
3. Memory used as a *read pointer*, allowing us to force the program to access arbitrary memory.
4. Memory used as a *write pointer*, allowing us to overwrite arbitrary memory.
5. Memory used as a *code pointer*, allowing us to redirect program execution. 

So memory corruption is pretty dangerous! Now we wonder... *how can we cause a memory corruption?*

**Cause 1: Classic Buffer Overflow**
```C
int main() {
    char buf[16];
    read(0 buf, 100);
}
```
This is a simple overwrite. The buffer is only 16 bytes in size, but we can write 100 bytes to it. Thus we can corrupt 100 - 16 = *84* bytes of memory after this buffer.

**Cause 2: Signedness Mixups** \
```C
int main() {
    int size;
    char buf[16];
    scanf("%i", &size);     // <-- -1 = 0xffffffff
    if (size > 16) exit(1); // <-- checks -1 < 16
    read(0, buf, size);     // size = 0xffffffff
}
```
The standard C library uses *unsigned integers*. \
The default types (short, long, int) are *signed*. 

So by inputting `-1` for `size`, we bypass the `if` as `-1 > 16` is false and read in a large amount of data into buffer. Way more than 16 bytes, hence our memory corruption. This is a buffer overflow from a signedness mixup.

**Cause 3: Integer Overflow**
```C
int main() {
    unsigned int size;
    scanf("%i", &size);
    char *buf = alloca(size+1); // <-- allocate space on stack
    read(0, buf, size);
}
```
The `alloca` function allocates a `size` amount of space on the stack. `Int` is a 32-bit value. If we input `0xffffffff` as our size, `size+1` becomes `0`. So we allocate no space on the stack. This means that we can read a large amount of arbitrary data onto the stack, hence our memory corruption.

**Cause 4: Off-by-one Error** \
This is a very common mistake among programmers. If a program has this error, we might be able to access one more element than the programmer thought. Hence we can corrupt one byte of memory, which might be very dangerous. Think leaking the stack canary.

Speak of stack canary, let's talk about mitigations against memory corruptions. How can we protect our programs against them?

**Mitigation 1: Stack Canaries** \
They are used to fight against buffer overflows into the return address and are very effective at doing so.
- In the function prologue, write a random value at the end of the stack frame, before the return address and saved frame pointer.

- In the function epilogue, check if this value is the same. Exit if not.

Stack canaries always start with `\x00`. 

Unfortunately, there are some situations in which we can bypass stack canaries to still memory corrupt.
1. Leak canary with another vulnerability.
2. Bruteforce canary for forking processes.
    - Forked child processes have the same canary as the parent process.
3. Jump over the canary.

**Mitigation 2: Address Space Layout Randomization** \
Memory corruptions often focus on corrupting pointers to point somewhere else. 

For non-PIE programs, instructions are always in the same location. \
For PIE programs, locations are given as offsets from random locations.

Q: What if we randomize the location of code and data in memory? \
Q: Where can the attacker point to now? \
Q: How do you redirect execution if you don't know where any code is?
1. Leak addresses with another vulnerability.
2. Overwrite the offset.
    - The least signification 4 nibbles are not random.
    - Pages are always aligned to a `0x1000` alignment.
    - The last 3 nibbles of an address are never changed.
3. Bruteforce for forking processes.

Tip: \
Disable ASLR for local testing
- pwn.process(..., aslr=False)
- gdb disables ASLR by default unless program is SUID

The core of both these mitigations is secrets. The stack canary is randomized and kept secret from everyone. With ASLR, the whole address space is randomized and kept secret from everyone. The validity of both mitigations rely on the attacker not knowing these secrets.

Unfortunately, there are some memory errors which leads to the **disclosure** of these secrets.

**Cause of Disclosure 1: Buffer Overread**
```C
int main() {
    char buf[16] = {0};
    write(1, buf, 100);
}
```





## Program Exploitation