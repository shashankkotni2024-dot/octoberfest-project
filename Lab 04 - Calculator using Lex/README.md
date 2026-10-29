# Lab 04: Simple Calculator using Lex

## 1. Aim
To implement a simple calculator using the Lex (FLEX) tool that performs basic arithmetic operations (addition, subtraction, multiplication, and division) on user-entered arithmetic expressions and handles division-by-zero errors.

---

## 2. Files in this Directory
- [`calc_lex.l`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2004%20-%20Calculator%20using%20Lex/calc_lex.l): Lex specification matching arithmetic patterns and computing results.
- [`bce5183_lab34.pdf`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2004%20-%20Calculator%20using%20Lex/bce5183_lab34.pdf): Lab report containing Assignment 3 and 4.

---

## 3. Execution Commands (In Order)

### Linux / WSL (Ubuntu)
```bash
# Step 1: Navigate to this directory
cd "Lab Fat Preparation/Lab 04 - Calculator using Lex"

# Step 2: Generate C scanner with flex
flex calc_lex.l

# Step 3: Compile generated C code with GCC and the flex library (-lfl)
gcc lex.yy.c -o calc_lex -lfl

# Step 4: Run the executable
./calc_lex
```

### Windows (Using WSL or WinFlex)
From Windows WSL terminal, run the commands above.
Or using WinFlex:
```cmd
win_flex calc_lex.l
gcc lex.yy.c -o calc_lex.exe
calc_lex.exe
```

---

## 4. Test Inputs & Expected Outputs

| Input Expression | Expected Output | Notes |
| :--- | :--- | :--- |
| `10 + 5` | `Result = 15` | Addition |
| `25 - 8` | `Result = 17` | Subtraction |
| `6 * 7` | `Result = 42` | Multiplication |
| `20 / 4` | `Result = 5.00` | Division |
| `15 / 0` | `Error: Division by zero is not allowed.` | Zero-division guard |
| `abc + 5` | `Invalid Expression` | Default rule match |

*(Press `Ctrl+D` on Linux/WSL or `Ctrl+Z` then `Enter` on Windows to exit).*

---

## 5. Key Concepts & Viva Notes
1. **Direct Evaluation in Lex vs. Lex+YACC**:
   - In pure Lex, regular expressions directly capture the operands and operator simultaneously (e.g., `[0-9]+[ \t]*"+"[ \t]*[0-9]+`).
   - `sscanf(yytext, "%d + %d", &a, &b)` is used to extract the numeric values from the lexeme.
   - Limitation of pure Lex: It can easily parse binary expressions (`a + b`), but cannot naturally handle arbitrarily nested expressions with operator precedence (e.g., `a + b * c`) or recursive parentheses without a grammar parser (which is why YACC is used in Lab 08).
