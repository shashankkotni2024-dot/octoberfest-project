%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
int flag = 0;
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

line:
    exp '\n' {
        if (!flag) {
            printf("Result = %d\nValid Expression\n", $1);
        }
        return 0;
    }
    ;

exp:
    NUMBER          { $$ = $1; }
    | exp '+' exp   { $$ = $1 + $3; }
    | exp '-' exp   { $$ = $1 - $3; }
    | exp '*' exp   { $$ = $1 * $3; }
    | exp '/' exp   { 
        if ($3 == 0) { 
            printf("Error: Division by zero is not allowed!\n"); 
            flag = 1; $$ = 0; 
        } else $$ = $1 / $3; 
    }
    | '-' exp %prec UMINUS { $$ = -$2; }
    | '(' exp ')'   { $$ = $2; }
    ;

%%

void yyerror(const char *s) { flag = 1; }

int main(void) {
    printf("Enter the arithmetic expression: ");
    yyparse();
    if (flag) printf("Invalid Expression\n");
    return 0;
}
