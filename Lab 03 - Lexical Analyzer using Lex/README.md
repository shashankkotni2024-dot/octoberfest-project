# Lab 03: Lexical Analyzer using Lex (FLEX)

## 1. Aim
To implement a Lexical Analyzer using the Lex (FLEX) tool that identifies and classifies tokens such as keywords, identifiers, constants, operators, delimiters, and special symbols from a given C program.

---

## 2. Files in this Directory
- [`lexer.l`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2003%20-%20Lexical%20Analyzer%20using%20Lex/lexer.l): Lex specification defining regular expressions and corresponding actions.
- [`sample_input.c`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2003%20-%20Lexical%20Analyzer%20using%20Lex/sample_input.c): Sample C program for tokenization.
- [`bce5183_lab34.pdf`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2003%20-%20Lexical%20Analyzer%20using%20Lex/bce5183_lab34.pdf): Lab report containing Assignment 3 and 4.

---

## 3. Execution Commands (In Order)

### Linux / WSL (Ubuntu)
```bash
# Step 1: Navigate to this directory
cd "Lab Fat Preparation/Lab 03 - Lexical Analyzer using Lex"

# Step 2: Generate the C lexical scanner file (lex.yy.c) from the lex specification
flex lexer.l

# Step 3: Compile the generated C code with GCC linking the flex library (-lfl)
gcc lex.yy.c -o lexer -lfl

# Step 4: Run the lexical analyzer passing sample_input.c
./lexer sample_input.c

# Or run interactively (type source code and press Ctrl+D to terminate):
./lexer
```

### Windows (Using WinFlex or WSL)
In Windows WSL bash, run the exact Linux commands above. If using standalone `win_flex.exe`:
```cmd
win_flex lexer.l
gcc lex.yy.c -o lexer.exe
lexer.exe sample_input.c
```

---

## 4. Expected Output
```text
Keyword        : int
Identifier     : a
Operator       : =
Constant       : 10
Delimiter      : ;
Keyword        : float
Identifier     : b
Operator       : =
Constant       : 20
Special Symbol : .
Constant       : 5
Delimiter      : ;
Keyword        : if
Delimiter      : (
Identifier     : a
Operator       : <
Identifier     : b
Delimiter      : )
Delimiter      : {
Identifier     : a
Operator       : ++
Delimiter      : ;
Delimiter      : }
```

---

## 5. Key Concepts & Viva Notes
1. **Lex File Structure**:
   - **Definitions Section (`%{ ... %}`)**: Header inclusions, variable declarations, and regular definitions (e.g., `digit [0-9]`).
   - **Rules Section (`%% ... %%`)**: Patterns and actions executed when a pattern is matched: `pattern { action }`.
   - **User Subroutines (`%% ...`)**: Supporting C functions, including `main()` and `yywrap()`.
2. **Special Lex Variables and Functions**:
   - `yytext`: Pointer to the matched string (lexeme).
   - `yyleng`: Length of the matched string.
   - `yylex()`: Main scanning function called to fetch tokens.
   - `yywrap()`: Called when the scanner hits EOF. Returning 1 terminates the scanner.
   - `yyin`: File pointer for the input stream (defaults to `stdin`).
3. **Pattern Precedence**:
   - Lex prioritizes the longest match (maximum munch).
   - If two patterns match the same length, the rule listed earlier in the file takes precedence.
