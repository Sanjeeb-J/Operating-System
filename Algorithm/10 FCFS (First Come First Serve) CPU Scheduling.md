
---

## **ALGORITHM: FCFS (First Come First Serve) CPU Scheduling**

### **FUNCTION 1: sortByArrival()**

**Input:** Array of Process structures `p[]` and integer `n` (number of processes)

**Output:** Array sorted by arrival time in ascending order

**Steps:**

1. **START**
    
2. **Bubble Sort by Arrival Time:**
    
    - Loop from `i = 0` to `i < n - 1`
        - Loop from `j = 0` to `j < n - i - 1`
            - **If** `p[j].arrival_time > p[j + 1].arrival_time` **Then**
                - **Swap** processes:
                    - `temp = p[j]`
                    - `p[j] = p[j + 1]`
                    - `p[j + 1] = temp`
3. **END**
    

---

### **FUNCTION 2: fcfsScheduling()**

**Input:** Array of Process structures `p[]` and integer `n`

**Output:** Array with calculated completion_time, turnaround_time, and waiting_time

**Steps:**

1. **START**
    
2. **Declare** variable `current_time = 0`
    
3. **Process Each Job (FCFS Logic):**
    
    - Loop from `i = 0` to `i < n`
        - **If** `current_time < p[i].arrival_time` **Then**
            - `current_time = p[i].arrival_time`
            - (CPU is idle, so start when process arrives)
        - **Calculate Completion Time:**
            - `p[i].completion_time = current_time + p[i].burst_time`
        - **Calculate Turnaround Time:**
            - `p[i].turnaround_time = p[i].completion_time - p[i].arrival_time`
        - **Calculate Waiting Time:**
            - `p[i].waiting_time = p[i].turnaround_time - p[i].burst_time`
        - **Update Current Time:**
            - `current_time = p[i].completion_time`
4. **END**
    

---

### **FUNCTION 3: displayProcesses()**

**Input:** Array of Process structures `p[]` and integer `n`

**Output:** Table of all processes with their metrics and averages

**Steps:**

1. **START**
    
2. **Print Table Header:**
    
    - Print "PID | AT | BT | CT | TAT | WT"
3. **Declare** variables:
    
    - `ttt = 0` (total turnaround time)
    - `twt = 0` (total waiting time)
4. **Print Each Process:**
    
    - Loop from `i = 0` to `i < n`
        - **Print** Process ID, Arrival Time, Burst Time, Completion Time, Turnaround Time, Waiting Time
        - **Add** turnaround time to `ttt`
        - **Add** waiting time to `twt`
5. **Calculate and Print Averages:**
    
    - **Average Turnaround Time** = `ttt / n`
    - **Average Waiting Time** = `twt / n`
6. **END**
    

---

### **MAIN FUNCTION: main()**

**Input:** Number of processes and their arrival times and burst times

**Output:** Scheduling table with averages

**Steps:**

1. **START**
    
2. **Input Number of Processes:**
    
    - **Read** `n` (number of processes)
3. **Declare** array of Process structures: `p[n]`
    
4. **Input Process Details:**
    
    - Loop from `i = 0` to `i < n`
        - `p[i].id = i + 1`
        - **Read** arrival time and burst time for each process
        - Store in `p[i].arrival_time` and `p[i].burst_time`
5. **Sort by Arrival Time:**
    
    - **Call** `sortByArrival(p, n)`
6. **Perform FCFS Scheduling:**
    
    - **Call** `fcfsScheduling(p, n)`
7. **Display Results:**
    
    - **Call** `displayProcesses(p, n)`
8. **Return** 0
    
9. **END**
    

---

## **How to Execute:**

```bash
# Compile
gcc program.c -o program

# Run
./program
```

---

## **Key Concepts:**

|Term|Formula|Explanation|
|---|---|---|
|**Arrival Time (AT)**|Given|When process arrives in ready queue|
|**Burst Time (BT)**|Given|CPU time needed by process|
|**Completion Time (CT)**|max(current_time, AT) + BT|When process finishes|
|**Turnaround Time (TAT)**|CT - AT|Total time from arrival to completion|
|**Waiting Time (WT)**|TAT - BT|Time spent waiting in ready queue|
|**FCFS**|First Come First Serve|Processes execute in arrival order|

---
