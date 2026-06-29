---
title: "Fuzzing notes"
date: 2026-06-22T00:00:00-00:00
draft: false
math: true
---

> "you are only as good as your last CVE"

### [Parking game fuzzer notes](/notes/parking-game-fuzzer)

## Libfuzzer Template
[clang helper code for fuzzing](https://github.com/llvm/llvm-project/blob/main/compiler-rt/include/fuzzer/FuzzedDataProvider.h)

libfuzzer harness template:

```c
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <string>
#include <vector>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzz(data, size);
    // harness code here

    return 0;
}
```

## AIxCC Team Atlanta notes from VRI (RITSEC)

[Notes](/Team%20Atlanta%20Concise%20Notes.pdf)

## OSS Fuzz introspector 

[https://introspector.oss-fuzz.com/](https://introspector.oss-fuzz.com/)

check project-wise - [https://introspector.oss-fuzz.com/project-profile?project=abseil-cpp](https://introspector.oss-fuzz.com/project-profile?project=abseil-cpp)

## Random Notes 

https://securitylab.github.com/resources/fuzzing-sockets-FTP/ 
- use [preeny](https://github.com/zardus/preeny) as a preloading library, it disables randomization. (especially useful for socket based fuzzing)
- in case of socket based program, remove socket dependancy from software.  `send` <-> `write`. `accept` <-> `input file descriptor`.
- we can use `getrandom` for file upload cases
- avoid using `rmdir` or `unlink` to minimize randomization
- transform multi-process architecture to single process since afl coverage map doesn't receive coverage signal from child process.
- signals should be patched sincle AFL execution is dependant on signals. commenting calls to `alarm(2)` is helpful.
- remove unnecessary delays / sleeps.
- **effective fuzzing requires detailed knowledged of internals of software**
- **Manual code audit. Static analysis. Fuzzing**

## important features that should be present in fuzzers (regularly updated)
- forkserver
- some sort of persitence fuzzing workflow OR inprocess fuzzing (libafl ??)
- good mutation algorithms
- static analysis before fuzzing. Path constraint fuzzing ?
- input replay functionality. Easy to say but sometimes trivial (race conditions)
- cli args ??
- good seed selection / harness generation using AI 
- *i am speed* needless to say - speed is important


