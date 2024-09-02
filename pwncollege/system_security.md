# System Security


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



