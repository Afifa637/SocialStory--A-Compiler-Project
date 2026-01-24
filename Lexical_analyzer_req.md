# Complete Lexical Analyzer Requirements Checklist

## ✅ MANDATORY FEATURES (Will Be Asked/Tested)

### 1. **Keywords Recognition**
- [ ] Reserved words (if, while, for, etc.)
- [ ] Case sensitivity handling
- [ ] Multi-word keywords (unique feature!)

### 2. **Identifiers**
- [ ] Variable names (alphanumeric + underscore)
- [ ] Must start with letter or underscore
- [ ] Cannot be keywords
- [ ] Length handling

### 3. **Literals**
- [ ] Integer literals (123, 0, -45)
- [ ] Floating-point literals (3.14, 0.5, -2.7)
- [ ] String literals ("hello", "world")
- [ ] Character literals ('a', 'b') - optional
- [ ] Boolean literals (true/false)

### 4. **Operators**
- [ ] Arithmetic: +, -, *, /, %
- [ ] Relational: ==, !=, <, <=, >, >=
- [ ] Logical: &&, ||, !
- [ ] Assignment: =
- [ ] Compound assignment: +=, -=, *=, /= (bonus)
- [ ] Increment/Decrement: ++, -- (bonus)

### 5. **Delimiters/Separators**
- [ ] Parentheses: ( )
- [ ] Braces: { }
- [ ] Brackets: [ ]
- [ ] Semicolon: ;
- [ ] Comma: ,
- [ ] Dot/Period: .
- [ ] Colon: :

