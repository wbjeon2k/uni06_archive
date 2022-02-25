//
// LinkedBinaryTree.h (Version 1.0)
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//
/*
20161248 JEON WOONGBAE
wbjeon2k@gmail.com

attatchLeftSubtree:
	parent of the subtree._root = p.v;
	p.v's left child = subtree's root
	make subtree's root as NULL, size as 0 -> delete subtree

attatchRightSubtree:
	same as attatchLeftSubtree

nodeheight:
	get the height of a designated node recursively

others: trivial

*/

#ifndef ASSIGNMENT2_LINKEDBINARYTREE
#define ASSIGNMENT2_LINKEDBINARYTREE




#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <stdexcept>

using namespace std;

template <typename Elem>
class LinkedBinaryTree {
protected:
	class Node {
	private:
		Elem elt;
		Node * par;
		Node * left;
		Node* right;
		Node() : elt(), par(NULL), left(NULL), right(NULL) { };
		~Node() {
			elt = NULL;
			par = NULL;
			left = NULL;
			right = NULL;
		}
	public:
		friend class Position;
		friend class LinkedBinaryTree<Elem>;
	};


public:
	class Position {

	private:
		Node* v;

	public:
		Position(Node* a = NULL) : v(a) {};
		Elem& operator*() const { return v->elt;}
		Position left() const { return Position(v->left); }
		Position right() const { return Position(v->right); }
		Position parent() const { return Position(v->par); }
		bool isRoot() const { return v->par == NULL; }
		bool isExternal() const { return (v->left == NULL) && (v->right == NULL); }
		bool isNull() const { return (v == NULL); }

		friend class LinkedBinaryTree<Elem>;

		
	};
	typedef list<Position> PositionList;
	

public:

	LinkedBinaryTree();
	int size() const;
	bool empty() const;
	Position root() const;
	PositionList positions() const; 
	void addRoot();
	void expandExternal(const Position& p);
	Position removeAboveExternal(const Position& p);
	int height() const;
	void attachLeftSubtree(const Position& p, LinkedBinaryTree& subtree);
	void attachRightSubtree(const Position& p, LinkedBinaryTree& subtree);
	void removeSubtree(const Position& p);

protected:
	void preorder(Node* v, PositionList& pl) const;
	int nodeHeight(const Position& p) const;
private:
	Node* _root;
	int n;

};

template<typename Elem>
LinkedBinaryTree<Elem>::LinkedBinaryTree() : _root(NULL), n(0) {}

template<typename Elem>
int LinkedBinaryTree<Elem>::size() const{
	return n;
}

template<typename Elem>
bool LinkedBinaryTree<Elem>::empty() const{
	return (size() == 0);
}

template<typename Elem>
typename LinkedBinaryTree<Elem>::Position LinkedBinaryTree<Elem>::root() const {
	return Position(_root);
}

template<typename Elem>
void LinkedBinaryTree<Elem>::addRoot() {
	if (_root != NULL) {
		throw runtime_error("Root is not empty");
	}
	_root = new Node;
	n = 1;
}

template<typename Elem>
void LinkedBinaryTree<Elem>::expandExternal(const Position& p) {
	if ( p.isNull() ) {
		throw runtime_error("The node is empty");
	}
	Node* v = p.v;
	if (v->left == NULL && v->right == NULL) {
		v->left = new Node;
		v->left->par = v;
		v->right = new Node;
		v->right->par = v;
		this->n += 2;
	}
	else {
		throw runtime_error("Node is an internal node");
	}
}

template<typename Elem> 
typename LinkedBinaryTree<Elem>::Position LinkedBinaryTree<Elem>::removeAboveExternal(const Position& p) {
	if (!p.isExternal()) {
		throw runtime_error("Node is an internal node");
	}
	Node* w = p.v;
	if (w == _root) {
		delete w;
		n -= 1;
		w = NULL;
		_root = NULL;
		return Position(w);
	}
	Node* v = w->par;
	Node* sib = (w == v->left ? v->right : v->left);

	if (v == _root) {
		_root = sib;
		sib->par = NULL;
	}
	else {
		Node* gpar = v->par;
		if (v == gpar->left) gpar->left = sib;
		else gpar->right = sib;
		sib->par = gpar;
	}
	delete w;
	delete v;
	n -= 2;
	return Position(sib);
}

