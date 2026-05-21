
---

## **ALGORITHM: FIFO (First In First Out) Page Replacement**

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
1. **Initialize Frames:**
    
    - Declare `frame[frames]` array
    - Declare `faults = 0` (page fault counter)
    - Declare `index = 0` (pointer to next frame to replace)
    - Loop from `i = 0` to `i < frames`
        - `frame[i] = -1` (mark frame as empty)
```c
  int frame[frames];
  int faults = 0;
  int index = 0; // Points to next frame to replace (FIFO order)

  // Initialize frames as empty
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
            - `frame[index] = page[i]` (replace page at index)
            - `index = (index + 1) % frames` (move to next frame in circular manner)
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

    // Check for page hit
    for (int j = 0; j < frames; j++)
    {
      if (frame[j] == page[i])
      {
        found = 1;
        break;
      }
    }

    // If page not found → Page Fault
    if (!found)
    {
      frame[index] = page[i];
      index = (index + 1) % frames; // Circular replacement
      faults++;
    }

    // Display frame status
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
Frames: 3 2 8
Frames: 9 2 8
Frames: 9 1 8
Frames: 9 1 5
Frames: 9 1 2

Total Page Faults = 8
```

---
