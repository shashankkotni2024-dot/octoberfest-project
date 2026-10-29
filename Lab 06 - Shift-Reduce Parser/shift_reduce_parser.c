#include <stdio.h>
#include <string.h>

#define MAX 50

typedef struct { char lhs, rhs[MAX]; } Prod;
Prod gram[MAX];
int n, top = -1, res_cnt = 0;
char stack[MAX], input[MAX], res[MAX][64];

// Checks if top of stack matches production RHS
int matches(char *rhs) {
    int len = strlen(rhs);
    if (top + 1 < len) return 0;
    return !memcmp(stack + top - len + 1, rhs, len);
}

// Reduces stack by RHS length and pushes LHS
void do_reduce(char lhs, char *rhs) {
    top -= strlen(rhs);
    stack[++top] = lhs;
    stack[top + 1] = '\0';
}

// Backtracking Shift-Reduce parser
int parse(int ip) {
    // Acceptance: Input exhausted and stack contains only start symbol
    if (input[ip] == '\0' && top == 0 && stack[0] == gram[0].lhs) return 1;

    // Try all possible REDUCE actions
    for (int p = 0; p < n; p++) {
        if (matches(gram[p].rhs)) {
            char old[MAX]; strcpy(old, stack);
            int old_top = top;
            do_reduce(gram[p].lhs, gram[p].rhs);
            sprintf(res[res_cnt++], "REDUCE %c->%s", gram[p].lhs, gram[p].rhs);

            if (parse(ip)) return 1;

            strcpy(stack, old); top = old_top; res_cnt--; // Backtrack
        }
    }

    // Try SHIFT action
    if (input[ip] != '\0') {
        char old[MAX]; strcpy(old, stack);
        int old_top = top;
        stack[++top] = input[ip];
        stack[top + 1] = '\0';
        sprintf(res[res_cnt++], "SHIFT %c", input[ip]);

        if (parse(ip + 1)) return 1;

        strcpy(stack, old); top = old_top; res_cnt--; // Backtrack
    }
    return 0;
}

int main(void) {
    printf("Enter number of productions: ");
    if (scanf("%d", &n) != 1) return 1;

    printf("Enter productions (e.g., E->E+T):\n");
    for (int i = 0; i < n; i++) {
        char p[MAX]; scanf("%s", p);
        gram[i].lhs = p[0];
        strcpy(gram[i].rhs, p + 3);
    }

    printf("Enter input string: ");
    scanf("%s", input);

    if (parse(0)) {
        printf("\n%-20s %-20s\n----------------------------------------\n", "STACK", "ACTION");
        top = -1;
        for (int i = 0; i < res_cnt; i++) {
            if (!strncmp(res[i], "SHIFT", 5)) {
                stack[++top] = res[i][6];
                stack[top + 1] = '\0';
            } else {
                char lhs, rhs[MAX];
                sscanf(res[i], "REDUCE %c->%s", &lhs, rhs);
                do_reduce(lhs, rhs);
            }
            printf("%-20s %-20s\n", stack, res[i]);
        }
        printf("\nACCEPT\n");
    } else {
        printf("\nREJECT\n");
    }
    return 0;
}
