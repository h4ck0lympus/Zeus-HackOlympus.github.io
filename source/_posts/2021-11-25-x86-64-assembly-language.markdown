---
layout: post
title: "x86-64 Assembly Language"
date: 2021-11-25 10:07:42 +0530
comments: true
paginate: true
categories: ["asm"] 
---

#### Prerequisite: Knowledge about simple programming language terms like variables, functions etc. 

### Registers 

ASM works a lot around registers, I try to think of them as variables which only store data types up to 8 bytes.Now there are special registers and register for general use.

In the start (during 8 bit days) we only had 4 general purpose registers - a,b,c,d. 

And Other 2 special purpose registers - sp (stack pointer) and bp (base pointer).    

But now (in 64 bit mode) we have a total of 11 general purpose registers and 4 special purpose registers: 

| Register |          Purpose         |
|:--------:|:------------------------:|
|    rax   | General Purpose Register |
|    rbx   | General Purpose Register |
|    rcx   | General Purpose Register |
|    rdx   | General Purpose Register |
|    r8    | General Purpose Register |
|    r9    | General Purpose Register |
|    r10   | General Purpose Register |
|    r11   | General Purpose Register |
|    r12   | General Purpose Register |
|    r13   | General Purpose Register |
|    r14   | General Purpose Register |
|    r15   | General Purpose Register |
|    rsp   | Special Purpose Register |
|    rbp   | Special Purpose Register |
|    rsi   | Special Purpose Register |
|    rdi   | Special Purpose Register |

In above registers 'r' means 64 bit register. If we want to use 32 bit register we use 'e' prefix. **We can also use 32/16/8 bit registers in 64 bit mode** . The following illustration will explain it clearly : 

<img src="/images/x86-64/Registers.drawio.png" class="center" style="width: 70%">

### Syscall 

Behind the working of every program, there are syscalls involved; These syscalls are permissions which the program ask for from the "supreme authority" - the kernel. Now why this happens ? Because the program does not directly run in the privileged mode for security reasons. 

In C language we have glibc that provide us functions like `printf`, `scanf` etc. which performs syscalls for us in the background.Now before making a syscall we have to set some parameters to define the syscall and its behaviour. We define the syscall using "codes", for example `write` syscall has code 1 in x86-64. Now `write` takes 3 arguments: `fd`(file descriptor we have to write), `buf` (stuff we have to write), and `count` (How many characters to write). How do we know this ? using `man 3 write` which return the man page of write. 

We set these arguments using different register and all this follows a calling convention. The calling convention is as follows: 

<img src="/images/x86-64/Calling_convention.png" class="center" style="width: 60%">

To get a list of all the syscalls : `cat /usr/include/x86_64-linux-gnu/asm/unistd_64.h` We don't need to remember this path. I mean if you ever forget this path simply investigate this using other techniques like preprocessor output and printing predefined standard macros like this: `echo SYS_write | gcc -include sys/syscall.h -E -` here we are just asking the compiler to return the preprocessor output to stdout. 

That's all folks. In next article we'll write our first assembly program. 

