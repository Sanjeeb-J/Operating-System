
---
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_REF 1000
#define MAX_FRAMES 7
```
## **ALGORITHM: Optimal Page Replacement**

### **FUNCTION 1: generateReferenceString()**

**Input:** Array `page[]` and integer `pages` (reference string length)

**Output:** Random page reference string (pages 0-9) printed to console

**Steps:**

1. **START**
    
2. **Seed Random Number Generator:**
    
    - **Call** `srand(time(NULL))`
3. **Print Header:**
    
    - Print "Reference String:"
4. **Generate Random Pages:**
    
    - Loop from `i = 0` to `i < pages`
        - `page[i] = rand() % 10` (generate random page 0-9)
        - Print `page[i]`
5. **Print Newline**
    
6. **END**
    
```c
void generateReferenceString(int page[], int pages)
{
  srand(time(NULL));
  printf("Reference String:\n");

  for (int i = 0; i < pages; i++)
  {
    page[i] = rand() % 10;
    printf("%d ", page[i]);
  }
  printf("\n");
}
```
---

### **FUNCTION 2: optimalPageReplacement()**

**Input:**

- Array `page[]` (reference string)
- Integer `pages` (reference string length)
- Integer `frames` (number of frames)

**Output:**

- Frame status after each page reference
- Total page faults

**Steps:**

1. **START**
```c
void optimalPageReplacement(int page[], int pages, int frames)
```
1. **Initialize Variables:**
    
    - Declare `frame[MAX_FRAMES]` array
    - Declare `faults = 0` (page fault counter)
    - Loop from `i = 0` to `i < frames`
        - `frame[i] = -1` (mark frame as empty)
```c
  int frame[MAX_FRAMES];
  int faults = 0;

  /* Initialize frames */
  for (int i = 0; i < frames; i++)
    frame[i] = -1;
```
1. **Process Each Page Reference:**
    
    - Loop from `i = 0` to `i < pages`
        
        - **Declare** `found = 0`
            
        - **Check for Page Hit (Page Already in Memory):**
            
            - Loop from `j = 0` to `j < frames`
                - **If** `frame[j] == page[i]` **Then**
                    - (Page found in memory - HIT)
                    - `found = 1`
                    - **Break** from loop
        - **If** `found == 0` **Then**
            
            - (Page not in memory - PAGE FAULT)
                
            - **Declare** `index = -1`, `farthest = -1`
                
            - **Check for Empty Frame:**
                
                - Loop from `j = 0` to `j < frames`
                    - **If** `frame[j] == -1` **Then**
                        - (Empty frame found)
                        - `index = j`
                        - **Break** from loop
            - **If** `index == -1` **Then**
                
                - (No empty frame, must find page to replace)
                    
                - **Find Page Used Farthest in Future:**
                    
                    - Loop from `j = 0` to `j < frames`
                        
                        - **Declare** `k`
                            
                        - **Search for Future Occurrence:**
                            
                            - Loop from `k = i + 1` to `k < pages`
                                - **If** `frame[j] == page[k]` **Then**
                                    - (Page used at position k)
                                    - **If** `k > farthest` **Then**
                                        - (This page is used farthest in future)
                                        - `farthest = k`
                                        - `index = j`
                                    - **Break** from loop
                        - **If** `k == pages` **Then**
                            
                            - (Page never used again - REPLACE IMMEDIATELY)
                            - `index = j`
                            - **Break** from loop
            - **Replace Page:**
                
                - `frame[index] = page[i]` (load new page into selected frame)
                - `faults++` (increment fault counter)
        - **Display Frame Status:**
            
            - Print "Frames: "
            - Loop from `j = 0` to `j < frames`
                - **If** `frame[j] != -1` **Then**
                    - Print `frame[j]`
                - **Else**
                    - Print "-" (empty frame)
            - Print newline
```c
for (int i = 0; i < pages; i++)
  {
    int found = 0;

    /* Check for page hit */
    for (int j = 0; j < frames; j++)
    {
      if (frame[j] == page[i])
      {
        found = 1;
        break;
      }
    }

    /* Page fault */
    if (!found)
    {
      int index = -1, farthest = -1;

      for (int j = 0; j < frames; j++)
      {
        if (frame[j] == -1)
        {
          index = j;
          break;
        }
      }

      if (index == -1)
      {

        for (int j = 0; j < frames; j++)
        {
          int k;

          for (k = i + 1; k < pages; k++)
          {
            if (frame[j] == page[k])
            {
              if (k > farthest)
              {
                farthest = k;
                index = j;
              }
              break;
            }
          }

          /* If page not used again */
          if (k == pages)
          {
            index = j;
            break;
          }
        }
      }
      /* If empty frame exists */

      frame[index] = page[i];
      faults++;
    }

    /* Display frames */
    printf("Frames: ");
    for (int j = 0; j < frames; j++)
    {
      if (frame[j] != -1)
        printf("%d ", frame[j]);
      else
        printf("- ");
    }
    printf("\n");
  }
