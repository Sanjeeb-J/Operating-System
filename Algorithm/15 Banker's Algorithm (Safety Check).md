
---

## **ALGORITHM: Banker's Algorithm (Safety Check)**

**Input:**

- Number of processes (n)
- Number of resource types (m)
- Allocation Matrix
- Maximum Matrix
- Available Resources array

**Output:**

- Safe sequence if system is in safe state
- "NOT in safe state" if deadlock possible

**Steps:**

1. **START**
```c
#include <stdio.h>
#define MAX 10
```
1. **Input Data:**
    
    - **Read** `n` (number of processes)
    - **Read** `m` (number of resource types)
    - **Read** Allocation Matrix `alloc[n][m]` (resources currently allocated to each process)
    - **Read** Maximum Matrix `max[n][m]` (maximum resources each process can request)
    - **Read** Available Resources array `avail[m]` (free resources available)
```c
  int n, m; // n = processes, m = resources
  int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
  int avail[MAX], finish[MAX], safeSeq[MAX];
  int i, j, count = 0;
  
  printf("Enter number of processes: ");
  scanf("%d", &n);

  printf("Enter number of resource types: ");
  scanf("%d", &m);
  
  printf("Enter Allocation Matrix:\n");
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      scanf("%d", &alloc[i][j]);

  printf("Enter Maximum Matrix:\n");
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      scanf("%d", &max[i][j]);

  printf("Enter Available Resources:\n");
  for (j = 0; j < m; j++)
    scanf("%d", &avail[j]);
```
1. **Calculate Need Matrix:**
    
    - Loop from `i = 0` to `i < n`
        - Loop from `j = 0` to `j < m`
            - `need[i][j] = max[i][j] - alloc[i][j]`
            - (Resources still needed by each process)
```c
for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      need[i][j] = max[i][j] - alloc[i][j];
```
1. **Initialize Finish Array:**
    
    - Loop from `i = 0` to `i < n`
        - `finish[i] = 0` (mark all processes as not finished)
```c
for (i = 0; i < n; i++)
    finish[i] = 0;
```
1. **Initialize Safe Sequence Counter:**
    
    - `count = 0`
2. **Find Safe Sequence (Banker's Algorithm Loop):**
    
    - **While** `count < n` **Do**
        
        - **Declare** `found = 0`
            
        - **Loop through processes** from `i = 0` to `i < n`
            
            - **If** `finish[i] == 0` **Then**
                - (Process not yet finished)
                    
                - **Declare** `flag = 1`
                    
                - **Check if process can be satisfied:**
                    
                    - Loop from `j = 0` to `j < m`
                        - **If** `need[i][j] > avail[j]` **Then**
                            - (Process needs more resources than available)
                            - `flag = 0`
                            - **Break** from loop
                - **If** `flag == 1` **Then**
                    
                    - (Process can be satisfied)
                        
                    - **Add** process to safe sequence: `safeSeq[count++] = i`
                        
                    - **Release Resources:**
                        
                        - Loop from `j = 0` to `j < m`
                            - `avail[j] += alloc[i][j]`
                            - (Return allocated resources to available pool)
                    - **Mark as Finished:**
                        
                        - `finish[i] = 1`
                        - `found = 1`
        - **If** `found == 0` **Then**
            
            - (No process could be satisfied in this iteration)
            - **Print** "System is NOT in safe state."
            - **Return** with error (deadlock possible)
```c
while (count < n)
  {
    int found = 0;
    for (i = 0; i < n; i++)
    {
      if (finish[i] == 0)
      {
        int flag = 1;
        for (j = 0; j < m; j++)
        {
          if (need[i][j] > avail[j])
          {
            flag = 0;
            break;
          }
        }
        if (flag)
        {
          safeSeq[count++] = i;
          for (j = 0; j < m; j++)
            avail[j] += alloc[i][j];
          finish[i] = 1;
          found = 1;
        }
      }
    }
    if (found == 0)
    {
      printf("System is NOT in safe state.\n");
      return 0;
    }
  }
```
1. **Output Safe Sequence:**
    
    - **Print** "System is in SAFE state."
    - **Print** "Safe sequence: "
    - Loop from `i = 0` to `i < n`
        - **Print** `P[safeSeq[i]]` (process IDs in safe order)
```c
  printf("System is in SAFE state.\nSafe sequence: ");
  for (i = 0; i < n; i++)
    printf("P%d ", safeSeq[i]);
```
1. **Return** 0
    
2. **END**
    

---

## **How to Execute:**

```bash
# Compile
gcc program.c -o program

# Run
./program
```

**Example Input:**

```
Processes = 5
Resources = 3

Allocation Matrix
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

Maximum Matrix
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

Available
3 3 2
```

**Example Output:**

```
System is in SAFE state
Safe sequence: P1 P3 P4 P0 P2
```

---

## **Key Concepts:**

|Concept|Formula|Explanation|
|---|---|---|
|**Allocation**|Given|Resources currently held by process|
|**Maximum**|Given|Maximum resources process can request|
|**Need**|Max - Allocation|Additional resources process may need|
|**Available**|Given initially|Free resources in system|
|**Safe State**|Exists safe sequence|System can satisfy all processes|
|**Safe Sequence**|Ordering of processes|Order in which processes can complete safely|
|**Deadlock**|No safe sequence|System cannot satisfy all processes|

---
