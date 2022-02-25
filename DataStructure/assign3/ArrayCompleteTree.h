/*
20161248 JEON WOONGBAE
wbjeon2k@gmail.com

*/

//
// ArrayCompleteTree.h  (Version 1.0)
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//

#ifndef ASSIGNMENT3_ARRAYCOMPLETETREE_H
#define ASSIGNMENT3_ARRAYCOMPLETETREE_H

// You are *not* allowed to include other header files

#include <iostream>
#include <stdexcept>

using namespace std;


/*
 * An array-based, adaptable complete tree with location-aware entries.
 * This implementation is based on Section 8.3 and Section 8.4 in the textbook.
 * The difference is that the underlying data structure is a raw array.
 * When the array runs out of space, the doubling strategy is employed
 * to enlarge the array.
 *
 * Notice that you are *not* allowed to define any other member variables in this class.
 */
template<typename E>
class ArrayCompleteTree {
public:

	/*
	* Locator
	*/
	class Locator {
	int i;   // the index of the location-aware entry in v

	public:
		Locator(int _i);
		friend class ArrayCompleteTree<E>;
	};

	/*
	* Location Aware Entry
	*/
	class LocationAwareEntry {
	E e;             // the element
	Locator *loc;    // a pointer to the locator of this entry

	public:
		LocationAwareEntry();
		LocationAwareEntry(E _e, int i);
		//LocationAwareEntry(const LocationAwareEntry& entry);
		//~LocationAwareEntry();
		//LocationAwareEntry& operator=(const LocationAwareEntry& entry);
		void clear();
		friend class ArrayCompleteTree<E>;
	};

	/*
	* Position
	*/
	class Position {
	const ArrayCompleteTree *tree;     // the array of location-aware entries (the same pointer as ArrayCompleteTree::v)
	Locator *loc;              // a pointer to the locator object of the entry pointed by this Position object.

	public:
		Position();
		Position(const ArrayCompleteTree *_tree, Locator *_loc);
		E& operator*() const;
		bool operator==(const Position &p) const;
		friend class ArrayCompleteTree<E>;
	};




private:

	LocationAwareEntry* v;   // the array of location-aware entries
	int vsize;               // the size of v
	int n;                   // the number of used entries in v

public:
	ArrayCompleteTree(int _vsize = 10);
	ArrayCompleteTree(const ArrayCompleteTree& t);
	~ArrayCompleteTree();
	int size() const;
	Position left(const Position& p) const;
	Position right(const Position& p) const;
	Position parent(const Position& p) const;
	bool hasLeft(const Position& p) const;
	bool hasRight(const Position& p) const;
	bool isRoot(const Position& p) const;
	Position root() const;
	Position last() const;
	void addLast(const E& e);
	void removeLast();
	void swap(const Position& p, const Position& q);
	void cleanup();

};


template <typename E>
ArrayCompleteTree<E>::Locator::Locator(int _i) {
	this->i = _i;
}

template <typename E>
ArrayCompleteTree<E>::LocationAwareEntry::LocationAwareEntry() {
	this->e = E();
	this->loc = NULL;
}

template <typename E>
ArrayCompleteTree<E>::LocationAwareEntry::LocationAwareEntry(E _e, int i) {
	this->e = _e;
	this->loc = new Locator(i);
}


/*
template <typename E>
ArrayCompleteTree<E>::LocationAwareEntry::~LocationAwareEntry() {
	this->e = E();
	if (this->loc != NULL) {
		delete (this->loc);
		this->loc = NULL;
	}	
}
*/

/*
template <typename E>
ArrayCompleteTree<E>::LocationAwareEntry::LocationAwareEntry(const LocationAwareEntry& entry) {
	this->e = entry.e;
	this->loc = new Locator(entry.loc->i);
	//*(this->loc) = *(entry.loc);
}

*/

