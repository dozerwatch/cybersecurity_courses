# Sandboxing

## Introduction

In the beginning (~ 1950s)...
- computers can only execute one program at a time
- programs are written on punchcards
- programs ran on bare metal (hardware)
- each process was omnipotent

The split of OS and userspace (~ 1960s)...
- hardware measures were developed to separate system and process code
- this allowed multiple processes to run at the same time
- this ensured a process can't destroy computer hardware
- processes could still clobber each other

The rise of virtual memory (~ 1980s)...
- hardware measures were developed to separate the memory space of different processes

The rise of in-process separation (~ 1990s)...
- creation of scripting languages
- scripting languages have an implicit separation between interpreter and interpreted code

Browser hacking (~ 2000s)...
- web browsers have many functionalities all stuffed into one program
- to enable rich content on the web, technologies like Adobe Flash ran with full permissions of the user, which led to many vulnerabilities
- drive-by downloads - where users download a vulnerable program and their machine gets taken over

Browser hacking mitigations (~ 2010s)...
- eliminate Adobe Flash
- hackers moved on to other technologies

The rise of sandboxing (~ 2010s)...
- untrusted code/data should run with almost zero permissions
-   1. spawn privileged parent process
    2. spawn sandboxed child processes
    3. when child needs to perform privileged action, it asks the parent
- this is the ideal model, but it is not always like this

Sandboxing is *extremely* effective. There are several mitigations that are so effective that a second vulnerability is needed to bypass them.

Sandboxes are a strong mitigation:
- need one set of vulnerability to exploit sandboxed process
- need another set of vulnerability to break out of sandbox

## chroot

A traditional sandboxing technique is to use `chroot`, which first appeared in Unix in 1979.

All `chroot` does is change the meaning of `/` for a process and its children. It changes the root `/` to be another directory specified in its first and only argument.

This used to be the de-facto way to sandbox, but it is not a very good sandbox for many reasons. Now it is obsolete.

Only privileged users like root can run `chroot`.