---
layout: post
title: "Writing programs in x86-64 ASM and pwncollege embryoasm writeup"
date: 2022-01-04 15:28:24 +0530
comments: true
categories: asm
paginate: true
keywords: 
description:  
---

Before reading this, it's an advice to please read [previous article](/blog/2021/11/25/x86-64-assembly-language/) of ASM series.

So now that we know some basics of registers and syscalls. We will move onto the part where we use our newfound knowledge to write some assembly code. 

**The following ASM code is specific to GAS (GNU Assembler)**

### Step by Step Hello world ASM program breakdown  

```assembly
.section .text
    .intel_syntax noprefix
    .global _start
    _start:
        mov rax, 1
        lea rsi, [rip+str]
        mov rdx, 13
        syscall

        mov rax, 60
        mov rdi, 0
        syscall

    str:
        .string "Hello world\n"
```


Now in my [first article](/blog/2021/01/24/Memory-Mapping-Introduction/), I explained different sections/mapping of memory. Most important sections among those are `.text` section and `.data`, because it is `.text` where we write code and `.data` where we define variables and constants. 

In the above *hello world* program, we are only using the `.text` section and keeping the code as minimal and simple as possible. 

So in the first line we are defining the section. In order to define a section we do `.section <section name>`

In our case, as we are only using `.text` : 

```asm 
.section .text 
```

Now because we are using GAS, the default ASM sytax is AT&T but we are writing in intel syntax so we need to specify that to the assembler. We do this using : 

```asm 
.intel_syntax noprefix 
``` 

`.global` is GAS directive which helps in defining symbols in object file. Every ASM code must have a `_start` symbol. It defines the entry point of ASM code. 

In GAS we do all this using : 

```asm 
.global _start # first we define a symbol
_start : # then we mark the entry point 
``` 

Oh ! by the way, we use `#` in GAS for comments. 

### MOV instruction  

The `mov` instruction is the very basic and is used extensively in a assembly program.  It is used to copy/move data from one register to another. In intel, it works in the following way : 

``` 
mov <destination register> , <source register>
``` 

For example we need to copy number 6263 in register `rax`, We'll do : 

```asm 
mov rax, 6263 # rax = 6263
```

### LEA instruction 

The `lea` instruction is used to copy some **address** in some register. 

```
lea <destination register> , <source effective address>
``` 
This is also used extensively because we are loading effective address, So we can also do math in one instruction itself and assembler will understand it and assemble it for us. In `mov` instruction it's not possible.  

### SYSCALL instruction 

syscall instruction, as name says, is used for making system calls. 

### Main Hello world code 

Now to write something on screen, we need to write on stdout (it's file descriptor is 1). So in total we need to do 2 syscalls (write and exit syscalls).

To do write syscall we need to give it some arguments. We give arguments based on calling convention (Discussed in previous [article](/blog/2021/11/25/x86-64-assembly-language/)) . 

<img src="/images/x86-64/Calling_convention.png" class="center" style="width: 60%">

We can either use a good [website](https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md) or if you are a console fan then method used in [previous article](/blog/2021/11/25/x86-64-assembly-language/) to get syscall number and to see arguments use 2nd page of `man` command. 

<img src="/images/x86-64/man_write.png" class="center"> 

`echo SYS_write | gcc -include sys/syscall.h -E - ` 

So, putting everything together and writing a subroutine for `write` syscall

**1st argument :** fd (File descriptor which in our case is 1 for stdout) <br>
**2nd argument :** buf (Buffer, Address of info which has to be written on screen ?) <br>
**3rd argument :** count (Buffer size) <br>

All these arguments have to be set according to calling convention. 

```asm 
mov rax, 1         # syscall code is set through rax register 
mov rdi, 1         # set fd to stdout (1)  
lea rsi, [rip+str] # use rip (instruction pointer) to access label str
mov rdx, 13        # Hello world\n\0 size = 13
syscall            # perform syscall 
``` 

Label `str` is basically a space in memory where "hello world" is stored in form of bytes. `lea` instruction will calculate the address of the start of buffer using `rip` register (instruction pointer). 

I recommend you to write the `exit` subroutine without looking at my code. 

**Exit subroutine :**

```asm 
mov rax, 60 # syscall code for exit is 60 
mov rdi, 0  # return address of exit 
syscall     # perform syscall 
```

So to putting all the pieces together and we get our assembly code : 

```asm 
.section .text
    .intel_syntax noprefix
    .global _start
    _start:
        mov rax, 1
        lea rsi, [rip+str]
        mov rdx, 13
        syscall

        mov rax, 60
        mov rdi, 0
        syscall

    str:
        .string "Hello world\n"
```

I hope after reading this, you would have understood assembly and basic concepts related to memory. Now like any other language, assembly is just about practice, pratice and practice. Once you master it, I guarantee, assembly and C will become your favorite language. 


### [Pwn.College Embryoasm](https://dojo.pwn.college/challenges/asm)  Writeup

I have already started the instance, so let' connnect `ssh -i ~/.ssh/key.pub hacker@dojo.pwn.college` . 

<img src="/images/x86-64/asm_1.png" class="center" > 

So this is easy. As explained above. We can just do `mov rdi, 0x1337`

full code : 

```asm 
.section .text 
    .intel_syntax noprefix 
    .global _start 
    _start : 
        mov rdi, 0x1337
```

First we assemble it and compile it into an ELF then we will convert copy bytes of that ELF in a different file. 

to do so : 
```
gcc -nostdlib -static exp.s -o exp
objcopy --dump-section .text=exp.bin exp
```

Then we will pipe the bytes into the challenge. 

<img src="/images/x86-64/asm_1_flag.png" class="center" > 

We can also do this using python script through pwntools. 

Python script : 

```py
#!/usr/bin/env python3
import pwn
pwn.context.log_level = "INFO"
pwn.context.encoding = "latin"
pwn.context.arch = "amd64"
pwn.warnings.simplefilter("ignore")

assembly = """mov rdi, 0x1337"""

proc = pwn.process("/challenge/embryoasm_level1")
print(proc.readrepeat(1).decode())
proc.send(pwn.asm(assembly))
print(proc.readrepeat(1).decode())
```

In future I'll write some interesting articles on some more instructions in ASM, file operations through assembly, shellcoding and operating system design.  

A [wise man](https://deut-erium.github.io/about.html)👨‍💻 (check out his [blog](https://deut-erium.github.io/)) once said to me, "its almost like playing lego ... you have to put the pieces together ..." 

On that note, 

Signing out


