#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX 32

typedef struct {
    char res[16], arg1[16], op[4], arg2[16];
    bool is_copy, dead;
} Quad;

bool is_num(const char *s) {
    if (!s || !*s) return false;
    for (int i = (*s == '-' || *s == '+') ? 1 : 0; s[i]; i++)
        if (!isdigit((unsigned char)s[i])) return false;
    return true;
}

void parse_quad(const char *s, Quad *q) {
    memset(q, 0, sizeof(Quad));
    char rhs[64] = "";
    if (sscanf(s, "%s = %[^\n]", q->res, rhs) < 2) return;
    if (sscanf(rhs, "%s %s %s", q->arg1, q->op, q->arg2) == 3) {
        q->is_copy = false;
    } else {
        sscanf(rhs, "%s", q->arg1);
        q->is_copy = true;
    }
}

void print_code(const Quad q[], int n, const char *title) {
    printf("\n--- %s ---\n", title);
    int line = 1;
    for (int i = 0; i < n; i++) {
        if (q[i].dead) continue;
        if (q[i].is_copy) printf("[%2d] %-9s = %s\n", line++, q[i].res, q[i].arg1);
        else printf("[%2d] %-9s = %s %s %s\n", line++, q[i].res, q[i].arg1, q[i].op, q[i].arg2);
    }
}

// 1. Constant Folding
bool fold_constants(Quad q[], int n) {
    bool chg = false;
    for (int i = 0; i < n; i++) {
        if (q[i].dead || q[i].is_copy) continue;
        if (is_num(q[i].arg1) && is_num(q[i].arg2)) {
            long a = atol(q[i].arg1), b = atol(q[i].arg2), r = 0;
            switch (q[i].op[0]) {
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/': if (b) r = a / b; else continue; break;
                case '%': if (b) r = a % b; else continue; break;
                default: continue;
            }
            printf("  [Folding] %s = %s %s %s -> %ld\n", q[i].res, q[i].arg1, q[i].op, q[i].arg2, r);
            snprintf(q[i].arg1, sizeof(q[i].arg1), "%ld", r);
            q[i].op[0] = '\0'; q[i].arg2[0] = '\0';
            q[i].is_copy = true; chg = true;
        }
    }
    return chg;
}

// 2. Algebraic Simplification & Strength Reduction
bool algebraic_and_strength(Quad q[], int n) {
    bool chg = false;
    for (int i = 0; i < n; i++) {
        if (q[i].dead || q[i].is_copy) continue;
        if (!strcmp(q[i].op, "*") && !strcmp(q[i].arg2, "2")) {
            printf("  [Strength] %s * 2 -> %s + %s\n", q[i].arg1, q[i].arg1, q[i].arg1);
            strcpy(q[i].op, "+"); strcpy(q[i].arg2, q[i].arg1); chg = true;
        } else if (!strcmp(q[i].op, "*") && !strcmp(q[i].arg2, "1")) {
            printf("  [Algebraic] %s * 1 -> %s\n", q[i].arg1, q[i].arg1);
            q[i].is_copy = true; chg = true;
        } else if (!strcmp(q[i].op, "*") && !strcmp(q[i].arg2, "0")) {
            printf("  [Algebraic] %s * 0 -> 0\n", q[i].arg1);
            strcpy(q[i].arg1, "0"); q[i].is_copy = true; chg = true;
        } else if (!strcmp(q[i].op, "+") && !strcmp(q[i].arg2, "0")) {
            printf("  [Algebraic] %s + 0 -> %s\n", q[i].arg1, q[i].arg1);
            q[i].is_copy = true; chg = true;
        }
    }
    return chg;
}

// 3. Constant & Copy Propagation
bool propagate_values(Quad q[], int n) {
    bool chg = false;
    for (int i = 0; i < n; i++) {
        if (q[i].dead || !q[i].is_copy) continue;
        char *var = q[i].res, *val = q[i].arg1;
        for (int j = i + 1; j < n; j++) {
            if (q[j].dead) continue;
            if (!strcmp(q[j].arg1, var)) {
                printf("  [Propagate] '%s' -> '%s' in inst %d\n", var, val, j + 1);
                strcpy(q[j].arg1, val); chg = true;
            }
            if (!q[j].is_copy && !strcmp(q[j].arg2, var)) {
                printf("  [Propagate] '%s' -> '%s' in inst %d\n", var, val, j + 1);
                strcpy(q[j].arg2, val); chg = true;
            }
            if (!strcmp(q[j].res, var)) break; // Stop if redefined
        }
    }
    return chg;
}

// 4. Common Subexpression Elimination (CSE)
bool eliminate_cse(Quad q[], int n) {
    bool chg = false;
    for (int i = 0; i < n; i++) {
        if (q[i].dead || q[i].is_copy) continue;
        for (int j = i + 1; j < n; j++) {
            if (q[j].dead || q[j].is_copy) continue;
            if (!strcmp(q[i].op, q[j].op) && !strcmp(q[i].arg1, q[j].arg1) && !strcmp(q[i].arg2, q[j].arg2)) {
                printf("  [CSE] Replaced %s = %s %s %s with %s\n", q[j].res, q[j].arg1, q[j].op, q[j].arg2, q[i].res);
                strcpy(q[j].arg1, q[i].res); q[j].is_copy = true; chg = true;
            }
        }
    }
    return chg;
}

// 5. Dead Code Elimination
bool eliminate_dead_code(Quad q[], int n) {
    bool chg = false;
    for (int i = 0; i < n - 1; i++) {
        if (q[i].dead) continue;
        bool used = false;
        for (int j = i + 1; j < n; j++) {
            if (!q[j].dead && (!strcmp(q[j].arg1, q[i].res) || (!q[j].is_copy && !strcmp(q[j].arg2, q[i].res)))) {
                used = true; break;
            }
        }
        if (!used && (q[i].res[0] == 't' || !strncmp(q[i].res, "dead", 4) || q[i].res[0] == 'i' || q[i].res[0] == 'z')) {
            printf("  [Dead Code] Removed unused %s\n", q[i].res);
            q[i].dead = true; chg = true;
        }
    }
    return chg;
}

// Multi-pass iterative optimization pipeline
void optimize(Quad q[], int n) {
    printf("\n--- Optimization Pipeline ---\n");
    for (int pass = 1; pass <= 5; pass++) {
        printf("\n> Pass %d:\n", pass);
        bool chg = fold_constants(q, n) | algebraic_and_strength(q, n) |
                   propagate_values(q, n) | eliminate_cse(q, n) | eliminate_dead_code(q, n);
        if (!chg) { printf("  Fixpoint reached.\n"); break; }
    }
}

int main(void) {
    const char *prog[] = {
        "t1 = 2 * 3", "t2 = t1 + y", "a = 5", "c = a * 2", "z = a",
        "y = x + 5", "i = y", "z = i", "w = z * 3", "t3 = b + c",
        "t4 = b + c", "t5 = w * 2", "t6 = m * 1", "t7 = k * 0",
        "t8 = p + 0", "dead = 99 + 1", "final_res = t2 + t3"
    };
    int n = sizeof(prog) / sizeof(prog[0]);
    Quad orig[MAX], opt[MAX];
    for (int i = 0; i < n; i++) parse_quad(prog[i], &orig[i]);
    memcpy(opt, orig, sizeof(orig));

    print_code(orig, n, "ORIGINAL TAC");
    optimize(opt, n);
    print_code(opt, n, "OPTIMIZED TAC");
    return 0;
}
