
---

## **ALGORITHM: LRU (Least Recently Used) Page Replacement**

**Input:**

- Reference string length (number of page requests)
- Number of frames (1-7)

**Output:**

- Reference string (random pages 0-9)
- Frame status after each page reference
- Total page faults

**Steps:**

1. **START**
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_REF 1000
#define MAX_FRAMES 7

int main(int argc, char *argv[])
```
1. **Input Validation:**
    
    - **If** command-line arguments != 3 **Then**
        - Print usage message
        - Return error code 1
        - **EXIT**
```c
  if (argc != 3)
  {
    printf("Usage: %s <reference_string_length> <number_of_frames(1-7)>\n", argv[0]);
    return 1;
  }
```
1. **Parse Input:**
    
    - `pages = atoi(argv[1])` (convert to integer: reference string length)
    - `frames = atoi(argv[2])` (convert to integer: number of frames)
```c
  int pages = atoi(argv[1]);
  int frames = atoi(argv[2]);
```
1. **Validate Frame Count:**
    
    - **If** `frames < 1` OR `frames > 7` **Then**
        - Print "Number of frames must be between 1 and 7"
        - Return error code 1
        - **EXIT**
```c
  if (frames < 1 || frames > 7)
  {
    printf("Number of frames must be between 1 and 7\n");
    return 1;
  }
```
1. **Generate Reference String:**
    
    - **Call** `srand(time(NULL))` (seed random number generator)
    - Print "Reference String:"
    - Loop from `i = 0` to `i < pages`
        - `page[i] = rand() % 10` (generate random page 0-9)
        - Print `page[i]`
```c
  int page[MAX_REF];

  /* Generate random page reference string (0–9) */
  srand(time(NULL));
  printf("Reference String:\n");
  for (int i = 0; i < pages; i++)
  {
    page[i] = rand() % 10;
    printf("%d ", page[i]);
  }
```
1. **Initialize Frames and Time Arrays:**
    
    - Declare `frame[frames]` (page frame array)
    - Declare `time[frames]` (last used time for each frame)
    - Declare `count = 0` (global time counter)
    - Declare `faults = 0` (page fault counter)
    - Loop from `i = 0` to `i < frames`
        - `frame[i] = -1` (mark frame as empty)
        - `time[i] = 0` (initialize time to 0)
```c
  int frame[frames], time[frames];
  int count = 0, faults = 0;

  // Initialize frames as empty
  for (int i = 0; i < frames; i++)
  {
    frame[i] = -1;
    time[i] = 0;
  }
```
1. **Process Each Page Reference:**
    
    - Loop from `i = 0` to `i < pages`
        
        - **Declare** `found = 0`
            
        - **Check for Page Hit (Page Already in Memory):**
            
            - Loop from `j = 0` to `j < frames`
                - **If** `frame[j] == page[i]` **Then**
                    - (Page found in memory - HIT)
                    - `count++` (increment global time counter)
                    - `time[j] = count` (update frame's last used time to current time)
                    - `found = 1`
                    - **Break** from loop
        - **If** `found == 0` **Then**
            
            - (Page not in memory - PAGE FAULT)
                
            - **Find Least Recently Used Frame:**
                
                - `lru = 0` (assume frame 0 is LRU)
                - Loop from `j = 1` to `j < frames`
                    - **If** `time[j] < time[lru]` **Then**
                        - (Frame j has smaller timestamp - older/LRU)
                        - `lru = j`
            - **Replace LRU Page:**
                
                - `frame[lru] = page[i]` (load new page into LRU frame)
                - `count++` (increment global time counter)
                - `time[lru] = count` (update frame's time to current)
                - `faults++` (increment fault counter)
        - **Display Frame Status:**
            
            - Print "Frames: "
            - Loop from `j = 0` to `j < frames`
                - **If** `frame[j] != -1` **Then**
                    - Print `frame[j]`
                - **Else**
                    - Print "-" (empty frame)
```c
for (int i = 0; i < pages; i++)
  {
    int found = 0;

    // Check if page is already in frame (HIT)
    for (int j = 0; j < frames; j++)
    {
      if (frame[j] == page[i])
      {
        count++;
        time[j] = count; // Update recently used time
        found = 1;
        break;
      }
    }

    // If page not found (MISS)
    if (!found)
    {
      int lru = 0;

      // Find least recently used frame
      for (int j = 1; j < frames; j++)
      {
        if (time[j] < time[lru])
        {
          lru = j;
        }
      }

      frame[lru] = page[i];
      count++;
      time[lru] = count;
      faults++;
    }

    // Display frames after each page reference
    printf("\nFrames: ");
    for (int j = 0; j < frames; j++)
    {
      if (frame[j] != -1)
        printf("%d ", frame[j]);
      else
        printf("- ");
    }
  }
