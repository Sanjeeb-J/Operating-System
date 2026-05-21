```c
#include <stdio.h>
#include <stdbool.h>  

#define MAX 100

struct Process {
  int id, arrival_time, burst_time;
  int remaining_time, waiting_time, turnaround_time, completion_time;
};

int queue[MAX], front = 0, rear = 0;
```

---

## **ALGORITHM: Round Robin (RR) CPU Scheduling**

### **FUNCTION 1: enqueue()**

**Input:** Process ID `pid`

**Output:** Adds process to rear of queue

**Steps:**

1. **START**
    
2. **Add** process ID to `queue[rear]`
    
3. **Increment** `rear++`
    
4. **END**
    
```c
void enqueue(int pid)
{
  queue[rear++] = pid;
}
```

---

### **FUNCTION 2: dequeue()**

**Input:** None

**Output:** Process ID from front of queue, or -1 if queue is empty

**Steps:**

1. **START**
    
2. **If** `front == rear` **Then**
    
    - **Return** -1 (queue is empty)
3. **Else**
    
    - **Get** process ID from `queue[front]`
    - **Increment** `front++`
    - **Return** process ID
4. **END**
    
```c
int dequeue()
{
  if (front == rear)
    return -1;
  return queue[front++];
}
```

---

### **FUNCTION 3: isEmpty()**

**Input:** None

**Output:** True if queue is empty, False otherwise

**Steps:**

1. **START**
    
2. **If** `front == rear` **Then**
    
    - **Return** True
3. **Else**
    
    - **Return** False
4. **END**
    
```c
bool isEmpty()
{
  return front == rear;
}
```

---

### **FUNCTION 4: isInQueue()**

**Input:** Process ID `pid`

**Output:** True if process is in queue, False otherwise

**Steps:**

1. **START**
    
2. **Loop** from `i = front` to `i < rear`
    
    - **If** `queue[i] == pid` **Then**
        - **Return** True
3. **Return** False (process not found)
    
4. **END**
    

---

### **FUNCTION 5: roundRobin()**

**Input:** Array of Process structures `p[]`, integer `n` (number of processes), integer `time_quantum`

**Output:** Array with calculated completion_time, turnaround_time, and waiting_time; prints results

**Steps:**

1. **START**
    
2. **Declare** variables:
    
    - `time = 0` (current CPU time)
    - `completed = 0` (number of completed processes)
    - `visited[n]` (array to track enqueued processes)
    - `total_wt = 0`, `total_tat = 0` (for averages)
3. **Initialize Visited Array:**
    
    - Loop from `i = 0` to `i < n`
        - `visited[i] = false`
4. **Enqueue Initial Processes:**
    
    - Loop from `i = 0` to `i < n`
        - **If** `p[i].arrival_time == 0` **Then**
            - **Call** `enqueue(i)`
            - `visited[i] = true`
5. **Round Robin Scheduling Loop:**
    
    - **While** `completed < n` **Do**
        
        - **If** queue is empty **Then**
            
            - `time++`
            - **Check for New Arrivals:** Loop from `j = 0` to `j < n`
                - **If** `p[j].arrival_time <= time` AND `p[j].remaining_time > 0` AND `!visited[j]` **Then**
                    - **Call** `enqueue(j)`
                    - `visited[j] = true`
            - **Continue** to next iteration
        - **Dequeue Process:** `i = dequeue()`
            
        - **Execute Process for Time Quantum:**
            
            - **If** `p[i].remaining_time > time_quantum` **Then**
                - `time += time_quantum`
                - `p[i].remaining_time -= time_quantum`
            - **Else**
                - `time += p[i].remaining_time`
                - `p[i].completion_time = time`
                - `p[i].remaining_time = 0`
                - `completed++`
        - **Check for New Arrivals During This Time:**
            
            - Loop from `j = 0` to `j < n`
                - **If** `p[j].arrival_time <= time` AND `p[j].remaining_time > 0` AND `!visited[j]` **Then**
                    - **Call** `enqueue(j)`
                    - `visited[j] = true`
        - **Re-enqueue Current Process if Not Done:**
            
            - **If** `p[i].remaining_time > 0` **Then**
                - **Call** `enqueue(i)`
