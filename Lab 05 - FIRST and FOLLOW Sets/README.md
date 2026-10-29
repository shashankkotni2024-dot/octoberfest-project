# Lab 05: FIRST and FOLLOW Set Computation in C

## 1. Aim
To develop a C program that accepts a Context-Free Grammar (CFG) as input and computes the FIRST and FOLLOW sets for every non-terminal symbol in the grammar, supporting epsilon ($\epsilon$) productions represented by `#`.

---

## 2. Files in this Directory
- [`first_follow.c`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2005%20-%20FIRST%20and%20FOLLOW%20Sets/first_follow.c): C source code for calculating FIRST and FOLLOW sets.
- [`sample_grammar.txt`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2005%20-%20FIRST%20and%20FOLLOW%20Sets/sample_grammar.txt): Test grammar input file.
- [`bce5183_lab5.pdf`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2005%20-%20FIRST%20and%20FOLLOW%20Sets/bce5183_lab5.pdf): Original submitted lab report.

---

## 3. Execution Commands (In Order)

### Linux / WSL (Ubuntu)
```bash
# Step 1: Navigate to this directory
cd "Lab Fat Preparation/Lab 05 - FIRST and FOLLOW Sets"

# Step 2: Compile the C source code
gcc first_follow.c -o first_follow

# Step 3: Run interactively
./first_follow

# Or redirect input from sample_grammar.txt
./first_follow < sample_grammar.txt
```

### Windows (PowerShell / Command Prompt with MinGW GCC)
```powershell
# Step 1: Navigate to this directory
cd "Lab Fat Preparation\Lab 05 - FIRST and FOLLOW Sets"

# Step 2: Compile with GCC
gcc first_follow.c -o first_follow.exe

# Step 3: Run with sample input redirected
Get-Content sample_grammar.txt | .\first_follow.exe
```

---

## 4. Test Grammar & Expected Output

### Input
```text
8
E->TR
R->+TR
R->#
T->FY
Y->*FY
Y->#
F->(E)
F->i
```

### Output
```text
========== FIRST SETS ==========
FIRST(E) = { ( }
FIRST(R) = { + }
FIRST(R) = { # }
FIRST(T) = { ( }
FIRST(Y) = { * }
FIRST(Y) = { # }
FIRST(F) = { ( }
FIRST(F) = { i }

========== FOLLOW SETS ==========
FOLLOW(E) = { $, ) }
FOLLOW(R) = {  }
FOLLOW(R) = {  }
FOLLOW(T) = { + }
FOLLOW(Y) = {  }
FOLLOW(Y) = {  }
FOLLOW(F) = { * }
FOLLOW(F) = {  }
```

---

## 5. Key Concepts & Viva Notes
1. **Definition of FIRST($\alpha$)**:
   - Set of terminals that begin strings derived from $\alpha$.
   - If $\alpha \xrightarrow{*} \epsilon$, then $\epsilon \in \text{FIRST}(\alpha)$ (represented by `#`).
2. **Rules for FIRST**:
   - If $X$ is a terminal, $\text{FIRST}(X) = \{X\}$.
   - If $X \to \epsilon$, add $\epsilon$ to $\text{FIRST}(X)$.
   - If $X \to Y_1 Y_2 \dots Y_k$: Add $\text{FIRST}(Y_1) \setminus \{\epsilon\}$ to $\text{FIRST}(X)$. If $Y_1 \xrightarrow{*} \epsilon$, add $\text{FIRST}(Y_2) \setminus \{\epsilon\}$, and so on. If all $Y_i \xrightarrow{*} \epsilon$, add $\epsilon$.
3. **Definition of FOLLOW($A$)**:
   - Set of terminals that can appear immediately to the right of $A$ in some sentential form.
4. **Rules for FOLLOW**:
   - Place `$` (end-of-input marker) in $\text{FOLLOW}(S)$, where $S$ is the start symbol.
   - For $A \to \alpha B \beta$: everything in $\text{FIRST}(\beta)$ (except $\epsilon$) is in $\text{FOLLOW}(B)$.
   - If $A \to \alpha B$ or $A \to \alpha B \beta$ where $\text{FIRST}(\beta)$ contains $\epsilon$: everything in $\text{FOLLOW}(A)$ is in $\text{FOLLOW}(B)$.
   - $\epsilon$ is **never** in a FOLLOW set.
