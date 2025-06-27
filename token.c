#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_TOKEN_LENGTH 100
#define MAX_INPUT_LENGTH 10000
#define MAX_UNIQUE_TOKENS 1000
enum TokenType {
TOKEN_IDENTIFIER,
TOKEN_NUMBER,
TOKEN_OPERATOR,
TOKEN_PUNCTUATION,
TOKEN_LITERAL,
TOKEN_KEYWORD,
TOKEN_COMMENT,
TOKEN_UNKNOWN
};
struct Token {
enum TokenType type;
char value[MAX_TOKEN_LENGTH];
};
void addUniqueToken(char *tokenArray[], int *size, const char *value) {
for (int i = 0; i < *size; i++) {
if (strcmp(tokenArray[i], value) == 0) {
return;
} }
tokenArray[*size] = strdup(value);
(*size)++;
}
int isKeyword(const char *value) {
const char *keywords[] = {
"auto", "double", "int", "const", "struct", "short", "float", "unsigned",
"break", "else", "long", "continue", "switch", "for", "signed", "void",
"case", "enum", "register", "default", "typedef", "goto", "sizeof", "volatile",
"char", "extern", "return", "do", "union", "if", "static", "while"
};
for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
if (strcmp(value, keywords[i]) == 0) {
return 1;
}}
return 0;
}
void getNextToken(const char *input, int *currentIndex, struct Token *token) {
int index = 0;
char ch;
while (isspace(input[*currentIndex])) {
(*currentIndex)++;
}
ch = input[*currentIndex];
if (ch == '\0') {
token->type = TOKEN_UNKNOWN;
token->value[0] = '\0';
return;
}
if (ch == '/' && input[*currentIndex + 1] == '/') {
token->type = TOKEN_COMMENT;
(*currentIndex) += 2;
while (input[*currentIndex] != '\n' && input[*currentIndex] != '\0') {
token->value[index++] = input[*currentIndex];
(*currentIndex)++;
}
token->value[index] = '\0';
return;
}
if (ch == '/' && input[*currentIndex + 1] == '*') {
token->type = TOKEN_COMMENT;
(*currentIndex) += 2;
while (!(input[*currentIndex] == '*' && input[*currentIndex + 1] == '/') && input[*currentIndex] != '\0') {
token->value[index++] = input[*currentIndex];
(*currentIndex)++;
}
if (input[*currentIndex] == '*' && input[*currentIndex + 1] == '/') {
(*currentIndex) += 2;
}
token->value[index] = '\0';
return;
}
if (ch == '"') {
(*currentIndex)++;
token->type = TOKEN_LITERAL;
while (input[*currentIndex] != '"' && input[*currentIndex] != '\0') {
token->value[index++] = input[*currentIndex];
(*currentIndex)++;
}
if (input[*currentIndex] == '"') {
(*currentIndex)++;
}
token->value[index] = '\0';
return;
}
if (isalpha(ch) || ch == '_') {
while (isalnum(ch) || ch == '_') {
token->value[index++] = ch;
(*currentIndex)++;
ch = input[*currentIndex];
}
token->value[index] = '\0';
if (isKeyword(token->value)) {
token->type = TOKEN_KEYWORD;
} else {
token->type = TOKEN_IDENTIFIER;
}
return; }
if (isdigit(ch)) {
while (isdigit(ch)) {
token->value[index++] = ch;
(*currentIndex)++;
ch = input[*currentIndex];
}
token->value[index] = '\0';
token->type = TOKEN_NUMBER;
return; }
if (strchr("+-*/=", ch)) {
token->value[index++] = ch;
token->value[index] = '\0';
token->type = TOKEN_OPERATOR;
(*currentIndex)++;
return;
}
if (strchr("(){}[],;", ch)) {
token->value[index++] = ch;
token->value[index] = '\0';
token->type = TOKEN_PUNCTUATION;
(*currentIndex)++;
return;
}
token->value[index++] = ch;
token->value[index] = '\0';
token->type = TOKEN_UNKNOWN;
(*currentIndex)++;
}
void processFile(const char *filename) {
FILE *file = fopen(filename, "r");
if (file == NULL) {
perror("Unable to open file!");
exit(EXIT_FAILURE);
}
fseek(file, 0, SEEK_END);
long fileSize = ftell(file);
fseek(file, 0, SEEK_SET);
char *str = (char *)malloc(fileSize + 1);
fread(str, 1, fileSize, file);
str[fileSize] = '\0';
fclose(file);
int currentIndex = 0;
struct Token token;
char *keywords[MAX_UNIQUE_TOKENS];
char *identifiers[MAX_UNIQUE_TOKENS];
char *numbers[MAX_UNIQUE_TOKENS];
char *operators[MAX_UNIQUE_TOKENS];
char *punctuations[MAX_UNIQUE_TOKENS];
char *literals[MAX_UNIQUE_TOKENS];
char *comments[MAX_UNIQUE_TOKENS];
int keywordCount = 0;
int identifierCount = 0;
int numberCount = 0;
int operatorCount = 0;
int punctuationCount = 0;
int literalCount = 0;
int commentCount = 0;
while (str[currentIndex] != '\0') {
getNextToken(str, &currentIndex, &token);
switch (token.type) {
case TOKEN_KEYWORD:
addUniqueToken(keywords, &keywordCount, token.value);
break;
case TOKEN_IDENTIFIER:
addUniqueToken(identifiers, &identifierCount, token.value);
break;
case TOKEN_NUMBER:
addUniqueToken(numbers, &numberCount, token.value);
break;
case TOKEN_OPERATOR:
addUniqueToken(operators, &operatorCount, token.value);
break;
case TOKEN_PUNCTUATION:
addUniqueToken(punctuations, &punctuationCount, token.value);
break;
case TOKEN_LITERAL:
addUniqueToken(literals, &literalCount, token.value);
break;
case TOKEN_COMMENT:
addUniqueToken(comments, &commentCount, token.value);
break;
default:
break;
} }
printf("\nTokens:");
printf("\nKeywords: ");
for (int i = 0; i < keywordCount; i++) {
printf("%s ", keywords[i]);
free(keywords[i]);
}
printf("\nIdentifiers: ");
for (int i = 0; i < identifierCount; i++) {
printf("%s ", identifiers[i]);
free(identifiers[i]);
}
printf("\nNumbers: ");
for (int i = 0; i < numberCount; i++) {
printf("%s ", numbers[i]);
free(numbers[i]);
}
printf("\nOperators: ");
for (int i = 0; i < operatorCount; i++) {
printf("%s ", operators[i]);
free(operators[i]);
}
printf("\nSpecial symbols or delimiters: ");
for (int i = 0; i < punctuationCount; i++) {
printf("%s ", punctuations[i]);
free(punctuations[i]);
}
printf("\nLiterals: ");
for (int i = 0; i < literalCount; i++) {
printf("%s ", literals[i]);
free(literals[i]);
}
printf("\nNon Tokens:");
printf("\nComments: ");
for (int i = 0; i < commentCount; i++) {
printf("%s ", comments[i]);
free(comments[i]);
} free(str);}
int main() {
processFile("input.txt");
return 0;
}
