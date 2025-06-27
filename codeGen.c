#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
typedef struct {
char op[3];
char arg1[10];
char arg2[10];
char result[10];
} Quadruple;
char stack[MAX][10];
int top = -1;
Quadruple quadruples[MAX];
int quad_index = 0;
int temp_var_count = 1;
void push(char *str) {
strcpy(stack[++top], str);
}
char* pop() {
return top == -1 ? NULL : stack[top--];
}
int precedence(char op) {
if (op == '+' || op == '-') return 1;
if (op == '*' || op == '/') return 2;
if (op == '(') return 0;
return -1;
}
void infix_to_postfix(char *infix, char *postfix) {
int j = 0;
for (int i = 0; infix[i]; i++) {
char ch = infix[i];
if (isalnum(ch)) {
postfix[j++] = ch;
} else if (ch == '(') {
push("(");
} else if (ch == ')') {
while (strcmp(stack[top], "(") != 0) postfix[j++] = pop()[0];
pop();
} else {
while (top != -1 && precedence(stack[top][0]) >= precedence(ch)) postfix[j++] = pop()[0];
char op_str[2] = {ch, '\0'};
push(op_str);
}
}
while (top != -1) postfix[j++] = pop()[0];
postfix[j] = '\0';
}
void new_temp(char *temp) {
sprintf(temp, "t%d", temp_var_count++);
}
void generate_quadruples(char *postfix) {
char op1[10], op2[10], result[10];
for (int i = 0; postfix[i]; i++) {
char ch = postfix[i];
if (isalnum(ch)) {
char operand[2] = {ch, '\0'};
push(operand);
} else {
Quadruple q;
sprintf(q.op, "%c", ch);
strcpy(op2, pop());
strcpy(op1, pop());
strcpy(q.arg1, op1);
strcpy(q.arg2, op2);
new_temp(result);
strcpy(q.result, result);
push(result);
quadruples[quad_index++] = q;
}
}
}
void generate_machine_instructions() {
printf("\nMACHINE INSTRUCTIONS\n");
int reg_count = 0;
char reg_map[10][10];
for (int i = 0; i < quad_index; i++) {
int reg1 = -1, reg2 = -1;
for (int j = 0; j < reg_count; j++) {
if (strcmp(reg_map[j], quadruples[i].arg1) == 0) reg1 = j;
if (strcmp(reg_map[j], quadruples[i].arg2) == 0) reg2 = j;
}
if (reg1 == -1) {
printf("MOV R%d, %s\n", reg_count, quadruples[i].arg1);
strcpy(reg_map[reg_count], quadruples[i].arg1);
reg1 = reg_count++;
}
if (reg2 == -1) {
printf("MOV R%d, %s\n", reg_count, quadruples[i].arg2);
strcpy(reg_map[reg_count], quadruples[i].arg2);
reg2 = reg_count++;
}
int result_reg = reg_count++;
strcpy(reg_map[result_reg], quadruples[i].result);
if (strcmp(quadruples[i].op, "+") == 0) {
printf("ADD R%d, R%d, R%d\n", result_reg, reg1, reg2);
} else if (strcmp(quadruples[i].op, "-") == 0) {
printf("SUB R%d, R%d, R%d\n", result_reg, reg1, reg2);
} else if (strcmp(quadruples[i].op, "*") == 0) {
printf("MUL R%d, R%d, R%d\n", result_reg, reg1, reg2);
} else if (strcmp(quadruples[i].op, "/") == 0) {
printf("DIV R%d, R%d, R%d\n", result_reg, reg1, reg2);
}
}
}
int main() {
char infix[MAX], postfix[MAX];
printf("Enter the infix expression: ");
scanf("%s", infix);
infix_to_postfix(infix, postfix);
printf("Postfix Expression: %s\n", postfix);
generate_quadruples(postfix);
printf("\nQuadruple Table:\n");
printf("Ref\tOperator\tArg1\tArg2\tResult\n");
for (int i = 0; i < quad_index; i++) {
printf("%d\t%s\t\t%s\t%s\t%s\n", i, quadruples[i].op, quadruples[i].arg1, quadruples[i].arg2, quadruples[i].result);
}
generate_machine_instructions();
return 0;
}
