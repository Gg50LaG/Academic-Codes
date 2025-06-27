#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100
#define MAX_VARS 100
typedef struct {
char var[10];
char expression[MAX_LEN];
int is_used;
} Variable;
Variable vars[MAX_VARS];
int var_count = 0;
void mark_used_variables() {
for (int i = 0; i < var_count; i++) {
for (int j = 0; j < var_count; j++) {
if (strstr(vars[i].expression, vars[j].var) != NULL) {
vars[j].is_used = 1;
}
}
}
}
void dead_code_elimination() {
printf("After dead code elimination\n");
for (int i = 0; i < var_count; i++) {
if (vars[i].is_used) {
printf("%s=%s\n", vars[i].var, vars[i].expression);
}
}
}
void common_subexpression_elimination() {
printf("\nEliminate Common Expression\n");
for (int i = 0; i < var_count; i++) {
for (int j = i + 1; j < var_count; j++) {
if (strcmp(vars[i].expression, vars[j].expression) == 0) {
strcpy(vars[j].expression, vars[i].var);
}
}
}
for (int i = 0; i < var_count; i++) {
printf("%s=%s\n", vars[i].var, vars[i].expression);
}
}
void optimize_code() {
printf("\nOptimized code\n");
for (int i = 0; i < var_count; i++) {
if (vars[i].is_used) {
printf("%s=%s\n", vars[i].var, vars[i].expression);
}
}
}
int main() {
FILE *file;
char line[MAX_LEN];
file = fopen("input.txt", "r");
if (!file) {
printf("Error: Could not open file\n");
return 1;
}
while (fgets(line, sizeof(line), file)) {
char var[10];
char expression[MAX_LEN];
if (sscanf(line, "%[^=]=%[^\n]", var, expression) == 2) {
strcpy(vars[var_count].var, var);
strcpy(vars[var_count].expression, expression);
vars[var_count].is_used = 0;
var_count++;
}
}
fclose(file);
vars[var_count - 1].is_used = 1;
mark_used_variables();
dead_code_elimination();
common_subexpression_elimination();
optimize_code();
return 0;
}
