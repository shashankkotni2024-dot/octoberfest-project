# Compiler Design (CD) — Lab FAT Preparation Master Guide

Comprehensive preparation repository containing all experiments, executable source codes, test programs, submitted lab reports, and exact terminal commands to compile and execute each experiment.

---

## 📑 Table of Experiments

| Lab # | Experiment Name | Language / Tool | Key Files | Quick Execution Command (Linux/WSL) |
| :---: | :--- | :---: | :--- | :--- |
| **01** | [**Symbol Table Implementation**](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2001%20-%20Symbol%20Table) | C (GCC) | `symbol_table.c`, `lab1_input.c` | `gcc symbol_table.c -o st && ./st` |
| **02** | [**Lexical Analyzer (Tokenizer) in C**](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2002%20-%20Lexical%20Analyzer%20in%20C) | C (GCC) | `lexical_analyzer.c`, `sample_input.c` | `gcc lexical_analyzer.c -o lexer && ./lexer sample_input.c` |
| **03** | [**Lexical Analyzer using Lex**](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2003%20-%20Lexical%20Analyzer%20using%20Lex) | Lex (FLEX) + C | `lexer.l`, `sample_input.c` | `flex lexer.l && gcc lex.yy.c -o lexer -lfl && ./lexer sample_input.c` |
| **04** | [**Calculator using Lex**](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2004%20-%20Calculator%20using%20Lex) | Lex (FLEX) + C | `calc_lex.l` | `flex calc_lex.l && gcc lex.yy.c -o calc_lex -lfl && ./calc_lex` |
| **05** | [**FIRST and FOLLOW Sets**](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2005%20-%20FIRST%20and%20FOLLOW%20Sets) | C (GCC) | `first_follow.c`, `sample_grammar.txt` | `gcc first_follow.c -o ff && ./ff < sample_grammar.txt` |
| **06** | [**Shift-Reduce Parser**](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2006%20-%20Shift-Reduce%20Parser) | C (GCC) | `shift_reduce_parser.c`, `sample_input.txt` | `gcc shift_reduce_parser.c -o srp && ./srp < sample_input.txt` |
| **08** | [**Calculator using Lex & YACC**](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2008%20-%20Calculator%20using%20Lex%20and%20YACC) | Lex + YACC / Bison | `calc.l`, `calc.y` | `yacc -d calc.y && lex calc.l && gcc y.tab.c lex.yy.c -o calc && ./calc` |
| **09** | [**Balancing Symbols Checker**](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2009%20-%20Balancing%20Symbols%20Checker) | Lex + YACC / Bison | `balance.l`, `balance.y` | `yacc -d balance.y && lex balance.l && gcc y.tab.c lex.yy.c -o balance && ./balance` |
| **10** | [**Three-Address Code (TAC)**](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2010%20-%20Three-Address%20Code%20Generation) | C (GCC) | `tac_generator.c` | `gcc tac_generator.c -o tac && ./tac` |
| **11** | [**Code Optimization Techniques**](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2011%20-%20Code%20Optimization%20Techniques) | C (GCC) | `code_optimizer.c` | `gcc code_optimizer.c -o opt && ./opt` |

---

## 🛠️ Environment & Prerequisites

### 1. Linux / WSL (Recommended for Lex & YACC)
All code runs natively in Ubuntu under Windows Subsystem for Linux (WSL).
```bash
# Verify compiler and generator tools:
gcc --version     # GNU Compiler Collection
flex --version    # Fast Lexical Analyzer Generator
bison --version   # GNU Bison (YACC equivalent)
```
*(If missing in WSL, install via: `sudo apt update && sudo apt install gcc flex bison`)*

### 2. Windows Native (MinGW GCC)
Labs 01, 02, 05, 06, 10, and 11 can be compiled directly on Windows using MinGW `gcc.exe`:
```powershell
gcc <filename>.c -o <filename>.exe
.\<filename>.exe
```
For Labs 03, 04, 08, 09 on Windows, either execute via `wsl` command directly or use `win_flex` and `win_bison`.

---

## ⚡ Quick One-Line Execution Commands per Experiment

### Lab 01 — Symbol Table
```bash
cd "Lab Fat Preparation/Lab 01 - Symbol Table"
gcc symbol_table.c -o symbol_table && ./symbol_table lab1_input.c
```

### Lab 02 — Lexical Analyzer in C
```bash
cd "Lab Fat Preparation/Lab 02 - Lexical Analyzer in C"
gcc lexical_analyzer.c -o lexical_analyzer && ./lexical_analyzer sample_input.c
```

### Lab 03 — Lexical Analyzer using Lex
```bash
cd "Lab Fat Preparation/Lab 03 - Lexical Analyzer using Lex"
flex lexer.l && gcc lex.yy.c -o lexer -lfl && ./lexer sample_input.c
```

### Lab 04 — Calculator using Lex
```bash
cd "Lab Fat Preparation/Lab 04 - Calculator using Lex"
flex calc_lex.l && gcc lex.yy.c -o calc_lex -lfl && ./calc_lex
```

### Lab 05 — FIRST and FOLLOW Sets
```bash
cd "Lab Fat Preparation/Lab 05 - FIRST and FOLLOW Sets"
gcc first_follow.c -o first_follow && ./first_follow < sample_grammar.txt
```

