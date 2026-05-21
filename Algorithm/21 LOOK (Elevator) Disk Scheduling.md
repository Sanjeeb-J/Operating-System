
---
```c
#include <stdio.h>
#include <stdlib.h>
```
## **ALGORITHM: LOOK (Elevator) Disk Scheduling**

### **FUNCTION 1: sort()**

**Input:** Array `arr[]` and integer `n` (size of array)

**Output:** Array sorted in ascending order using Bubble Sort

**Steps:**

1. **START**
    
2. **Bubble Sort Algorithm:**
    
    - Loop from `i = 0` to `i < n - 1`
        - Loop from `j = 0` to `j < n - i - 1`
            - **If** `arr[j] > arr[j + 1]` **Then**
                - (Elements out of order)
                - **Swap:**
                    - `temp = arr[j]`
                    - `arr[j] = arr[j + 1]`
                    - `arr[j + 1] = temp`
3. **END**
    
```c
void sort(int arr[], int n)
{
  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - i - 1; j++)
      if (arr[j] > arr[j + 1])
      {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
}
```
---

### **MAIN FUNCTION: main()**

**Input:**

- Number of disk requests (n)
- Disk request sequence (cylinder numbers)
- Initial head position
- Direction (0 = left, 1 = right)

**Output:**

- Total seek time using LOOK algorithm

**Steps:**

1. **START**
    
2. **Initialize Variables:**
    
    - Declare `requests[100]` (array to store cylinder numbers)
    - Declare `n`, `head`, `totalSeek = 0`, `direction`
```c
  int requests[100], n, head, totalSeek = 0;
  int direction;
```
1. **Input Number of Requests:**
    
    - **Print** "Enter number of requests: "
    - **Read** `n`
```c
  printf("Enter number of requests: ");
  scanf("%d", &n);
```
1. **Input Request Sequence:**
    
    - **Print** "Enter request sequence: "
    - Loop from `i = 0` to `i < n`
        - **Read** `requests[i]`
```c
  printf("Enter request sequence: ");
  for (int i = 0; i < n; i++)
    scanf("%d", &requests[i]);
```
1. **Input Initial Head Position:**
    
    - **Print** "Enter initial head position: "
    - **Read** `head`
```c
  printf("Enter initial head position: ");
  scanf("%d", &head);
```
1. **Input Initial Direction:**
    
    - **Print** "Enter direction (0 = left, 1 = right): "
    - **Read** `direction`
```c
  printf("Enter direction (0 = left, 1 = right): ");
  scanf("%d", &direction);
```
1. **Sort Request Sequence:**
    
    - **Call** `sort(requests, n)` (sort requests in ascending order)
```c
  sort(requests, n);
```
1. **Find Pivot Point:**
    
    - **Declare** `index`
    - Loop from `index = 0` to `index < n`
        - **If** `head < requests[index]` **Then**
            - (Found first request greater than head)
            - **Break** from loop
    - After loop: `index` points to first request ≥ head
```c
  int index;
  for (index = 0; index < n; index++)
    if (head < requests[index])
      break;
```
1. **LOOK Scheduling (Direction = 1: Right First):**
    
    - **If** `direction == 1` **Then**
        
        - **Move Right (toward higher cylinders):**
            - Loop from `i = index` to `i < n`
                - `totalSeek += abs(head - requests[i])`
                - `head = requests[i]`
        - **Then Move Left (toward lower cylinders):**
            - Loop from `i = index - 1` to `i >= 0` (decrement)
                - `totalSeek += abs(head - requests[i])`
                - `head = requests[i]`
```c
  if (direction == 1)
  {
    // Move right
    for (int i = index; i < n; i++)
    {
      totalSeek += abs(head - requests[i]);
      head = requests[i];
    }

    // Then move left
    for (int i = index - 1; i >= 0; i--)
    {
      totalSeek += abs(head - requests[i]);
      head = requests[i];
    }
  }
```
1. **LOOK Scheduling (Direction = 0: Left First):**
    
    - **Else** (direction == 0)
        
        - **Move Left (toward lower cylinders):**
            - Loop from `i = index - 1` to `i >= 0` (decrement)
                - `totalSeek += abs(head - requests[i])`
                - `head = requests[i]`
        - **Then Move Right (toward higher cylinders):**
            - Loop from `i = index` to `i < n`
                - `totalSeek += abs(head - requests[i])`
                - `head = requests[i]`
```c
  else
  {
    // Move left
    for (int i = index - 1; i >= 0; i--)
    {
      totalSeek += abs(head - requests[i]);
      head = requests[i];
    }

    // Then move right
    for (int i = index; i < n; i++)
    {
      totalSeek += abs(head - requests[i]);
      head = requests[i];
    }
  }
```
1. **Output Results:**
    
    - **Print** "Total Seek Time (LOOK): " followed by `totalSeek`
```c
printf("Total Seek Time (LOOK): %d\n", totalSeek);
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

**Example Input 1 (Direction Right):**

```
Enter number of requests: 8
Enter request sequence: 82 170 43 140 24 16 190 130
Enter initial head position: 50
Enter direction (0 = left, 1 = right): 1
```

**Example Output 1:**

```
Total Seek Time (LOOK): 314
```
