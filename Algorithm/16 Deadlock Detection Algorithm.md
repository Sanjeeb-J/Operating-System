
---

## **ALGORITHM: Deadlock Detection Algorithm**

**Input:**

- Number of processes (n)
- Number of resource types (m)
- Allocation Matrix `alloc[n][m]` (resources currently held)
- Request Matrix `request[n][m]` (resources being requested)
- Available Resources array `avail[m]` (free resources)

**Output:**

- List of deadlocked processes (if any)
- "No deadlock detected" message (if system is safe)

**Steps:**

1. **START**
```c
#include <stdio.h>

#define MAX 10
```
1. **Input Data:**
    
    - **Read** `n` (number of processes)
    - **Read** `m` (number of resource types)
    - **Read** Allocation Matrix `alloc[n][m]`
    - **Read** Request Matrix `request[n][m]`
    - **Read** Available Resources array `avail[m]`
```c
int n, m;
    int alloc[MAX][MAX], request[MAX][MAX];
    int avail[MAX], finish[MAX];
    int i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Request Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources:\n");
    for(j = 0; j < m; j++)
        scanf("%d", &avail[j]);
```
1. **Initialize Finish Array:**
    
    - Loop from `i = 0` to `i < n`
        - `finish[i] = 0` (mark all processes as not finished)
```c
    for(i = 0; i < n; i++)
        finish[i] = 0;
```
1. **Deadlock Detection Loop:**
    
    - **Declare** `changed = 1`
        
    - **While** `changed == 1` **Do**
        
        - `changed = 0` (reset flag)
            
        - **Loop through processes** from `i = 0` to `i < n`
            
            - **If** `finish[i] == 0` **Then**
                - (Process not yet finished)
                    
                - **Declare** `flag = 1`
                    
                - **Check if all requests can be satisfied:**
                    
                    - Loop from `j = 0` to `j < m`
                        - **If** `request[i][j] > avail[j]` **Then**
                            - (Process request exceeds available resources)
                            - `flag = 0`
                            - **Break** from loop
                - **If** `flag == 1` **Then**
                    
                    - (Process request can be granted)
                        
                    - **Release Allocated Resources:**
                        
                        - Loop from `j = 0` to `j < m`
                            - `avail[j] += alloc[i][j]`
                            - (Return all resources held by this process)
                    - **Mark as Finished:**
                        
                        - `finish[i] = 1`
                        - `changed = 1`
                        - (Set flag to continue checking)
```c
int changed = 1;
    while(changed) {
        changed = 0;
        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int flag = 1;
                for(j = 0; j < m; j++) {
                    if(request[i][j] > avail[j]) {
                        flag = 0;
                        break;
                    }
                }
                if(flag) {
                    for(j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    finish[i] = 1;
                    changed = 1;
                }
            }
        }
    }
```
1. **Check for Deadlocked Processes:**
    
    - **Declare** `deadlock = 0`
        
    - Loop from `i = 0` to `i < n`
        
        - **If** `finish[i] == 0` **Then**
            - (Process never finished)
            - `deadlock = 1`
            - **Print** "Process P[i] is deadlocked."
```c
int deadlock = 0;
    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {
            deadlock = 1;
            printf("Process P%d is deadlocked.\n", i);
        }
    }
```
1. **Output Result:**
    
    - **If** `deadlock == 0` **Then**
        - **Print** "No deadlock detected."
```c
    if(!deadlock)
        printf("No deadlock detected.\n");
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

**Example Input 1 (No Deadlock):**

```
Enter number of processes: 3
Enter number of resource types: 2
Enter Allocation Matrix:
1 0
2 1
0 1
Enter Request Matrix:
0 1
1 0
0 0
Enter Available Resources:
0 0
```

**Example Output 1:**

```
No deadlock detected.
```

---
