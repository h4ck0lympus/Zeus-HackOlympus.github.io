---
layout: page
title: Weekly progress/log
permalink: /log/
comments: false
---

I am planning to log my weekly progress as a way to be honest to myself and note my findings. So here it is :

Before starting this, random notes from Week 0:

1. **Why can't we fuzz multithreaded programs using libfuzzer and afl++ ?** I researched and found this question answered in one of the [google group](https://groups.google.com/g/afl-users/c/lzDYaClQIco). 
    So there are basically 2 main reasons: 
    - fuzzing is a feedback driven process. It uses coverage bitmap to track the coverage. More the coverage of the fuzzer the better the probability of finding bugs with the particular fuzzing instance. 
    This coverage bitmap is created per process so it will be shared between the threads. Whenever we fuzz multithreaded programs, we are sharing this coverage bitmap with other threads. So one of the
    threads in the bitmap, marking the regions that are not covered by the other threads causing false coverage and decreasing fuzzing efficiency.
    - another reason is the fact that AFL++ uses `fork()` to create a replica of parent process and send input to the child input. Using `fork()` is generally discouraged because `fork()`
    calling thread will be preserved while other threads will be killed and it can have severe impacts because locks are not released in the kernel, also shared memory can be corrupted.
2. **How is coverage bitmap initialized ?** 
    - One program contains one or more functions, each functions contain one or more basic block. These basic-blocks are basically nodes in control-flow graph (CFG). Edge between 2 nodes in CFG (i.e edge between)
    is represented by one bit.
3. Also finally finished lvl 3. Prime trick to exploit race conditions is to keep minimum change between 2 threads running simultaneously (Atleast this worked ...). Before this also finished 3 papers - KRACE, razzer and exprace,
    pretty interesting stuff :)

### Week 1 - 06/02/2024 - 06/09/2024

