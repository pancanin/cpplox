# cpplox
Interpreter for a custom scripting language

## Steps

1. Scanning
Go through the source code, character by character, and create a list of meaningful 'words'. Report any syntax errors.
We consume greedily until we reach terminating character.

2. Parsing
Create an AST from the individual words that we found in Scanning phase.
We start by matching the broadest category of our language - the expression and first attempt to match the next level precedence.
The order is:
1. Expression
2. Equality
3. Comparison
4. Addition + Subtraction
5. Multiplication and Division
6. Unary
7. Primary (literals)

3. Interpretation
Walk the tree, but this time start with the most concrete category of expressions - primary (literals). In tree language, that means start from the leafs.
So we go the other way, compared to the parsing stage.
The result of evaluating the tree could be a value or a side-effect, i.e. storing a variable.

## Bugs

- When the process is terminated with Ctrl + C, the program crashes.
- "123asd" as input prints 123 and ignores the "asd" part.


## Lessons learned

- Never ignore the warnings from the compiler. Really odd linking errors could happen and some compilers are more strict than others.
- In visual studio compiler, when you have reference to an object fields in classes, you must import the header files of these classes. Forward declarations won't work for fields.