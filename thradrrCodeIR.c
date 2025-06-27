#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX 100
struct Quadruple {
char op[MAX],arg1[MAX],arg2[MAX],result[MAX];
};
struct Triple {
char op[MAX],arg1[MAX],arg2[MAX];
};
struct Stack {
char items[MAX][MAX];
int top;
};
void initStack(struct Stack* s) {
s->top = -1;
}
bool isEmpty(struct Stack* s) {
return s->top == -1;
}
void push(struct Stack* s, const char* item) {
if (s->top < MAX - 1)
strcpy(s->items[++(s->top)], item);
}
char* pop(struct Stack* s) {
if (!isEmpty(s))
return s->items[(s->top)--];
return NULL;
}
char* peek(struct Stack* s) {
if (!isEmpty(s))
return s->items[s->top];
return NULL;
}
bool isOperator(char c) {
return c == '+' || c == '-' || c == '*' || c == '/';
}
bool isUnaryMinus(const char* expression, size_t pos) {
return (pos == 0 || expression[pos - 1] == '(' || isOperator(expression[pos - 1])) && expression[pos] == '-';
}
int getPrecedence(char op) {
if (op == '+' || op == '-') return 1;
if (op == '*' || op == '/') return 2;
return 0;
}
void infixToPostfix(const char* equation, char postfix[][MAX], int* size) {
struct Stack operators;
initStack(&operators);
char currentVar[MAX];
size_t length = strlen(equation);
*size = 0;
for (size_t i = 0; i < length; ++i) {
char c = equation[i];
if (c == ' ') continue;
if (isalnum(c)) {
int j = 0;
while (isalnum(c)) {
currentVar[j++] = c;
c = equation[++i];
}
currentVar[j] = '\0';
strcpy(postfix[(*size)++], currentVar);
--i;
} else {
if (isUnaryMinus(equation, i)) {
push(&operators, "u");
} else if (isOperator(c)) {
while (!isEmpty(&operators) && peek(&operators) != NULL && strcmp(peek(&operators), "(") != 0 && getPrecedence(peek(&operators)[0]) >= getPrecedence(c)) {
strcpy(postfix[(*size)++], pop(&operators));
}
char op[2] = {c, '\0'};
push(&operators, op);
} else if (c == '(') {
char openParen[] = "(";
push(&operators, openParen);
} else if (c == ')') {
while (!isEmpty(&operators) && strcmp(peek(&operators), "(") != 0) {
strcpy(postfix[(*size)++], pop(&operators));
}
pop(&operators);
}
}
}
while (!isEmpty(&operators))
strcpy(postfix[(*size)++], pop(&operators));
}
void generateQuadruples(char postfix[][MAX], int size, const char* assignmentVar, struct Quadruple* quadruples, int* quadCount) {
struct Stack operands;
initStack(&operands);
int i,tempCount = 1;
*quadCount = 0;
for ( i = 0; i < size; ++i) {
char* token = postfix[i];
if (strcmp(token, "u") == 0) {
if (isEmpty(&operands)) {
printf("ERROR!\nError: Invalid equation format.\n");
exit(1);
}
char* arg1 = pop(&operands);
char result[MAX];
sprintf(result, "t%d", tempCount++);
strcpy(quadruples[(*quadCount)++].op, "uminus");
strcpy(quadruples[*quadCount - 1].arg1, arg1);
strcpy(quadruples[*quadCount - 1].result, result);
push(&operands, result);
} else if (isOperator(token[0])) {
if (operands.top < 1) {
printf("ERROR!\nError: Invalid equation format.\n");
exit(1);
}
char* arg2 = pop(&operands);
char* arg1 = pop(&operands);
char result[MAX];
sprintf(result, "t%d", tempCount++);
strcpy(quadruples[(*quadCount)++].op, token);
strcpy(quadruples[*quadCount - 1].arg1, arg1);
strcpy(quadruples[*quadCount - 1].arg2, arg2);
strcpy(quadruples[*quadCount - 1].result, result);
push(&operands, result);
} else
push(&operands, token);
}
if (!isEmpty(&operands)) {
char* result = pop(&operands);
strcpy(quadruples[(*quadCount)++].op, "=");
strcpy(quadruples[*quadCount - 1].arg1, result);
strcpy(quadruples[*quadCount - 1].result, assignmentVar);
}
}
void generateTriples(struct Quadruple quadruples[], int quadruplesSize, struct Triple triples[]) {
int i;
for ( i = 0; i < quadruplesSize; ++i) {
struct Quadruple quad = quadruples[i];
char arg1[10], arg2[10];
if (strncmp(quad.arg1, "t", 1) == 0) {
sprintf(arg1, "(%d)", i);
} else {
strcpy(arg1, quad.arg1);
}
if (strncmp(quad.arg2, "t", 1) == 0) {
sprintf(arg2, "(%d)", i - 1);
} else {
strcpy(arg2, quad.arg2);
}
strcpy(triples[i].op, quad.op);
strcpy(triples[i].arg1, arg1);
strcpy(triples[i].arg2, arg2);
}
}
void generateThreeAddressCode(struct Quadruple* quadruples, int quadCount) {
printf("\nThree Address Code Representation:\n"); int i;
for ( i = 0; i < quadCount; ++i) {
if (strcmp(quadruples[i].op, "uminus") == 0) {
printf("%s = -%s\n", quadruples[i].result, quadruples[i].arg1);
} else if (strcmp(quadruples[i].op, "=") == 0) {
printf("%s = %s\n", quadruples[i].result, quadruples[i].arg1);
} else {
printf("%s = %s %s %s\n", quadruples[i].result, quadruples[i].arg1, quadruples[i].op, quadruples[i].arg2);
}
}
}
int main() {
char equation[MAX],assignmentVar[MAX],expression[MAX];
printf("Enter an equation: ");
fgets(equation, sizeof(equation), stdin);
equation[strcspn(equation, "\n")] = '\0';
size_t equalPos = strcspn(equation, "=");
strncpy(assignmentVar, equation, equalPos);
assignmentVar[equalPos] = '\0';
strcpy(expression, equation + equalPos + 1);
char postfix[MAX][MAX];
int i,size = 0,quadCount = 0;
infixToPostfix(expression, postfix, &size);
struct Quadruple quadruples[MAX];
generateQuadruples(postfix, size, assignmentVar, quadruples, &quadCount);
printf("\nQuadruples Representation:\n");
printf("%-5s %-10s %-10s %-10s %-10s\n", "Idx", "Op", "Arg1", "Arg2", "Result");
for ( i = 0; i < quadCount; ++i) {
printf("%-5d %-10s %-10s %-10s %-10s\n", i, quadruples[i].op, quadruples[i].arg1, quadruples[i].arg2, quadruples[i].result);
}
struct Triple triples[MAX];
generateTriples(quadruples, quadCount, triples);
printf("\nTriples Representation:\n");
printf("%-5s %-10s %-10s %-10s\n", "Idx", "Op", "Arg1", "Arg2");
for ( i = 0; i < quadCount; ++i) {
printf("%-5d %-10s %-10s %-10s\n", i, triples[i].op, triples[i].arg1, triples[i].arg2);
}
generateThreeAddressCode(quadruples, quadCount);
return 0;
}
