# CS 421 Programming Assignment: Expression Validator
*Copyright 2016 Brittany Dibble, Caleb Evans*

For this school project, we were to write a program that simulates a pushdown
automaton to determine whether an arithmetic expression is syntactically valid.

## Setup

To compile the program, run:  
```bash
g++ expression-validator.cpp -o expression-validator.out
```

To execute the compiled program, run:  
```bash
./expression-validator.out
```

The program reads expressions from `expressions.txt` (one expression per line).
Spaces within any of the input expressions are prohibited and rejected by the
parser.
