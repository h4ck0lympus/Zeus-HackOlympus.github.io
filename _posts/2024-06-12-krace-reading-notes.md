---
layout: post
title: KRACE reading notes
date: 2024-06-12 16:38 -0700
---

These are very rough notes on [KRACE paper](https://ieeexplore.ieee.org/abstract/document/9152693) 

### Coverage guided fuzzing in KRACE

New coverage metric: alias instruction pair coverage, or alias coverage.

1. Branch coverage
2. Collect all pairs of memory access instructions X <-> Y such that X may be interfering with memory being written by Y at one time.

### Input Generation in KRACE

1. Basically has the same philosophy as syzkaller. Uses a combination of syscalls and mutates on it.

2. Novel part: 
    A) multi threaded seeds (seeds are initial input to a fuzzer that is further modified) In the case of KRACE, seeds start at multiple threads. 
    B) KRACE preserve the the threads will interleave(combining or alternating execution of threads) in already found coverage. 
    C) Input generator also produce thread scheduling, it does it by employing delay injection scheme and relies on alias coverage metric to determine whether more delay is needed or not. (this scheduling cannot be employed on the whole kernel concurrency)

### KRACE Bug manifestation/identification

KRACE hooks every memory access and for each pair of accesses to the same memory address, It checks if :

1. belong to 2 threads and at least one should be memory-write
2. strictly ordered access to memory.
3. if a shared lock exists that guards such access.-.

Every execution is a fresh run from a clean-slate kernel.

Bug checker doesn't run all the time, but only when new coverage is reported.

### Alias coverage working

When keeping track of coverage while fuzzing concurrent programs we can't just keep track of code paths explored but, we also need to keep track of possible thread interleavings explored.

1. label all memory-accessing instructions in a program: `i1, i2, i3, ... iN`.
2. Each memory address `M` keeps track  of it's last write operation and context, represented by `A <- <ix, tx>`. If new access to `M` is observed, from instruction `iy`, context ty: update `A <- <iy, ty>`. Otherwise, if tx = ty do nothing, else record directed pair ix->iy.

### Feedback Mechanism to alias coverage fuzzing

If the alias coverage keeps growing, the fuzzer should come up with more delay schdules, otherwise the if the coverage growth stalls, it is a sign that current test case heading towards a saturations and it switch to other seed.

### Input generation in fuzzing

A single list of syscalls that is called as main list. This main list comprises of sublist which define per-thread syscall. Each sublist contains disjoint sequence of syscall in main list.

Input generation occurs in a way that syscalls that order of syscalls remains preserved.

Evolution strategies are mutation (syscall arguments are mutated.), addtition (new syscall are added), deletion (syscall are deleted) and shuffling.

Shuffling means syscalls order in main list is preserved, but in sublist they are shuffled. So basically they are redistributed to explored different possible thread interleavings.

### Thread scheduling control

At runtime, delay is injected between 2 or more syscalls. "Before launching the kernel, KRACE generates a ring buffer of random numbers and maps it to the kernel address space. At every memory access point, the instrumented code fetches a random number from the ring buffer, say T, and delays for T memory accesses observed by KRACE system-wise" (KRACE paper).

### Data race detection

Say we have 2 memory operations, `<ix, iy>` , They both are potential data race candidate if they access same memory location. They are issued from different context `tx` and `ty` and atleast one of them is a write operation.

#### Lockset Analysis

Set of locks acquired for reading purpose by a thread t and instruction i is stored in a set known as reader-side lockset denoted by LSR<t, i>
Similiarly for writing purpose a set is knwn as writer-side lock set denoted by LSW<t, i>

If read operations of thread 1 on memory cell M doesn't intersect with write operations of thread 2.

or vice versa

Or if write operations of both thread don't intersect