6. **Calculate Metrics:**
    
    - Loop from `i = 0` to `i < n`
        - `p[i].turnaround_time = p[i].completion_time - p[i].arrival_time`
        - `p[i].waiting_time = p[i].turnaround_time - p[i].burst_time`
        - `total_wt += p[i].waiting_time`
        - `total_tat += p[i].turnaround_time`
7. **Print Results:**
    
    - **Print** Table header: "PID | AT | BT | CT | TAT | WT"
    - Loop through all processes and print their details
    - **Print** "Average Waiting Time" = `total_wt / n`
    - **Print** "Average Turnaround Time" = `total_tat / n`
8. **END**
    
```c
void roundRobin(struct Process p[], int n, int time_quantum)
{
  int time = 0, completed = 0;
  float total_wt = 0, total_tat = 0;
  bool visited[n];

  for (int i = 0; i < n; i++)
    visited[i] = false;

  // Enqueue all processes that arrive at time 0
  for (int i = 0; i < n; i++)
  {
    if (p[i].arrival_time == 0)
    {
      enqueue(i);
      visited[i] = true;
    }
  }

  while (completed < n)
  {
    if (isEmpty())
    {
      time++;
      for (int i = 0; i < n; i++)
      {
        if (p[i].arrival_time <= time && p[i].remaining_time > 0 && !visited[i])
        {
          enqueue(i);
          visited[i] = true;
        }
      }
      continue;
    }

    int i = dequeue();

    if (p[i].remaining_time > time_quantum)
    {
      time += time_quantum;
      p[i].remaining_time -= time_quantum;
    }
    else
    {
      time += p[i].remaining_time;
      p[i].completion_time = time;
      p[i].remaining_time = 0;
      completed++;
    }

    // Enqueue new arrivals during this time
    for (int j = 0; j < n; j++)
    {
      if (p[j].arrival_time <= time && p[j].remaining_time > 0 && !visited[j])
      {
        enqueue(j);
        visited[j] = true;
      }
    }

    // Re-enqueue current process if it's not done
    if (p[i].remaining_time > 0)
    {
      enqueue(i);
    }
  }

  // Now calculate TAT and WT using completion time
  for (int i = 0; i < n; i++)
  {
    p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
    total_wt += p[i].waiting_time;
    total_tat += p[i].turnaround_time;
  }

  // Display results
  printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++)
  {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n",
           p[i].id, p[i].arrival_time, p[i].burst_time,
           p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
  }

  printf("\nAverage Waiting Time: %.2f", total_wt / n);
  printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}
```

---

### **MAIN FUNCTION: main()**

**Input:** Number of processes, arrival times, burst times, and time quantum

**Output:** Round Robin scheduling table with averages

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
5. **Input Time Quantum:**
    
    - **Read** `time_quantum`
6. **Perform Round Robin Scheduling:**
    
    - **Call** `roundRobin(p, n, time_quantum)`
7. **Return** 0
    
8. **END**
    
```c
int main()
{
  int n, time_quantum;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  struct Process p[n];

  printf("Enter arrival time and burst time for each process:\n");
  for (int i = 0; i < n; i++)
  {
    p[i].id = i + 1;
    printf("Process %d (AT BT): ", p[i].id);
    scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    p[i].remaining_time = p[i].burst_time;
  }

  printf("Enter time quantum: ");
  scanf("%d", &time_quantum);

  roundRobin(p, n, time_quantum);

  return 0;
}
```

---

## **Key Concepts:**

|Term|Formula|Explanation|
|---|---|---|
|**Arrival Time (AT)**|Given|When process arrives in ready queue|
|**Burst Time (BT)**|Given|Total CPU time needed by process|
|**Time Quantum (TQ)**|Given|Maximum time slice for each process|
|**Remaining Time**|BT - (executed time)|CPU time still needed|
|**Completion Time (CT)**|When remaining_time = 0|When process finishes|
|**Turnaround Time (TAT)**|CT - AT|Total time from arrival to completion|
|**Waiting Time (WT)**|TAT - BT|Time spent waiting in ready queue|
|**Queue**|FIFO|First In First Out data structure|

---
