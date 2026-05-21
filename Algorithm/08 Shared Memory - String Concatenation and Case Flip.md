
---

## **ALGORITHM: Shared Memory - String Concatenation and Case Flip**

**Input:** Three strings from user

**Output:** Concatenated strings with flipped case (uppercase ↔ lowercase)

**Steps:**

1. **START**
    
2. **Declare** variables: `shmid` (shared memory ID), `shm` (pointer to shared memory), `pid` (process ID), `i` (loop counter), `final[]` (final result array)
    
3. **Create Shared Memory:**
    
    - **Call** `shmget(IPC_PRIVATE, SIZE, 0666 | IPC_CREAT)` to create shared memory segment
    - Store returned ID in `shmid`
    - **If** `shmid < 0` **Then**
        - Print error message "shmget"
        - Exit with error code 1
4. **Attach Shared Memory:**
    
    - **Call** `shmat(shmid, NULL, 0)` to attach shared memory to process
    - Store returned pointer in `shm`
    - **If** `shm == (char *)-1` **Then**
        - Print error message "shmat"
        - Exit with error code 1
5. **Parent Process - Read Input:**
    
    - **Input:** Read first string into `shm` (offset 0)
    - **Input:** Read second string into `shm + 100` (offset 100)
    - **Input:** Read third string into `shm + 200` (offset 200)
6. **Create Child Process:** Call `fork()` and store return value in `pid`
    
7. **If** `pid == 0` **Then** (Child Process)
    
    - **Declare** `result[]` array
    - **Copy** first string from `shm` to `result`
    - **Concatenate** space to `result`
    - **Concatenate** second string from `shm + 100` to `result`
    - **Concatenate** space to `result`
    - **Concatenate** third string from `shm + 200` to `result`
    - **Copy** concatenated `result` to `shm + 300` (send back to parent)
    - **Detach** shared memory: **Call** `shmdt(shm)`
    - **Exit** child process with code 0
8. **Else** (Parent Process, `pid > 0`)
    
    - **Wait** for child process to complete: **Call** `wait(NULL)`
    - **Copy** result from `shm + 300` to `final`
    - **Flip Case:** Loop through each character in `final` (from `i = 0` to end)
        - **If** character is lowercase **Then**
            - Convert to uppercase using `toupper()`
        - **Else If** character is uppercase **Then**
            - Convert to lowercase using `tolower()`
    - **Print** final output
    - **Detach** shared memory: **Call** `shmdt(shm)`
    - **Remove** shared memory: **Call** `shmctl(shmid, IPC_RMID, NULL)`
9. **Return** 0
    
10. **END**
    

---

## **How to Execute:**

```bash
# Compile
gcc program.c -o program

# Run
./program
```

**Example Output:**

```
Enter first string: hello
Enter second string: world
Enter third string: test

Final Output: HELLO WORLD TEST
```

---

## **Shared Memory Layout:**

```
Memory Offset:
[0-99]       → First string
[100-199]    → Second string
[200-299]    → Third string
[300-599]    → Final concatenated result
```

---

## **Key Concepts:**

|Concept|Explanation|
|---|---|
|**Shared Memory**|IPC mechanism allowing multiple processes to access same memory|
|**shmget()**|Creates/accesses shared memory segment|
|**shmat()**|Attaches shared memory to process address space|
|**shmdt()**|Detaches shared memory from process|
|**shmctl()**|Controls shared memory (IPC_RMID removes it)|
|**IPC_PRIVATE**|Creates new private shared memory segment|
|**strcat()**|Concatenates strings|
|**toupper()**|Converts character to uppercase|
|**tolower()**|Converts character to lowercase|
|**islower()**|Checks if character is lowercase|
|**isupper()**|Checks if character is uppercase|

