%{
    #include <stdlib.h>
    #include <stdio.h>
    extern int yylval;
%}

%%
[0-9]+      { yylval = atoi(yytext); return 256; }
"+"        {return '+';}
"("        {return '(';}
")"        {return ')';}
[\n]      { return '\n';}
.            { printf("Unknown character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
