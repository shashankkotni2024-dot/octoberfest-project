%{
#include <stdio.h>

int yylex(void);
void yyerror(const char *s);
int flag = 0;
%}

%%

line:
    exp '\n' {
        if (!flag) printf("Output : Balanced Symbols\n");
        return 0;
    }
    ;

exp:
    '(' exp ')' exp
    | '[' exp ']' exp
    | '{' exp '}' exp
    | /* empty */
    ;

%%

void yyerror(const char *s) { flag = 1; }

int main(void) {
    printf("Input : ");
    yyparse();
    if (flag) printf("Output : Unbalanced Symbols\n");
    return 0;
}
