# Kernel Security

**What is the OS kernel?**
- Processes are like the *states*.
- Kernel is like the *federal government*.

The kernel handles processes' interaction with each other and with external resources.

**What are these external resources?**
- `hlt` ins: stops CPU.
- `in`, `out` ins: interact with hardware peripherals.
- `cr3` reg: controls page table used to translate virtual addresses to physical addresses.
- `MSR_LSTAR` reg: defines where syscall ins jumps to.

**The CPU tracks a *privilege level* that controls access to resources.**
- `Ring 3`: Userspace
- `Ring 0`: Kernel
- `Ring -1`: Hypervisor mode

Ring 0 privilege level became an issue with the rise of VMs. A VM's guest kernel should not have unlimited access to the host's physical hardware. Thus ring -1 was invented.

**There are different types of OS models.**
- `Monolithic`: single, unified kernel binary that runs in ring 0 and handles all OS-level tasks. Drivers are libraries loaded into this binary.
    - So device drivers are part of the kernel, meaning any vulnerability inside a driver is a kernel vulnerability.
- `Microkernel`: tiny kernel binary that performs most basic services required for an OS to run. Everything else runs in less privilege levels and must ask the kernel to talk to hardware on their behalf.
- `Hybrid`: combination of both.

**How can we switch between rings?** (AMD64)
1. At boot up, the kernel setes `MSR_LSTAR` to point to the syscall handler routine.
2. A userspace program interacts with kernel with `syscall`.
    - Privilege level switches to ring 0.
    - Control flow jumps to `MSR_LSTAR`.
    - Return address saved to `rcx`.
3. Return to userspace.
    - Privilege level switches to ring 3.
    - Control flow jumps to `rcx`.

### Kernel Modules
---
A kernel module is a library that is loaded into the kernel binary. Similar to a userspace library:
1. The module is an ELF file (.ko).
2. The module is loaded into the address space of the kernel.
3. Code in the module runs at ring 0.

These modules are used to implement device drives, filesystems, networking functionality and more. Typically a kernel module
1. reads data from userspace,
2. does some stuff with the data,
3. writes data to userspace,
4. return to userspace.


### Memory 
---
Userspace processes have their virtual memory at low addresses.

Kernel has its virtual memory at high addresses.