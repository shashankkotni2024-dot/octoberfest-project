#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 64

// Operator precedence
int prec(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Generates Three-Address Code (TAC) for an arithmetic expression
void generate_tac(char *expr) {
    char target[16] = "", rhs[MAX] = "";
    char *eq = strchr(expr, '=');

    // Separate LHS target variable and RHS expression if '=' exists
    if (eq) {
        *eq = '\0';
        sscanf(expr, "%s", target);
        strcpy(rhs, eq + 1);
    } else {
        strcpy(rhs, expr);
    }

    // Step 1: Infix to Postfix conversion (Shunting-yard algorithm)
    char postfix[MAX][16];
    int post_cnt = 0;
    char op_stack[MAX];
    int op_top = -1;

    for (int i = 0; rhs[i]; i++) {
        // Ignore whitespace
        if (isspace(rhs[i])) continue;

        if (isalnum(rhs[i])) {
            char tok[16];
            int k = 0;
            while (isalnum(rhs[i])) tok[k++] = rhs[i++];
            tok[k] = '\0';
            i--;
            strcpy(postfix[post_cnt++], tok);
        } else if (rhs[i] == '(') {
            op_stack[++op_top] = '(';
        } else if (rhs[i] == ')') {
            while (op_top >= 0 && op_stack[op_top] != '(') {
                postfix[post_cnt][0] = op_stack[op_top--];
                postfix[post_cnt++][1] = '\0';
            }
            if (op_top >= 0) op_top--; // Discard '('
        } else if (strchr("+-*/%^", rhs[i])) {
            char op = rhs[i];
            while (op_top >= 0 && prec(op_stack[op_top]) >= prec(op) && op != '^') {
                postfix[post_cnt][0] = op_stack[op_top--];
                postfix[post_cnt++][1] = '\0';
            }
            op_stack[++op_top] = op;
        }
    }
    while (op_top >= 0) {
        postfix[post_cnt][0] = op_stack[op_top--];
        postfix[post_cnt++][1] = '\0';
    }

    // Step 2: Postfix to TAC generation using an operand stack
    char val_stack[MAX][16];
    int val_top = -1;
    int temp_id = 1;

    printf("\n--- Three-Address Code (TAC) ---\n");
    for (int i = 0; i < post_cnt; i++) {
        if (isalnum(postfix[i][0])) {
            // Push operand to stack
            strcpy(val_stack[++val_top], postfix[i]);
        } else {
            // Pop two operands for binary operator
            char arg2[16], arg1[16];
            strcpy(arg2, val_stack[val_top--]);
            strcpy(arg1, val_stack[val_top--]);

            char temp[16];
            sprintf(temp, "t%d", temp_id++);
            printf("%s = %s %s %s\n", temp, arg1, postfix[i], arg2);

            // Push temporary result back to stack
            strcpy(val_stack[++val_top], temp);
        }
    }

    // Final assignment to LHS variable (if present)
    if (target[0] && val_top >= 0) {
        printf("%s = %s\n", target, val_stack[val_top]);
    }
}

int main(void) {
    char buf[128];
    while (1) {
        printf("\nEnter arithmetic expression (or 'exit' to quit):\n> ");
        if (!fgets(buf, sizeof(buf), stdin)) break;
        buf[strcspn(buf, "\r\n")] = '\0';
        if (!strcmp(buf, "exit") || !strcmp(buf, "quit")) break;
        if (!buf[0]) continue;
        generate_tac(buf);
    }
    return 0;
}
