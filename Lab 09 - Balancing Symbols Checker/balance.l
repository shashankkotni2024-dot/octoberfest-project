%{
#include <stdio.h>
#include "y.tab.h"
%}

%%

[(){}\[\]\n]            { return yytext[0]; }
[a-zA-Z0-9+\-*/= \t]+   ; /* Ignore operands, operators, and whitespace */
.                       { return yytext[0]; }

%%

int yywrap(void) { return 1; }
