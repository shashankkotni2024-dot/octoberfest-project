# Lab 10: Three-Address Code (TAC) Generation

## 1. Aim
To write a C program to generate Three-Address Code (TAC), Quadruples, and Triples representation for a given arithmetic expression using temporary variables, respecting operator precedence and associativity.

---

## 2. Files in this Directory
- [`tac_only.c`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2010%20-%20Three-Address%20Code%20Generation/tac_only.c): **Simplified C program (TAC only)** — converts arithmetic expressions to Three-Address Code using an operand stack without quadruples or triples.
- [`tac_generator.c`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2010%20-%20Three-Address%20Code%20Generation/tac_generator.c): Complete C source code for parsing expressions, converting to postfix, and outputting TAC, Quadruples, and Triples.
- [`lab10_report.pdf`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2010%20-%20Three-Address%20Code%20Generation/lab10_report.pdf): Original submitted lab report (PDF).
- [`lab10_report.docx`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2010%20-%20Three-Address%20Code%20Generation/lab10_report.docx): Original submitted lab report (Word document).

---

## 3. Execution Commands (In Order)

### Option A: Simplified TAC Only (`tac_only.c`)
```bash
# Linux / WSL
gcc tac_only.c -o tac_only
./tac_only

# Windows (PowerShell / Command Prompt)
gcc tac_only.c -o tac_only.exe
.\tac_only.exe
```

### Option B: Full TAC + Quadruples + Triples (`tac_generator.c`)
```bash
# Linux / WSL
gcc tac_generator.c -o tac_generator
./tac_generator

# Windows (PowerShell / Command Prompt)
gcc tac_generator.c -o tac_generator.exe
.\tac_generator.exe
```

---

## 4. Test Expressions & Expected Outputs

### Expression 1: `a = b + c * d`
```text
============================================================
Input Expression: a = b + c * d
============================================================

--- 1. Token Classification ---
Operands Identified  : a, b, c, d
Operators Identified : +, *, = (assignment)

--- 2. Postfix Notation ---
b c d * + 

--- 3. Three-Address Code (TAC) ---
t1 = c * d
t2 = b + t1
a = t2

--- 4. Quadruples Representation ---
+-------+----------+------------+------------+------------+
| Index | Operator | Argument 1 | Argument 2 |   Result   |
+-------+----------+------------+------------+------------+
|  0    |    *     | c          | d          | t1         |
|  1    |    +     | b          | t1         | t2         |
|  2    |    =     | t2         | -          | a          |
+-------+----------+------------+------------+------------+

--- 5. Triples Representation ---
+-------+----------+------------+------------+
| Index | Operator | Argument 1 | Argument 2 |
+-------+----------+------------+------------+
|  (0)  |    *     | c          | d          |
|  (1)  |    +     | b          | (0)        |
|  (2)  |    =     | a          | (1)        |
+-------+----------+------------+------------+
```

### Expression 2: `x = (a + b) * (c - d) / e`
Produces temporary variables `t1 = a + b`, `t2 = c - d`, `t3 = t1 * t2`, `t4 = t3 / e`, and `x = t4`.

---

## 5. Key Concepts & Viva Notes
1. **Three-Address Code (TAC)**:
   - An intermediate representation where each instruction has at most one operator and at most three operand addresses (e.g., `x = y op z`).
   - Linearized representation of the syntax tree.
2. **Quadruples**:
   - A 4-tuple record: `(Operator, Argument 1, Argument 2, Result)`.
   - Explicitly names temporary variables in the `Result` field.
   - Benefit: Optimization passes (like code motion) can easily rearrange statements without modifying operand references.
3. **Triples**:
   - A 3-tuple record: `(Operator, Argument 1, Argument 2)`.
   - Does NOT use temporary variable names; references previous results by their statement index / pointer (e.g., `(0)`, `(1)`).
   - Drawback: Moving an instruction requires updating all index references throughout the table.
4. **Indirect Triples**:
   - Uses an array of pointers to Triples. Optimization reorders the pointer array rather than changing the Triples themselves.
