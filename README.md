# Compiler-using-C-Flex-Bison
Small compiler that does a lexical analysis, syntax analysis and produce the three address code of the input file 
In details:
Project Report Compilers

Language specifications

- A single main() routine. No other functions can be defined
- Integer variables only
- A variable must be defined before it can be used. You can initialize a variable at declaration time and you can only declare one variable at a time
- The name of a variable must consist of an alphabetic character followed by one or more alphabetic characters or numbers
- A print instruction is available in the format: print(id) where id is a previously declared variable
- Handles arithmetic expressions and logical expressions
- It is possible to assign to a variable the value of an arithmetic expression or of a logical expression.
- There are also if, if-else and while statements. The condition of if and while must be the result of a logical expression and must be contained in round brackets. The bodies of the if, the else and the while must be enclosed in curly brackets (blocks), moreover these must always present at least one statement
- All instructions must end with ';'. Exceptions are if, else and while.
- New variables can be defined within the blocks enclosed by curly brackets. You can also use already defined variable names. These variables have local visibility, so the variables and their values will be deleted when leaving the block. Variables defined in outer blocks are visible in all nested blocks.
- Comments can be added, they can only be on one line at a time and must be preceded by '//' and their end is identified by the special character '\n' (new line).


Design choices
Lexical Analyzer (Flex)

The lexical analyzer is responsible for detecting language tokens. Based on the detected token, the appropriate actions are performed. For example, in the case of "int", "if", "main", etc... the relative token is returned, in the case in which an "id" (i.e. the name of a variable) is detected, the lexeme is duplicated and saved in a yylval field, which is the global variable that allows Flex to pass the semantic value associated with the token to the syntactic analyzer (Bison), and then the relative token is also returned. The same goes for the "num" token: in this case the lexeme is converted to an integer, saved in another yylval field, and the corresponding token is returned.

Syntactic Analyzer (Bison)

In Bison the YYSTYPE has been redefined through the directive '%union'. There are 3 fields: number (integer), identifier (string) and label (a structure used exclusively for flow control instructions). The various tokens, their precedence and the associativity of arithmetic and logical operators have been defined.
A context-free grammar has been defined that reflects the previously outlined language specifications. The syntactic analyzer takes care of translating the source code into Three Address Code, then printing out the equivalent instructions in 3AC.
No use is made of inherited attributes for handling the flow control instructions (if and while), but only synthesized attributes are used. The implementation of these instructions is done through the use of markers embedded in the grammar.

IF:
The if statement is handled by creating two new labels. The first one is saved in a temporary variable while the second one is stored in the field 'label1' of $$ (nonterminal ifstmt). At this point the instructions for conditional jump (first label) and unconditional jump (second label) are printed. The conditional jump label is then printed. The semantic action associated with the rule reduction allows printing the label had been stored in $$ since the information was passed via a synthesized attribute ('label1') from the child node to the parent node in the parse tree.
Another label stored in the field 'label2' was also generated, the use of which, however, is relative to the if-else statement.

IF-ELSE:
The if is handled exactly as in the previous case. In the productions that identify the if-else there are two markers: 'er1' and 'er2'. The first one prints the unconditional jump that must be executed in case the program has entered the if body (in order to avoid executing the else body). The second one prints the label of the if body. When the body of the if is finished, the unconditional jump instruction (exit from the if) is printed and then the relative label.
WHILE:
Also in this case the handling is very similar to the IF case. It is only added a marker in the production of whilestmt that allows to print the label related to the jump to return to the beginning of the while, in order to test again the condition.


Note about the delivered files

The delivered folder contains two versions of the compiler: the first one outputs the 3AC relative to the input code and the input/output examples are in Version 1/Examples.
The second version instead has a slightly modified Bison file. The grammar is the same but this time instead of simply output the instructions in 3AC an executable C file is created (if obviously no errors are found during compilation). The syntactic analyzer also creates a library "temp.h" that contains the libraries "uthash.h" (used for the symbol table) and "list.h" (used for the symbol table stack) and declares the variable "list" initializing it to NULL and all the temporary variables needed for the execution of the output C file. In this case the outputs are each inside a separate folder (in Version 2) along with the libraries needed to compile and run the C file.
The two versions share the Flex file, the "list.h" and "uthash.h" libraries, and the input files.

PLEASE NOTE THIS IS THE ENGLISH VERSION OF THE FILE relazione 