```
1. **Output Results:**
    
    - Print newline
    - Print "Total Page Faults = " followed by `faults`
```c
printf("\nTotal Page Faults = %d\n", faults);
```
1. **END**
    

---

### **MAIN FUNCTION: main()**

**Input:** Command-line arguments (reference string length and number of frames)

**Output:** Optimal page replacement results

**Steps:**

1. **START**
    
2. **Input Validation:**
    
    - **If** `argc != 3` **Then**
        - Print usage message
        - Return error code 1
        - **EXIT**
3. **Parse Input:**
    
    - `pages = atoi(argv[1])`
    - `frames = atoi(argv[2])`
4. **Validate Frame Count:**
    
    - **If** `frames < 1` OR `frames > 7` **Then**
        - Print "Number of frames must be between 1 and 7"
        - Return error code 1
        - **EXIT**
5. **Declare Reference String Array:**
    
    - Declare `page[MAX_REF]`
6. **Generate Reference String:**
    
    - **Call** `generateReferenceString(page, pages)`
7. **Perform Optimal Page Replacement:**
    
    - **Call** `optimalPageReplacement(page, pages, frames)`
8. **Return** 0
    
9. **END**
    
```c
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Usage: %s <reference_string_length> <number_of_frames(1-7)>\n", argv[0]);
    return 1;
  }

  int pages = atoi(argv[1]);
  int frames = atoi(argv[2]);

  if (frames < 1 || frames > 7)
  {
    printf("Number of frames must be between 1 and 7\n");
    return 1;
  }

  int page[MAX_REF];

  generateReferenceString(page, pages);
  optimalPageReplacement(page, pages, frames);

  return 0;
}
```
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
Frames: 3 2 8
Frames: 9 2 8
Frames: 9 1 8
Frames: 9 1 5
Frames: 9 2 5

Total Page Faults = 6
```

---

## **Key Concepts:**

|Concept|Explanation|
|---|---|
|**Optimal Algorithm**|Replace page used farthest in future|
|**Future Knowledge**|Assumes we know future page references|
|**Minimum Faults**|Theoretical minimum possible faults|
|**Unrealistic**|Impossible in real systems (need future info)|
|**Benchmark**|Used to evaluate other algorithms|
|**Farthest in Future**|Page with next use farthest away|
|**Never Used Again**|Replace if page never appears again|

---

## **Algorithm Logic:**

```
FOR each page reference:
  IF page in memory:
    Page HIT - no action
  ELSE:
    Page FAULT
    IF empty frame exists:
      Load page into empty frame
    ELSE:
      Find page used farthest in future
      IF page never used again:
        Replace that page immediately
      ELSE:
        Replace page with farthest next use
      Load new page
    faults++
  Display frame contents
```

---

## **Optimal Page Replacement Mechanism:**

```
Reference String: 5, 2, 8, 3, 2, 5, 9, 1, 5, 2
Frames: 3

Time  Ref  Action              Future Uses      Frames    Faults
──────────────────────────────────────────────────────────────
0     5    Load 5              2,8,3,2,5,9...  [5,-,-]   1
1     2    Load 2              8,3,2,5,9,1...  [5,2,-]   2
2     8    Load 8              3,2,5,9,1,5...  [5,2,8]   3
3     3    5→pos7, 2→pos4, 8→∞ Replace 8       [5,2,3]   4
4     2    Found (HIT)         5,9,1,5,2       [5,2,3]   -
5     5    Found (HIT)         9,1,5,2         [5,2,3]   -
6     9    5→pos8, 2→pos9, 3→∞ Replace 3       [5,2,9]   5
7     1    5→pos8, 2→pos9, 9→∞ Replace 9       [5,2,1]   6
8     5    Found (HIT)         2               [5,2,1]   -
9     2    Found (HIT)         -               [5,2,1]   -
```

