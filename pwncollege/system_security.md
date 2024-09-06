# System Security

- [Sandboxing](#sandboxing)
- [Race Conditions](#race-conditions)
- [Kernel Security](#kernel-security)
- [System Exploitation](#system-exploitation)

## Sandboxing

**`Namespacing`** - a set of names used to identify a group of objects.

## Race Conditions

### Introduction
---

Before Albert Einstein, everything happened at once. After Albert Einstein, time caused things to be sequential, including processes. This means that instructions are executed in order. Fundamentally, this causes problems. What happens if there are multiple processes running at once?

These process' instructions will very likely get interwoven. One cause is the bottlenecking of current computer architectures: not even cores, too many concurrent processes. There just isn't even resources. This interweaving of instructions can lead to bugs. 

Abusing these type of bugs requires racing to beat a process's instruction with your own at certain weak points. This involves making the chances you get to the weak point first as high as possible.

Attacks exploit a race condition by changing the state that a program is running in while the program assumes that this state has not changed. 

### Time of Check to Time of Use
---

One attack is called Time of Check to Time of Use (TOCTOU), which involves an attacker changing the state of the victim program between the time of check (e.g. if condition) and time of use (victim program does an action based on condition). By changing the state during that time frame, we can cause the victim program to do the action we want.

### Examples of attacks
---

Attack 1: Race in the filesystem

- The filesystem is a shared resource.
- Attackers might have access to part of the filesystem that the victim program is using.
- Change the file and you change the state of the victim program!

### Increase attack window
----

Remember that we want to make our chances of getting to the weak point as high as possible. We can do this by slowing down the victim process to make the attack window be open longer. How can we slow down the victim process?

Method 1: `nice` - change process priority.
- man `nice`, cmon now.

Method 2: Superrrrrrr long paths.
- Path size limit of 4096 bytes.
- Bypass path size limit using symbolic links (limit of 40 symlinks).

### Processes and Threads
---

Processes have their own virtual memory, registers, file descriptors, process ID, and security properties: uid, gid, seccomp rules.

Nah, I'm just kidding! Haha!

A process is actually made up of 1 or more threads. Every process has a main thread that has the same thread ID as the process ID. 

These threads share virtual memory and file descriptors. \
But have their own registers, stack, thread ID, and security properties: uid, gid, seccomp rules.

**The execution order between theads is not deterministic!**

How to make a thread? \
Threads are created using the `clone` syscall, the successor of `fork`, allowing for control over what is shared between parent and child.

Threads often communicate using *global* variables. This can lead to a TOCTOU vulnerability.

There are some differences between libc and syscall functions. \
libc `setuid()` sets UID of *all* threads. \
syscall `setuid()` sets UID of *only* caller thread.

libc `exit()` calls `exit_group()` to terminate *all* threads.
syscall `exit()` terminates *only* caller thread.

### Races in Memory
---
The *filesystem* is a common race condition battleground because it is a shared resource between *processes*.

The *memory* is a common race condition battleground because it is a shared resource between *threads*.

TOCTOU attacks are possible for both race conditions.

**Double Fetch**: Special case of TOCTOU. Bypass a check on first fetch and change important variable before second fetch.

**Data Races**: In a process with two threads that each increment by 1 then decrement by 1 a variable `num` infinitely, it is expected that `num = 0` always. However, because execution order between threads is nondeterministic, there are cases where `num` increases infinitely, or decreases infinitely, or more.

Data races can be prevented using **mutexes** which locks a block of code from being executed by another thread if one thread is executing it already. This block of code is called a *critical section*.

### Signals and Reentrancy
---
Processes can register signal handlers to handle any signal except SIGKILL and SIGSTOP.

Signals *immediately* pause process execution and invoke the handler function.

You can send *any* signal to *any* process at *any* time with the same rUID as you. This means you can cause a program to suddenly divert execution to the handler. So you can make code execution nondeterministic, creating a race condition using signals.

This problem can be solved with reentrant functions. These are functions that would operate properly even when interrupted with an instance of themselves. *I am still confused on this part but am skipping over it because it isn't used in the challenges*.



## Kernel Security

## System Exploitation