1. Setting up razzer. Razzer up until now is not able to compile on host `playground` . So trying docker (I don't want to get into dependency hell).
2. Successful in compiling razzer. It was successful with ubuntu 16.04 with default configurations. Needed some very minor changes in create-image.sh for debootstrap to work in docker.
3. solved lvl4. Learning **trust GDB, IDA can be wrong, GDB cannot be...**
4. **fork keeps the same memory layout as parent so leaking something in parent/child will be good for other sub-processes too** 

### Week 2 - 06/10/2024 - 06/16/2024
1. solved lvl5, lvl6, lvl7, lvl8, and lvl 12. Got Green belt.
2. we can do `fork` syscall using `SYS_CLONE` with flag `SIGCHLD`.
3. never trusting chromium syscall blog table. `SYS_CLONE` arguments were wrong.
5. started afl++ reading.

### Week 3 - 06/17/2024 - 06/22/2024
1. `unlikely` and `likely` macro in afl++ source code. They help compiler to signal if a code block is usually going to be checked or not because of often same result of being true/false. Provides minor performance boost necessary in big codebase.
`long __builtin_expect(long EXP, long C);` tells the compiler that `EXP` will generally have value of `C`. In almost all cases will it be used in the context of boolean expressions in which case it is much more convenient to define two helper macros:
```
#define unlikely(expr) __builtin_expect(!!(expr), 0)
#define likely(expr) __builtin_expect(!!(expr), 1)
```
(from [What every programmer should know about memory](https://www.akkadia.org/drepper/cpumemory.pdf))
2. generate compilation database from `clang` tooling, `bear -- <make command>`
3. trying to test harness coverage.
4. looked into `llvm-cov` too test coverage metric of a harness
5. GoogleCTF 2024. Worked on pycalc challenge. Learned a lot of random things about how python bytecode works. How virtual stack in cpython works. `LOAD_CONST`, `LOAD_ATTR` etc. JIT adaptive bytecode in python 3.11 . Studied some python optamizations in python3.11 

### Week 4 - 06/23/2024 - 06/30/2024
1. Still working on coverage reports and setting up harness for fuzzing.
2. Participated in UIUCTF solo. Solved 500 point challenge from pwn, `syscall`.
3. we can read a file using `mmap` given we can open a file. I used `openat` syscall for that as `open` was blocked. Using sleep, we can carefully craft a sidechannel attack (delay in program) to leak anything.

### Week 5 - 7/1/2024 - 7/7/2024

1. coverage reports for oss-fuzz project `gcloud storage ls gs://oss-fuzz-coverage/latest_report_info/ | grep <PROJECT>`. Then we can do `gcloud storage cat gs:<link_from_json>`
2. oss-fuzz project build status: `https://oss-fuzz-build-logs.storage.googleapis.com/`
3. oss-fuzz fuzz introspector: `https://oss-fuzz-introspector.storage.googleapis.com/index.html`. Introspector index: `https://introspector.oss-fuzz.com/indexing-overview`

### Week 6 - 7/8/2024 - 7/15/2024
1. NOTE: oss-fuzz is not made to fuzz previous versions of projects. Trying to find a way to go around this limitation.
2. Not much research work. Did assignments and solved challenges from old CTF's. Looked at kernel pwn.

### Week7 - 7/16/2024 - 7/23/2024
1. Cool way to use exclusive or (bitwise XOR):
suppose we need to find median of 3 numbers. Normally code for this can be complex but using XOR we can make it straight forward:
```
    input a, b, c
    if (a > b) ^ (a > c):
        a is median
    else if (b > a) ^ (b > c):
        b is median
    else:
        c is median
```

`(a > b) ^ (a > c)` only one should be true. If (a > b) is true and (a > c) is false, it's logically proven that c > a > b. Hence a being median.
2. cool resource:  https://fibonhack.it/resources/pwn
3. imaginary ctf 2024 with ASU HC.
4. To test the harness we can write smaller code rather than testing the reading code base. That's what I did this time. Code base is huge, we can't spend time just reading it and making it work with pre-existing tools, so prove/disprove the hypothesis by small test code.
5. Finally done with community college summer course I was taking. For the final project I had to implement binary search in MIPS assembly. Loved the experience !

### Week8 - 7/24/2024 - 8/16/2024

1. Move out :(

### 8/16/2024 - 8/25/2024

1. Semester started, done with move in.
2. Started format string module on pwncollege.
3. made simple harness.

### 8/26/2024 - 9/1/2024
1. started some algo practice, streak of 11 in 2 days.
2. continued practice on format string 
3. continued making better harness

### 9/1/2024 - 9/7/2024
1. Did leetcode. Learned a new algorithm - toroise and hare 2 pointer algo. Did LRU Cache question.
2. Practiced for interview
3. Read about C++ intrinsics. 
4. Played CSAW ctf with ASU HC. Solved a basic and easy challenge about bash scripting. No pwn solves.
5. Learned a lot about cepstral analysis and sound cryptography.
6. mat343 work 1.2, 1.3. MATLAB lab 1.
7. CSE360 - HW#2

### 9/8/2024 - 9/14/2024
1. Applied in some more internship applications.
2. Did leet. Solved around 4 more questions (1282 and some more i don't remember).
3. Did CSE355 assignment for DFA and NFA construction.
4. Project-1 CSE330.
5. Studied Matrix LU decomposition - MAT343. Did MAT343 work.
6. Did setup for cse360 and hw#3.
7. MAT343 -1.4, 1.5, 2.1.
8. CSE340 HW1. 

### 9/15/2024 - 9/21/2024

1. CSE355 Hw-1. Worked on a lot of DFA and NFA problems. Made a DFA that accepts all binary string divisbile by 5. Really cool problem. I am gonna write a blog post for this in future.
2. Started working on project-1 CSE340. A parser, lexical analyzer and custom regular expression matcher implemented using regular expression graph made using thompson construction of NFA. I will write a blog post about it in future.
3. Went to hacker devils meeting and did leet problem.
4. Recitation 3 CSE355.
5. MAT343 - 2.2, 3.1. MATLAB Lab 2
6. CSE360 - HW#4

### 9/22/2024 - 9/28/2024
1. Project2 CSE330. Wrote a kernel module and custom syscall. Cool project.
2. Continued working on project1 due on 27th. 
3. MAT343 - 3.2.
5. MAT343 Exam on 26th.
6. Heap exploitation module started in CSE466.
7. CSE355 HW2.

### 9/29/2024 - 10/5/2024
1. MAT343 - matlab lab3.
2. Studied pumping lemma, did pumping lemma CSE355 assignment - recitation 5.
3. Studied for CSE355 (on 2nd Oct) and CSE330 (on 7th October.) exam.
4. Revised tcache heap exploitation. 
5. CSE360 - HW#5

### 10/6/2024 - 10/12/2024
1. CSE340 HW2.
2. MAT343 - 3.3, 3.4.
3. CSE340 exam on 9th, Started CSE360 project phase1 9th, after exam, finished successfuly !
4. Did challenged heap exploitation module.

### 10/13/2024 - 10/19/2024
1. heap exploitation all over except last challenge.
2. CSE330 project3 - Wrote code for kernel threads, synchronized producer and consumer using semaphore.
3. CSE355 Recitation 7 and HW3.
4. MAT343 - 3.5, 3.6. 

### 10/20/2024 - 10/26/2024

1. CSE360 HW#6 and midterm exam.
2. CSE355 Recitation 8 and Recitation 9
3. mat343 4.1, 4.2, and lab 4
4. Applied for internship.

### 10/27/2024 - 11/2/2024

1. MAT343 5.1.
2. CSE360 Project phase2.
3. CSE 355 - recitation 10 and HW4.
4. CSE340 HW3.

### 11/3/2024 - 11/9/2024
1. CSE330 project 4.
3. MAT343 Test2 - 5th Nov.
4. CSE355 Test2 - 6th Nov.