//https://stackoverflow.com/questions/32491603/t-is-not-a-valid-template-type-argument-for-parameter-t

template <typename Elem>
typename LinkedBinaryTree<Elem>::PositionList LinkedBinaryTree<Elem>::positions() const {
	PositionList pl;
	//if (this->empty() == true || _root == NULL) {
	//	throw runtime_error("Tree is empty");
	//}
	preorder(_root, pl);
	return PositionList(pl);
}

template <typename Elem>
void LinkedBinaryTree<Elem>::preorder(Node* v, PositionList& pl) const {
	if (v == NULL) {
		return;
	}
	if (v != NULL) {
		pl.push_back(Position(v));
	}
	if (v->left != NULL) {
		preorder(v->left, pl);
	}
	if (v->right != NULL) {
		preorder(v->right, pl);
	}
}

template <typename Elem>
int LinkedBinaryTree<Elem>::height() const {
	if (this->_root == NULL || this->empty() == true) {
		throw runtime_error("Tree is empty");
	}
	return nodeHeight(this->root());
}

template <typename Elem>
int LinkedBinaryTree<Elem>::nodeHeight(const Position& p) const {

	//get the height of a designated node recursively
	if ( p.isNull() ) {
		return -1;
	}
	int i = 0;
	i = 1 + max( nodeHeight( p.left() ), nodeHeight( p.right() ) );
	return i;
}



template <typename Elem>
void LinkedBinaryTree<Elem>::removeSubtree(const Position& p) {
	if (p.isNull()) {
		return;
	}
	
	removeSubtree(p.right());
	removeSubtree(p.left());
	
	this->n -= 1;

	
	Node* w = p.v;

	if (p.isRoot() == false) {
		Node* par = p.parent().v;
		(w == par->left ? par->left = NULL : par->right = NULL);
		delete w;
		w = NULL;
		//par = NULL;
	}
	else {
		delete w;
		w = NULL;
		_root = NULL;
	}
	
}

template <typename Elem>
void LinkedBinaryTree<Elem>::attachRightSubtree(const Position& p, LinkedBinaryTree<Elem>& subtree) {
	if (p.right().isNull() != true) {
		throw runtime_error("Right child of the node is not empty");
	}
	if (p.isNull() == true) {
		throw runtime_error("Node is empty");
	}
	if (subtree.empty() == true) {
		throw runtime_error("Subtree is empty");
	}

	Node* w = p.v;
	Node* newroot = subtree._root;

	w->right = newroot;
	newroot->par = w;
	newroot = w;
	this->n += subtree.n;
	subtree._root = NULL;
	subtree.n = 0;
}

template <typename Elem>
void LinkedBinaryTree<Elem>::attachLeftSubtree(const Position& p, LinkedBinaryTree<Elem>& subtree) {
	/*
	parent of the subtree._root = p.v;
	p.v's left child = subtree's root
	make subtree's root as NULL, size as 0 -> delete subtree
	*/
	if (p.left().isNull() != true) {
		throw runtime_error("Left child of the node is not empty");
	}
	if (p.isNull() == true) {
		throw runtime_error("Node is empty");
	}
	if (subtree.empty() == true) {
		throw runtime_error("Subtree is empty");
	}
	Node* w = p.v;
	Node* newroot = subtree._root;

	w->left = newroot;
	newroot->par = w;
	newroot = w;
	this->n += subtree.n;
	subtree._root = NULL;
	subtree.n = 0;
}


#endif // !ASSIGNMENT2_LINKEDBINARYTREE
