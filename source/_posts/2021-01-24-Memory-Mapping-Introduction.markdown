---
layout: post
comments: true
title: "Memory Mapping Introduction"
date: "2021-01-24"
categories: 
  - "asm"
---

#### **Memory mapping**

Memory of computer has addresses for its smooth working. These addresses are same for everyone and does not change from use to use. The first byte is at address 0, the second byte is at address 1, and so on until the last byte of the computer's memory. Basically if I want to explain memory mapping in short there are memory registers that map memory. First a "logical" address is given to these processes which are currently running on the computer by CPU. This "logical" address is completely temporary and is not same for all users, its completely virtual. This process when becomes a permanent process, is assigned a "physical" address on the memory itself.

How exciting huh ? Well for me these things are very exciting 😁

**These mapping registers can only map data of 2 different size - 4096 bytes and 2 megabytes. Linux uses 2MB for the kernel and 4Kb for most other uses**. Recent CPUs can support up to 1GB !!

To understand these concepts more clearly, you all can read this book ([link](http://library.bagrintsev.me/ASM/Introduction%20to%2064bit%20Intel%20Assembly%20Language%20Programming%20for%20Linux.2011.pdf)) and watch this Youtube video by Ted-Ed [link](https://www.youtube.com/watch?v=p3q5zWCw8J4&t=22s)

I have ended memory mapping in very short and has just given you a little overview because I can't explain everything here but you all can look the links that I have given you all.

So now comes the more exciting part. Ever heard of stack, heap etc. Well in this article you will be explained everything. That's why I just love assembly, It completely builds all the concepts clear related to working of computers.

#### **Process Memory Model**

For the smooth running of a process linux memory is divided into 4 logical segments- text, data, heap and stack. A process is mapped from lowest address i.e. **text** to the highest address i.e. **stack**.

Now before moving ahead I would like to discuss about 2 types of memory - **logical and physical**. **The segmentation is done in the logical part** of the memory because it can vary but the **pages(blocks) are the part of physical part** of the memory as a block size remains constant.

<img src="/images/process-memory-dia.png" align="left">
<br>

**Text** - In assembly text segment is indicated by `.text` , It contains the machine instructions of a program. It basically tells the story of what program does.

**Data** - Data segment contains all the **static data**. It is represented by `.data` .Which means it contains all variables that have been initialized in the program.

**.bss** - Above data segment, there is `.bss` segment which stands for "block started by symbol". Ths segment contains data which is statistically allocated in a process, but is not stored in the executable file. Instead this data is allocated when the process is loaded into **memory**.

.**rodata** - Sometimes `.rodata` is also seen. Basically `.rodata` is a segment where all the constants are placed and `.data` is a segment where all the variable are placed.

**Heap** - Heap is basically some space reserved by the program so that it can use it for future purposes when calling functions like `malloc`.

**Stack** - It is basically temporary storage space for a process. The size of stack is set by the linux kernel, typically to 16 MB. This is enough for our processes.

Now the above segments is for a page(block) of memory. So basically the minimum size of segments depends on page size.

The size of segments vary according to usage but the ultimate size of the page will remain same. for example Sometimes, you will see that processor is processing a lot of information in that case we can assume that .text part is large but other parts is small.Sometimes processing done is less but still `.data` is large but others are small. Sometimes a process needs more temporary storage for later use so stack will be more in size.

**Hello world program in assembly.**

I do not want you to understand the whole code below. Just observe how segmentation has been performed in the code and keep this code in the back of your mind so that you can understand and write codes yourself in the upcoming articles.

```asm
.section .text
    .intel_syntax noprefix 
    .global _start
    _start:
        mov rax, 1
        mov rdi, 1
        lea rsi, [rip+msg]
        mov rdx, 13
        syscall
        
        mov rax, 60
        mov rdi, 0
        syscall
    msg:
        .ascii "Hello world\n\0" 
```
To run this:

```sh
gcc helloworld.s -nostdlib --static -o helloworld
./helloworld
```
I have not added a lot of things in this article. So please read and view the following sources.

**Sources:**

Book link given in the **previous article.**

[http://www.cs.uwm.edu/classe](http://www.cs.uwm.edu/classes/cs315/Bacon/Lecture/HTML/ch10s04.html)[s/cs315/Bacon/Lecture/HTML/ch10s04.htm](http://www.cs.uwm.edu/classes/cs315/Bacon/Lecture/HTML/ch10s04.html)[l](http://www.cs.uwm.edu/classes/cs315/Bacon/Lecture/HTML/ch10s04.html)

[https://jameshfisher.com/2018/03/10/linux-assembly-hello-world/](https://jameshfisher.com/2018/03/10/linux-assembly-hello-world/)

[https://web.stanford.edu/class/archive/cs/cs107/cs107.1212/schedule.html](https://web.stanford.edu/class/archive/cs/cs107/cs107.1212/schedule.html)

https://www.youtube.com/watch?v=HWwNTWY1rxo
