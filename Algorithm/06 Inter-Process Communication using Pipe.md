
---

## **ALGORITHM: Inter-Process Communication using Pipe**

**Input:** Three integers a, b, c

**Output:** Values of b², 4ac, and √(b² - 4ac)

**Steps:**

1. **START**
    
2. **Declare** array `fd[2]` for pipe file descriptors, and variables `a`, `b`, `c`, `four_ac`, `b_square`, `result`
    
3. **Input:** Read three integers `a`, `b`, `c` from user
    
4. **Create Pipe:** Call `pipe(fd)` function
    
    - **If** pipe creation fails **Then**
        - Print "Pipe creation failed"
        - Return error code 1
        - **EXIT**
5. **Create Child Process:** Call `fork()` function
    
6. **If** `fork() == 0` **Then** (Child Process)
    
    - **Close** read end of pipe: `close(fd[0])`
    - **Calculate** `four_ac = 4 * a * c`
    - **Write** `four_ac` value to pipe using `write(fd[1], &four_ac, sizeof(four_ac))`
    - **Close** write end of pipe: `close(fd[1])`
7. **Else** (Parent Process)
    
    - **Close** write end of pipe: `close(fd[1])`
    - **Calculate** `b_square = b * b`
    - **Read** `four_ac` value from pipe using `read(fd[0], &four_ac, sizeof(four_ac))`
    - **Close** read end of pipe: `close(fd[0])`
    - **Calculate** `result = √(b_square - four_ac)` using `sqrt()` function
    - **Print** `b_square`
    - **Print** `four_ac`
    - **Print** `result`
8. **Return** 0
    
9. **END**
    

---

## **How to Execute:**

```bash
# Compile with math library
gcc program.c -o program -lm

# Run
./program
```

**Example Output:**

```
Enter values of a, b and c: 1 5 6
b^2 = 25
4ac = 24
Result = sqrt(b^2 - 4ac) = 1.00
```

---

## **Key Concepts:**

| Concept      | Explanation                                          |
| ------------ | ---------------------------------------------------- |
| **Pipe**     | Creates communication channel between parent & child |
| **fd[0]**    | Read end of pipe                                     |
| **fd[1]**    | Write end of pipe                                    |
| **write()**  | Child sends data through pipe                        |
| **read()**   | Parent receives data from pipe                       |
| **close()**  | Closes unused file descriptors                       |
| **-lm flag** | Links math library for `sqrt()` function             |

