
---
```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int main(int argc,char * argv[]) 
```
---
## **ALGORITHM: SSTF (Shortest Seek Time First) Disk Scheduling**

**Input:**

- Number of disk requests (n)
- Initial head position
- Disk size

**Output:**

- Disk request sequence
- Total seek time
- Movement path of disk head

**Steps:**

1. **START**
    
2. **Input Validation:**
    
    - **If** command-line arguments != 4 **Then**
        - Print usage message
        - Return error code 1
        - **EXIT**
```c
if(argc != 4){
        printf("Usage: 
            %s 
            <number of requests>
            <head position>
            <disk size>\n"
            ,argv[0]);
        return 1;
    }
```
1. **Parse Input:**
    
    - `n = atoi(argv[1])` (number of requests)
    - `head = atoi(argv[2])` (initial head position)
    - `diskSize = atoi(argv[3])` (disk size in cylinders)
```c
    int n = atoi(argv[1]);
    int head = atoi(argv[2]);
    int diskSize = atoi(argv[3]);
```
1. **Initialize Variables:**
    
    - Declare `requests[100]` (array to store cylinder numbers)
    - Declare `visited[100] = {0}` (track processed requests)
    - Declare `totalSeek = 0` (total seek time counter)
```c
	int requests[100], visited[100] = {0};
	int totalSeek = 0;
```
1. **Generate Random Disk Requests:**
    
    - **Call** `srand(time(NULL))` (seed random generator)
    - Print "Requests:"
    - Loop from `i = 0` to `i < n`
        - `requests[i] = rand() % diskSize` (generate random cylinder 0 to diskSize-1)
        - Print `requests[i]`
```c
    srand(time(NULL));
    printf("Requests:\n");
    for(int i= 0;i<n;i++){
        requests[i] = rand() % diskSize;
        printf("%d ",requests[i]);
    }
```
1. **SSTF Disk Scheduling Algorithm:**
    
    - Loop from `i = 0` to `i < n`
        
        - **Declare** `minDist = 999999` (initialize to maximum)
            
        - **Declare** `index = -1` (no request selected yet)
            
        - **Find Closest Unvisited Request:**
            
            - Loop from `j = 0` to `j < n`
                - **If** `visited[j] == 0` **Then**
                    - (Request not yet serviced)
                    - `dist = abs(head - requests[j])` (calculate distance from current head)
                    - **If** `dist < minDist` **Then**
                        - (This request is closer)
                        - `minDist = dist`
                        - `index = j`
        - **Service Selected Request:**
            
            - `visited[index] = 1` (mark request as visited/serviced)
            - `totalSeek += minDist` (add distance to total)
            - `head = requests[index]` (move head to this cylinder)
```c
    for(int i = 0; i < n; i++) {
        int minDist = 999999, index = -1;

        for(int j = 0; j < n; j++) {
            if(!visited[j]) {
                int dist = abs(head - requests[j]);
                if(dist < minDist) {
                    minDist = dist;
                    index = j;
                }
            }
        }
        
        printf("%d ", requests[index]);
        visited[index] = 1;
        totalSeek += minDist;
        head = requests[index];
    }
```
1. **Output Results:**
    
    - Print "Total Seek Time (SSTF): " followed by `totalSeek`
```c
    printf("Total Seek Time (SSTF): %d\n", totalSeek);
```
1. **Return** 0
    
2. **END**
    

---

## **How to Execute:**

```bash
# Compile
gcc program.c -o program

# Run with 10 requests, head at 50, disk size 200
./program 10 50 200

# Run with 15 requests, head at 100, disk size 250
./program 15 100 250

# Run with 20 requests, head at 0, disk size 300
./program 20 0 300
```

**Example Output:**

```
Requests:
45 150 80 90 120 60 110 20 160 190

Total Seek Time (SSTF): 210
```

---
