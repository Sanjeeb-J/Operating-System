
---
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READERS 5
#define WRITERS 2
#define OPERATIONS 5

sem_t wrt, mutex;
int readcount = 0;
int dataValue = 0;
```

---

## **ALGORITHM: Readers-Writers Problem (Reader-Preference Solution)**

### **FUNCTION 1: reader()**

**Input:** Thread argument containing reader ID

**Output:** Reader performs multiple read operations on shared data

**Steps:**

1. **START**
    
2. **Extract** reader ID from argument
    
3. **Loop** from `i = 0` to `i < OP` (number of operations)
    
    - **ENTRY SECTION (Reading):**
        - **Wait on Semaphore** `mutex` (to protect readcount)
            
            - `sem_wait(&mutex)`
        - **Increment** `readcount++` (one more reader)
            
        - **If** `readcount == 1` **Then**
            
            - (First reader, block all writers)
            - **Wait on Semaphore** `wrt` (writer semaphore)
                - `sem_wait(&wrt)`
        - **Signal Semaphore** `mutex` (release lock on readcount)
            
            - `sem_post(&mutex)`
    - **CRITICAL SECTION (Read Operation):**
        - **Print** "Reader [id] reads value: [value]"
        - **Sleep** for 1 second
    - **EXIT SECTION (Finishing Read):**
        - **Wait on Semaphore** `mutex`
            
            - `sem_wait(&mutex)`
        - **Decrement** `readcount--` (one less reader)
            
        - **If** `readcount == 0` **Then**
            
            - (Last reader, allow writers)
            - **Signal Semaphore** `wrt` (release writer semaphore)
                - `sem_post(&wrt)`
        - **Signal Semaphore** `mutex`
            
            - `sem_post(&mutex)`
    - **Sleep** for 1 second
4. **Exit Thread:** `pthread_exit(NULL)`
    
5. **END**
    
```c
void *reader(void *arg)
{
  int id = *(int *)arg;

  for (int i = 0; i < OPERATIONS; i++)
  {
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
      sem_wait(&wrt);
    sem_post(&mutex);

    printf("Reader %d reads value : %d\n", id, dataValue);
    sleep(1);

    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
      sem_post(&wrt);
    sem_post(&mutex);

    sleep(1);
  }

  pthread_exit(NULL);
}
```

---

### **FUNCTION 2: writer()**

**Input:** Thread argument containing writer ID

**Output:** Writer performs multiple write operations on shared data

**Steps:**

1. **START**
    
2. **Extract** writer ID from argument
    
3. **Loop** from `i = 0` to `i < OP` (number of operations)
    
    - **ENTRY SECTION (Requesting Write):**
        - **Wait on Semaphore** `wrt` (writer semaphore)
            - `sem_wait(&wrt)`
            - (Block until no reader or writer is using data)
    - **CRITICAL SECTION (Write Operation):**
        - **Increment** `value++` (modify shared data)
        - **Print** "Writer [id] writes value: [value]"
        - **Sleep** for 2 seconds (simulate write time)
    - **EXIT SECTION (Finishing Write):**
        - **Signal Semaphore** `wrt` (release writer semaphore)
            - `sem_post(&wrt)`
            - (Allow other writer or readers)
    - **Sleep** for 1 second
4. **Exit Thread:** `pthread_exit(NULL)`
    
5. **END**
    
```c
void *writer(void *arg)
{
  int id = *(int *)arg;

  for (int i = 0; i < OPERATIONS; i++)
  {
    sem_wait(&wrt);

    dataValue++;
    printf("Writer %d writes value : %d\n", id, dataValue);
    sleep(2);

    sem_post(&wrt);

    sleep(1);
  }

  pthread_exit(NULL);
}
```

---

### **MAIN FUNCTION: main()**

**Input:** None

**Output:** Synchronized read-write operations with proper coordination

**Steps:**

1. **START**
    
2. **Declare** variables:
    
    - `r[RE]` (array of reader threads)
    - `w[WR]` (array of writer threads)
    - `rid[RE]` (array of reader IDs)
    - `wid[WR]` (array of writer IDs)
3. **Initialize Semaphores:**
    
    - **Call** `sem_init(&mutex, 0, 1)` (binary semaphore for readcount protection, initial value = 1)
    - **Call** `sem_init(&wrt, 0, 1)` (binary semaphore for writer exclusion, initial value = 1)
4. **Create Reader Threads:**
    
    - Loop from `i = 0` to `i < RE`
        - `rid[i] = i + 1` (assign reader ID)
        - **Call** `pthread_create(&r[i], NULL, reader, &rid[i])` (create reader thread)
5. **Create Writer Threads:**
    
    - Loop from `i = 0` to `i < WR`
        - `wid[i] = i + 1` (assign writer ID)
        - **Call** `pthread_create(&w[i], NULL, writer, &wid[i])` (create writer thread)
6. **Wait for All Reader Threads:**
    
    - Loop from `i = 0` to `i < RE`
        - **Call** `pthread_join(r[i], NULL)` (wait for reader thread to complete)
7. **Wait for All Writer Threads:**
    
    - Loop from `i = 0` to `i < WR`
        - **Call** `pthread_join(w[i], NULL)` (wait for writer thread to complete)
8. **Destroy Semaphores:**
    
    - **Call** `sem_destroy(&mutex)` (destroy mutex semaphore)
    - **Call** `sem_destroy(&wrt)` (destroy writer semaphore)
9. **Return** 0
    
10. **END**
    

```c
int main()
{
  pthread_t r[READERS], w[WRITERS];
  int rid[READERS], wid[WRITERS];

  sem_init(&mutex, 0, 1);
  sem_init(&wrt, 0, 1);

  for (int i = 0; i < READERS; i++)
  {
    rid[i] = i + 1;
    pthread_create(&r[i], NULL, reader, &rid[i]);
  }

  for (int i = 0; i < WRITERS; i++)
  {
    wid[i] = i + 1;
    pthread_create(&w[i], NULL, writer, &wid[i]);
  }

  for (int i = 0; i < READERS; i++)
    pthread_join(r[i], NULL);

  for (int i = 0; i < WRITERS; i++)
    pthread_join(w[i], NULL);

  sem_destroy(&mutex);
  sem_destroy(&wrt);

  return 0;
}
```

---

## **How to Execute:**

```bash
# Compile with pthread and semaphore libraries
gcc program.c -o program -lpthread

