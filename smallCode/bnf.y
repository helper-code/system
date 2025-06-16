%{
#include <stdio.h>
#include <stdlib.h>
typedef struct ASTNode {
char* type;
struct ASTNode *left, *right;
int value; // For NUM nodes
} ASTNode;
ASTNode* createNode(char* type, ASTNode* left, ASTNode* right, int value);
void printAST(ASTNode* node, int level);
int yylex(void);
int yyerror(const char *s);
%}
%union {
int num;
struct ASTNode* node;
}
%token <num> NUM
%type <node> expr term factor
%%
input:
expr { printAST($1, 0); }
;
expr:
expr '+' term { $$ = createNode("ADD", $1, $3, 0); }
| term { $$ = $1; }
;
term:
term '*' factor { $$ = createNode("MUL", $1, $3, 0); }
| factor { $$ = $1; }
;
factor:
'(' expr ')' { $$ = $2; }
| NUM { $$ = createNode("NUM", NULL, NULL, $1); }
;
%%
int main() {
printf("Enter an expression:\n");
yyparse();
return 0;
}
int yyerror(const char *s) {
fprintf(stderr, "Parse error: %s\n", s);
return 1;
}
ASTNode* createNode(char* type, ASTNode* left, ASTNode* right, int value) {
ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
node->type = type;
node->left = left;
node->right = right;
node->value = value;
return node;
}
void printAST(ASTNode* node, int level) {
if (!node) return;
for (int i = 0; i < level; i++) printf(" ");
if (node->type == "NUM")
printf("%s(%d)\n", node->type, node->value);
else
printf("%s\n", node->type);
printAST(node->left, level + 1);
printAST(node->right, level + 1);
}
