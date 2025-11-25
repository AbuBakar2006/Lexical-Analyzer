# 🔎 C++ Lexical Analyzer

A custom **Lexical Analyzer (Lexer)** implemented in C++. This program reads source code from a file, removes comments, and tokenizes the input using Regular Expressions (`std::regex`). It processes the code to generate three separate output files: a stream of tokens, a symbol table, and an error log.

## 🚀 Features

* **Token Recognition:** Identifies Keywords, Operators, Numbers, String Literals, and Identifiers.
* **Comment Handling:**
    * Removes single-line comments starting with `#`.
    * Removes inline block comments enclosed in `/* ... */`.
* **Symbol Table:** Automatically tracks unique identifiers and maps them to the line number of their first occurrence.
* **Error Reporting:** Logs invalid or unrecognized tokens to a separate error file.
* **Detailed Output:** Generates three distinct text files for easy analysis.

## 🛠️ Language Specifications

This analyzer is designed for a specific custom syntax with the following rules:

| Category | Patterns / Words Supported |
| :--- | :--- |
| **Keywords** | `assignment`, `if`, `else`, `print` |
| **Operators** | `=`, `+`, `-`, `*`, `/`, `<`, `>`, `<=`, `>=`, `==`, `!=` |
| **Delimiters** | `(`, `)`, `{`, `}`, `;`, `"` |
| **Comments** | `#` (Single line), `/* */` (Inline) |
| **Identifiers** | Regex: `[A-Za-z_][A-Za-z0-9_]*` (Start with letter/underscore) |
| **Numbers** | Regex: `[0-9]+(\.[0-9]+)?` (Integers and Decimals) |

## 📂 Project Structure

The program reads from an input file and generates the following outputs in the same directory:

1.  **`tokens.txt`**: A list of all valid tokens found, their type, and line number.
2.  **`symbol_table.txt`**: A list of unique identifiers found.
3.  **`errors.txt`**: A log of any characters or patterns that did not match the defined rules.

## 💻 How to Run

### 1. Compile
Run the following command in your terminal to build the project:

```bash
g++ main.cpp -o lexical analyzer
```

### 2. Run
Execute the compiled program
```bash
lexical analyzer.cpp
```

### 3. Input
The program will prompt you for the file path. Enter the name of your source file or the complete address of your file.
```text
Enter File Address: input.txt
```

## 📝 Input File Format
```text
# Variable declaration
assignment val = 30;

if (val > 20) {
    print "Success";
}
```

## Generated Output(tokens.txt)
```text
assignment  Keyword     Line 2
val         Identifier  Line 2
=           Operator    Line 2
30          Number      Line 2
;           Symbol      Line 2
if          Keyword     Line 4
(           Symbol      Line 4
val         Identifier  Line 4
>           Operator    Line 4
20          Number      Line 4
)           Symbol      Line 4
{           Symbol      Line 4
print       Keyword     Line 5
"Success"   String      Line 5
;           Symbol      Line 5
}           Symbol      Line 6
```

## ⚠️ Requirements
* **C++ Compiler** (GCC, MinGW, Clang, or MSVC).
* **C++11 standard or higher** (required for `<regex>` support).
