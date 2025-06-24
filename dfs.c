#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int n;
int a[MAX][MAX];
int state[MAX];
int stack[MAX];
int top = -1;

void push(int v) {
    if (top == (MAX - 1)) {
        printf("\nError: Stack Overflow\n");
        return;
    }
    top++;
    stack[top] = v;
}

int pop() {
    int v;
    if (top == -1) {
        printf("\nStack Underflow\n");
        exit(1);
    } else {
        v = stack[top];
        top--;
        return v;
    }
}

int isEmpty() {
    if (top == -1)
        return 1;
    else
        return 0;
}

void DFS(int v) {
    int i;
    push(v);
    while (!isEmpty()) {
        v = pop();
        if (state[v] == 1) {
            printf("%d ", v);
            state[v] = 2;
        }
        for (i = n - 1; i >= 0; i--) {
            if (a[v][i] == 1 && state[i] == 1)
                push(i);
        }
    }
}

void DFS_t() {
    int v;
    for (v = 0; v < n; v++)
        state[v] = 1;
    printf("\nEnter start node for DFS : ");
    scanf("%d", &v);
    DFS(v);
    printf("\n");
}

void createGraph() {
    int i, maxEdges, origin, destin;
    printf("\nEnter number of nodes : ");
    scanf("%d", &n);
    maxEdges = n * (n - 1);
    for (i = 1; i <= maxEdges; i++) {
        printf("\nEnter edge %d( -3 -3 to quit ) : ", i);
        scanf("%d %d", &origin, &destin);
        if ((origin == -3) && (destin == -3))
            break;
        if (origin >= n || destin >= n || origin < 0 || destin < 0) {
            printf("\nInvalid Edge/ Node!\n");
            i--;
        } else {
            a[origin][destin] = 1;
        }
    }
}

void main() {
    printf("DEPTH FIRST SEARCH");
    createGraph();
    DFS_t();
}
