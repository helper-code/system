%{
#include "y.tab.h"
#include <stdlib.h>
%}
%%
[0-9]+ {
yylval.num = atoi(yytext);
return NUM;
}
[ \t\n]+ ; // skip whitespace
"(" { return '('; }
")" { return ')'; }
"+" { return '+'; }
"*" { return '*'; }
. {
printf("Unexpected character: %s\n", yytext);
return 0;
}
%%

int yywrap() {return 1;}