/*
template <typename E>
typename ArrayCompleteTree<E>::LocationAwareEntry&
ArrayCompleteTree<E>::LocationAwareEntry::operator=(const LocationAwareEntry& entry) {

	if (&entry != this) {
		this->e = entry.e;
		if (this->loc != NULL) {
			delete (this->loc);
			if (entry.loc != NULL) {
				this->loc = new Locator(entry.loc->i);
			}
			else {
				this->loc = NULL;
			}
		}
		else {
			if (entry.loc != NULL) {
				this->loc = new Locator(entry.loc->i);
			}
			else {
				this->loc = NULL;
			}
		}
	}

	return *this;
}

*/

template <typename E>
void ArrayCompleteTree<E>::LocationAwareEntry::clear() {
	if (this->loc != NULL) {
		delete (this->loc);
		this->loc = NULL;
	}
}

template <typename E>
ArrayCompleteTree<E>::Position::Position() {
	this->tree = NULL;
	this->loc = NULL;
}

template <typename E>
ArrayCompleteTree<E>::Position::Position(const ArrayCompleteTree *_tree, Locator *_loc) {
	(this->tree) = _tree;
	(this->loc) = new Locator(_loc->i);
	//*(this->loc) = *(_loc);
}

template <typename E>
E& ArrayCompleteTree<E>::Position::operator*() const {
	if (this->tree->v != NULL || this->loc != NULL) {
		return (this->tree->v[this->loc->i]).e;
	}
	else {
		throw runtime_error("Position is empty");
	}
}

template <typename E>
bool ArrayCompleteTree<E>::Position::operator==(const Position &p) const {
	if (this->tree->v == NULL && p->tree->v == NULL) {
		return true;
	}
	else if (this->tree->v == NULL && p->tree->v != NULL) {
		return false;
	}
	else if (this->tree->v != NULL && p->tree->v == NULL) {
		return false;
	}
	else {
		return (*(this) == *p);
	}
}


template <typename E>
ArrayCompleteTree<E>::ArrayCompleteTree(int _vsize) {
	this->n = 0;
	this->vsize = _vsize;
	(this->v) = new LocationAwareEntry[this->vsize];
}


template <typename E>
ArrayCompleteTree<E>::ArrayCompleteTree(const ArrayCompleteTree& t) {
	this->n = t.n;
	this->vsize = t.vsize;
	
	if (vsize > 0) {
		v = new LocationAwareEntry[this->vsize];
		for (int i = 0; i < n; ++i) {
			*((this->v) + i) = *((t.v) + i);
		}
	}
	else if(vsize ==0) {
		v = NULL;
	}
	else {
		throw runtime_error("Size cannot be a negative integer");
	}
}

template <typename E>
ArrayCompleteTree<E>::~ArrayCompleteTree() {
	for (int i = 0;i < n;++i) {
		v[i].clear();
	}
	this->vsize = 0;
	this->n = 0;
	if (this->v != NULL) {
		delete [] (this->v);
		this->v = NULL;
	}
}
	

template <typename E>
int ArrayCompleteTree<E>::size() const {
	return n;
}

template <typename E>
typename ArrayCompleteTree<E>::Position ArrayCompleteTree<E>::left(const Position& p) const{
	if (p.loc == NULL) {
		throw runtime_error("Locator is empty");
	}
	if (p.tree == NULL) {
		throw runtime_error("Tree is empty");
	}
	if ((p.tree)->v == NULL) {
		throw runtime_error("Array is empty");
	}
	
	int idx = p.loc->i;
	if (2 * idx + 1 < this->n) {
		Locator * nloc = new Locator(2 * idx + 1);
		return Position(this, nloc);
	}
	else {
		throw runtime_error("Index out of range");
	}
}


