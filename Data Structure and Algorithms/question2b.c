#include <stdio.h>
#define size 100

struct queue
{
    int front;
    int rear;
    int que[size];
} q;

void init()
{
    q.front = q.rear = -1;
}

int enqueue(int item)
{
    if (q.rear >= size - 1)
    {
        printf("queue overflow!\n");
        return -1;
    }
    else if (q.front == -1)
        q.front++;
    q.que[++q.rear] = item;
    return q.rear;
}

int dequeue()
{
    if (q.front == -1 || q.front > q.rear)
    {
        printf("queue underflow\n");
        return -1;
    }
    int item = q.que[q.front++];
    return item;
}

void display()
{
    if (q.front == -1 || q.front > q.rear)
    {
        printf("queue underflow\n");
        return;
    }
    if (q.rear == size - 1)
    {
        printf("queue overflow\n");
        return;
    }
    for (int i = q.front; i <= q.rear; i++)
        printf("%d ", q.que[i]);
    printf("\n");
}

int findMax()
{
    if (q.front == -1 || q.front > q.rear)
    {
        printf("queue is empty\n");
        return -1;
    }

    int max = q.que[q.front];
    int n = q.rear - q.front + 1;

    for (int i = 0; i < n; i++)
    {
        int item = dequeue();
        if (item > max)
            max = item;
        enqueue(item);
    }
    return max;
}

int main()
{
    init();
    int choice = 1, value;

    while (choice == 1)
    {
        printf("***********SELECT YOUR CHOICE************\n\n");
        printf("1.enqueue:\n\n");
        printf("2.dequeue:\n\n");
        printf("3.display:\n\n");
        printf("4.find max:\n\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("enter the value: \n");
            scanf("%d", &value);
            enqueue(value);
            break;

        case 2:
            value = dequeue();
            if (value != -1)
                printf("the dequeued value is %d\n", value);
            break;

        case 3:
            display();
            break;

        case 4:
            value = findMax();
            if (value != -1)
                printf("the max value is %d\n", value);
            break;

        default:
            break;
        }
        printf("Do you wish to continue, 1/0\n");
        scanf("%d", &choice);
    }
}

