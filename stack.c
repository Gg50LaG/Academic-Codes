#include <stdio.h>

void push(int x);
int pop();
void peek();
void display();

int size, top = -1;
int stk[10], x, i;

void main() {
    int opt, ch, ele;

    printf("\nEnter the size of STACK: ");
    scanf("%d", &size);

    do {
        printf("Enter the Choice (1.PUSH 2.POP 3.DISPLAY 4.PEEK): ");
        scanf("%d", &opt);

        switch (opt) {
            case 1:
                printf("Enter a value to be pushed: ");
                scanf("%d", &ele);
                push(ele);
                break;
            case 2:
                pop();
                break;
            case 3:
                display();
                break;
            case 4:
                peek();
                break;
            default:
                printf("\nPlease Enter a Valid Choice (1/2/3/4)");
        }

        printf("\nDo you wish to continue (1-YES/0-NO): ");
        scanf("%d", &ch);
    } while (ch == 1);
}

void push(int x) {
    if (top >= size - 1) {
        printf("\nSTACK is over flow");
    } else {
        top++;
        stk[top] = x;
    }
}

int pop() {
    if (top <= -1) {
        printf("\nStack is under flow");
        return -1;
    } else {
        x = stk[top];
        top--;
        return x;
    }
}

void display() {
    if (top >= 0) {
        printf("\nThe elements in STACK");
        for (i = 0; i <= top; i++)
            printf("\n%d", stk[i]);
    } else {
        printf("\nThe STACK is empty");
    }
}

void peek() {
    if (top == -1) {
        printf("\nThe STACK is empty");
    } else {
        printf("\nThe TOP MOST element in the STACK is %d", stk[top]);
    }
}
