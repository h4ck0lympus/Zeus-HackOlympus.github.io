---
title: Lockset mechanism in linux kernel
date: 2024-06-17

---
**Lockset Mechanism in Linux kernel**

1. **Locks:** Prevent multiple threads to access shared resources simultaneously by allowing only one thread to acquire “lock” at a time. When a lock is enabled for a thread, other threads are blocked from accessing the resources/memory.

2. **Spinlocks:** type of lock that busy-wait until lock becomes available. Suitable when wait time is short. Should be used with precaution because takes resources while waiting and can also call deadlocks.

    1. **busywait**: busywait means that the thread will repeatedly check if lock has been removed.  

3. **Mutexes:** This allows threads to block and be put to sleep while waiting for lock to become available. This doesn’t take resources because it is not busywaiting.

4. **Semaphores:** Semaphores maintain count to to represent the number of resources. Process update this count whenever a resource is in use.

    example:

    ```
    semaphore s = 1;
   
    # when thread is using the resource

    s-- ; # decrement s, to signal that it’s in use
    wait(s)
    // do_operation
    
    # after operation is done
    s++; # increment again when lock has been removed
    ```


5. **Atomic Operations:** Some operations don’t need locking mechanism and should always be running in background, atomic operations are these types of operations. They are free from any locks.*

6. **Read-Copy Update(RCU):** RCU is a synchronization mechanism used in linux kernel to manage multiple read of memory synchronously. Particularly usefule where reads significantly outnumber writes.



