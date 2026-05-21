## **ALGORITHM: Command-Line Addition**

1. START
    
2. Declare integer variables `a`, `b`
    
3. Check whether `argc != 3`
    
4. If true, print usage message and EXIT
    
5. Convert `argv[1]` to integer and store in `a`
    
6. Convert `argv[2]` to integer and store in `b`
    
7. Calculate `sum = a + b`
    
8. Print the value of `sum`
    
9. Return 0
    
10. END
    

---

## **ALGORITHM: Process Creation and Execution**

1. START
    
2. Declare variable `pid` of type `pid_t`
    
3. Check whether `argc != 3`
    
4. If true, print usage message and EXIT
    
5. Call `fork()` and store result in `pid`
    
6. Check whether `pid < 0`
    
7. If true, print error message and EXIT
    
8. If `pid == 0`
    
    - Create argument array
        
    - Store `"./add"` in first position
        
    - Store `argv[1]` and `argv[2]` in next positions
        
    - Store `NULL` at end of array
        
    - Print child process message
        
    - Call `execvp()` to execute add program
        
    - Print error if `execvp()` fails
        
9. Else
    
    - Print parent process message
        
10. Return 0
    
11. END

```
// Compile both
gcc add.c -o add
gcc adder.c -o myadder

// Run
./myadder 10 20
```
