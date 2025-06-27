#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct {
char name[50];
char type[50];
int size;
char scope[50];
int address;
int line_no;
struct Symbol *ptr_address;
} Symbol;
typedef struct {
Symbol *array;
size_t size;
size_t capacity;
} SymbolTable;
void initTable(SymbolTable *table, size_t initialSize) {
table->array = (Symbol *)malloc(initialSize * sizeof(Symbol));
table->size = 0;
table->capacity = initialSize;
}
void insertTable(SymbolTable *table, Symbol symbol) {
if (table->size == table->capacity) {
table->capacity *= 2;
table->array = (Symbol *)realloc(table->array, table->capacity * sizeof(Symbol));
}
table->array[table->size] = symbol;
table->array[table->size].ptr_address = &table->array[table->size];
table->size++;
}
void freeTable(SymbolTable *table) {
free(table->array);
}
int getSize(const char *type) {
if (strcmp(type, "int") == 0) return 4;
if (strcmp(type, "float") == 0) return 4;
if (strcmp(type, "double") == 0) return 8;
if (strcmp(type, "char") == 0) return 1;
return 0;
}
void parseLine(char *line, SymbolTable *table, int *address, int line_no, char *scope) {
char *token = strtok(line, " ");
char type[50];
char name[50];
while (token != NULL) {
if (strcmp(token, "int") == 0 || strcmp(token, "float") == 0 ||
strcmp(token, "double") == 0 || strcmp(token, "char") == 0) {
strcpy(type, token);
token = strtok(NULL, " ,;(){}=");
if (token != NULL && isalpha(token[0])) {
strcpy(name, token);
Symbol symbol;
strcpy(symbol.name, name);
strcpy(symbol.type, type);
symbol.size = getSize(type);
symbol.address = (*address)++;
strcpy(symbol.scope, scope);
symbol.line_no = line_no;
insertTable(table, symbol); } }
token = strtok(NULL, " ,;(){}=");
} }
void parseFunction(char *line, SymbolTable *table, int line_no) {
char *token = strtok(line, " ");
char returnType[50];
char funcName[50];
char params[100];
if (token != NULL) {
strcpy(returnType, token);
token = strtok(NULL, " ,;(){}=");
}
if (token != NULL && isalpha(token[0])) {
strcpy(funcName, token);
Symbol symbol;
strcpy(symbol.name, funcName);
strcpy(symbol.type, "function");
symbol.size = 0;
symbol.address = -1;
strcpy(symbol.scope, "global");
symbol.line_no = line_no;
insertTable(table, symbol);
token = strtok(NULL, "()");
}
if (token != NULL) {
strcpy(params, token);
char *param = strtok(params, ",");
while (param != NULL) {
char paramType[50];
char paramName[50];
sscanf(param, "%s %s", paramType, paramName);
Symbol symbol;
strcpy(symbol.name, paramName);
strcpy(symbol.type, paramType);
symbol.size = getSize(paramType);
symbol.address = -1;
strcpy(symbol.scope, "function parameter");
symbol.line_no = line_no;
insertTable(table, symbol);
param = strtok(NULL, ",");
} } }
void parseFile(FILE *file, SymbolTable *table) {
char line[256];
int address = 1000;
int line_no = 0;
char scope[50] = "global";
while (fgets(line, sizeof(line), file)) {
line_no++;
if (strstr(line, "int") != NULL || strstr(line, "float") != NULL ||
strstr(line, "double") != NULL || strstr(line, "char") != NULL) {
if (strstr(line, "(") != NULL && strstr(line, ")") != NULL) {
parseFunction(line, table, line_no);
sscanf(line, "%*s %*s %*s %s", scope);
} else {
parseLine(line, table, &address, line_no, scope);
} } } }
int main() {
FILE *file = fopen("input.txt", "r");
if (file == NULL) {
perror("Unable to open file!");
return EXIT_FAILURE;
}
SymbolTable table;
initTable(&table, 10);
parseFile(file, &table);
fclose(file);
printf("%-5s %-10s %-5s %-18s %-8s %-20s\n", "NAME", "TYPE", "SIZE", "SCOPE", "LINE_NO", "PTR_ADDRESS");
for (size_t i = 0; i < table.size; i++) {
Symbol symbol = table.array[i];
printf("%-5s %-10s %-5d %-18s %-8d %p\n",
symbol.name,
symbol.type,
symbol.size,
symbol.scope,
symbol.line_no,
(void*)symbol.ptr_address);
}
freeTable(&table);
return 0;
}
