#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char prod[MAX][MAX], first[MAX][MAX], follow[MAX][MAX];
int n, first_cnt[MAX], follow_cnt[MAX];

// Adds symbol to set if not already present
void add_to_set(char *set, int *cnt, char ch) {
    for (int i = 0; i < *cnt; i++)
        if (set[i] == ch) return;
    set[(*cnt)++] = ch;
}

// Finds index of production having non-terminal nt as LHS
int get_idx(char nt) {
    for (int i = 0; i < n; i++)
        if (prod[i][0] == nt) return i;
    return -1;
}

// Computes FIRST set for production at index
void find_first(int idx) {
    char *rhs = prod[idx] + 3;
    for (int i = 0; rhs[i]; i++) {
        char s = rhs[i];
        if (!isupper(s)) {
            add_to_set(first[idx], &first_cnt[idx], s);
            if (s != '#') break;
        } else {
            int nt = get_idx(s);
            if (nt == -1) break;
            if (!first_cnt[nt]) find_first(nt);
            int eps = 0;
            for (int j = 0; j < first_cnt[nt]; j++) {
                if (first[nt][j] == '#') eps = 1;
                else add_to_set(first[idx], &first_cnt[idx], first[nt][j]);
            }
            if (!eps) break;
        }
    }
    if (rhs[0] == '#') add_to_set(first[idx], &first_cnt[idx], '#');
}

// Checks if FIRST set contains epsilon (#)
int has_eps(int idx) {
    if (idx == -1) return 0;
    for (int i = 0; i < first_cnt[idx]; i++)
        if (first[idx][i] == '#') return 1;
    return 0;
}

// Computes FIRST set for remainder of RHS string
void first_of_str(char *rhs, int pos, char *res, int *cnt) {
    int eps = 1;
    for (int i = pos; rhs[i]; i++) {
        char s = rhs[i];
        if (!isupper(s)) {
            if (s != '#') add_to_set(res, cnt, s);
            eps = (s == '#');
            if (!eps) break;
        } else {
            int nt = get_idx(s);
            if (nt == -1) break;
            for (int j = 0; j < first_cnt[nt]; j++)
                if (first[nt][j] != '#') add_to_set(res, cnt, first[nt][j]);
            if (!has_eps(nt)) { eps = 0; break; }
        }
    }
    if (eps) add_to_set(res, cnt, '#');
}

// Computes FOLLOW sets iteratively until fixpoint
void find_follow() {
    add_to_set(follow[0], &follow_cnt[0], '$');
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < n; i++) {
            char *rhs = prod[i] + 3;
            for (int j = 0; rhs[j]; j++) {
                if (!isupper(rhs[j])) continue;
                int cur = get_idx(rhs[j]);
                if (cur == -1) continue;

                char temp[MAX]; int temp_cnt = 0;
                first_of_str(rhs, j + 1, temp, &temp_cnt);

                for (int k = 0; k < temp_cnt; k++) {
                    if (temp[k] != '#') {
                        int old = follow_cnt[cur];
                        add_to_set(follow[cur], &follow_cnt[cur], temp[k]);
                        if (old != follow_cnt[cur]) changed = 1;
                    }
                }
                if (!temp_cnt || has_eps(get_idx(rhs[j + 1]))) {
                    int lhs = get_idx(prod[i][0]);
                    for (int k = 0; k < follow_cnt[lhs]; k++) {
                        int old = follow_cnt[cur];
                        add_to_set(follow[cur], &follow_cnt[cur], follow[lhs][k]);
                        if (old != follow_cnt[cur]) changed = 1;
                    }
                }
            }
        }
    }
}

int main(void) {
    // Hardcoded grammar: standard arithmetic expression CFG
    const char *grammar[] = {
        "E->TR", "R->+TR", "R->#", "T->FY",
        "Y->*FY", "Y->#", "F->(E)", "F->i"
    };
    n = 8;
    for (int i = 0; i < n; i++) strcpy(prod[i], grammar[i]);

    printf("Grammar:\n");
    for (int i = 0; i < n; i++) printf("  Production %d: %s\n", i + 1, prod[i]);

    for (int i = 0; i < n; i++)
        if (!first_cnt[i]) find_first(i);

    find_follow();

    printf("\n========== FIRST SETS ==========\n");
    for (int i = 0; i < n; i++) {
        printf("FIRST(%c) = { ", prod[i][0]);
        for (int j = 0; j < first_cnt[i]; j++)
            printf("%c%s", first[i][j], j < first_cnt[i] - 1 ? ", " : "");
        printf(" }\n");
    }

    printf("\n========== FOLLOW SETS ==========\n");
    for (int i = 0; i < n; i++) {
        printf("FOLLOW(%c) = { ", prod[i][0]);
        for (int j = 0; j < follow_cnt[i]; j++)
            printf("%c%s", follow[i][j], j < follow_cnt[i] - 1 ? ", " : "");
        printf(" }\n");
    }
    return 0;
}
