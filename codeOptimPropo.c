#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
int values[150];
int main() {
int j, i = 0;
int no_of_lines = 0;
char lines[20][20];
FILE *file;
file = fopen("input1.txt", "r");
if (file == NULL) {
printf("Error opening file.\n");
return 1;
}
while (fgets(lines[no_of_lines], sizeof(lines[no_of_lines]), file) != NULL) {
lines[no_of_lines][strcspn(lines[no_of_lines], "\n")] = '\0';
no_of_lines++;
}
fclose(file);
printf("After constant propagation\n");
for (i = 0; i < no_of_lines; i++) {
int flag = 0;
for (j = 2; j < strlen(lines[i]); j++) {
if (isalpha(lines[i][j])) {
flag = 1;
}
}
if (flag == 0) {
int j;
char temp[20];
for (j = 2; j < strlen(lines[i]); j++)
temp[j - 2] = lines[i][j];
temp[j - 2] = '\0';
int value = atoi(temp);
values[lines[i][0]] = value;
} else {
int operand1, operand2;
if (isalpha(lines[i][2]))
operand1 = values[lines[i][2]];
else {
int j;
char temp[20];
for (j = 2; isdigit(lines[i][j]); j++)
temp[j - 2] = lines[i][j];
temp[j - 2] = '\0';
operand1 = atoi(temp);
}
char operator;
for (j = 2; isalnum(lines[i][j]); j++);
operator = lines[i][j];
if (isalpha(lines[i][j + 1]))
operand2 = values[lines[i][j + 1]];
else {
int k, index = 0;
char temp[20];
for (k = j + 1; isdigit(lines[i][k]); k++)
temp[index++] = lines[i][k];
temp[index] = '\0';
operand2 = atoi(temp);
}
printf("%c=%d%c%d\n", lines[i][0], operand1, operator, operand2);
switch (operator) {
case '+':
printf("Result: %d\n", operand1 + operand2);
values[lines[i][0]] = operand1 + operand2;
break;
case '-':
printf("Result: %d\n", operand1 - operand2);
values[lines[i][0]] = operand1 - operand2;
break;
case '*':
printf("Result: %d\n", operand1 * operand2);
values[lines[i][0]] = operand1 * operand2;
break;
case '/':
if (operand2 != 0) {
printf("Result: %d\n", operand1 / operand2);
values[lines[i][0]] = operand1 / operand2;
} else {
printf("Error: Division by zero.\n");
}
break;
}
}
}
return 0;
}
