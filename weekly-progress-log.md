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

### Week 1 - 06/02/2024 - 06/08/2024

1. Setting up razzer. Razzer up until now is not able to compile on host `playground` . So trying docker (I don't want to get into dependency hell).
2. Successful in compiling razzer. It was successful with ubuntu 16.04 with default configurations. Needed some very minor changes in create-image.sh for debootstrap to work in docker.
3. solved lvl4. Learning **trust GDB, IDA can be wrong, GDB cannot be...**
4. **fork keeps the same memory layout as parent so leaking something in parent/child will be good for other sub-processes too** 
