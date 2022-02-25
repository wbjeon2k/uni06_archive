#include "Buffer.h"
#include <iostream>

using namespace std;


Buffer::Buffer() {//empty buffer
	count = 0;
	head = NULL;
}

Buffer::Buffer(const Buffer & other) {
	copy(other);//calls copy
}

Buffer::~Buffer() {
	clear();//deletes buffer
}

Buffer & Buffer::operator=(const Buffer& original) {
	copy(original);//assigns buffer
	return *this;
}

bool Buffer::isEmpty() {
	if (this->count == 0) {//if count is 0
		return true;//it is empty
	}
	else {
		return false;
	}
}

Node* Buffer::getHead() {
	if (isEmpty() == true) {//if empty, then return blank node
		return new Node();
	}
	else {
		return this->head;
	}
	
}

Node* Buffer::getTail() {
	if (isEmpty() == true) {//if empty, return blank node
		return new Node();
	}
	else {
		return (this->head->getPrev());
	}
	
}

string Buffer::getHeadElement() {
	if (count == 0) {//if empty, return blank string
		return "";
	}
	else {
		return ( head->getWord() );
	}
}

string Buffer::getTailElement() {
	if (count == 0) {//if empty, return blank string
		return "";
	}
	else {
		return (head->getPrev()->getWord());
	}
}

void Buffer::produceAtHead(const string input) {
	Node* tmp = new Node(input);
	if (this->isEmpty() == true) {//if it produces at the head
		head = tmp;//new node is the head
	}
	else {//link new node with neighbouring ones
		Iterator iter(head);
		tmp->setPrev((iter - 1).getCurr());
		tmp->setNext(iter.getCurr());
		this->head->getPrev()->setNext(tmp);
		this->head->setPrev(tmp);
		
		
		head = tmp;
	}
	++(this->count);
}

void Buffer::produceAtTail(const string input) {
	Node* tmp = new Node(input);
	
	if (this->isEmpty() == true) {//if the buffer is empty
		head = tmp;//new node is the head
	}
	else {
		Iterator iter(head);//link the new node with neighbours
		tmp->setPrev(this->head->getPrev());
		tmp->setNext(this->head);
		this->head->getPrev()->setNext(tmp);
		this->head->setPrev(tmp);
	}
	
	++(this->count);
}

Iterator Buffer::produceAtMiddle(Iterator pos, const string input) {
	Node* tmp = new Node(input);//link new node with neighbours
	tmp->setPrev((pos - 1).getCurr());
	tmp->setNext(pos.getCurr());
	(pos - 1).getCurr()->setNext(tmp);
	pos.getCurr()->setPrev(tmp);
	
	++(this->count);
	return Iterator(tmp);
	
}

void Buffer::consumeAtHead() {
	Iterator tmp(head);
	if (this->isEmpty()) {//if it is emtpy
		return;//do not consume
	}
	else {
		this->head->getNext()->setPrev(this->head->getPrev());//delete head
		this->head->getPrev()->setNext(this->head->getNext());
	}
	head = head->getNext();//set new head
	//delete tmp.getCurr();
	--(this->count);
}

void Buffer::consumeAtTail() {
	Iterator tmp(head);
	if (this->isEmpty()) {
		return;
	}
	else {
		(tmp - 2).getCurr()->setNext(tmp.getCurr());//delete the tail
		tmp.getCurr()->setPrev((tmp-2).getCurr());
	}
	--(this->count);
}


void Buffer::consume(Iterator it) {
	if (this->isEmpty()) {
		return;
	}
	
	(it+1).getCurr()->setPrev((it-1).getCurr());
	(it-1).getCurr()->setNext((it+1).getCurr());
	if (it.getCurr() == this->head) head = head->getNext();//if it points the head, then set the new head
	--(this->count);
}

void Buffer::consume(Iterator s, Iterator t) {
	if (this->isEmpty()) {
		return;
	}
	if (s == t) {
		return;
	}
	int step;
	for (int j = 0;j <= this->count;j++) {//count the number of elements consume have to delete
		if (s + j == t) {
			step = j;
			break;
		}
	}
	for (int i = 0;i < step;i++) {// consume [s,t)
		consume(s+i);
	}
}

unsigned Buffer::size() const{
	
	return (this)->count;//return count
}

string& Buffer::operator[](int i)const {
	Iterator tmp(head);
	return ( (tmp + i).getCurr()->getWord() );//returns the string nth node has
}

Iterator Buffer::getHeadItr() {
	return Iterator(head);//returns iterator of head
}

Iterator Buffer::getTailItr() {
	return Iterator(head->getPrev());//returns iterator of tail
}

Iterator Buffer::getNextItr(Iterator it) {
	return ++it;
}

Iterator Buffer::getPrevItr(Iterator it) {
	return --it;
}

void Buffer::print() {
	if (this->isEmpty() == true) {// if the buffer is empty
		cout << " -> ";
	}
	else {
		for (unsigned i = 0;i < this->count;i++) {
			cout << (*this)[i];
			if (i != count - 1) {
				cout << " -> ";
			}
		}
	}
	cout << "\n\n";//two endls
}

void Buffer::copy(const Buffer& other) {//copy member variables
	this->count = other.count;
	this->head = other.head;
}

void Buffer::clear() {
	deleteBuffer(head);//call deleteBuffer
}

void Buffer::deleteBuffer(Node * input) {
	Iterator iter(input);
	if (this->isEmpty()) {//until it becomes empty
		return;
	}
	consume(iter);//consume buffer
	deleteBuffer((iter+1).getCurr());
	
}

bool findNode(Iterator first, Iterator last, string str) {
	while(true){
		if (first.getCurr()->getWord() == str) {
			return true;
		}
		if (first == last) {
			break;
		}
		first++;
	}
	
	return false;
}

