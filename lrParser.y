%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
void yyerror(const char *s);
extern char *yytext;
extern int input_pointer;

char stack[1000];
int top = -1;
char input_buffer[1000];
int step = 1;

void push(char c) {
    stack[++top] = c;
}

void pop() {
    if (top >= 0) top--;
}

void print_table(const char *input, const char *action) {
    printf("%-5d ", step++);
    for (int i = 0; i <= top; i++) {
        printf("%c", stack[i]);
    }
    printf("\t %-20s %-20s\n", &input_buffer[input_pointer], action);
}
%}

%token ID

%%

S: E '$' { print_table(&input_buffer[input_pointer], "Accept"); exit(0); };

E: E '+' T { print_table(&input_buffer[input_pointer], "Reduce by E -> E + T"); }
  | T { print_table(&input_buffer[input_pointer], "Reduce by E -> T"); }
  ;

T: T '*' F { print_table(&input_buffer[input_pointer], "Reduce by T -> T * F"); }
  | F { print_table(&input_buffer[input_pointer], "Reduce by T -> F"); }
  ;

F: '(' E ')' { print_table(&input_buffer[input_pointer], "Reduce by F -> (E)"); }
  | ID { print_table(&input_buffer[input_pointer], "Reduce by F -> id"); }
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at position %d (%s)\n", s, input_pointer + 1, yytext);
}

int main() {
    printf("Enter expression (without spaces, use single letter identifiers): ");
    if (scanf("%s", input_buffer) != 1) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    printf("\n%-5s %-20s %-20s %-20s\n", "Step", "Stack", "Input", "Action");
    printf("-----------------------------------------------------------------------\n");

    // Initialize the stack with a starting symbol (you might need to adjust based on your generated parser states)
    // For a typical LR(0) parser, you might not need to push anything explicitly.
    // However, the generated parser will handle the initial state.

    yyparse();

    printf("\nParsing completed.\n");
    return 0;
}



