---
title: "Fuzzing notes"
date: 2026-06-22T00:00:00-00:00
draft: false
math: true
---

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

## OSS Fuzz introspector 

[https://introspector.oss-fuzz.com/](https://introspector.oss-fuzz.com/)

check project vise ex - [https://introspector.oss-fuzz.com/project-profile?project=abseil-cpp](https://introspector.oss-fuzz.com/project-profile?project=abseil-cpp)


