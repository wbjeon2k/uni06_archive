//
// assignment1.cpp (Version 1.0)
//
// Please write your name, your student ID, and your email address here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
/*
20161248 Jeon Woongbae
Email : wbjeon2k@gmail.com || woongbae@unist.ac.kr

description is written in some kind of pseudocode.

getpriority(Token){
	return priority(icp in textbook) of operators
	( : return 0
	*,/ : return 1
	+,- : return 2
	otherwise : throw runtime error
}

getinstackpriority(Token){
	return in-stack priority(isp in textbook) of operators
	*./ : return 1
	+,- : return 2
	( : return 3
	otherwise : runtime error
}

postfix(expression){
	for all tokens in the expression: starting from front{
		if token is a number : add it to result
		if token is a closed paranthesis : pop stack until it reaches to open paranthesis
		otherwise : push it to stack
	}
}

eval(expression){
push tokens into the stack.
when it reaches to an operator, pop two tokens, and evaluate with the proper operator
if it fails to pop two tokens, then throw runtime error, because of mismatch in operator & operand.
when the result overflows, then throw runtime error
push the result back in the stack
}


*/
//


// include header filers here
#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
#include "LinkedStack.h"
#include "Token.h"
#include "tokenizer.h"


using namespace std;


int getPriority(Token token) {
	//priority:
	//0 : (
	//1 : *,/
	//2 : +,-
	//etc : runtime error
	Token::TokenType Toktype = token.getTokenType();
	Token::Operator Opertype = token.getOperator();
	int prior = 0;

	if (Toktype == Token::CONSTANT_TOKEN) {
		throw runtime_error("token is not an operator");
	}
	else if (Opertype == Token::CLOSE_PARENTHESIS_OPERATOR) {
		throw runtime_error("token is a CLOSE_PARANTHESIS_OPERATOR");
	}
	else if (Opertype == Token::OPEN_PARENTHESIS_OPERATOR) {
		prior = 0;
		return prior;
	}
	else if (Opertype == Token::MULTIPLICATION_OPERATOR || Opertype == Token::DIVISION_OPERATOR) {
		prior = 1;
		return prior;
	}
	else if (Opertype == Token::ADDITION_OPERATOR || Opertype == Token::SUBTRACTION_OPERATOR) {
		prior = 2;
		return prior;
	}

}


int getInStackPriority(Token token) {
	//priority:
	//0 : *,/
	//1 : +,-
	//2 : (
	//etc : runtime error

	int prior=0;
	Token::Operator Opertype = token.getOperator();
	Token::TokenType Toktype = token.getTokenType();

	if (Toktype == Token::CONSTANT_TOKEN) {
		throw runtime_error("token is a CONSTANT_OPERATOR");
	}
	else if (Opertype == Token::CLOSE_PARENTHESIS_OPERATOR) {
		throw runtime_error("token is a CLOSE_PARANTHESIS_OPERATOR");
	}
	else if (Opertype == Token::OPEN_PARENTHESIS_OPERATOR) {
		prior = 3;
		return prior;
	}
	else if (Opertype == Token::MULTIPLICATION_OPERATOR || Opertype == Token::DIVISION_OPERATOR) {
		prior = 1;
		return prior;
	}
	else if (Opertype == Token::ADDITION_OPERATOR || Opertype == Token::SUBTRACTION_OPERATOR) {
		prior = 2;
		return prior;
	}

}


vector<Token> postfix(const vector<Token>& expression) {

	LinkedStack<Token> stack;
	vector<Token> postprocess ;

	for (vector<Token>::const_iterator iter = expression.begin(); iter != expression.end(); iter++) {
		if ((*iter).isConstant()) {
			//cout << (*iter).getConstant();
			(postprocess).push_back((*iter));
		}
		else if ((*iter).getOperator() == Token::CLOSE_PARENTHESIS_OPERATOR) {
			while (stack.empty() == false && stack.top().getOperator() != Token::OPEN_PARENTHESIS_OPERATOR) {
				(postprocess).push_back(stack.top());
				stack.pop();
			}
			//for (; stack.top().getOperator() != Token::OPEN_PARENTHESIS_OPERATOR; stack.pop()) {
			//	(postprocess).push_back(stack.top());	
			//}
			stack.pop();
		}
		else {
			
			while (stack.empty() == false && getInStackPriority(stack.top()) <= getPriority(*iter) ) {
				//cout << "instack priority: " << getInStackPriority(stack.top()) << endl;
				//cout << "ic priority: " << getPriority(*iter) << endl;

				(postprocess).push_back(stack.top());
				stack.pop();
			}
			//for (; getInStackPriority(stack.top()) <= getPriority(*iter); stack.pop()) {
			//	(postprocess).push_back(stack.top());
			//}
			
			
			stack.push(*iter);
		}
	}

	while (stack.empty() == false) {
		(postprocess).push_back(stack.top());
		stack.pop();
	}
	//for (; stack.empty() != true; (postprocess).push_back(stack.top()), stack.pop());

	
	return postprocess;

}


int eval(const vector<Token>& expression) {

	LinkedStack<Token> stack;
	int result;

	for (vector<Token>::const_iterator iter = expression.begin(); iter != expression.end(); iter++) {

		if ((*iter).isConstant()) {
			stack.push(*iter);
		}
		else {
			Token::Operator oper = (*iter).getOperator();
			int a = 0, b = 0;
			long long c = 0;
			if (stack.empty() == true) {
				throw runtime_error("Operator and operand does not match");
			}
			b = stack.top().getConstant();
			(stack.empty() != true ? stack.pop() : throw runtime_error("Operator and operand does not match"));
			a = stack.top().getConstant();
			(stack.empty() != true ? stack.pop() : throw runtime_error("Operator and operand does not match"));
			if (oper == Token::ADDITION_OPERATOR) {
				c = (long long)a + (long long)b;
				if (c > INT_MAX || c < INT_MIN) {
					throw runtime_error("Overflow at addition");
				}
				else {
					stack.push(Token( (int)c ));
				}
				
			}
			else if (oper == Token::SUBTRACTION_OPERATOR) {
				c = (long long)a - (long long)b;
				if (c > INT_MAX || c < INT_MIN) {
					throw runtime_error("Overflow at subtraction");
				}
				else {
					stack.push(Token((int)c));
				}
			}
			else if (oper == Token::MULTIPLICATION_OPERATOR) {
				c = (long long)a*(long long)b;
				if (c > INT_MAX || c < INT_MIN) {
					throw runtime_error("Overflow at multiplication");
				}
				else {
					stack.push(Token((int)c));
				}
			}
			else if (oper == Token::DIVISION_OPERATOR) {
				if (b == 0) {
					throw runtime_error("Cannot divide by 0");
				}
				else {
					c = a / b;
					stack.push( Token((int)c) );
				}
			}
		}

	}
	//2147483647
	return (stack.top().getConstant());

}

