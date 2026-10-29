# Lab 02: Lexical Analyzer (Tokenizer) in C

## 1. Aim
To design and implement a Lexical Analyzer (Tokenizer) in C programming language without external lexer tools to scan, identify, and classify different types of tokens (Keywords, Identifiers, Numbers, Operators, Separators, String Literals) from a C source file and compute the total number of tokens.

---

## 2. Files in this Directory
- [`lexical_analyzer.c`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2002%20-%20Lexical%20Analyzer%20in%20C/lexical_analyzer.c): C source code for the tokenizer.
- [`sample_input.c`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2002%20-%20Lexical%20Analyzer%20in%20C/sample_input.c): Test C source file to tokenize.
- [`lab2_cd.pdf`](file:///c:/Users/shash/OneDrive/Documents/cd_labexps/Lab%20Fat%20Preparation/Lab%2002%20-%20Lexical%20Analyzer%20in%20C/lab2_cd.pdf): Original submitted lab report.

---

## 3. Execution Commands (In Order)

### Linux / WSL (Ubuntu)
```bash
# Step 1: Navigate to this directory
cd "Lab Fat Preparation/Lab 02 - Lexical Analyzer in C"

# Step 2: Compile the C source code
gcc lexical_analyzer.c -o lexical_analyzer

# Step 3: Run the executable passing the input file as argument
./lexical_analyzer sample_input.c

# Or run interactively (it will prompt for filename):
./lexical_analyzer
# Then type: sample_input.c
```

### Windows (PowerShell / Command Prompt with MinGW GCC)
```powershell
# Step 1: Navigate to this directory
cd "Lab Fat Preparation\Lab 02 - Lexical Analyzer in C"

# Step 2: Compile with GCC
gcc lexical_analyzer.c -o lexical_analyzer.exe

# Step 3: Run the executable
.\lexical_analyzer.exe sample_input.c
```

---

## 4. Expected Output
```text
----------------------------------------
TOKEN           LEXEME         
----------------------------------------
IDENTIFIER      include        
OPERATOR        <              
IDENTIFIER      stdio          
IDENTIFIER      h              
OPERATOR        >              
KEYWORD         int            
IDENTIFIER      main           
SEPARATOR       (              
SEPARATOR       )              
SEPARATOR       {              
KEYWORD         int            
IDENTIFIER      a              
OPERATOR        =              
NUMBER          10             
SEPARATOR       ;              
KEYWORD         float          
IDENTIFIER      b              
OPERATOR        =              
NUMBER          5.5            
SEPARATOR       ;              
KEYWORD         return         
NUMBER          0              
SEPARATOR       ;              
SEPARATOR       }              
----------------------------------------
Total Number of Tokens = 24
```

---

## 5. Key Concepts & Viva Notes
1. **Token vs. Lexeme vs. Pattern**:
   - **Token**: Abstract symbol representing a lexical category (e.g., `KEYWORD`, `IDENTIFIER`, `NUMBER`).
   - **Lexeme**: Concrete instance of characters in the source text matching a pattern (e.g., `int`, `count`, `5.5`).
   - **Pattern**: Rule describing the structure of a lexeme (e.g., `[a-zA-Z_][a-zA-Z0-9_]*`).
2. **Lookahead & Backtracking**: `ungetc(ch, fp)` is used to push back the character that terminated an identifier or number token so it can be re-evaluated as the next token.
3. **Classification Order**:
   - Alphabetic characters and underscores trigger identifier scanning; once captured, the buffer is checked against the keyword table (`isKeyword`).
   - Digits trigger numeric constant scanning (including floating point `.`).
   - Specific character sets are matched for single-character operators and delimiters.
