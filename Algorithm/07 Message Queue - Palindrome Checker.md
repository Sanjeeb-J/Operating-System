
---

## **ALGORITHM: Message Queue - Palindrome Checker**

**Input:** A string from user

**Output:** Whether the string is a palindrome or not

**Steps:**

1. **START**
    
2. **DEFINE** Message structure with fields:
    
    - `type` (long integer)
    - `text` (character array of size MAX)
3. **DEFINE** Function `send(msgid, msg)`:
    
    - **Call** `msgsnd()` to send message to queue with message ID `msgid`
4. **DEFINE** Function `receive(msgid, msg, type)`:
    
    - **Call** `msgrcv()` to receive message from queue with message ID `msgid` of given `type`
5. **Declare** variables: `key`, `msgid`, `msg` (message structure), `original[]`, `reversed[]`, `i`, `len`
    
6. **Create Message Queue:**
    
    - **Call** `ftok("prog", 60)` to create unique key and store in `key`
    - **Call** `msgget(key, 0666 | IPC_CREAT)` to create message queue and store ID in `msgid`
7. **Create Child Process:** Call `fork()`
    
8. **If** `fork() == 0` **Then** (Child Process)
    
    - **Call** `receive(msgid, &msg, 1)` to receive original string (type 1)
    - **Copy** received message to `original`
    - **Calculate** `len = strlen(original)`
    - **Reverse** the string: Loop from `i = 0` to `i < len`
        - `reversed[i] = original[len - i - 1]`
    - **Add** null terminator: `reversed[len] = '\0'`
    - **Set** `msg.type = 2`
    - **Copy** reversed string to `msg.text`
    - **Call** `send(msgid, &msg)` to send reversed string back (type 2)
9. **Else** (Parent Process)
    
    - **Input:** Read string from user into `original`
    - **Set** `msg.type = 1`
    - **Copy** `original` to `msg.text`
    - **Call** `send(msgid, &msg)` to send original string to child (type 1)
    - **Call** `receive(msgid, &msg, 2)` to receive reversed string (type 2)
    - **Copy** received message to `reversed`
    - **Check Palindrome:** **If** `strcmp(original, reversed) == 0` **Then**
        - Print "The string is a PALINDROME"
    - **Else**
        - Print "The string is NOT a PALINDROME"
    - **Remove** message queue: **Call** `msgctl(msgid, IPC_RMID, NULL)`
10. **Return** 0
    
11. **END**
    

---

## **How to Execute:**

```bash
# Compile
gcc program.c -o program

# Run
./program
```

**Example Output:**

```
Enter a string: racecar
The string is a PALINDROME

Enter a string: hello
The string is NOT a PALINDROME
```

---

## **Key Concepts:**

|Concept|Explanation|
|---|---|
|**Message Queue**|IPC mechanism for inter-process communication|
|**ftok()**|Creates unique key for message queue|
|**msgget()**|Creates or accesses message queue|
|**msgsnd()**|Sends message to queue|
|**msgrcv()**|Receives message from queue|
|**msgctl()**|Controls message queue (IPC_RMID removes it)|
|**msg.type**|Type field used to filter messages (1 for original, 2 for reversed)|
|**strcmp()**|Compares two strings (returns 0 if equal)|
