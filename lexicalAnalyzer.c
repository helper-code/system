#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_SIZE 100

// List of keywords
const char *keywords[] = {
    "int", "float", "return", "char", "if", "else", "while", "for", "double", "void"
};

int isKeyword(const char *str) {
    for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isSpecialSymbol(char ch) {
    return ch == ';' || ch == ',' || ch == '(' || ch == ')' ||
           ch == '{' || ch == '}' || ch == '=' || ch == '+' ||
           ch == '-' || ch == '*' || ch == '/' || ch == '<' || ch == '>';
}

int isOperator(char ch) {
    return ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '<' || ch == '>';
}

void printToken(const char *type, const char *value) {
    printf("<%s, %s>\n", type, value);
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    char ch, token[MAX_TOKEN_SIZE];
    int i = 0, inSingleLineComment = 0, inMultiLineComment = 0;
    char prev = '\0';

    while ((ch = fgetc(fp)) != EOF) {
        // Handle comments
        if (inSingleLineComment) {
            if (ch == '\n')
                inSingleLineComment = 0;
            continue;
        }
        if (inMultiLineComment) {
            if (prev == '*' && ch == '/')
                inMultiLineComment = 0;
            prev = ch;
            continue;
        }

        if (prev == '/' && ch == '/') {
            inSingleLineComment = 1;
            prev = '\0';
            continue;
        }
        if (prev == '/' && ch == '*') {
            inMultiLineComment = 1;
            prev = '\0';
            continue;
        }

        if (prev == '/' && ch != '/' && ch != '*') {
            token[0] = '/';
            token[1] = '\0';
            printToken("Operator", token);
        }

        // Tokenize strings
        if (ch == '"') {
            i = 0;
            token[i++] = ch;
            while ((ch = fgetc(fp)) != EOF && ch != '"') {
                token[i++] = ch;
            }
            token[i++] = '"';
            token[i] = '\0';
            printToken("String", token);
            prev = '\0';
            continue;
        }

        // Tokenize identifiers and keywords
        if (isalpha(ch) || ch == '_') {
            i = 0;
            token[i++] = ch;
            while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_')) {
                token[i++] = ch;
            }
            token[i] = '\0';
            if (isKeyword(token))
                printToken("Keyword", token);
            else
                printToken("Identifier", token);
            prev = ch;
            continue;
        }

        // Tokenize numbers
        if (isdigit(ch)) {
            i = 0;
            token[i++] = ch;
            int isFloat = 0;
            while ((ch = fgetc(fp)) != EOF && (isdigit(ch) || ch == '.')) {
                if (ch == '.') isFloat = 1;
                token[i++] = ch;
            }
            token[i] = '\0';
            printToken(isFloat ? "Float" : "Integer", token);
            prev = ch;
            continue;
        }

        // Handle special symbols and operators
        if (isSpecialSymbol(ch)) {
            token[0] = ch;
            token[1] = '\0';
            if (isOperator(ch))
                printToken("Operator", token);
            else
                printToken("Symbol", token);
            prev = '\0';
            continue;
        }

        // Skip whitespace
        if (isspace(ch)) {
            prev = '\0';
            continue;
        }

        prev = ch;
    }

    fclose(fp);
    return 0;
}
