# Starve Free Readers Writers Problem

The Readers-writers problem is one of the most common problems in process synchronization. In this problem, there are two types of users: 

1. The Readers who want to read the shared resource, and 
2. The Writers who want to modify the shared resources. 

There are three variations to this problem, which deal with situations in which many concurrent threads of execution try to access the same shared resource at one time.

### First readers–writers problem
In this problem, new readers can also enter the critical section to read that resource when one reader is accessing the resource. However, the writer may lead to starvation as it may not get a chance to alter the resources as new readers may continuously enter to read the resource. Hence, the constraint in this problem is that no reader shall be kept waiting if the share is currently opened for reading.

### Second readers–writers problem
This problem is similar to the above problem, although here, the readers may starve. In this problem, the writer is given preference. The reader must wait until the last writer exits the critical section by modifying the resource and release the lock to allow readers to access the resource. Hence, the constraint in this problem is that no writer shall be kept waiting longer than necessary once added to the queue.

### Third readers–writers problem
This problem overcomes the downsides of the previous two problems of starvation. It is also known as the Starve-Free-Readers-Writers-Problem. It will give priority to the resources in the order of their arrival. For example, if a writer wants to write to the resource, it will wait until the current readers execute their tasks. Meanwhile, other readers accessing the resources would not be allowed to do so. Hence, the constraint is that no thread shall be allowed to starve.

***

## Explanation of the Code

A total of three semaphores are used here:

- `rMutex`: 
This semaphore is used to update the readers' count. Hence, this is available only to readers method.
- `getAccess`: 
If the readers are reading and if the writer tries to access the critical section, it would get blocked and vice versa. Thus, this is either in control of the reader or the writer.  However, if one reader is reading and another reader tries to access it, there would not be any problem. This semaphore gets updated in three instances. Firstly, when the first reader arrives. Secondly, when the last reader leaves the critical section and lastly when any writer writes to the resource.
- `turn`: 
This semaphore is used at the start of the entry section of readers/writers code. This involves checking if there is any process already waiting for its turn, and if so, it gets blocked. If not, it accesses the semaphore, and no new reader or writer will now execute before this process. Thus, it helps in preserving the `turn` of process.

An integer variable is also used:

- `readCount`: It is used to update the number of readers at a specific time.

For the read method, firstly, wait for `turn`, and `rMutex` is called. Now, if any process is already in the queue, the calling process is blocked as the `turn` would be one. Otherwise, it would make `turn` equal to one. `rMutex` is used to check whether there is any other process updating the readers count. If the reader count is 0, then do not allow the writer to access the critical section. Once the reader count is updated, both the semaphores are released. After reading of resource, `readCount` is decremented by getting hold of `rMutex`, and if the reader count is zero, writers can now access the critical section. For the write method, we first check the `turn` semaphore, and then the writer gets access with the `getAccess` semaphore. Since the `turn` would be preserved, the `turn` semaphore can now be released. The writers then modify the resources, and finally, `getAccess` is released. Thus, our objective of preventing any process from starving is achieved successfully.

***

## Correctness of the Solution

### Mutual Exclusion

Only a single writer can access the critical section at a certain time. This is ensured by the `getAccess` semaphore. This makes certain of the mutual exclusion among the writers and . This mutual exclusion is also maintained when the first reader tries to access the critical section and it has to acquire the `getAccess` mutex lock to access the critical section, thus, ensuring mutual exclusion between the readers and writers.

### Bounded Waiting

A reader/writer has to first acquire the `turn` semaphore which uses a FIFO(First In First Out) queue for the blocked processes before accessig the critical section. Hence, as the queue uses a FIFO(First In First Out) policy, each and every process has to hold back for a finite amount of time before it can access the critical section. Thus, this meets the requirement of bounded waiting.

### Progress Requirement

The readers and writers takes a finite amount of time to pass through the critical section and the code is structured so as to ensure that there are no chances for deadlock. Also, at the end of each reader writer code the semaphore for other processes, to enter into critical section, is released.
