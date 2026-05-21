
---

## **ALGORITHM: Process Creation using Fork()**

**Input:** None

**Output:** Process information (PID details)

**Steps:**

1. **START**
    
2. **Declare** a variable `pid` of type `pid_t` (process ID)
    
3. **Call** `fork()` function and store the return value in `pid`
    
4. **If** `pid < 0` **then**
    
    - Print message "Fork failed"
    
    **Else If** `pid == 0` **then**
    
    - This is the **Child Process**
    - Print message "Child process"
    - Print child's own PID using `getpid()`
    - Print parent's PID using `getppid()`
    - Sleep for 50 seconds
    
    **Else** (i.e., `pid > 0`)
    
    - This is the **Parent Process**
    - Print message "Parent process"
    - Print parent's own PID using `getpid()`
    - Print the child's PID (value stored in `pid`)
    - Sleep for 50 seconds
5. **END**
    

---