---

## **Finding Farthest in Future:**

```c
// Algorithm:
for (int j = 0; j < frames; j++) {
    int k;
    
    // Search for next occurrence
    for (k = i + 1; k < pages; k++) {
        if (frame[j] == page[k]) {
            // Found next use at position k
            if (k > farthest) {
                farthest = k;  // This is farthest so far
                index = j;
            }
            break;
        }
    }
    
    // If k == pages, page never used again
    if (k == pages) {
        index = j;  // Replace this immediately
        break;
    }
}
```

---

## **Comparison: FIFO vs LRU vs Optimal:**

```
Reference: 5, 2, 8, 3, 2, 5, 9, 1, 5, 2
Frames: 3

FIFO:
[5] [5,2] [5,2,8] [3,2,8] [3,2,8] [3,2,8] [9,2,8] [9,1,8] [9,1,5] [9,1,2]
Faults: 8

LRU:
[5] [5,2] [5,2,8] [3,2,8] [3,2,8] [3,5,8] [3,5,9] [3,5,1] [5,5,1] [5,2,1]
Faults: 7

OPTIMAL:
[5] [5,2] [5,2,8] [5,2,3] [5,2,3] [5,2,3] [5,2,9] [5,2,1] [5,2,1] [5,2,1]
Faults: 6 (BEST)

Optimal ≤ LRU ≤ FIFO (always true)
```

---

## **Why Optimal is Unrealistic:**

```
ADVANTAGES:
✓ Gives minimum page faults
✓ Optimal by definition
✓ Good for comparison/benchmarking

DISADVANTAGES:
✗ Requires future knowledge
✗ Impossible to implement in real systems
✗ Only useful for evaluation purposes
✗ Can't predict real-world page requests
```

---

## **Optimal Algorithm Characteristics:**

|Aspect|Description|
|---|---|
|**Optimality**|Theoretical minimum faults|
|**Implementation**|Impossible in practice|
|**Use Case**|Benchmark for other algorithms|
|**Complexity**|O(frames × remaining_pages)|
|**Fairness**|Treats all pages optimally|
|**Predictability**|Perfect (with future knowledge)|

---

## **Page Replacement Decision Tree:**

```
Page not in memory (FAULT)
        ↓
    Empty frame?
    /          \
  YES           NO
   ↓             ↓
Load page   Search future
            references
            ↓
     Find page used
     farthest ahead
            ↓
      Replace that page
```

---

## **Handling Never-Used-Again Pages:**

```c
// If loop completes without finding future use:
if (k == pages) {
    // Page never used again
    index = j;  // Replace immediately
    break;      // No need to check other pages
}

This gives priority to removing "dead" pages.
```

---

## **Time Complexity:**

```
For each page reference (n pages):
  Search frames: O(frames)
  Search future: O(frames × remaining_pages)
  
Total: O(n × frames × n) = O(n² × frames)
where n = pages, frames = number of frames

This is higher than FIFO or LRU due to future scanning.
```

---

## **Belady's Anomaly Not Present:**

```
Optimal algorithm does NOT suffer from Belady's anomaly.
More frames ALWAYS results in fewer or equal page faults.

This is proven by the optimal replacement policy:
- Replaces page used farthest in future
- Adding frames can only help, never hurt
```

---

## **Command-Line Examples:**

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
page[MAX_REF]      → Reference string (pages 0-9)
frame[MAX_FRAMES]  → Physical memory frames
faults             → Total page faults counter
index              → Index of frame to replace
farthest           → Farthest future occurrence position
found              → Flag: 1 if page hit, 0 if fault
```

---

## **Real-World Application:**

```
Although optimal is unrealistic, it:
1. Provides theoretical lower bound on faults
2. Evaluates how well LRU approximates optimal
3. Helps understand page replacement principles
4. Used in educational contexts
5. Guides algorithm design improvements
```

---

## **Algorithm Efficiency Ranking:**

```
1. OPTIMAL      → Minimum faults (unrealistic)
2. LRU          → Near-optimal (realistic)
3. FIFO         → Simple but suboptimal
4. RANDOM       → Worst performance

Real systems use LRU approximations because:
- Can't access future information
- Optimal is O(n² × frames)
- LRU is O(n × frames)
```

