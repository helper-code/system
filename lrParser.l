
%{
#include "y.tab.h"
extern char *yytext;
extern int input_pointer;
%}

%%

[0-9a-zA-Z] { input_pointer += yyleng; return ID; }
[+] { input_pointer += yyleng; return '+'; }
[] { input_pointer += yyleng; return ''; }
[(] { input_pointer += yyleng; return '('; }
[)] { input_pointer += yyleng; return ')'; }
[\n] { /* ignore */ }
[ \t] { /* ignore whitespace */ }
. { fprintf(stderr, "Invalid character: %s\n", yytext); input_pointer += yyleng; /* Consider error recovery */ }
<<EOF>> { return 0; /* Return 0 to signal end of input */ }

%%

int yywrap() {
    return 1;
}