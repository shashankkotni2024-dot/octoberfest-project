# Lab 01: Implementation of a Symbol Table in C

## 1. Aim
To design and implement a Symbol Table using the C programming language to store information about identifiers (variables and functions), their data types, scopes, and allocated memory sizes, while detecting redeclaration errors within the same scope.

---

## 2. Files in this Directory
- [`symbol_table.c`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2001%20-%20Symbol%20Table/symbol_table.c): Complete C source code using hash table (djb2 hash algorithm) and scope stack.
- [`lab1_input.c`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2001%20-%20Symbol%20Table/lab1_input.c): Test input program containing global, function, and block-level nested scopes.
- [`lab1_report.pdf`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2001%20-%20Symbol%20Table/lab1_report.pdf): Original submitted lab report.

---

## 3. Execution Commands (In Order)

### Linux / WSL (Ubuntu)
```bash
# Step 1: Navigate to this directory
cd "Lab Fat Preparation/Lab 01 - Symbol Table"

# Step 2: Compile the C source code
gcc symbol_table.c -o symbol_table

# Step 3: Run the executable (defaults to reading lab1_input.c)
./symbol_table

# Or explicitly specify any C source file to analyze:
./symbol_table lab1_input.c
```

### Windows (Command Prompt / PowerShell with MinGW GCC)
```powershell
# Step 1: Navigate to this directory
cd "Lab Fat Preparation\Lab 01 - Symbol Table"

# Step 2: Compile with GCC
gcc symbol_table.c -o symbol_table.exe

# Step 3: Run the executable
.\symbol_table.exe lab1_input.c
```

---

## 4. Expected Output
```text
Reading and parsing 'lab1_input.c'...

[Compile Error]: Redefinition of identifier 'localResult' in scope 'block_lvl_3'.

======================================================
NAME            TYPE       SCOPE        MEMORY (Bytes)
======================================================
main            int        local        4         
globalCount     int        global       4         
blockVar        char       local        1         
localResult     int        local        4         
localResult     int        local        4         
i               int        local        4         
i               int        local        4         
scaleFactor     float      local        4         
scaleFactor     float      global       4         
calculate       void       global       0         
```

---

## 5. Key Concepts & Viva Notes
1. **Symbol Table Structure**: A hash table with chaining (linked list at each bucket) provides $O(1)$ average-time lookup and insertion while gracefully handling collisions.
2. **Hashing Algorithm (djb2)**: Computes hash as `hash = ((hash << 5) + hash) + c` (which is `hash * 33 + c`), providing excellent distribution across hash buckets.
3. **Scope Management**: A scope stack tracks parent contexts as the parser enters (`{`) and exits (`}`) nested compound blocks. Identifiers with the same name can exist in different scopes (shadowing), but redeclaration in the same scope triggers a compile error.
4. **Memory Allocation Mapping**:
   - `int`: 4 bytes
   - `float`: 4 bytes
   - `char`: 1 byte
   - `double`: 8 bytes
   - `void`: 0 bytes
