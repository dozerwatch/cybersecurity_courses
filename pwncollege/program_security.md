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
**Level 8:** `ln -s` and `chmod` \
**Level 9:** `jmp` \ 

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





gcc -nostdlib -static -o code shellcode.s && objcopy --dump-section .text=raw code && ls -l && objdump -M intel -d code



0x7f -  0111 1111 - DEL
        0011 1111 - 0x3f

0x62 -  0110 0010 - 
        1100 0100 - 0xa4
        0011 0001 - 0x31





## Reverse Engineering


## Problems


## Memory Errors


## Problems


## Program Exploitation


## Problems
