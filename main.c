#include <stdio.h>

int yyparse();

int main() {
    printf("Enter an expression:\n");
    return yyparse();
}