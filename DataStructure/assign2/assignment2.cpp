//
// assignment2.cpp
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//


/*

20161248 JEON WOONGBAE
wbjeon2k@gmail.com

parsePostfixExpression:
	if operand: push
	if operator: pop two operand, make them as children

inorder:
	get token
	if operand: push
	if operator : pop two tokens, combine them, and push expression

simplify_subtree:
	generate positionlist which takes the postfix order
	iterate through the positionlist, which is same as iterating from bottom to top
	if meets operator: check wheter left&right are both constants, compute, and replace node

others: trivial


*/


#include <iostream>
#include <stdexcept>
#include <list>
#include <stack>
#include <limits>
#include <string>
#include <sstream>
#include <algorithm>
#include "LinkedBinaryTree.h"
#include "Symbol.h"
#include "assignment2.h"


LinkedBinaryTree<Symbol> parsePostfixExpression(list<string> tokens) {
	/*
	if operand: push
	if operator: pop two operand, make them as children
	*/
	stack< LinkedBinaryTree<Symbol> > expstack;
	list<string>::iterator iter;
	for (iter = tokens.begin(); iter != tokens.end(); ++iter) {
		Symbol s = Symbol(*iter);
		if (s.isOperator()) {
			if (expstack.empty()) {
				throw runtime_error("Operator and operand does not match");
			}
			LinkedBinaryTree<Symbol> a = expstack.top();
			expstack.pop();
			if (expstack.empty()) {
				throw runtime_error("Operator and operand does not match");
			}
			LinkedBinaryTree<Symbol> b = expstack.top();
			expstack.pop();

			LinkedBinaryTree<Symbol> opr;
			opr.addRoot();
			*opr.root() = s;

			opr.attachLeftSubtree(opr.root(), b);
			opr.attachRightSubtree(opr.root(), a);
			expstack.push(opr);
		}
		else{
			LinkedBinaryTree<Symbol> oprnd;
			oprnd.addRoot();
			*oprnd.root() = s;

			expstack.push(oprnd);
		}
	}
	if (expstack.size() != 1) {
		throw runtime_error("Error in the equation");
	}

	return expstack.top();

}

void postorder(const LinkedBinaryTree<Symbol>::Position& p, LinkedBinaryTree<Symbol>::PositionList& pl) {
	if (p.isNull() == true) {
		return;
	}
	if (!p.left().isNull()) {
		postorder(p.left(), pl);
	}
	if (!p.right().isNull()) {
		postorder(p.right(), pl);
	}
	pl.push_back(p);
}

//http://scanftree.com/Data_Structure/postfix-to-infix

string inorder(LinkedBinaryTree<Symbol>::PositionList& pl) {
	/*
	get token
	if operand: push
	if operator : pop two tokens, combine them, and push expression
	*/
	stack<string> expstack;

	for (list<LinkedBinaryTree<Symbol>::Position>::const_iterator pos_iter = pl.begin();
		pos_iter != pl.end();
		++pos_iter)
	{
		string blank = " ";
		if ((**pos_iter).isOperator()) {
			string exp = "(";
			Symbol::Operator opr = (**pos_iter).getOperator();
			string oprstr;

			if (opr == Symbol::addition) {
				oprstr = "+";
			}
			else if (opr == Symbol::multiplication) {
				oprstr = "*";
			}
			else if (opr == Symbol::division) {
				oprstr = "/";
			}
			else if (opr == Symbol::subtraction) {
				oprstr = "-";
			}
			else {
				throw runtime_error("Invalid operator");
			}


			string a = expstack.top();
			expstack.pop();
			string b = expstack.top();
			expstack.pop();

			exp = exp + blank + b + blank + oprstr + blank + a + blank + ")";
			expstack.push(exp);

		}
		else if ((**pos_iter).isConstant()) {
			int a = (**pos_iter).getConstant();
			stringstream ss;
			ss << a;
			string str = ss.str();
			expstack.push(str);
		}
		else if ((**pos_iter).isVariable()) {
			string str = (**pos_iter).getVariable();
			expstack.push(str);
		}
	}

	return expstack.top();
}

void print_inorder(const LinkedBinaryTree<Symbol>& tree) {

	LinkedBinaryTree<Symbol>::PositionList pl;
	
	postorder(tree.root(), pl);
	string expression = inorder(pl);
	cout << expression;
	
}

void print_postorder(const LinkedBinaryTree<Symbol>& tree) {
	LinkedBinaryTree<Symbol>::PositionList pl;
	postorder(tree.root(), pl);
	for (list<LinkedBinaryTree<Symbol>::Position>::const_iterator pos_iter = pl.begin();
		pos_iter != pl.end();
		++pos_iter)
	{
		*pos_iter;
		cout << **pos_iter << " ";
	}
}

int symdepth(const LinkedBinaryTree<Symbol>::Position& p, const Symbol& s) {
	if (p.isNull()) {
		return 0;
	}
	if (*p == s) {
		return 0;
	}
	if (p.isExternal() == false) {
		return 1 + min(symdepth(p.right(), s), symdepth(p.left(), s));
	}
	else {
		return INT_MAX;
	}
	
}

int findMinimumDepth(const LinkedBinaryTree<Symbol>& tree, const Symbol& sym) {

	int mini = INT_MAX;
	bool chk = false;
	LinkedBinaryTree<Symbol>::PositionList pl = tree.positions();
	for (list<LinkedBinaryTree<Symbol>::Position>::const_iterator pos_iter = pl.begin();
		pos_iter != pl.end();
		++pos_iter)
	{
		if (**pos_iter == sym) {
			mini = min(mini, symdepth(tree.root(), **pos_iter));
			chk = true;
		}
	}
	if (chk) {
		return mini;
	}
	else {
		return -1;
	}

}


void substitute(const LinkedBinaryTree<Symbol>& tree, const Symbol& variable, const Symbol& constant) {
	LinkedBinaryTree<Symbol>::PositionList pl = tree.positions();
	for (list<LinkedBinaryTree<Symbol>::Position>::const_iterator pos_iter = pl.begin();
		pos_iter != pl.end();
		++pos_iter)
	{
		if (**pos_iter == variable) {
			**pos_iter = constant;
		}
	}
}


void simplify_subtree(LinkedBinaryTree<Symbol>& tree) {
	/*
	generate positionlist which takes the postfix order
	iterate through the positionlist, which is same as iterating from bottom to top
	if meets operator: check wheter left&right are both constants, compute, and replace node
	*/
	LinkedBinaryTree<Symbol>::PositionList pl;
	postorder(tree.root(), pl);
	for (list<LinkedBinaryTree<Symbol>::Position>::const_iterator pos_iter = pl.begin();
		pos_iter != pl.end();
		++pos_iter)
	{
		Symbol s = **pos_iter;
		LinkedBinaryTree<Symbol>::Position rnode((*pos_iter).right());
		LinkedBinaryTree<Symbol>::Position lnode((*pos_iter).left());


		if (s.isOperator()) {
			if ((*rnode).isConstant() && (*lnode).isConstant() && (lnode).isExternal() && (rnode).isExternal()) {

				**pos_iter = Symbol(s.compute((*lnode).getConstant(), (*rnode).getConstant()));
				tree.removeSubtree(rnode);
				tree.removeSubtree(lnode);
					
			}
		}

	}
	
}

// X 1 + X * 9 5 - 2 + / X 7 4 - * Y + - #

