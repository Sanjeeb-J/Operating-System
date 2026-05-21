

---

## **ALGORITHM: SRT (Shortest Remaining Time) CPU Scheduling**

### **FUNCTION 1: findNextProcess()**

**Input:** Array of Process structures `p[]`, integer `n`, and current `current_time`

**Output:** Index of process with shortest remaining time (that has arrived), or -1 if none available

**Steps:**

1. **START**
    
2. **Declare** variables:
    
    - `min_time = INT_MAX` (initialize to maximum value)
    - `index = -1` (no process found yet)
3. **Find Process with Minimum Remaining Time:**
    
    - Loop from `i = 0` to `i < n`
        - **If** `p[i].arrival_time <= current_time` AND `p[i].remaining_time > 0` **Then**
            - (Process has arrived and still has work to do)
                
            - **If** `p[i].remaining_time < min_time` **Then**
                
                - `min_time = p[i].remaining_time`
                - `index = i`
            - **Else If** `p[i].remaining_time == min_time` AND `p[i].arrival_time < p[index].arrival_time` **Then**
                
                - (Tie-breaker: choose process that arrived earlier)
                - `index = i`
4. **Return** `index`
    
5. **END**
    

---

### **FUNCTION 2: srtScheduling()**

**Input:** Array of Process structures `p[]` and integer `n`

**Output:** Array with calculated completion_time, turnaround_time, and waiting_time

**Steps:**

1. **START**
    
2. **Declare** variables:
    
    - `completed = 0` (number of completed processes)
    - `current_time = 0` (current CPU time)
3. **SRT Scheduling Loop:**
    
    - **While** `completed < n` **Do**
        - **Call** `findNextProcess(p, n, current_time)` to get index of next process
            
        - Store result in `index`
            
        - **If** `index == -1` **Then**
            
            - (No process has arrived, CPU is idle)
            - `current_time++`
            - **Continue** to next iteration
        - **Execute Process for 1 Unit of Time:**
            
            - `p[index].remaining_time--`
            - (Reduce remaining burst time by 1)
        - **If** `p[index].remaining_time == 0` **Then**
            
            - (Process is complete)
            - `p[index].completion_time = current_time + 1`
            - `p[index].turnaround_time = p[index].completion_time - p[index].arrival_time`
            - `p[index].waiting_time = p[index].turnaround_time - p[index].burst_time`
            - `completed++`
        - `current_time++`
            
        - (Move to next time unit)
            
4. **END**
    

---

### **FUNCTION 3: displayProcesses()**

**Input:** Array of Process structures `p[]` and integer `n`

**Output:** Table of all processes with their metrics and averages

**Steps:**

1. **START**
    
2. **Declare** variables:
    
    - `ttt = 0` (total turnaround time)
    - `twt = 0` (total waiting time)
3. **Print Table Header:**
    
    - Print "PID | AT | BT | CT | TAT | WT"
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

**Output:** SRT scheduling table with averages

**Steps:**

1. **START**
    
2. **Input Number of Processes:**
    
    - **Read** `n`
3. **Declare** array of Process structures: `p[n]`
    
4. **Input Process Details:**
    
    - Loop from `i = 0` to `i < n`
        - `p[i].id = i + 1`
        - **Read** arrival time and burst time
        - Store in `p[i].arrival_time` and `p[i].burst_time`
        - `p[i].remaining_time = p[i].burst_time`
        - (Initialize remaining time to burst time)
5. **Perform SRT Scheduling:**
    
    - **Call** `srtScheduling(p, n)`
6. **Display Results:**
    
    - **Call** `displayProcesses(p, n)`
7. **Return** 0
    
8. **END**
    

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
|**Burst Time (BT)**|Given|Total CPU time needed by process|
|**Remaining Time**|BT - (executed time)|CPU time still needed|
|**Completion Time (CT)**|When remaining_time = 0|When process finishes|
|**Turnaround Time (TAT)**|CT - AT|Total time from arrival to completion|
|**Waiting Time (WT)**|TAT - BT|Time spent waiting in ready queue|
|**SRT**|Shortest Remaining Time|Process with least remaining time executes next|

---
