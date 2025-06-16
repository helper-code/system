#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30
#define EPSILON '#' // epsilon symbol
// Grammar Production Rules
char production[10][10] = {
 "E=TX",
 "X=+TX",
 "X=#",
 "T=FY",
 "Y=*FY",
 "Y=#",
 "F=(E)",
 "F=id"
};
// Parse table: 5 non-terminals x 6 terminals
char table[5][6][10];
// Non-terminals: E, X (E'), T, Y (T'), F
// Terminals: i (id), +, *, (, ), $
char terminals[] = {'i', '+', '*', '(', ')', '$'};
int getNonTerminalIndex(char c) {
 switch (c) {
 case 'E': return 0;
 case 'X': return 1;
 case 'T': return 2;
 case 'Y': return 3;
 case 'F': return 4;
 default: return -1;
 }
}
int getTerminalIndex(char c) {
 switch (c) {
 case 'i': return 0; // id
 case '+': return 1;
 case '*': return 2;
 case '(': return 3;
 case ')': return 4;
 case '$': return 5;
 default: return -1;
 }
}
// Initialize parse table with "error"
void initParseTable() {
 for (int i = 0; i < 5; i++)
 for (int j = 0; j < 6; j++)
 strcpy(table[i][j], "error");
}
// Manually fill the parse table
void fillParseTable() {
 strcpy(table[0][0], "TX"); // E → TX
 strcpy(table[0][3], "TX"); // E → TX
 strcpy(table[1][1], "+TX"); // X → +TX
 strcpy(table[1][4], "#"); // X → ε
 strcpy(table[1][5], "#"); // X → ε
 strcpy(table[2][0], "FY"); // T → FY
 strcpy(table[2][3], "FY"); // T → FY
 strcpy(table[3][1], "#"); // Y → ε
 strcpy(table[3][2], "*FY"); // Y → *FY
 strcpy(table[3][4], "#"); // Y → ε
 strcpy(table[3][5], "#"); // Y → ε
 strcpy(table[4][0], "i"); // F → id
 strcpy(table[4][3], "(E)"); // F → (E)
}
// Display the parse table
void displayParseTable() {
 printf("\nParse Table:\n");
 printf("\t i\t +\t *\t (\t )\t $\n");
 for (int i = 0; i < 5; i++) {
 printf("%c\t", "EXTYF"[i]);
 for (int j = 0; j < 6; j++) {
 printf("%s\t", table[i][j]);
 }
 printf("\n");
 }
}
// Simulate LL(1) parsing
void parseInput(char input[]) {
 char stack[MAX];
 int top = 0;
 stack[top] = '$';
 stack[++top] = 'E'; // Start symbol
 int i = 0;
 printf("\nStack\tInput\tAction\n");
 printf("--------------------------------------------\n");
 while (top >= 0) {
 // Display Stack
 for (int k = 0; k <= top; k++) printf("%c", stack[k]);
 printf("\t%s\t", &input[i]);
 if (stack[top] == input[i]) {
 printf("Match %c\n", input[i]);
 top--;
 i++;
 } else if (stack[top] == '$') {
 printf("Error!\n");
 break;
 } else {
 int row = -1, col = -1;
 if (stack[top] == 'E') row = 0;
 else if (stack[top] == 'X') row = 1;
 else if (stack[top] == 'T') row = 2;
 else if (stack[top] == 'Y') row = 3;
 else if (stack[top] == 'F') row = 4;
 if (input[i] == 'i') col = 0;
 else if (input[i] == '+') col = 1;
 else if (input[i] == '*') col = 2;
 else if (input[i] == '(') col = 3;
 else if (input[i] == ')') col = 4;
 else if (input[i] == '$') col = 5;
 if (row == -1 || col == -1 || strcmp(table[row][col], "error") == 0) {
 printf("Error!\n");
 break;
 } else if (strcmp(table[row][col], "#") == 0) {
 printf("Pop epsilon\n");
 top--;
 } else {
 printf("Output: %c -> %s\n", stack[top], table[row][col]);
 char temp[10];
 strcpy(temp, table[row][col]);
 top--;
 for (int k = strlen(temp) - 1; k >= 0; k--) {
 if (temp[k] != EPSILON)
 stack[++top] = temp[k];
 }
 }
 }
 }
 // Final ACCEPT / REJECT
 if (top == -1 && input[i] == '\0') {
 printf("\nAccepted!\n");
 } else {
 printf("\nRejected!\n");
 }
}
int main() {
 initParseTable();
 fillParseTable();
 displayParseTable();
 char input[30];
 printf("\nEnter the input string (use 'i' for id, end with $): ");
 scanf("%s", input);
 parseInput(input);
 return 0;
}