# Run
./program
```

**Example Output:**

```
Reader 1 reads value : 0
Reader 2 reads value : 0
Reader 3 reads value : 0
Writer 1 writes value : 1
Reader 4 reads value : 1
Reader 5 reads value : 1
Writer 2 writes value : 2
Reader 1 reads value : 2
...and so on
```

---

## **Key Concepts:**

|Concept|Explanation|
|---|---|
|**Semaphore**|Synchronization primitive (counter-based)|
|**Binary Semaphore**|Value 0 or 1 (like mutex)|
|**sem_wait()**|Decrement semaphore (block if ≤ 0)|
|**sem_post()**|Increment semaphore (wake up waiting thread)|
|**mutex**|Protects `readcount` variable from race conditions|
|**wrt (writer)**|Controls exclusive access to shared data|
|**readcount**|Number of active readers|
|**Reader-Preference**|Multiple readers can read simultaneously|
|**Mutual Exclusion**|Writers have exclusive access|

---

## **Synchronization Rules:**

```
READERS:
1. First reader acquires wrt semaphore (blocks writers)
2. Multiple readers can read simultaneously
3. Last reader releases wrt semaphore (allows writers)

WRITERS:
1. Writer acquires wrt semaphore (waits for all readers/writers)
2. Writer modifies shared data exclusively
3. Writer releases wrt semaphore (allows other readers/writers)
```

---