//https://en.wikipedia.org/wiki/Binary_tree
template <typename E>
typename ArrayCompleteTree<E>::Position ArrayCompleteTree<E>::right(const Position& p) const{
	if (p.loc == NULL) {
		throw runtime_error("Locator is empty");
	}
	if (p.tree == NULL) {
		throw runtime_error("Tree is empty");
	}
	if ((p.tree)->v == NULL) {
		throw runtime_error("Array is empty");
	}
	

	int idx = p.loc->i;
	if (2 * idx + 2 < this->n) {
		Locator * nloc = new Locator(2 * idx + 2);
		return Position(this, nloc);
	}
	else {
		throw runtime_error("Index out of range");
	}
	
}


template <typename E>
typename ArrayCompleteTree<E>::Position ArrayCompleteTree<E>::parent(const Position& p) const {

	if (p.loc == NULL) {
		throw runtime_error("Locator is empty");
	}
	if (p.tree == NULL) {
		throw runtime_error("Tree is empty");
	}
	if ((p.tree)->v == NULL) {
		throw runtime_error("Array is empty");
	}

	int idx = p.loc->i;
	if (idx != 0) {
		Locator * nloc = new Locator((idx - 1) / 2);
		return Position(this, nloc);
	}
	else {
		throw runtime_error("Root have no parent");
	}
}

template <typename E>
bool ArrayCompleteTree<E>::hasLeft(const Position& p) const {
	if (p.loc == NULL) {
		throw runtime_error("Locator is null");
	}
	int idx = p.loc->i;
	return (2 * idx + 1 < this->n ? true : false);
}

template <typename E>
bool ArrayCompleteTree<E>::hasRight(const Position& p) const {
	if (p.loc == NULL) {
		throw runtime_error("Locator is null");
	}
	int idx = p.loc->i;
	return (2 * idx + 2 < this->n ? true : false);
}


template <typename E>
bool ArrayCompleteTree<E>::isRoot(const Position& p) const {
	if (n == 0) {
		throw runtime_error("Tree is empty");
	}
	if (p.loc == NULL) {
		throw runtime_error("Locator is null");
	}
	int idx = p.loc->i;
	return (idx == 0 ? true : false);
}

template <typename E>
typename ArrayCompleteTree<E>::Position ArrayCompleteTree<E>::root() const {
	if (n == 0) {
		throw runtime_error("Tree is empty");
	}
	return Position(this, this->v[0].loc);
}

template <typename E>
typename ArrayCompleteTree<E>::Position ArrayCompleteTree<E>::last() const {
	if (n == 0) {
		throw runtime_error("Tree is empty");
	}
	return Position(this, this->v[n-1].loc);
}
template <typename E>
void ArrayCompleteTree<E>::addLast(const E& e) {
	if (n == vsize) {
		LocationAwareEntry* tmpv = new LocationAwareEntry[2 * vsize];
		for (int i = 0;i < n;++i) {
			*(tmpv + i) = *(v + i);
		}
		delete [] v;
		v = tmpv;
		vsize = vsize * 2;
	}
	n += 1;
	
	
	*(v + n - 1) = LocationAwareEntry(e, n - 1);
	
	

}

template <typename E>
void ArrayCompleteTree<E>::removeLast() {

	if (n == 0) {
		throw runtime_error("Tree is empty");
	}
	v[n - 1].clear();
	n -= 1;

}

template <typename E>
void ArrayCompleteTree<E>::swap(const Position& p, const Position& q) {

	if (p.loc == NULL || q.loc == NULL) {
		throw runtime_error("Locator is null");
	}

	E tmp = *q;
	*q = *p;
	*p = tmp;

	int tmploc = q.loc->i;
	q.loc->i = p.loc->i;
	p.loc->i = tmploc;
}

template <typename E>
void ArrayCompleteTree<E>::cleanup() {
	if (n == vsize) {
		return;
	}
	if (n == 0) {
		throw runtime_error("Tree is empty");
	}
	LocationAwareEntry* tmpv = new LocationAwareEntry[n];
	for (int i = 0;i < n;++i) {
		*(tmpv + i) = *(v + i);
	}
	delete[] v;
	v = tmpv;
	vsize = n;
}
#endif 
