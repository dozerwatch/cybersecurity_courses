# Program Security
- [Shellcode Injection](#shellcode-injection)
    - [Problems](#problems)
- [Reverse Engineering](#reverse-engineering)
    - [Problems](#problems-1)
- [Memory Errors](#memory-errors)
    - [Problems](#problems-2)
- [Program Exploitation](#program-exploitation)
    - [Problems](#problems-3)

## Shellcode Injection


### Problems
**Level 2:** NOP Sled \
**Level 3:** `xor` and `shl` \
**Level 4:** `push <2 bytes>` and `pop [<r64>]` \
**Level 5:** `inc byte ptr [rip]` `.byte 0xcb` \
**Level 7:** `chmod` \
**Level 8, 10, 11, 12:** `ln -s` and `chmod` \
**Level 9:** `jmp`

### Level 10 
My level 8 worked for this level. The reason is that my raw shellcode is only 16 bytes, which causes the sort filter to not even run! The sort code is 
```C
uint64_t *input = shellcode_mem;
int sort_max = shellcode_size / sizeof(uint64_t) - 1;
for (int i = 0; i < sort_max; i++)
    for (int j = 0; j < sort_max-i-1; j++)
        if (input[j] > input[j+1])
        {
            uint64_t x = input[j];
            uint64_t y = input[j+1];
            input[j] = y;
            input[j+1] = x;
        }
```
So `sort_max = 1` causing the second for loop to not run at all, meaning the whole sorting doesn't happen at all.

### Level 14

Wow what a level! For this level, you had only 6 bytes of shellcode. So every byte matters! The important concepts for this level is **Living Off The Land**, which means to use the data already in the registers just before your shellcode executes, and `push` and `pop` are both only one byte. 

We use the 2 stage method to solve this level. Stage 1 reads a large number of bytes from stdin into the RIP register. For stage 2, we can write anything, really, to get the flag since there is so much space left. First, specific to this challenge, we must get to where RIP is pointing. Stage 1 actually places us behind where RIP is pointing. We can do this with a bunch of `NOP` instructions. Now we write our stage 2 code and get the flag.



## Reverse Engineering


## Problems


## Memory Errors


## Problems


## Program Exploitation


## Problems
