
---

## **COMPLETE ALGORITHM: Multi-Threading - Statistical Calculations**

### **FUNCTION 1: find_mean()**

**Input:** Global array `a[]` and integer `n`

**Output:** Global variable `mean` (average of all elements)

**Steps:**

1. **START**
    
2. **Declare** variable `sum = 0`
    
3. **Loop** from `i = 0` to `i < n`
    
    - **Add** `a[i]` to `sum`
4. **Calculate** `mean = sum / n` (convert to float)
    
5. **Exit** thread using `pthread_exit(NULL)`
    
6. **END**
    

---

### **FUNCTION 2: find_median()**

**Input:** Global array `a[]` and integer `n`

**Output:** Global variable `median` (middle value of sorted array)

**Steps:**

1. **START**
    
2. **Sort Array using Bubble Sort:**
    
    - Loop from `i = 0` to `i < n - 1`
        - Loop from `j = i + 1` to `j < n`
            - **If** `a[i] > a[j]` **Then**
                - **Swap:**
                    - `temp = a[i]`
                    - `a[i] = a[j]`
                    - `a[j] = temp`
3. **Find Median:**
    
    - **If** `n % 2 == 0` **Then** (even number of elements)
        - `median = (a[n/2] + a[n/2 - 1]) / 2.0`
    - **Else** (odd number of elements)
        - `median = a[n/2]`
4. **Exit** thread using `pthread_exit(NULL)`
    
5. **END**
    

---

### **FUNCTION 3: find_sd()**

**Input:** Global array `a[]`, integer `n`, and global variable `mean`

**Output:** Global variable `sd` (standard deviation)

**Steps:**

1. **START**
    
2. **Declare** variable `sum = 0`
    
3. **Calculate Sum of Squared Differences:**
    
    - Loop from `i = 0` to `i < n`
        - **Add** `(a[i] - mean)²` to `sum`
        - `sum += (a[i] - mean) * (a[i] - mean)`
4. **Calculate Standard Deviation:**
    
    - `sd = √(sum / n)` using `sqrt()` function
5. **Exit** thread using `pthread_exit(NULL)`
    
6. **END**
    

---

### **MAIN FUNCTION: main()**

**Input:** Command-line arguments (numbers)

**Output:** Mean, Median, and Standard Deviation

**Steps:**

1. **START**
    
2. **Declare** thread identifiers: `t1`, `t2`, `t3`
    
3. **Read Input:**
    
    - **Calculate** `n = argc - 1`
    - **If** `n <= 0` **Then**
        - Print "Enter numbers as command line arguments"
        - Return error code 1
        - **EXIT**
4. **Store Numbers in Array:**
    
    - Loop from `i = 0` to `i < n`
        - `a[i] = atoi(argv[i + 1])` (convert string to integer)
5. **Create Thread 1 (Mean Calculation):**
    
    - **Call** `pthread_create(&t1, NULL, find_mean, NULL)`
6. **Create Thread 2 (Median Calculation):**
    
    - **Call** `pthread_create(&t2, NULL, find_median, NULL)`
7. **Wait for Thread 1 to Complete:**
    
    - **Call** `pthread_join(t1, NULL)`
    - (Now `mean` is calculated, needed for SD calculation)
8. **Create Thread 3 (Standard Deviation Calculation):**
    
    - **Call** `pthread_create(&t3, NULL, find_sd, NULL)`
    - (This can start only after Thread 1 finishes because it needs `mean`)
9. **Wait for Thread 2 to Complete:**
    
    - **Call** `pthread_join(t2, NULL)`
10. **Wait for Thread 3 to Complete:**
    
    - **Call** `pthread_join(t3, NULL)`
11. **Output Results:**
    
    - **Print** `Mean =` with 2 decimal places
    - **Print** `Median =` with 2 decimal places
    - **Print** `Standard Deviation =` with 2 decimal places
12. **Return** 0
    
13. **END**
    

---

## **How to Execute:**

```bash
# Compile with pthread and math libraries
gcc program.c -o program -lpthread -lm

# Run with numbers
./program 10 20 30 40 50
```

**Output:**

```
Mean = 30.00
Median = 30.00
Standard Deviation = 14.14
```

---

## **Example Calculations (for 10, 20, 30, 40, 50):**

**Mean:**

- Sum = 10 + 20 + 30 + 40 + 50 = 150
- Mean = 150 / 5 = 30.00

**Median (Already sorted):**

- Sorted array: [10, 20, 30, 40, 50]
- n = 5 (odd)
- Median = a[5/2] = a[2] = 30.00

**Standard Deviation:**

- (10-30)² = 400
- (20-30)² = 100
- (30-30)² = 0
- (40-30)² = 100
- (50-30)² = 400
- Sum = 1000
- SD = √(1000/5) = √200 = 14.14
