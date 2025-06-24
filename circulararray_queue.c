#include <stdio.h>

int size, x, i, cq[5];
int front = -1, rear = -1;

int isfull() {
    if ((front == 0 && rear == size - 1) || (front == rear + 1))
        return 1;
    else
        return 0;
}

void enqueue(int x) {
    if (isfull())
        printf("\nFULL QUEUE");
    else {
        if ((front == -1) && (rear == -1)) {
            front++;
            rear++;
            cq[rear] = x;
        } else {
            rear = (rear + 1) % size;
            cq[rear] = x;
        }
    }
}

int isempty() {
    if (front == -1)
        return 1;
    else
        return 0;
}

int dequeue() {
    if (isempty())
        printf("\nEMPTY QUEUE");
    else {
        if (front == rear) {
            front = -1;
            rear = -1;
            return x;
        } else {
            x = cq[front];
            front = (front + 1) % size;
            return x;
        }
    }
}

void display() {
    if (isempty()) {
        printf("\nEMPTY QUEUE");
    } else {
        printf("\nElements in a Queue are :");
        for (i = front; i != rear; i = (i + 1) % size)
            printf("\t%d", cq[i]);
        printf("\t%d", cq[rear]);
    }
    printf("\n");
}

void main() {
    int ele, ch = 1;
    printf("Size of Circular Queue : ");
    scanf("%d", &size);
    int cq[size];
    while (ch < 4 && ch != 0) {
        printf("\nEnter your choice(1-Enqueue,2-Dequeue,3-Display): ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter the element which is to be inserted: ");
                scanf("%d", &ele);
                enqueue(ele);
                display();
                break;
            case 2:
                dequeue();
                display();
                break;
            case 3:
                display();
        }
    }
}
