# Lab 09: Balancing Symbols Checker using Lex and YACC

## 1. Aim
To design and implement a Balancing Symbols Checker using Lex and YACC that accepts an expression or sequence of symbols, verifies the matching and correct nesting of parentheses `()`, square brackets `[]`, and curly braces `{}`, and reports whether the symbols are balanced or unbalanced.

---

## 2. Files in this Directory
- [`balance.l`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2009%20-%20Balancing%20Symbols%20Checker/balance.l): Lex specification filtering out alphanumeric characters/operators and passing bracket characters and newlines to the parser.
- [`balance.y`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2009%20-%20Balancing%20Symbols%20Checker/balance.y): YACC grammar specification verifying context-free nested bracket balancing.
- [`lab_report_9.pdf`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2009%20-%20Balancing%20Symbols%20Checker/lab_report_9.pdf): Original submitted lab report.

---

## 3. Execution Commands (In Order)

### Linux / WSL (Ubuntu)
```bash
# Step 1: Navigate to this directory
cd "Lab Fat Preparation/Lab 09 - Balancing Symbols Checker"

# Step 2: Generate parser with YACC (creates y.tab.c and y.tab.h)
yacc -d balance.y
# Note: bison -d -y balance.y is equivalent.

# Step 3: Generate scanner with Lex (creates lex.yy.c)
lex balance.l
# Note: flex balance.l is equivalent.

# Step 4: Compile both C files with GCC
gcc y.tab.c lex.yy.c -o balance_check

# Step 5: Run the checker
./balance_check
```

### Windows (Using WSL or WinFlexBison)
In WSL terminal, run the Linux commands above.
If using WinFlexBison:
```cmd
win_bison -d -y balance.y
win_flex balance.l
gcc y.tab.c lex.yy.c -o balance_check.exe
balance_check.exe
```

---

## 4. Test Cases & Expected Outputs

| Input Sequence | Output | Remarks |
| :--- | :--- | :--- |
| `{[()]}` | `Output : Balanced Symbols` | Properly nested diverse brackets |
| `a + (b * [c + {d - e}])` | `Output : Balanced Symbols` | General expression with valid nesting |
| `{[(])}` | `Output : Unbalanced Symbols` | Improper overlap / crossed brackets |
| `((())` | `Output : Unbalanced Symbols` | Missing closing parenthesis |
| `)()` | `Output : Unbalanced Symbols` | Premature closing parenthesis |

---

## 5. Key Concepts & Viva Notes
1. **Why Regular Expressions Cannot Check Arbitrary Nesting**:
   - Matching nested structures of arbitrary depth requires counting/memory (a pushdown automaton), which is beyond the capability of finite automata (Regular Languages).
   - Hence, YACC (Context-Free Grammar / PDA) is required to parse balanced parentheses via recursive CFG rules:
     ```yacc
     exp: '(' exp ')' exp
        | '[' exp ']' exp
        | '{' exp '}' exp
        | /* empty */
        ;
     ```
2. **Lex Role**:
   - Lex ignores whitespace and identifiers/operators `[a-zA-Z0-9+\-*/= \t]+ ;` and forwards only parentheses, brackets, braces, and newlines to YACC.
3. **Error Handling**:
   - If a symbol violates the nesting grammar, `yyerror()` sets `flag = 1`, causing the program to output `Unbalanced Symbols`.
