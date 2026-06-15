+++
title = 'Software Hardening'
date = '2026-06-15'
draft = false
+++

# Memory Tagging

- tag memory with unique "color" everytime `malloc()` or `free()` is called. 
- encode tag inside ptrs (returned by malloc) :
- 
    ```
    if pointer_tag != memory_tag:
        crash()
    ```

![OOB detection](/images/oob-mte-demo.png)
![UAF detection](/images/oob-mte-demo.png)

- 2 problems: performance (due to repeated checking). User inconvinience (buggy apps will straight up crash).
- check if chip supports ADB `adb shell grep mte /proc/cpuinfo`
- **vulnerable to side-channel attacks**
- 64 bit ARM pointer layout:

```
Bit:     63          60 59          56 55                         0
         +--------------+--------------+---------------------------+
Pointer: | upper nibble | logical tag  | actual virtual address    |
         +--------------+--------------+---------------------------+
                           4 bits
```

- `uint8_t logical_tag = (pointer >> 56) & 0xF;`
- we can allocate MTE memory/page by using `PROT_MTE` allocation tag in MTE supported hardware.
- multiple behaviors possible in case of tag mismatch:
* ignore - default mode.
* synchronous - SIGSESV called right there and then when the mismatch happens and process halts.
* asynchronous - SIGSEV is recorded and raised after process has ended. Memory access doesn't occur. Not good for debugging, will not return fault address.
* asymmetric mode : 
    * read with mismatched tag - handled synchronously
    * write with mismatched tag - handled asynchronously
    * 
```
    if (pointer_tag != memory_tag) {
    if (operation == READ) {
        raise_precise_SIGSEGV_now();
    } else if (operation == WRITE) {
        record_pending_fault();
        continue_execution();
    }
}
```

**References:**
1. https://thore.io/posts/2025/09/introduction-to-arm-memory-tagging-extensions/
2. https://docs.google.com/presentation/d/10V_msbtEap9dNerKvTrRAzvfzYdrQFC8e2NYHCZYJDE/view
3. https://www.kernel.org/doc/html/v6.12/arch/arm64/memory-tagging-extension.html
4. linux kernel docs - https://www.kernel.org/doc/html/v6.12/arch/arm64/memory-tagging-extension.html

# Pointer authentication (PAC)

TODO

# Control Flow Integrity (CFI)

TODO

## BTI

TODO

## Shadow Stack

TODO


# Smart Pointers in C++


