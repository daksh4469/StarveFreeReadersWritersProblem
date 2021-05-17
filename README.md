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
