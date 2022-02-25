#include "Node.h"
#include <iostream>

using namespace std;

Node::Node() {
	word = "";
	next = this;
	prev = this;
}

Node::Node(std::string input) {
	word = input;
	next = this;
	prev = this;
}

Node::Node(std::string input, Node* other) {
	this->setWord(input);
	//other is previous node
	this->setPrev(other);
	this->setNext(other);
	other->setNext(this);
	other->setPrev(this);
}

string& Node::getWord() {
	return word;
}

Node* Node::getNext() const {
	return this->next;
}

Node* Node::getPrev() const {
	return this->prev;
}

void Node::setWord(std::string input) {
	this->word = input;
}

void Node::setNext(Node * input) {
	this->next = input;
}

void Node::setPrev(Node * input) {
	this->prev = input;
}
