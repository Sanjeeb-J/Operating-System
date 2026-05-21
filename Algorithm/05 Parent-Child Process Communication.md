
---

## **ALGORITHM: Parent-Child Process Communication**

**Input:** None

**Output:** Text messages from parent and child processes

**Steps:**

1. **START**
    
2. **Declare** variable `pid` of type `pid_t`
    
3. **Call** `fork()` function and store return value in `pid`
    
4. **If** `pid < 0` **Then**
    
    - Print error message "Fork failed"
    - Return error code 1
    - **EXIT**
5. **Else If** `pid == 0` **Then** (Child Process)
    
    - Print "PCCSL407 "
    - Child process continues
6. **Else** (Parent Process, `pid > 0`)
    
    - **Call** `wait(NULL)` to wait for child process to complete
    - Print "Operating Systems Lab"
7. **Return** 0 (success)
    
8. **END**
    

---

## **How to Execute:**

```bash
# Compile
gcc program.c -o program

# Run
./program
```

**Output:**

```
PCCSL407 Operating Systems Lab
```

---

## **Why wait(NULL) is important:**

The `wait(NULL)` ensures the **parent waits** for the child to finish printing before the parent prints. Without it, the output order would be unpredictable! ✅