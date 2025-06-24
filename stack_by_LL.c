#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *ptr;
} *top, *top1, *temp;

int count = 0;

void push(int data) {
    if (top == NULL) {
        top = (struct node *)malloc(1 * sizeof(struct node));
        top->ptr = NULL;
        top->info = data;
    } else {
        temp = (struct node *)malloc(1 * sizeof(struct node));
        temp->ptr = top;
        temp->info = data;
        top = temp;
    }
    count++;
}

int pop() {
    top1 = top;
    if (top1 == NULL) {
        printf("\nStack Underflow");
        return -1;
    } else {
        top1 = top1->ptr;
        int popped = top->info;
        free(top);
        top = top1;
        count--;
        return popped;
    }
}

void display() {
    top1 = top;
    if (top1 == NULL) {
        printf("\nStack Underflow\n");
        return;
    }
    printf("\nELEMENTS OF STACK: ");
    while (top1 != NULL) {
        printf("\n%d", top1->info);
        top1 = top1->ptr;
    }
    printf("\nTOP : %d\n", top);
}

int main() {
    int choice, value;
    printf("\nImplementation of Stack using Linked List");
    while (1) {
        printf("\n1. Push 2. Pop 3. Display 4. Exit");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\nEnter the value to insert: ");
                scanf("%d", &value);
                push(value);
                display();
                break;
            case 2:
                printf("\nPopped element is : %d", pop());
                display();
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("\nEnter Valid Choice\n");
        }
    }
}
