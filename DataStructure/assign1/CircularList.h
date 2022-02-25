//
// CircularList.h (Version 1.0)
//
// Please write your name, your student ID, and your email address here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.

/*
20161248 Jeon Woongbae
Email : wbjeon2k@gmail.com || woongbae@unist.ac.kr

In the CircularList class, the CNode class, which is the node class, is defined as an inner class.
CirculasList has 3 private members : cursor, AVLhead, lsize
cursor is to check the back of the circular list.
AVLhead is the head node of the available space list.
lsize is an integer to mark the size of the circular list.

Member function details

getNode() : returns CNode object
if the available space list is empty, return new CNode
otherwise, take one off from the list and return it.

add() : add a node after the cursor

~CircularList() : destructor
push every nodes into the available space list,
and then delete the available space list using cleanup().

empty() : if the cursor is NULL, then return true. Otherwise, return false

back() : return element where cursor locates

front() : return element where cursor->next locates

advance() : move cursor forward 1 time

size() : return lsize

reverse() : advance cursor, link cursor->next to cursor(link backward) for all the nodes

cleanup(): delete available space lis
*/
//


#ifndef  ASSIGNMENT1_CIRCULARLIST_H
#define ASSIGNMENT1_CIRCULARLIST_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <climits>

using namespace std;

template <typename Elem>
class CircularList
{
public:
	
	class CNode {
		CNode() {
			elem = Elem();
			next = NULL;
		}
		~CNode() {
			next = NULL;
		}
		
		Elem elem;
		CNode * next;
	public:
		friend class CircularList;

	};

	CircularList();
	~CircularList();

	bool empty() const;
	Elem& front() const;
	Elem& back() const;

	void advance();
	void add(const Elem & e);
	void remove();
	int size() const;
	void reverse();
	void cleanup();
	CNode * getNode() {
		//use getNode() instead of new
		//to properly use the available space list
		CNode * x;
		if (AVLhead) {
			x = AVLhead;
			AVLhead = AVLhead->next;
		}
		else {
			x = new CNode;
		}
		return x;
	}

private:
	
	CNode * AVLhead;
	CNode * cursor;
	int lsize;
};

template<typename Elem>
CircularList<Elem>::CircularList():cursor(NULL), AVLhead(NULL) {
	//initialize an object
	 lsize = 0; //incomplete
}


template<typename Elem>
CircularList<Elem>::~CircularList() {
	//add every node into available space list using remove
	//delete every nodes in available space list using cleanup								 
	while (!empty()) {
		remove();
	}
	cleanup();
}



template<typename Elem>
bool CircularList<Elem>::empty() const {//incomplete
	// if cursor == NULL

	if (this->cursor == NULL ) {
		return true;
	}
	else {
		return false;
	}
}

template<typename Elem>
Elem& CircularList<Elem>::front() const {//complete
	if (empty()) {
		//if empty, throw exception
		throw runtime_error("CircularList is empty");
	}
	return (cursor->next->elem);
}

template<typename Elem>
Elem & CircularList<Elem>::back() const {//complete
	if (empty()) {
		//if empty, throw exception
		throw runtime_error("CircularList is empty");
	}
	return (cursor->elem);
}

template<typename Elem>
inline void CircularList<Elem>::advance() {//complete
	if (cursor == NULL) {
		throw runtime_error("CircularList is empty");
	}
	cursor = cursor->next;
}

template<typename Elem>
void CircularList<Elem>::add(const Elem & e) {
	// add after cursor
	CNode* v = getNode(); 
	//use getNode instead of ordianry new
	v->elem = e;
	if (cursor == NULL) {
		// if the list was empty
		v->next = v;
		cursor = v;
	}
	else {
		v->next = cursor->next;
		cursor->next = v;
		//advance();
	}
	this->lsize += 1;
}

template<typename Elem>
void CircularList<Elem>::remove() {//incomplete
								   // add to available space list
	CNode * old = cursor->next;
	if (cursor == NULL) {
		throw runtime_error("CircularList is empty");
	}
	if (old == cursor) {
		//CNode * copy_cursor = getNode();
		//*(copy_cursor) = *cursor;
		//(copy_cursor)->next = AVLhead;
		//AVLhead = copy_cursor;
		cursor->next = AVLhead;
		AVLhead = cursor->next;
		this->cursor = NULL;

	}
	else {
		cursor->next = old->next;
		old->next = AVLhead;
		AVLhead = old;
	}
	
	this->lsize -= 1;
	
}

template<typename Elem>
int CircularList<Elem>::size() const {
	if (empty()) {
		return 0;
	}
	else {
		return (this->lsize);
	}
}

template<typename Elem>
void CircularList<Elem>::reverse() {

	//Horowitz p.193

	if (cursor == NULL) {
		throw runtime_error("CircularList is empty");
	}

	CNode* current = cursor->next;
	CNode* previous = cursor;


	for (int i = 0;i < size()+1;++i) {
		CNode *r = previous;
		previous = current;
		current = current->next;
		previous->next = r;
	}
	cursor = previous;
	

}

template <typename Elem>
void CircularList<Elem>::cleanup() {
	//delete available space list
	while (AVLhead != NULL) {
		CNode * old = AVLhead;
		AVLhead = old->next;
		delete old;
	}
}



#endif // ! ASSIGNMENT1_CIRCULARLIST_H

