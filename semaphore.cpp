// A process Block.
struct processBlock
{
    int *process_block;
    processBlock *nextBlock;
};

struct fifo_queue
{
    processBlock *front, *back;

    void *push(int *val)
    {
        processBlock *pBlock = new processBlock();

        pBlock->process_block = val;

        if (back == nullptr)
        {
            back->nextBlock = pBlock;
            back = pBlock;
        }
        else
        {
            front = back = pBlock;
        }
    }

    int *pop()
    {
        if (front == nullptr)
        {
            cout << "Underflow Error";
            return nullptr;
        }
        else
        {
            int *val = front->process_block;
            front = front->nextBlock;
            if (front == nullptr)
                back = nullptr;
            return val;
        }
    }
};

class Semaphore
{
public:
    fifo_queue *Q;
    int value;

    Semaphore(int v)
    {
        Q = new fifo_queue();
        value = v;
    }
};

void wait(Semaphore *S, int *process_id)
{
    S->value--;
    if (S->value < 0)
    {
        S->Q->push(process_id);

        // block() function blocks the process  with the help of system call. This process is transferred to the waiting queue.
        block();
    }
}

void signal(Semaphore *S)
{
    S->value++;
    if (S->value <= 0)
    {
        int *PID = S->Q->pop();

        // wakeup() function wakes up the process with the specific PID using the system calls.
        wakeup(PID);
    }
};