### Lab 06 — Shift-Reduce Parser
```bash
cd "Lab Fat Preparation/Lab 06 - Shift-Reduce Parser"
gcc shift_reduce_parser.c -o shift_reduce_parser && ./shift_reduce_parser < sample_input.txt
```

### Lab 08 — Calculator using Lex & YACC
```bash
cd "Lab Fat Preparation/Lab 08 - Calculator using Lex and YACC"
yacc -d calc.y && lex calc.l && gcc y.tab.c lex.yy.c -o calc && ./calc
```

### Lab 09 — Balancing Symbols Checker
```bash
cd "Lab Fat Preparation/Lab 09 - Balancing Symbols Checker"
yacc -d balance.y && lex balance.l && gcc y.tab.c lex.yy.c -o balance_check && ./balance_check
```

### Lab 10 — Three-Address Code (TAC) Generation
```bash
cd "Lab Fat Preparation/Lab 10 - Three-Address Code Generation"
# Simplified TAC only:
gcc tac_only.c -o tac_only && ./tac_only
# Or full TAC + Quadruples + Triples:
gcc tac_generator.c -o tac_generator && ./tac_generator
```

### Lab 11 — Code Optimization Techniques
```bash
cd "Lab Fat Preparation/Lab 11 - Code Optimization Techniques"
gcc code_optimizer.c -o code_optimizer && ./code_optimizer
```

---

## 🎓 High-Yield Lab FAT Viva & Theory Cheat Sheet

### 1. Lexical Analysis (Phase 1)
- **Token**: Abstract syntactic category (e.g., `KEYWORD`, `IDENTIFIER`, `NUMBER`).
- **Lexeme**: Concrete character sequence matching a token pattern (e.g., `int`, `counter`, `42`).
- **Pattern**: Regular expression describing the set of lexemes (e.g., `[a-zA-Z_][a-zA-Z0-9_]*`).
- **Lex Internal Variables & Functions**:
  - `yytext`: Pointer to current matched lexeme string.
  - `yyleng`: Length of the string in `yytext`.
  - `yylex()`: Main function scanning the input stream and executing pattern actions.
  - `yywrap()`: Called when EOF is reached. Returns `1` to stop or `0` to continue with new input.
  - `yyin`: `FILE*` pointer indicating the input file stream (defaults to `stdin`).

### 2. Syntax Analysis (Phase 2)
- **Context-Free Grammar (CFG)**: 4-tuple $G = (V, T, P, S)$ where $V$ is non-terminals, $T$ is terminals, $P$ is production rules, $S$ is start symbol.
- **FIRST Set**: Set of terminals that can begin strings derived from a non-terminal. Includes $\epsilon$ if the non-terminal can derive the empty string.
- **FOLLOW Set**: Set of terminals that can appear immediately to the right of a non-terminal in some sentential form. **$\epsilon$ is never in a FOLLOW set.** End-marker `$` belongs to $\text{FOLLOW}(S)$.
- **Shift-Reduce Parsing (Bottom-Up)**:
  - **Shift**: Push current terminal onto stack.
  - **Reduce**: Pop matching RHS (handle) from stack and push LHS non-terminal.
  - **Handle**: Substring matching a production's RHS whose reduction represents a step in reverse rightmost derivation.
  - **Shift/Reduce Conflict**: Cannot decide between shifting next token or reducing stack top.
  - **Reduce/Reduce Conflict**: Cannot decide which of two distinct production rules to reduce by.
- **YACC / Bison**:
  - `y.tab.c` and `y.tab.h`: Generated C parser and token header.
  - `%token`: Declares terminal symbols.
  - `%left`, `%right`: Declares operator associativity and precedence (rules declared later have higher precedence).
  - `$$`, `$1`, `$2`: Semantic values of LHS and RHS elements.
  - `yyparse()`: Invokes LALR(1) parsing loop.
  - `yyerror(const char *s)`: Handles syntax errors.

### 3. Intermediate Code Generation (Phase 3)
- **Three-Address Code (TAC)**: Linearized instruction sequence where each statement has at most one operator and at most three operands (`x = y op z`).
- **Quadruples**: Record containing `(op, arg1, arg2, result)`. Explicitly stores temporary names. Easy to rearrange during optimization.
- **Triples**: Record containing `(op, arg1, arg2)`. Omits temporary variable names and references previous computations by table index `(0)`, `(1)`. Takes less space, but moving instructions requires rewriting indices.

### 4. Code Optimization (Phase 4)
- **Constant Folding**: Evaluating constant expressions at compile-time (`2 * 3` $\to$ `6`).
- **Constant / Copy Propagation**: Forwarding constant values or copied variables to eliminate redundant reads (`a = 5; b = a * 2` $\to$ `b = 5 * 2`).
- **Common Subexpression Elimination (CSE)**: Reusing the result of an identical previously computed expression if operands have not changed.
- **Strength Reduction**: Replacing expensive operations with cheaper ones (`x * 2` $\to$ `x + x`).
- **Algebraic Simplification**: Using algebraic identities (`x * 1` $\to$ `x`, `x * 0` $\to$ `0`, `x + 0` $\to$ `x`).
- **Dead Code Elimination**: Removing computations whose results are never read.
- **Fixpoint Iteration**: Repeating optimization passes until no further changes occur.
