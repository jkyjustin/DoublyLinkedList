#ifdef _LINKEDLIST_H_

#include <stdexcept>
#include <cstdlib>
#include <iostream>

// default constructor
template <typename T>
LinkedList<T>::LinkedList() {
	size = 0;
	front = NULL;
	back = NULL;
}

// copy constructor, performs deep copy of list elements
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& ll) {
	CopyList(ll);
}

// destructor
template <typename T>
LinkedList<T>::~LinkedList() {
	DeleteList();
}

// MUTATORS

// helper function for deep copy
// Used by copy constructor and operator=
template <typename T>
void LinkedList<T>::CopyList(const LinkedList& ll) {
	if (ll.size!=0) {
		size = 0;
		Node<T>* curr = ll.front;
		for (int i = 0; i < ll.size; i++) {
			InsertBack(curr->data);
			curr = curr->next;
		}
	}
	else LinkedList();
}

// helper function for deep delete
// Used by destructor and copy/assignmen
template <typename T>
void LinkedList<T>::DeleteList() {
	Node<T>* temp = front;
	while (temp != NULL) {
		if (front == back) { // if reach end of loop
			delete front;
			break;
		}
		temp = front->next;
		delete front;
		front = temp;
	}
	size = 0;
	front = NULL;
	back = NULL;
}

// Inserts an item at the front of the list
// POST:  List contains item at position 0
// PARAM: item = item to be inserted
template <typename T>
void LinkedList<T>::InsertFront(T item) {
	if (size==0) {
		Node<T>* temp = new Node<T>(item);
		front = temp;
		back = temp;
		size++;
	}
	else {
		Node<T>* temp = new Node<T>(item);
		front->prev = temp;
		temp->next = front;
		front = temp;
		size++;
	}
}

// Inserts an item at the back of the list
// POST:  List contains item at back
// PARAM: item = item to be inserted
template <typename T>
void LinkedList<T>::InsertBack(T item) {
	if (size==0) {
		Node<T>* temp = new Node<T>(item);
		front = temp;
		back = temp;
		size++;
	}
	else {
		Node<T>* temp = new Node<T>(item);
		back->next = temp;
		temp->prev = back;
		back = temp;
		size++;
	}
}

// Inserts an item in position p (0-indexed)
// Throws exception for invalid index
// PRE:   0 <= p <= size
// POST:  List contains item at position p
// PARAM: item = item to be inserted, p = position where item will be inserted
template <typename T>
void LinkedList<T>::InsertAt(T item, int p) {
	if (p==0) {
		InsertFront(item);
		return;
	}	
	else if (p==size) {
		InsertBack(item);
		return;
	} 
	else if (0 < p && p < size) {
		Node<T>* curr = front;
		for (int i=0; i<size; i++) {
			if (i==p) {
				Node<T>* temp = new Node<T>(item);
				temp->prev = curr->prev;
				curr->prev->next = temp;
				curr->prev = temp;
				temp->next = curr;
				size++;
				return; 
			}
			else curr = curr->next;
		}
	}
	else {
		throw std::out_of_range("LinkedList::InsertAt - index out of range");
	}
}

// Removes and returns an item from position p (0-indexed)
// Throws exception if list is empty or index invalid
// PRE:   0 <= p < size
// POST:  Item is removed from list
// PARAM: p = position from where item will be removed
template <typename T>
T LinkedList<T>::RemoveAt(int p) {
	if (front == back) {
		Node<T>* temp = front;
		T result = temp->data;
		delete temp;
		front = NULL;
		back = NULL;
		size = 0;
		return result;
	}
	else if (p==0) {
		Node<T>* temp = front;
		T result = temp->data;
		front = front->next;
		front->prev=NULL;
		delete temp;		
		size--;
		return result;
	}
	else if (p==size-1) {
		Node<T>* temp = back;
		T result = temp->data;
		back = back->prev;
		back->next = NULL;
		delete temp;
		size--;
		return result;
	}
	else if (0 < p && p < (size-1)) {
		Node<T>* curr = front;
		for (int i=0; i<size; i++){
			if (p==i) {
				T result = curr->data;
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				curr->prev = NULL;
				curr->next = NULL;
				delete curr;
				size--;
				return result;
			}
			else curr = curr->next;
		}
	}
	else {
		throw std::out_of_range("LinkedList::RemoveAt - index out of range");
	}
}

// Appends the contents of the parameter list to the back of this list as a deep copy
// PRE:
// POST: List contains every element of ll appended to back, size is updated appropriately
template <typename T>
void LinkedList<T>::Append(const LinkedList& ll) {
	if (ll.Size()>0) {
		Node<T>* curr = ll.front;
		while (curr!=NULL) {
			InsertBack(curr->data);
			curr = curr->next;
		}
	}
}

// Removes duplicates from the list, preserving existing order of remaining items.
// The LAST occurrence of any duplicate (relative to the front of the list)
//   is the one which remains.
// Efficiency will not be a priority as long as the behaviour above is satisfied.
// PRE:   
// POST:  List contains no duplicates, front and back point to the appropriate nodes
// PARAM: 
template <typename T>
void LinkedList<T>::RemoveDuplicates() {
	Node<T>* curr1;
	curr1 = front;
	while (curr1 != NULL && curr1->next!=NULL) {
		Node<T>* curr2 = curr1->next;
		while (curr2!=NULL) {
			if (curr1->data == curr2->data) {
				if (curr1->prev!=NULL) {
					curr1->prev->next = curr1->next;
					curr1->next->prev = curr1->prev;
					curr1->prev = NULL;
					delete curr1;
					size--;
					break;
				} 
				else if (curr1->prev==NULL) {
					curr1->next->prev = NULL;
					curr1->next = NULL;
					curr1->prev = NULL;  
					delete curr1;
					size--;
					break;
				} 
			}
			curr2 = curr2->next;
		}
		curr1 = curr1->next;
	}
}


// ACCESSORS

// Returns size of list
template <typename T>
int LinkedList<T>::Size() const {
	return size;
}

// Returns whether the list is empty
template <typename T>
bool LinkedList<T>::IsEmpty() const {
	return size==0;
}

// Returns existence of item
template <typename T>
bool LinkedList<T>::Contains(T item) const {
	Node<T>* curr = front;
	if (curr==NULL) return false; // empty list, then return false
	else {
		for (int i = 0; i < size; i++) {
			if (item == curr->data) {
				return true;
			}
			curr = curr->next;
		}
	}
	return false;	
}

  // Returns item at index (0-indexed)
  // Throws exception for invalid index
template <typename T>
T LinkedList<T>::ElementAt(int p) const {
	if (p>=0 && p<size) {
		Node<T>* curr = front;
		for (int i = 0; i<size; i++) {
			if (p==i) {
				return curr->data;
			}
			curr = curr->next;
		}
	}
	else {
		throw std::out_of_range("LinkedList::ElementAt - index out of range");
		}
}



// OVERLOADED OPERATORS

// overloaded assignment operator
// must work in the following cases:
// list2 = list1 -> general case
// list2 = list2 -> should do nothing

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& ll) {
	if (this != &ll) {
		DeleteList();  // comment this out to get almost working LL tests
		CopyList(ll);
	}
	return *this;
}
//

#endif