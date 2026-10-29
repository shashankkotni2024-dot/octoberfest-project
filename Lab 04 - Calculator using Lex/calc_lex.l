%{
#include <stdio.h>
#include <stdlib.h>
%}

%%

[0-9]+[ \t]*\+[ \t]*[0-9]+  { int a, b; sscanf(yytext, "%d + %d", &a, &b); printf("Result = %d\n", a + b); }
[0-9]+[ \t]*\-[ \t]*[0-9]+  { int a, b; sscanf(yytext, "%d - %d", &a, &b); printf("Result = %d\n", a - b); }
[0-9]+[ \t]*\*[ \t]*[0-9]+  { int a, b; sscanf(yytext, "%d * %d", &a, &b); printf("Result = %d\n", a * b); }
[0-9]+[ \t]*\/[ \t]*[0-9]+  { int a, b; sscanf(yytext, "%d / %d", &a, &b); 
                              if (b == 0) printf("Error: Division by zero is not allowed.\n"); 
                              else printf("Result = %.2f\n", (float)a / b); }
[ \t\n]+                    ; /* Ignore spaces and newlines */
.                           { printf("Invalid Expression\n"); }

%%

int yywrap(void) { return 1; }

int main(void) {
    printf("Enter arithmetic expressions (e.g., 10+5):\n");
    yylex();
    return 0;
}
