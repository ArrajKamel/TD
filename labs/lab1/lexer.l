%{
    #include <stdlib.h>
    #include <stdio.h>
    #include "y.tab.h"
%}

%%
    [a-z]       {yylval.c = yytext[0]; return CHAR; }
    "|".        {return OR;}
    "*".        {return STAR;}
    "(".        {return LPAREN;}
    ")".        {return RPAREN;}
    [ \t\n]      { /* ignore whitespace */ };
    .            {fprintf("Unknown character: %s\n", yytext);}

%%

int yywrap() {
    return 1;
}
