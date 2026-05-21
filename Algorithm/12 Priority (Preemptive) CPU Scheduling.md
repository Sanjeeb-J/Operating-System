
---

## **ALGORITHM: Priority (Preemptive) CPU Scheduling**

### **FUNCTION 1: findHighestPriority()**

**Input:** Array of Process structures `p[]`, integer `n`, and current `current_time`

**Output:** Index of process with highest priority (lowest priority number) that has arrived and has remaining time, or -1 if none available

**Steps:**

1. **START**
    
2. **Declare** variables:
    
    - `min_priority = INT_MAX` (initialize to maximum value)
    - `index = -1` (no process found yet)
3. **Find Process with Highest Priority:**
    
    - Loop from `i = 0` to `i < n`
        - **If** `p[i].arrival_time <= current_time` AND `p[i].remaining_time > 0` **Then**
            - (Process has arrived and still has work to do)
                
            - **If** `p[i].priority < min_priority` **Then**
                
                - (Lower priority number = higher priority)
                - `min_priority = p[i].priority`
                - `index = i`
            - **Else If** `p[i].priority == min_priority` AND `p[i].arrival_time < p[index].arrival_time` **Then**
                
                - (Tie-breaker: choose process that arrived earlier)
                - `index = i`
4. **Return** `index`
    
5. **END**
    

---

### **FUNCTION 2: priorityPreemptiveScheduling()**

**Input:** Array of Process structures `p[]` and integer `n`

**Output:** Array with calculated completion_time, turnaround_time, and waiting_time

**Steps:**

1. **START**
    
2. **Declare** variables:
    
    - `completed = 0` (number of completed processes)
    - `current_time = 0` (current CPU time)
3. **Priority Preemptive Scheduling Loop:**
    
    - **While** `completed < n` **Do**
        - **Call** `findHighestPriority(p, n, current_time)` to get process with highest priority
            
        - Store result in `index`
            
        - **If** `index == -1` **Then**
            
            - (No process has arrived, CPU is idle)
            - `current_time++`
            - **Continue** to next iteration
        - **Execute Process for 1 Unit of Time:**
            
            - `p[index].remaining_time--`
            - (Reduce remaining burst time by 1)
            - (Can be preempted if higher priority process arrives)
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
    
    - Print "PID | AT | BT | PR | CT | TAT | WT"
4. **Print Each Process:**
    
    - Loop from `i = 0` to `i < n`
        - **Print** Process ID, Arrival Time, Burst Time, Priority, Completion Time, Turnaround Time, Waiting Time
        - **Add** turnaround time to `ttt`
        - **Add** waiting time to `twt`
5. **Calculate and Print Averages:**
    
    - **Average Turnaround Time** = `ttt / n`
    - **Average Waiting Time** = `twt / n`
6. **END**
    

---

### **MAIN FUNCTION: main()**

**Input:** Number of processes with their arrival time, burst time, and priority

**Output:** Priority scheduling table with averages

**Steps:**

1. **START**
    
2. **Input Number of Processes:**
    
    - **Read** `n`
3. **Declare** array of Process structures: `p[n]`
    
4. **Input Process Details:**
    
    - Loop from `i = 0` to `i < n`
        - `p[i].id = i + 1`
        - **Read** arrival time, burst time, and priority
        - Store in `p[i].arrival_time`, `p[i].burst_time`, and `p[i].priority`
        - `p[i].remaining_time = p[i].burst_time`
        - (Initialize remaining time to burst time)
5. **Perform Priority Preemptive Scheduling:**
    
    - **Call** `priorityPreemptiveScheduling(p, n)`
6. **Display Results:**
    
    - **Call** `displayProcesses(p, n)`
7. **Return** 0
    
8. **END**
    

---

## **Key Concepts:**

|Term|Explanation|
|---|---|
|**Arrival Time (AT)**|When process arrives in ready queue|
|**Burst Time (BT)**|Total CPU time needed by process|
|**Priority (PR)**|Priority number (lower = higher priority)|
|**Remaining Time**|CPU time still needed|
|**Completion Time (CT)**|When process finishes|
|**Turnaround Time (TAT)**|CT - AT (total time from arrival to completion)|
|**Waiting Time (WT)**|TAT - BT (time spent waiting in ready queue)|
|**Preemptive**|Higher priority process can interrupt lower priority|

---

