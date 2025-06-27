#include <stdio.h>
#include <string.h>
void generateThreeAddressCode(char *input) {
char var1[10], var2[10], op[10];
int baseAddress = 100;
char assignment1[50], assignment2[50];
sscanf(input, "%[^;]; %[^;]; if", assignment1, assignment2);
printf("%d: %s;\n", baseAddress, assignment1);
printf("%d: %s;\n", baseAddress + 1, assignment2);
baseAddress += 2;
sscanf(input, "%*[^if]if (%s %9s %s)", var1, op, var2);
printf("%d: if %s %s %s goto %d\n", baseAddress, var1, op, var2, baseAddress + 3);
printf("%d: return 0\n", baseAddress + 1);
printf("%d: goto %d\n", baseAddress + 2, baseAddress + 4);
printf("%d: return 1\n", baseAddress + 3);
printf("%d: \n",baseAddress + 4);
}
int main() {
FILE *file;
char filename[100], input[200], buffer[50];
printf("Enter the filename: ");
scanf("%s", filename);
file = fopen(filename, "r");
if (file == NULL) {
printf("Error opening file.\n");
return 1;
}
input[0] = '\0';
while (fgets(buffer, sizeof(buffer), file) != NULL) {
buffer[strcspn(buffer, "\n")] = 0;
strcat(input, buffer);
strcat(input, " ");
}
fclose(file);
generateThreeAddressCode(input);
return 0;
}
