/**
 * CS 421 Programming Assignment: Expression Validator
 * Copyright 2016 Brittany Dibble, Caleb Evans
 */
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <fstream>
using namespace std;

// A pushdown automaton used to validate arithmetic expressions
class ExpressionValidator {

	public:

		// The current state of the PDA
        // State 0: no input read
        // State 1: identifier (variable or digit) encountered
        // State 2: operator encountered
        // State 3: all input read
		int currentState;
		stack<char> symbolStack;

		/**
		 * Initializes a new validator object
		 */
		ExpressionValidator() {
			currentState = 0;
			resetSymbolStack();
		}

		/**
		 * Resets the symbol stack by reducing it to the stack start symbol
		 */
		void resetSymbolStack() {
			while (!symbolStack.empty()) {
				symbolStack.pop();
			}
			symbolStack.push('Z');
		}

		/**
		 * Checks if the given input symbol is a valid expression operator
		 * @param  symbol The input symbol to check
		 * @return        Returns true if the symbol is an operator; otherwise,
		 *                returns false
		 */
		bool isOperator(char symbol) {
			return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/');
		}

		/**
		 * Checks if the given input symbol is a valid expression variable
		 * @param  symbol The input symbol to check
		 * @return        Returns true if the symbol is an variable; otherwise,
		 *                returns false
		 */
		bool isVariable(char symbol) {
			return (symbol == 'x' || symbol == 'y' || symbol == 'z');
		}

		/**
		 * Reads an input symbol into the PDA
		 * @param  symbol The input symbol read
		 * @return        Returns true if the expression is still valid after
		 * the input symbol was read; otherwise, returns false
		 */
		bool readSymbol(char symbol) {

			if (isdigit(symbol) || isVariable(symbol)) {
				// Expect numbers to consist of multiple digits but expect
				// variable names to be only one character in length
				currentState = 1;
			} else if (currentState != 1 && symbol == '(') {
				// Expect opening parens to appear only before operators or
				// as the first symbol read
				symbolStack.push('(');
			} else if (currentState == 1 && symbol == ')' && symbolStack.size() >= 1) {
				// Expect closing parens to appear only after numbers or
				// variables
				symbolStack.pop();
			} else if (currentState == 1 && isOperator(symbol)) {
				// Expect operators to appear after numbers or variables
				currentState = 2;
			} else if (currentState == 2 && (isdigit(symbol) || isVariable(symbol))) {
				// Expect numbers or variables to follow operators
				currentState = 1;
			} else {
				return false;
			}

			return true;

		}

		/**
		 * Checks if the given expression is syntactically correct
		 * @param  expression An arithmetic expression as a string
		 * @return            true if the expression is syntactically valid;
		 *                    otherwise, returns false
		 */
		bool validateExpr(string expression) {

			// Reset validator state and symbol stack
			currentState = 0;
			resetSymbolStack();

			// Read entire expression, symbol by symbol
			for (int c = 0; c < expression.length(); c++) {
				if (!readSymbol(expression[c])) {
					// Stop reading input symbols if expression syntax is found
					// to be invalid at any point
					break;
				}
			}

			// If a number of variable was encountered and there all groups of
			// parents have been closed
			if (currentState == 1 && symbolStack.size() == 1) {
				// Move to final state and consider expression valid
				currentState = 3;
				return true;
			} else {
				return false;
			}

			return false;

		}

};

int main() {

	ExpressionValidator validator;
	string line;
	ifstream readIn ("expressions.txt");
	if (readIn.is_open()){
		while ( getline (readIn,line) ){
			cout << "Read In This Expression: " << line << endl;
			if(validator.validateExpr(line)){
				cout << "Expression is syntactically correct" << endl;
			}
			else cout << "Expression is not an arithmetic expression" << endl;
		}
		readIn.close();
	}
	else cout << "Unable to open file" << endl;


	readIn.close();
	return 0;
}
