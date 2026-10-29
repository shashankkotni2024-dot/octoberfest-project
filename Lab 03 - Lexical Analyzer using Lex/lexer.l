%{
#include <stdio.h>
%}

%%

int|float|char|double|void|if|else|for|while|return|break|continue  { printf("Keyword        : %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*                                              { printf("Identifier     : %s\n", yytext); }
[0-9]+                                                              { printf("Constant       : %s\n", yytext); }
"=="|"!="|"<="|">="|"++"|"--"|[+\-*/=<>]                            { printf("Operator       : %s\n", yytext); }
[;,(){}\[\]]                                                        { printf("Delimiter      : %s\n", yytext); }
[ \t\n]+                                                            ; /* Ignore whitespace */
.                                                                   { printf("Special Symbol : %s\n", yytext); }

%%

int yywrap(void) { return 1; }

int main(int argc, char *argv[]) {
    if (argc > 1) yyin = fopen(argv[1], "r");
    yylex();
    return 0;
}
