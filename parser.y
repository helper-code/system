%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"         // Defines ASTNode

extern int yylex();
void yyerror(const char *s);

ASTNode* root;
%}

/* Forward declaration for Bison's use in %union */
%code requires {
    #include "ast.h"
}

%union {
    int num;
    ASTNode* node;
}

%token <num> NUMBER
%type <node> expr term factor

%left '+' '-'
%left '*' '/'

%%

input:
    expr {
        root = $1;
        printf("Abstract Syntax Tree:\n");
        printAST(root, 0);
        freeAST(root);
    }
    ;

expr:
    expr '+' term { $$ = createOpNode(NODE_ADD, $1, $3); }
  | expr '-' term { $$ = createOpNode(NODE_SUB, $1, $3); }
  | term          { $$ = $1; }
  ;

term:
    term '*' factor { $$ = createOpNode(NODE_MUL, $1, $3); }
  | term '/' factor { $$ = createOpNode(NODE_DIV, $1, $3); }
  | factor          { $$ = $1; }
  ;

factor:
    NUMBER          { $$ = createNumNode($1); }
  | '(' expr ')'    { $$ = $2; }
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