```
1. **Output Results:**
    
    - Print newline
    - Print "Total Page Faults = " followed by `faults`
```c
printf("\n\nTotal Page Faults = %d\n", faults);
```
1. **Return** 0
    
2. **END**
    

---

## **How to Execute:**

```bash
# Compile
gcc program.c -o program

# Run with 20 page references and 3 frames
./program 20 3

# Run with 15 page references and 4 frames
./program 15 4

# Run with 10 page references and 2 frames
./program 10 2
```

**Example Output:**

```
Reference String:
5 2 8 3 2 5 9 1 5 2

Frames: 5
Frames: 5 2
Frames: 5 2 8
Frames: 3 2 8
Frames: 3 2 8
Frames: 5 2 8
Frames: 9 2 8
Frames: 9 1 8
Frames: 9 1 5
Frames: 9 2 5

Total Page Faults = 7
```

---

## **Key Concepts:**

|Concept|Explanation|
|---|---|
|**Page**|Unit of virtual memory|
|**Frame**|Unit of physical memory (RAM)|
|**Page Reference**|Request to access a page|
|**Page Hit**|Page already in memory - no fault|
|**Page Fault**|Page not in memory - must load from disk|
|**LRU**|Least Recently Used - replace oldest accessed page|
|**Time Stamp**|Counter tracking last access time|
|**Recently Used**|Page accessed most recently (highest time value)|

---

## **Algorithm Logic:**

```
count = 0 (global time)

FOR each page reference:
  count++
  
  IF page in memory:
    Page HIT
    Update time[frame] = count (mark as recently used)
  ELSE:
    Page FAULT
    Find frame with minimum time value (LRU)
    Replace LRU page with new page
    Update time[LRU_frame] = count
    faults++
  
  Display frame contents
```

---

## **LRU Page Replacement Mechanism:**

```
Reference String: 5, 2, 8, 3, 2, 5, 9, 1, 5, 2
Frames: 3 (capacity)

Time  Ref  Frames    Time[]      Hit/Fault  Action
──────────────────────────────────────────────────────
0     5    [5,-,-]   [1,0,0]     FAULT      Load 5, time[0]=1
1     2    [5,2,-]   [1,2,0]     FAULT      Load 2, time[1]=2
2     8    [5,2,8]   [1,2,3]     FAULT      Load 8, time[2]=3
3     3    [3,2,8]   [4,2,3]     FAULT      Replace 5 (time=1), time[0]=4
4     2    [3,2,8]   [4,5,3]     HIT        Page 2 found, time[1]=5
5     5    [3,5,8]   [4,6,3]     FAULT      Replace 8 (time=3), time[1]=6
6     9    [3,5,9]   [4,6,7]     FAULT      Replace 8 (time=3), time[2]=7
7     1    [3,5,1]   [4,6,8]     FAULT      Replace 3 (time=4), time[0]=8
8     5    [5,5,1]   [9,10,8]    HIT        Page 5 found, time[1]=9
9     2    [5,2,1]   [9,11,8]    FAULT      Replace 1 (time=8), time[1]=11
```

---

## **Time Array Tracking:**

```
time[] array tracks when each frame was last accessed:
- Higher value = more recent access
- Lower value = older access (LRU candidate)

