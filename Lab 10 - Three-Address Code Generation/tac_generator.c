#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 64

// Quadruple: (op, arg1, arg2, result)
typedef struct { char op[4], arg1[16], arg2[16], res[16]; } Quad;

// Triple: (op, arg1, arg2)
typedef struct { char op[4], arg1[16], arg2[16]; } Triple;

// Operator precedence
int prec(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Converts infix expression to postfix and generates TAC, Quadruples, Triples
void process(char *expr) {
    char target[16] = "", rhs[MAX] = "";
    char *eq = strchr(expr, '=');
    if (eq) {
        *eq = '\0';
        sscanf(expr, "%s", target);
        strcpy(rhs, eq + 1);
    } else {
        strcpy(rhs, expr);
    }

    // Infix to Postfix conversion using Shunting-yard algorithm
    char postfix[MAX][16]; int post_cnt = 0;
    char op_stack[MAX]; int op_top = -1;
    char operands[MAX][16]; int opnd_cnt = 0;
    char operators[MAX]; int opr_cnt = 0;

    for (int i = 0; rhs[i]; i++) {
        if (isspace(rhs[i])) continue;
        if (isalnum(rhs[i])) {
            char tok[16]; int k = 0;
            while (isalnum(rhs[i])) tok[k++] = rhs[i++];
            tok[k] = '\0'; i--;
            strcpy(postfix[post_cnt++], tok);
            strcpy(operands[opnd_cnt++], tok);
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
            operators[opr_cnt++] = op;
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

    // 1. Token Classification
    printf("\n--- 1. Token Classification ---\nOperands Identified  : ");
    if (target[0]) printf("%s, ", target);
    for (int i = 0; i < opnd_cnt; i++) printf("%s%s", operands[i], i < opnd_cnt - 1 ? ", " : "");
    printf("\nOperators Identified : ");
    for (int i = 0; i < opr_cnt; i++) printf("%c, ", operators[i]);
    if (target[0]) printf("= (assignment)");
    printf("\n");

    // 2. Postfix Notation
    printf("\n--- 2. Postfix Notation ---\n");
    for (int i = 0; i < post_cnt; i++) printf("%s ", postfix[i]);
    printf("\n");

    // 3. TAC, Quadruples and Triples Generation
    Quad quads[MAX]; int q_cnt = 0;
    Triple triples[MAX]; int t_cnt = 0;
    char val_stack[MAX][16]; int val_top = -1;
    int ref_stack[MAX];
    int temp_id = 1;

    for (int i = 0; i < post_cnt; i++) {
        if (isalnum(postfix[i][0])) {
            strcpy(val_stack[++val_top], postfix[i]);
            ref_stack[val_top] = -1;
        } else {
            char arg2[16], arg1[16];
            int ref2 = ref_stack[val_top];
            strcpy(arg2, val_stack[val_top--]);
            int ref1 = ref_stack[val_top];
            strcpy(arg1, val_stack[val_top--]);

            char res[16]; sprintf(res, "t%d", temp_id++);
            strcpy(quads[q_cnt].op, postfix[i]);
            strcpy(quads[q_cnt].arg1, arg1);
            strcpy(quads[q_cnt].arg2, arg2);
            strcpy(quads[q_cnt].res, res);
            q_cnt++;

            strcpy(triples[t_cnt].op, postfix[i]);
            if (ref1 != -1) sprintf(triples[t_cnt].arg1, "(%d)", ref1);
            else strcpy(triples[t_cnt].arg1, arg1);
            if (ref2 != -1) sprintf(triples[t_cnt].arg2, "(%d)", ref2);
            else strcpy(triples[t_cnt].arg2, arg2);
            t_cnt++;

            strcpy(val_stack[++val_top], res);
            ref_stack[val_top] = t_cnt - 1;
        }
    }

    if (target[0] && val_top >= 0) {
        strcpy(quads[q_cnt].op, "=");
        strcpy(quads[q_cnt].arg1, val_stack[val_top]);
        strcpy(quads[q_cnt].arg2, "-");
        strcpy(quads[q_cnt].res, target);
        q_cnt++;

        strcpy(triples[t_cnt].op, "=");
        strcpy(triples[t_cnt].arg1, target);
        sprintf(triples[t_cnt].arg2, "(%d)", ref_stack[val_top]);
        t_cnt++;
    }

    // Display TAC
    printf("\n--- 3. Three-Address Code (TAC) ---\n");
    for (int i = 0; i < q_cnt; i++) {
        if (!strcmp(quads[i].op, "=")) printf("%s = %s\n", quads[i].res, quads[i].arg1);
        else printf("%s = %s %s %s\n", quads[i].res, quads[i].arg1, quads[i].op, quads[i].arg2);
    }

    // Display Quadruples
    printf("\n--- 4. Quadruples Representation ---\n");
    printf("+-------+----------+------------+------------+------------+\n");
    printf("| Index | Operator | Argument 1 | Argument 2 |   Result   |\n");
    printf("+-------+----------+------------+------------+------------+\n");
    for (int i = 0; i < q_cnt; i++)
        printf("|  %-4d |    %-5s | %-10s | %-10s | %-10s |\n", i, quads[i].op, quads[i].arg1, quads[i].arg2, quads[i].res);
    printf("+-------+----------+------------+------------+------------+\n");

    // Display Triples
    printf("\n--- 5. Triples Representation ---\n");
    printf("+-------+----------+------------+------------+\n");
    printf("| Index | Operator | Argument 1 | Argument 2 |\n");
    printf("+-------+----------+------------+------------+\n");
    for (int i = 0; i < t_cnt; i++)
        printf("|  (%d)  |    %-5s | %-10s | %-10s |\n", i, triples[i].op, triples[i].arg1, triples[i].arg2);
    printf("+-------+----------+------------+------------+\n");
}

int main(void) {
    char buf[128];
    while (1) {
        printf("\nEnter an arithmetic expression (or 'exit' to quit):\n> ");
        if (!fgets(buf, sizeof(buf), stdin)) break;
        buf[strcspn(buf, "\r\n")] = '\0';
        if (!strcmp(buf, "exit") || !strcmp(buf, "quit")) break;
        if (!buf[0]) continue;
        process(buf);
    }
    return 0;
}
