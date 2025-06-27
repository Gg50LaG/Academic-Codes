%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>
void validatePAN(char* panNumber, char* name);
%}
%%
[A-Z]+[[:space:]]+[A-Z]*[0-9]*[A-Z] {
char name[100];
char panNumber[12];
sscanf(yytext, "%s %s", name, panNumber);
validatePAN(panNumber, name);
}
.|\n {}
%%
void validatePAN(char* panNumber, char* name) {
if (strlen(panNumber) != 10) {
printf("INVALID\n");
return;
}
for (int i = 0; i < 5; i++) {
if (!isupper(panNumber[i])) {
printf("INVALID\n");
return;
}
}
for (int i = 5; i < 9; i++) {
if (!isdigit(panNumber[i])) {
printf("INVALID\n");
return;
}
}
if (!isupper(panNumber[9])) {
printf("INVALID\n");
return;
}
if (panNumber[9] != name[0]) {
printf("INVALID\n");
} else {
printf("VALID\n");
}
}
int yywrap() {
return 1;
}
int main(int argc, char *argv[]) {
FILE *inputFile;
if (argc > 1) {
inputFile = fopen(argv[1], "r");
if (inputFile) {
yyin = inputFile;
yylex();
fclose(inputFile);
} else {
printf("Error opening file: %s\n", argv[1]);
}
} else {
printf("Please provide an input file.\n");
}
return 0;
}
