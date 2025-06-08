#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100
#define MAX_TOKENS 1000

// Define a structure to store symbol table entries
typedef struct {
    char token[MAX_TOKEN_LEN];
    char type[30];
    char scope[10];
    void *memory_address;
    char value[MAX_TOKEN_LEN];
} Symbol;

// List of C keywords
const char *keywords[] = {"int", "return", "if", "else", "while", "for", "printf", "float", "char", "double", "void", "main"};
int keyword_count = 11;

// Function to check if a token is a keyword
int is_keyword(char *token) {
    for (int i = 0; i < keyword_count; i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1; // It's a keyword
        }
    }
    return 0; // Not a keyword
}

// Function to check if a character is an operator
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>');
}

// Function to check if a character is punctuation
int is_punctuation(char c) {
    return (c == ',' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']');
}

int main() {
    FILE *file = fopen("input.c", "r");
    if (!file) {
        printf("Error: Could not open input file!\n");
        return 1;
    }

    Symbol symbolTable[MAX_TOKENS];
    int symbolCount = 0;
    char buffer[MAX_TOKEN_LEN];
    char c;
    int index = 0;
    int insideString = 0;
    int braceLevel = 0; // Track number of open '{'
    int inFunction = 0; // Are we inside a function?

    printf("\nReading C program from file...\nProcessed Code:\n");

    while ((c = fgetc(file)) != EOF) {
        printf("%c", c);

        if (c == '"') {
            insideString = !insideString;
        }

        if (c == '{') {
            braceLevel++;
            if (braceLevel == 1)
                inFunction = 1; // Entering function body
        } else if (c == '}') {
            braceLevel--;
            if (braceLevel == 0)
                inFunction = 0; // Exiting function body
        }

        if (insideString || isalnum(c) || c == '#' || c == '_') {
            buffer[index++] = c;
        } else {
            if (index > 0) {
                buffer[index] = '\0';
                index = 0;

                if (buffer[0] == '#') {
                    strcpy(symbolTable[symbolCount].type, "Preprocessor Directive");
                    strcpy(symbolTable[symbolCount].scope, "Global");
                } else if (is_keyword(buffer)) {
                    strcpy(symbolTable[symbolCount].type, "Keyword");
                    strcpy(symbolTable[symbolCount].scope, "Global");
                } else if (isdigit(buffer[0])) {
                    strcpy(symbolTable[symbolCount].type, "Integer");
                    strcpy(symbolTable[symbolCount].scope, inFunction ? "Local" : "Global");
                    strcpy(symbolTable[symbolCount].value, buffer);
                } else {
                    strcpy(symbolTable[symbolCount].type, "Identifier");
                    strcpy(symbolTable[symbolCount].scope, inFunction ? "Local" : "Global");
                }

                strcpy(symbolTable[symbolCount].token, buffer);
                symbolTable[symbolCount].memory_address = malloc(1);
                symbolCount++;
            }

            if (is_operator(c)) {
                Symbol op;
                sprintf(op.token, "%c", c);
                strcpy(op.type, "Operator");
                strcpy(op.scope, "-");
                op.memory_address = malloc(1);
                symbolTable[symbolCount++] = op;
            } else if (is_punctuation(c)) {
                Symbol punc;
                sprintf(punc.token, "%c", c);
                strcpy(punc.type, "Punctuation");
                strcpy(punc.scope, "-");
                punc.memory_address = malloc(1);
                symbolTable[symbolCount++] = punc;
            }
        }
    }

    fclose(file);

    printf("\n\nSymbol Table\n");
    printf("%-15s %-25s %-10s %-20s %-10s\n", "Symbol", "Type", "Scope", "Memory Address", "Value");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < symbolCount; i++) {
        printf("%-15s %-25s %-10s %-20p %-10s\n",
               symbolTable[i].token, symbolTable[i].type, symbolTable[i].scope,
               symbolTable[i].memory_address, symbolTable[i].value);
    }

    return 0;
}
	