### 6. **Comments**
- [ ] Single-line comments (// or #)
- [ ] Multi-line comments (/* */) - bonus
- [ ] Comments should be ignored (not tokenized)

### 7. **Whitespace Handling**
- [ ] Spaces, tabs, newlines ignored
- [ ] But used as token separators
- [ ] Line number tracking for errors

### 8. **String Processing**
- [ ] Proper quote handling
- [ ] Escape sequences (\n, \t, \", \\)
- [ ] String extraction without quotes
- [ ] Multi-line strings handling (bonus)

### 9. **Number Processing**
- [ ] Integer conversion (atoi)
- [ ] Float conversion (atof)
- [ ] Scientific notation (1.5e10) - bonus
- [ ] Negative numbers
- [ ] Hexadecimal (0xFF) - bonus
- [ ] Octal (0777) - bonus

### 10. **Error Detection**
- [ ] Invalid characters
- [ ] Unterminated strings
- [ ] Invalid number formats
- [ ] Line number reporting
- [ ] Meaningful error messages

### 11. **Token Attributes**
- [ ] Token type (enum/define)
- [ ] Token value (for numbers)
- [ ] Token lexeme (actual text)
- [ ] Line number
- [ ] Column number (bonus)

### 12. **Special Cases**
- [ ] Longest match rule (max munch)
- [ ] Lookahead (for <=, >=, ==, !=)
- [ ] Context-free tokenization
- [ ] EOF handling

### 13. **File I/O**
- [ ] Read from input file
- [ ] Write to output file
- [ ] Proper file handling (open/close)
- [ ] Error handling for file operations

### 14. **Memory Management**
- [ ] Dynamic string allocation
- [ ] Proper memory deallocation
- [ ] No memory leaks
- [ ] Buffer overflow protection

### 15. **Symbol Table (Advanced)**
- [ ] Store identifiers (bonus)
- [ ] Store constants (bonus)
- [ ] Lookup mechanism (bonus)

---

## 🎯 WHAT WILL IMPRESS THE TEACHER

### **Unique Features**
1. **Multi-word keywords** ("The account", "Every day for")
2. **Natural language operators** ("more than", "exceeded")
3. **Context-sensitive tokenization**
4. **Rich error messages with line numbers**
5. **Complete token information** (type, value, lexeme)

### **Technical Depth**
1. **Proper escape sequence handling** in strings
2. **Negative number handling**
3. **Float vs Integer distinction**
4. **Compound operators** (++, --, +=, -=)
5. **Multi-line comment support**
6. **Lookahead for multi-char operators**

### **Professional Quality**
1. **Clean output format**
2. **Comprehensive test file**
3. **Error recovery** (continue after errors)
4. **Well-documented code**
5. **Proper header files**

---

## ❌ COMMON MISTAKES TO AVOID

1. **Not handling negative numbers** properly
2. **String escape sequences** not working
3. **Comments appearing in output** (should be ignored)
4. **Line numbers** not tracked
5. **Memory leaks** from string allocation
6. **No error handling** for invalid input
7. **Operators like <=, >=, ==** recognized as separate tokens
8. **Keywords recognized as identifiers** ("if" → identifier instead of keyword)
9. **No file I/O** (reading from stdin instead)
10. **Unterminated strings** crashing the program

---

## 📋 QUESTIONS TEACHER MIGHT ASK

### Q1: "How does your lexer handle multi-character operators like <= and ==?"
**Answer:** Using longest match rule with lookahead in regex patterns.

### Q2: "What happens if there's an unterminated string?"
**Answer:** Error reported with line number, lexer continues scanning.

### Q3: "How do you distinguish between keywords and identifiers?"
**Answer:** Keywords are checked first in the pattern matching order.

### Q4: "How are escape sequences in strings handled?"
**Answer:** Regex pattern `\\.` matches any escaped character.

### Q5: "Why not store tokens in a symbol table?"
**Answer:** Symbol tables are for semantic analysis; lexer only tokenizes.

### Q6: "How do you handle comments?"
**Answer:** Matched and ignored - not passed to parser.

### Q7: "What about negative numbers?"
**Answer:** Handled in number pattern or as minus operator + number.

### Q8: "How is line number tracked?"
**Answer:** Using `%option yylineno` in Flex.

### Q9: "What's the difference between your language and just renaming C keywords?"
**Answer:** 
- Multi-word tokens
- Narrative syntax (verbs, not operators)
- Natural language comparisons
- Story-based structure

### Q10: "Can your lexer handle nested structures?"
**Answer:** Yes, it tokenizes braces, but validation is parser's job.

---

## ✅ FINAL CHECKLIST - ALL MUST BE ✅

### Basic Requirements
- [x] Keywords recognized
- [x] Identifiers recognized  
- [x] Integer literals
- [x] Float literals
- [x] String literals
- [x] Boolean literals
- [x] All operators
- [x] All delimiters
- [x] Comments ignored
- [x] Whitespace handled
- [x] Line numbers tracked

### Advanced Requirements  
- [ ] Escape sequences in strings ⚠️ MISSING
- [ ] Negative numbers ⚠️ NEEDS TESTING
- [ ] Multi-line comments ⚠️ MISSING
- [ ] Compound operators (++, --, +=) ⚠️ MISSING
- [ ] Unterminated string error ⚠️ NEEDS BETTER HANDLING
- [ ] Multiple error reporting ⚠️ NEEDS IMPROVEMENT

### Professional Polish
- [x] File I/O
- [x] Memory management
- [x] Error messages with line numbers
- [x] Clean output
- [x] Complete test coverage
- [ ] Symbol table (bonus) - NOT REQUIRED

---

## 🚀 WHAT NEEDS TO BE ADDED/FIXED

1. **Escape sequences** - Currently basic, need \n, \t, \\, \"
2. **Negative numbers** - Should work but needs explicit testing
3. **Multi-line comments** - Add /* */ support
4. **Compound operators** - Add ++, --, +=, -=, *=, /=
5. **Better error handling** - Continue after errors, report all
6. **Unterminated string detection** - Better error message
7. **Character literals** - Add 'a', 'b' support (optional)

---

## 📊 SCORING RUBRIC (Typical)

| Feature | Points |
|---------|--------|
| Keywords recognized | 10 |
| Identifiers handled | 10 |
| All literal types | 15 |
| Operators complete | 10 |
| Comments ignored | 5 |
| Error handling | 10 |
| File I/O | 5 |
| Line numbers | 5 |
| String processing | 10 |
| Code quality | 10 |
| Unique features | 10 |
| **TOTAL** | **100** |

Your current implementation: ~75/100
After additions: ~95/100