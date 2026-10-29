# Lab 11: Machine-Independent Code Optimization Techniques

## 1. Aim
To implement machine-independent code optimization techniques (Constant Folding, Constant and Copy Propagation, Common Subexpression Elimination, Strength Reduction, Algebraic Simplification, and Dead Code Elimination) on Three-Address Code (TAC).

---

## 2. Files in this Directory
- [`code_optimizer.c`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2011%20-%20Code%20Optimization%20Techniques/code_optimizer.c): Complete C source code implementing the multi-pass optimization engine.
- [`lab11_report.pdf`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2011%20-%20Code%20Optimization%20Techniques/lab11_report.pdf): Original submitted lab report (PDF).
- [`lab11_report.docx`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2011%20-%20Code%20Optimization%20Techniques/lab11_report.docx): Original submitted lab report (Word document).

---

## 3. Execution Commands (In Order)

### Linux / WSL (Ubuntu)
```bash
# Step 1: Navigate to this directory
cd "Lab Fat Preparation/Lab 11 - Code Optimization Techniques"

# Step 2: Compile the C source code with GCC
gcc code_optimizer.c -o code_optimizer

# Step 3: Run the optimizer
./code_optimizer
```

### Windows (PowerShell / Command Prompt with MinGW GCC)
```powershell
# Step 1: Navigate to this directory
cd "Lab Fat Preparation\Lab 11 - Code Optimization Techniques"

# Step 2: Compile with GCC
gcc code_optimizer.c -o code_optimizer.exe

# Step 3: Run the executable
.\code_optimizer.exe
```

---

## 4. Optimization Pipeline & Sample Output

### Initial TAC (17 Instructions)
```text
[ 1] t1        = 2 * 3
[ 2] t2        = t1 + y
[ 3] a         = 5
[ 4] c         = a * 2
[ 5] z         = a
[ 6] y         = x + 5
[ 7] i         = y
[ 8] z         = i
[ 9] w         = z * 3
[10] t3        = b + c
[11] t4        = b + c
[12] t5        = w * 2
[13] t6        = m * 1
[14] t7        = k * 0
[15] t8        = p + 0
[16] dead      = 99 + 1
[17] final_res = t2 + t3
```

### Pass-by-Pass Optimization Trace
```text
> Pass 1:
  [Folding] t1 = 2 * 3 -> 6
  [Folding] dead = 99 + 1 -> 100
  [Strength] a * 2 -> a + a
  [Strength] w * 2 -> w + w
  [Algebraic] m * 1 -> m
  [Algebraic] k * 0 -> 0
  [Algebraic] p + 0 -> p
  [Propagate] 't1' -> '6' in inst 2
  [Propagate] 'a' -> '5' in inst 4
  [Propagate] 'a' -> '5' in inst 4
  [Propagate] 'a' -> '5' in inst 5
  [Propagate] 'i' -> 'y' in inst 8
  [Propagate] 'z' -> 'y' in inst 9
  [CSE] Replaced t4 = b + c with t3
  [Dead Code] Removed unused t1, z, i, z, t4, t5, t6, t7, t8, dead

> Pass 2:
  [Folding] c = 5 + 5 -> 10
  [Propagate] 'c' -> '10' in inst 10

> Pass 3:
  Fixpoint reached.
```

### Final Optimized TAC (7 Instructions)
```text
[ 1] t2        = 6 + y
[ 2] a         = 5
[ 3] c         = 10
[ 4] y         = x + 5
[ 5] w         = y * 3
[ 6] t3        = b + 10
[ 7] final_res = t2 + t3
```

---

## 5. Key Concepts & Viva Notes
1. **Constant Folding**:
   - Evaluating compile-time constant expressions ahead of time (e.g., `2 * 3` replaced with `6`).
2. **Constant & Copy Propagation**:
   - Replacing variable occurrences with their known constant values (`a = 5` implies later occurrences of `a` become `5`) or copies (`i = y` implies later `i` becomes `y`).
3. **Common Subexpression Elimination (CSE)**:
   - Identifying identical expressions evaluated earlier whose operand values have not changed (e.g., `t4 = b + c` is replaced with `t3`).
4. **Strength Reduction**:
   - Replacing computationally expensive operations with equivalent cheaper ones (e.g., `x * 2` replaced with `x + x`).
5. **Algebraic Simplification / Identities**:
   - Utilizing mathematical identities to eliminate redundant arithmetic:
     - `x * 1` $\to$ `x`
     - `x * 0` $\to$ `0`
     - `x + 0` $\to$ `x`
6. **Dead Code Elimination**:
   - Removing instructions that calculate values that are never subsequently read or used before program termination or reassignment.
7. **Fixpoint Iteration**:
   - Running optimization passes repeatedly until a pass results in zero changes (no further optimization is possible).
