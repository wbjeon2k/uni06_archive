#include "Iterator.h"
#include <iostream>

using namespace std;

Iterator::Iterator(Node *currIn) {
	curr = currIn;
}

const string Iterator::operator*() const {
	string tmp = this->curr->getWord();
	delete curr;
	return tmp;

}

Iterator& Iterator::operator++() {//prefix
	this->curr = this->curr->getNext();
	return *this;
}

Iterator& Iterator::operator--() {//prefix
	this->curr = this->curr->getPrev();
	return *this;
}

Iterator Iterator::operator++(int) {//prefix
	Iterator tmp(*this);
	this->curr = this->curr->getNext();
	return tmp;
}

Iterator Iterator::operator--(int) {//prefix
	Iterator tmp(*this);
	this->curr = this->curr->getPrev();
	return tmp;
}

Iterator Iterator::operator+(const int & input) {
	Iterator tmp(this->curr);
	for (int i = 0;i < input;i++) {
		++tmp;
	}
	return tmp;
}

Iterator Iterator::operator-(const int & input) {
	Iterator tmp(this->curr);
	for (int i = 0;i < input;i++) {
		--tmp;
	}
	return tmp;
}

Iterator Iterator::operator+=(const int & input) {
	*this = *this + input;
	return *this;
}

Iterator Iterator::operator-=(const int & input) {
	*this = *this - input;
	return *this;
}

bool Iterator::operator==(const Iterator &other) {
	if (this->curr == other.curr) {
		return true;
	}
	else {
		return false;
	}
}

bool Iterator::operator!=(const Iterator &other) {
	if (this->curr != other.curr) {
		return true;
	}
	else {
		return false;
	}
}

Node *& Iterator::getCurr() {
	return curr;
}

//Iterator & Iterator::operator=(const Iterator &other) {
//	this->curr = other.curr;
//	return *this;
//}

