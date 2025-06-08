
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 100
#define EPSILON 'e'  // Representing epsilon as 'e'

// Grammar rules
typedef struct {
    char non_terminal;
    char productions[3][10];  // Max 3 productions per non-terminal
    int prod_count;
} GrammarRule;

GrammarRule grammar[] = {
    {'E', {"TX"}, 1},
    {'X', {"+TX", "e"}, 2},  // X → ε handled as 'e'
    {'T', {"F"}, 1}
};

int num_rules = sizeof(grammar) / sizeof(grammar[0]);
char parse_table[128][128][10];  // Stores production rules indexed by Non-Terminal & Terminal

// Function prototypes
void constructParseTable();
void displayParseTable();
void simulateParsing(const char*);
int isTerminal(char);
int getIndex(char);

int main() {
    constructParseTable();
    displayParseTable();

    char input[STACK_SIZE];
    printf("\nEnter input string: ");
    scanf("%s", input);
    strcat(input, "$");  // Append '$' as end marker

    simulateParsing(input);

    return 0;
}

// Check if character is a terminal
int isTerminal(char ch) {
    return (!isupper(ch) && ch != EPSILON && ch != '$');
}

// Get index of a non-terminal
int getIndex(char ch) {
    for (int i = 0; i < num_rules; i++) {
        if (grammar[i].non_terminal == ch) return i;
    }
    return -1;
}

// Construct LL(1) Parse Table
void constructParseTable() {
    for (int i = 0; i < num_rules; i++) {
        for (int j = 0; j < grammar[i].prod_count; j++) {
            char *prod = grammar[i].productions[j];
            char first = prod[0];

            if (isTerminal(first) || first == EPSILON) {
                strcpy(parse_table[grammar[i].non_terminal][first], prod);
            } else {
                strcpy(parse_table[grammar[i].non_terminal]['F'], prod);  // Example for 'F'
            }
        }
        if (grammar[i].non_terminal == 'X') {
            strcpy(parse_table['X']['$'], "e");  // ε handled as 'e'
        }
    }
}

// Display LL(1) Parse Table
void displayParseTable() {
    printf("\nLL(1) Parse Table:\n");
    printf("-------------------------------------------------\n");
    printf("Non-Terminal |  +   |  F   |  $   |\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < num_rules; i++) {
        printf("    %c        |", grammar[i].non_terminal);
        char terminals[] = {'+', 'F', '$'};
        for (int j = 0; j < 3; j++) {
            char *rule = parse_table[grammar[i].non_terminal][terminals[j]];
            printf(" %-3s |", (rule[0] != '\0') ? rule : "   ");
        }
        printf("\n-------------------------------------------------\n");
    }
}

// Simulate LL(1) Parsing
void simulateParsing(const char *input) {
    char stack[STACK_SIZE];
    int top = -1;
    stack[++top] = '$';
    stack[++top] = 'E';  // Start symbol

    int ip = 0;
    printf("\nParsing Steps:\n");
    printf("------------------------\n");
    printf("Stack          Input        Action\n");
    printf("------------------------\n");

    while (top >= 0) {
        char topStack = stack[top];
        char curInput = input[ip];

        // Print current stack state dynamically
for (int i = 0; i <= top; i++) {
    printf("%c", stack[i]);
}
printf("\t%-10s\t", input + ip);


        if (topStack == curInput) {  // Match terminal
            top--;
            ip++;
            printf("Match %c\n", curInput);
        } else if (isTerminal(topStack) || topStack == '$') {  // Error if unexpected symbol
            printf("Error: Unexpected symbol %c\n", curInput);
            return;
        } else {  // Apply production rule
            char *prod = parse_table[topStack][curInput];

            if (prod[0] == '\0') {
                printf("Error: No rule for %c\n", curInput);
                return;
            }

            printf("Apply %c -> %s\n", topStack, prod);
            top--;

            if (prod[0] != 'e') {  // Skip pushing 'ε'
                for (int i = strlen(prod) - 1; i >= 0; i--) {
                    stack[++top] = prod[i];
                }
            }
        }
    }

    if (top == -1 && input[ip] == '\0') {
        printf("\n String successfully parsed!\n");
    } else {
        printf("\n Parsing failed.\n");
    }
}