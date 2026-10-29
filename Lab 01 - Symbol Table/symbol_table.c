#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Symbol table entry
typedef struct {
    char name[32], type[16], scope[16];
    int size, scope_lvl;
} Symbol;

Symbol table[MAX];
int sym_count = 0, scope_lvl = 0;
char cur_scope[16] = "global", scope_stack[10][16];
int stack_top = 0;

// Returns byte size for primitive types
int get_size(char *type) {
    if (!strcmp(type, "int") || !strcmp(type, "float")) return 4;
    if (!strcmp(type, "char")) return 1;
    if (!strcmp(type, "double")) return 8;
    return 0;
}

// Checks if token is a type keyword
int is_type(char *s) {
    return (!strcmp(s, "int") || !strcmp(s, "float") || !strcmp(s, "char") || 
            !strcmp(s, "double") || !strcmp(s, "void"));
}

// Inserts identifier with redefinition check in current scope
void insert(char *name, char *type, char *scope) {
    for (int i = 0; i < sym_count; i++) {
        if (!strcmp(table[i].name, name) && table[i].scope_lvl == scope_lvl) {
            printf("[Compile Error]: Redefinition of identifier '%s' in scope '%s'.\n", name, scope);
            return;
        }
    }
    strcpy(table[sym_count].name, name);
    strcpy(table[sym_count].type, type);
    strcpy(table[sym_count].scope, scope_lvl == 0 ? "global" : "local");
    table[sym_count].size = get_size(type);
    table[sym_count].scope_lvl = scope_lvl;
    sym_count++;
}

// Displays symbol table
void display() {
    printf("\n======================================================\n");
    printf("%-15s %-10s %-12s %-10s\n", "NAME", "TYPE", "SCOPE", "MEMORY (Bytes)");
    printf("======================================================\n");
    for (int i = 0; i < sym_count; i++)
        printf("%-15s %-10s %-12s %-10d\n", table[i].name, table[i].type, table[i].scope, table[i].size);
}

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argc > 1 ? argv[1] : "lab1_input.c", "r");
    if (!fp) { printf("Error: Cannot open input file.\n"); return 1; }

    char token[32] = "", type[16] = "";
    int ch, idx = 0;
    strcpy(scope_stack[0], "global");

    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch) || strchr(";,(){}", ch)) {
            if (idx > 0) {
                token[idx] = '\0';
                if (is_type(token)) {
                    strcpy(type, token);
                } else if (type[0]) {
                    // Peek ahead to distinguish function declaration from variable
                    int next = ch;
                    while (isspace(next)) next = fgetc(fp);
                    if (next == '(') {
                        insert(token, type, cur_scope);
                        strcpy(scope_stack[++stack_top], cur_scope);
                        strcpy(cur_scope, token);
                        scope_lvl++;
                    } else {
                        insert(token, type, cur_scope);
                    }
                    if (next != ch) ungetc(next, fp);
                    type[0] = '\0';
                }
                idx = 0;
            }
            // Track nested block scopes
            if (ch == '{') {
                scope_lvl++;
                if (stack_top < scope_lvl) {
                    strcpy(scope_stack[++stack_top], cur_scope);
                    sprintf(cur_scope, "block_%d", scope_lvl);
                }
            } else if (ch == '}') {
                scope_lvl--;
                strcpy(cur_scope, stack_top > 0 ? scope_stack[stack_top--] : "global");
            }
        } else if (idx < 31) {
            token[idx++] = ch;
        }
    }
    fclose(fp);
    display();
    return 0;
}
