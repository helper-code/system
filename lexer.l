%{
#include "parser.tab.h"
%}

%%

[0-9]+      { yylval.num = atoi(yytext); return NUMBER; }
[ \t\n]     ; // Ignore whitespace
.           return yytext[0];

%%

int yywrap() {
    return 1;
}



