#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Checks if lexeme is a C keyword
int is_keyword(char *s) {
    char *kw[] = {"int", "float", "char", "double", "if", "else", "while",
                  "for", "return", "void", "break", "continue", "switch", "case", "do"};
    for (int i = 0; i < 15; i++)
        if (!strcmp(s, kw[i])) return 1;
    return 0;
}

int main(int argc, char *argv[]) {
    char fname[100];
    if (argc > 1) strcpy(fname, argv[1]);
    else { printf("Enter source file name: "); scanf("%99s", fname); }

    FILE *fp = fopen(fname, "r");
    if (!fp) { printf("Unable to open file.\n"); return 1; }

    printf("\n----------------------------------------\n");
    printf("%-15s %-15s\n", "TOKEN", "LEXEME");
    printf("----------------------------------------\n");

    int ch, count = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch)) continue;

        // Identifiers and Keywords
        if (isalpha(ch) || ch == '_') {
            char buf[64]; int i = 0;
            buf[i++] = ch;
            while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_')) buf[i++] = ch;
            buf[i] = '\0';
            if (ch != EOF) ungetc(ch, fp);
            printf("%-15s %-15s\n", is_keyword(buf) ? "KEYWORD" : "IDENTIFIER", buf);
            count++;
        }
        // Numeric constants
        else if (isdigit(ch)) {
            char buf[64]; int i = 0;
            buf[i++] = ch;
            while ((ch = fgetc(fp)) != EOF && (isdigit(ch) || ch == '.')) buf[i++] = ch;
            buf[i] = '\0';
            if (ch != EOF) ungetc(ch, fp);
            printf("%-15s %-15s\n", "NUMBER", buf);
            count++;
        }
        // Operators
        else if (strchr("+-*/%=<>!&|^", ch)) {
            printf("%-15s %-15c\n", "OPERATOR", ch);
            count++;
        }
        // Separators / Delimiters
        else if (strchr(";,(){}[]", ch)) {
            printf("%-15s %-15c\n", "SEPARATOR", ch);
            count++;
        }
        // String literals
        else if (ch == '"') {
            char buf[128]; int i = 0;
            while ((ch = fgetc(fp)) != EOF && ch != '"') buf[i++] = ch;
            buf[i] = '\0';
            printf("%-15s %-15s\n", "STRING", buf);
            count++;
        }
    }
    printf("----------------------------------------\n");
    printf("Total Number of Tokens = %d\n", count);
    fclose(fp);
    return 0;
}
