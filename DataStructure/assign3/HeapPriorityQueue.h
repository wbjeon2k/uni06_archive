/*
20161248 JEON WOONGBAE
wbjeon2k@gmail.com

*/

//
// HeapPriorityQueue.h  (Version 1.0)
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//

#ifndef ASSIGNMENT3_HEAPPRIORITYQUEUE_H
#define ASSIGNMENT3_HEAPPRIORITYQUEUE_H

// You are *not* allowed to include other header files

#include <iostream>
#include <stdexcept>
#include "ArrayCompleteTree.h"

using namespace std;


/*
 * This is a generic less-than comparator that relies on operator<() to
 * compare two objects. This generalizes the LeftRight class on Page 326
 * in the textbook.
 */
template<typename T>
class LessThanComparator {
public:
  bool operator()(const T& a, const T& b) const { return a < b; }
};


/*
 * A heap-based priority queue based on ArrayCompleteTree.
 * See Section 8.3.4 in the textbook for more information.
 *
 * Notice that you are *not* allowed to define any other member variables in this class.
 */
template<typename E, typename C>
class HeapPriorityQueue {
	
public:
	typedef typename ArrayCompleteTree<E>::Position Position;

	HeapPriorityQueue();
	HeapPriorityQueue(const HeapPriorityQueue& q);
	int size() const;
	bool empty() const;
	Position insert(const E& e);
	const E& min();
	//Position minp(); // 나중에 제거
	void removeMin();
	void remove(const Position& u);
	Position replace(const Position& p, const E& e);


private:
	void bubbleDown(const Position &u);
	void bubbleUp(const Position &u);
	//typedef typename ArrayCompleteTree<E>::Position Position;
	ArrayCompleteTree<E> T;  // the array-based complete tree
	C isLess;                // the less-than comparator

};


template<typename E, typename C>
HeapPriorityQueue<E, C>::HeapPriorityQueue() {
	//T=ArrayCompleteTree<E>();
	//isLess = C();
}


template<typename E, typename C>
HeapPriorityQueue<E, C>::HeapPriorityQueue(const HeapPriorityQueue& q): T(q.T) {
	isLess = (q.isLess);
}

template<typename E, typename C>
int HeapPriorityQueue<E, C>::size() const {
	return T.size();
}

template<typename E, typename C>
bool HeapPriorityQueue<E, C>::empty() const {
	return (T.size() == 0 ? true : false);
}

template<typename E, typename C>
void HeapPriorityQueue<E, C>::bubbleUp(const Position &u) {
	while (T.isRoot(u) == false) {
		Position v = T.parent(u);
		if (!isLess(*u, *v)) break;
		T.swap(u, v);
	}
}

template<typename E, typename C>
void HeapPriorityQueue<E, C>::bubbleDown(const Position &u) {
	while(T.hasLeft(u) == true) {
		Position v = T.left(u);
		if (T.hasRight(u) && isLess(*(T.right(u)), *v)) {
			v = T.right(u);
		}
		if (isLess(*v, *u)) {
			T.swap(u, v);
		}
		else break;
	}
}


template<typename E, typename C>
typename ArrayCompleteTree<E>::Position HeapPriorityQueue<E, C>::insert(const E &e) {
	T.addLast(e);
	Position u = T.last();
	bubbleUp(u);
	return u;
}

template<typename E, typename C>
void HeapPriorityQueue<E, C>::removeMin() {
	if (this->size() == 0) {
		throw runtime_error("Queue is emtpy");
	}
	if (this->size() == 1) {
		T.removeLast();
	}
	else {
		Position u = T.root();
		T.swap(u, T.last());
		T.removeLast();
		bubbleDown(u);
	}
}

template<typename E, typename C>
void HeapPriorityQueue<E, C>::remove(const Position& u) {
	if (this->size() == 0) {
		throw runtime_error("Queue is emtpy");
	}
	if (this->size() == 1) {
		T.removeLast();
	}
	else {
		Position v = T.last();
		T.swap(u, v);
		T.removeLast();
		if (T.isRoot(v) == true || isLess(*v, *(T.parent(v))) != true) {
			bubbleDown(v);
		}
		else {
			bubbleUp(v);
		}
		
	}
}

template<typename E, typename C>
const E& HeapPriorityQueue<E, C>::min() {
	if (this->size() == 0) {
		throw runtime_error("Queue is emtpy");
	}
	return *(T.root());
}


template<typename E, typename C>
typename ArrayCompleteTree<E>::Position HeapPriorityQueue<E, C>::replace(const Position &p, const E &e) {
	remove(p);
	return insert(e);
}

/*
template<typename E, typename C>
typename ArrayCompleteTree<E>::Position HeapPriorityQueue<E, C>::minp() {
	Position u = T.root();
	return u;
}
*/

#endif //ASSIGNMENT3_HEAPPRIORITYQUEUE_H
