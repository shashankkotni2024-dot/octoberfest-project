# Lab 06: Bottom-Up Shift-Reduce Parser in C

## 1. Aim
To design and implement a Bottom-Up Shift-Reduce Parser using C language for a given Context-Free Grammar (CFG) to verify whether an input string (such as `i+i*i`) is valid or invalid based on stack operations (Shift, Reduce, Accept, Reject).

---

## 2. Files in this Directory
- [`shift_reduce_parser.c`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2006%20-%20Shift-Reduce%20Parser/shift_reduce_parser.c): C source code for the shift-reduce parser with generic reduction search and backtracking.
- [`sample_input.txt`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2006%20-%20Shift-Reduce%20Parser/sample_input.txt): Sample grammar (arithmetic expression grammar) and input string `i+i*i`.
- [`lab6_bce5183.pdf`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2006%20-%20Shift-Reduce%20Parser/lab6_bce5183.pdf): Original submitted lab report.

---

## 3. Execution Commands (In Order)

### Linux / WSL (Ubuntu)
```bash
# Step 1: Navigate to this directory
cd "Lab Fat Preparation/Lab 06 - Shift-Reduce Parser"

# Step 2: Compile the C source code
gcc shift_reduce_parser.c -o shift_reduce_parser

# Step 3: Run interactively
./shift_reduce_parser

# Or redirect input from sample_input.txt:
./shift_reduce_parser < sample_input.txt
```

### Windows (PowerShell / Command Prompt with MinGW GCC)
```powershell
# Step 1: Navigate to this directory
cd "Lab Fat Preparation\Lab 06 - Shift-Reduce Parser"

# Step 2: Compile with GCC
gcc shift_reduce_parser.c -o shift_reduce_parser.exe

# Step 3: Run with sample input redirected
Get-Content sample_input.txt | .\shift_reduce_parser.exe
```

---

## 4. Sample Input & Step-by-Step Parse Trace

### Input Grammar
```text
6
E->E+T
E->T
T->T*F
T->F
F->(E)
F->i
i+i*i
```

### Output Trace
```text
STACK                ACTION              
----------------------------------------
i                    SHIFT i             
F                    REDUCE F->i         
T                    REDUCE T->F         
E                    REDUCE E->T         
E+                   SHIFT +             
E+i                  SHIFT i             
E+F                  REDUCE F->i         
E+T                  REDUCE T->F         
E+T*                 SHIFT *             
E+T*i                SHIFT i             
E+T*F                REDUCE F->i         
E+T                  REDUCE T->T*F       
E                    REDUCE E->E+T       

ACCEPT
```

---

## 5. Key Concepts & Viva Notes
1. **Four Basic Actions in Shift-Reduce Parsing**:
   - **Shift**: Move the next input symbol onto the top of the parser stack.
   - **Reduce**: Replace a substring at the top of the stack (the handle) that matches the right-hand side (RHS) of a production rule with the corresponding non-terminal on the left-hand side (LHS).
   - **Accept**: Announce successful parsing when the input is empty and the stack contains only the start symbol.
   - **Error**: Discovery of a syntax error when neither shift nor reduce is valid.
2. **Handle Pruning**:
   - A *handle* is a substring matching the RHS of a production whose reduction represents one step along the reverse of a rightmost derivation.
3. **Parsing Conflicts**:
   - **Shift/Reduce Conflict**: The parser cannot decide whether to shift the next input symbol or reduce the current stack symbols.
   - **Reduce/Reduce Conflict**: The parser cannot decide which of two or more distinct production rules to reduce with.
