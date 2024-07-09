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