Example:
frame[] = [3, 5, 1]
time[]  = [4, 6, 8]

Frame 3 (index 0): Last accessed at time 4 (oldest)
Frame 5 (index 1): Last accessed at time 6 (middle)
Frame 1 (index 2): Last accessed at time 8 (most recent)

If page fault occurs: Replace frame 3 (time=4, minimum)
```

---

## **LRU vs FIFO Comparison:**

```
Reference String: 5, 2, 8, 3, 2, 5, 9, 1, 5, 2
Frames: 3

FIFO Approach:
──────────────────────────────
[5] [5,2] [5,2,8] [3,2,8] [3,2,8] [3,2,8] [9,2,8] [9,1,8] [9,1,5] [9,1,2]
Faults: 8

LRU Approach:
──────────────────────────────
[5] [5,2] [5,2,8] [3,2,8] [3,2,8] [3,5,8] [3,5,9] [3,5,1] [5,5,1] [5,2,1]
Faults: 7 (BETTER)

LRU gives fewer page faults!
```

---

## **Finding Least Recently Used Frame:**

```c
// Algorithm to find LRU frame:
int lru = 0;
for (int j = 1; j < frames; j++) {
    if (time[j] < time[lru]) {
        lru = j;  // Found a frame accessed earlier
    }
}
// lru now holds index of least recently used frame
```

---

## **LRU Characteristics:**

|Aspect|Description|
|---|---|
|**Algorithm**|Replace page accessed longest time ago|
|**Optimality**|Near-optimal in practice|
|**Complexity**|O(frames) per page reference|
|**Implementation**|Requires time tracking|
|**Overhead**|Medium - need to track timestamps|
|**Performance**|Better than FIFO|
|**Reality**|Approximates optimal algorithm|

---

## **Page Fault Rate Comparison:**

```
Reference: 5, 2, 8, 3, 2, 5, 9, 1, 5, 2

FIFO:
Faults = 8
Rate = 8/10 = 80%

LRU:
Faults = 7
Rate = 7/10 = 70%

LRU performs 12.5% better!
```

---

## **Memory Access Timeline:**

```
Time Counter Evolution:
count = 0 → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → 10

Each page reference increments count:
- HIT: Update time[frame] = current count
- FAULT: Update time[LRU_frame] = current count

This tracks recency of access!
```

---

## **LRU Implementation Approaches:**

|Approach|Description|Complexity|
|---|---|---|
|**Counter-based**|Use timestamp (this code)|O(frames)|
|**Stack-based**|Use linked list|O(1) for hit|
|**Hardware-based**|Reference bit + clock|O(1) average|

---

## **Command-Line Usage:**

```bash
./program 10 2    → 10 references, 2 frames
./program 20 3    → 20 references, 3 frames
./program 50 4    → 50 references, 4 frames
./program 100 5   → 100 references, 5 frames
./program 1000 7  → 1000 references, 7 frames (max)
```

---

## **Key Variables:**

```c
page[MAX_REF]      → Random reference string (pages 0-9)
frame[frames]      → Physical memory frames
time[frames]       → Last access time for each frame
count              → Global time counter (incremented each reference)
faults             → Total page faults counter
found              → Flag: 1 if page hit, 0 if fault
lru                → Index of least recently used frame
```

---

## **Why LRU is Better Than FIFO:**

```
Principle: Pages used recently are likely to be used again soon
Therefore: Keep recently used pages, remove least recently used

This exploits TEMPORAL LOCALITY:
- Programs tend to reuse recently accessed data
- LRU respects this pattern
- FIFO ignores access patterns
```

---

## **Advantages & Disadvantages:**

|Aspect|LRU|FIFO|
|---|---|---|
|**Fault Rate**|Lower (better)|Higher|
|**Implementation**|Moderate|Simple|
|**Overhead**|Medium|Low|
|**Optimality**|Near-optimal|Not optimal|
|**Predictability**|Consistent|May vary|

