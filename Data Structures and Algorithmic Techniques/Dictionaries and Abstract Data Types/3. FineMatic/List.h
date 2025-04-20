/**
  @file Lista.h

  Implementation of the List ADT, using a 
  doubly linked list.

  Data Structures and Algorithms
  Faculty of Informatics
  Complutense University of Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/

/**
 Implementation of the List ADT using a doubly linked list.

 Operations are:

 - EmptyList: -> List. Generator implemented in the
   constructor without parameters.
 - Push_front: List, Elem -> List. Generator.
 - push_back: List, Elem -> List. Modifier.
 - front: List - -> Elem. Partial observer
 - pop_front: List - -> List. Partial modifier
 - back: List - -> Elem. Partial observer
 - pop_back: List - -> List. Partial modifier
 - empty: List -> Bool. Observer
 - size: List -> Integer. Observer.
 - at: List, Integer - -> Elem. Partial observer.

 @author Marco Antonio Gómez Martín
 */
template <class T>
class List {
private:
	/**
	 Node class that internally stores the element (of type T),
	 and two pointers, one to the previous node and one to the next node.
	 Both pointers could be NULL if the node is the first
	 and/or last of the linked list.
	 */
	class Nodo {
	public:
		/** Constructor; receives the element and links to the next and
		 previous nodes. */
		Nodo(const T &elem, Nodo *sig, Nodo *ant) :
			_elem(elem), _sig(sig), _ant(ant) {
		}

		/** Element stored in the node. */
		T _elem;

		/** Pointer to the next node in the list. */
		Nodo *_sig;

		/** Pointer to the previous node in the list. */
		Nodo *_ant;
	};

	/** Constructor; EmptyList operation. */
	List() : _prim(NULL), _ult(NULL), _numElems(0) {}

	/** Destructor; removes the doubly linked list. */
	~List() {
		libera();
	}

	/**
	 Adds a new element at the head of the list.
	 Generator operation.

	 @param elem Element to be added at the head of
	 the list.
	*/
	void push_front(const T &elem) {
		_prim = new Nodo(elem, _prim, NULL);
		if (_prim->_sig != NULL)
			_prim->_sig->_ant = _prim;
		else
			_ult = _prim;
		_numElems++;
	}

	/**
	 Adds a new element at the end of the list (to the 
	 "right"). Modifier operation.

	 push_back(e, EmptyList) = Cons(e, EmptyList)
	 push_back(e, Push_front(x, xs)) = Push_front(x, push_back(e, xs))
	*/
	void push_back(const T &elem) {
		_ult = new Nodo(elem, NULL, _ult);
		if (_ult->_ant != NULL)
			_ult->_ant->_sig = _ult;
		else
			_prim = _ult;
		_numElems++;
	}

	/**
	 Returns the value stored at the head of the
	 list. It is an error to ask for the first element of
	 an empty list.

	 front(Push_front(x, xs)) = x
	 error front(EmptyList)

	 @return Element at the head of the list.
	 */
	const T &front() const {
		if (_prim == NULL) throw InvalidAccessException();
		return _prim->_elem;
	}

	/**
	 Returns the value stored at the last position
	 of the list (to the right).
	 It is an error to ask for the first element of an empty list.

	 back(Push_front(x, xs)) = x           IF empty(xs)
	 back(Push_front(x, xs)) = back(xs)  IF !empty(xs)
	 error back(EmptyList)

	 @return Element at the tail of the list.
	 */
	const T &back() const {
		if (_ult == NULL) throw InvalidAccessException();
		return _ult->_elem;
	}

	/**
	 Removes the first element of the list.
	 It is an error to try to get the rest of an empty list.

	 pop_front(Push_front(x, xs)) = xs
	 error pop_front(EmptyList)
	*/
	void pop_front() {
		if (_prim == NULL) throw InvalidAccessException();
		Nodo *aBorrar = _prim;
		_prim = _prim->_sig;
		delete aBorrar;
		if (_prim != NULL) _prim->_ant = NULL;
		else _ult = NULL;
		_numElems--;
	}

	/**
	 Removes the last element of the list.
	 It is an error to try to get the beginning of an empty list.

	 inicio(Push_front(x, EmptyList)) = EmptyList
	 inicio(Push_front(x, xs)) = Push_front(x, inicio(xs)) IF !empty(xs)
	 error inicio(EmptyList)
	*/
	void pop_back() {
		if (_ult == NULL) throw InvalidAccessException();
		Nodo *aBorrar = _ult;
		_ult = _ult->_ant;
		delete aBorrar;
		if (_ult != NULL) _ult->_sig = NULL;
		else _prim = NULL;
		_numElems--;
	}

	/**
	 Observer operation to check if a list
	 has elements or not.

	 empty(EmptyList) = true
	 empty(Push_front(x, xs)) = false

	 @return true if the list has no elements.
	 */
	bool empty() const {
		return _prim == NULL;
	}

	/**
	 Returns the number of elements in the
	 list.
	 size(EmptyList) = 0
	 size(Push_front(x, xs)) = 1 + size(xs)

	 @return Number of elements.
	 */
	unsigned int size() const {
		return _numElems;
	}

	/**
	 Returns the i-th element of the list, considering
	 that the first element (first())
	 is element 0 and the last is size()-1,
	 i.e., idx is in [0..size()-1].
	 Partial observer operation that can fail
	 if an incorrect index is given. The index is
	 an unsigned integer to prevent requesting
	 negative elements.

	 elem(0, Push_front(x, xs)) = x
	 elem(n, Push_front(x, xs)) = elem(n-1, xs) if n > 0
	 error elem(n, xs) if !( 0 <= n < size(xs) )
	*/
	const T &at(unsigned int idx) const {
		if (idx >= _numElems) throw InvalidAccessException();
		Nodo *act = _prim;
		for (unsigned int i = 0; i < idx; i++)
			act = act->_sig;
		return act->_elem;
	}

	/**
	 Internal class that implements an iterator over
	 the list that allows traversing the list but does not
	 allow changing them.
	 */
	class ConstIterator {
	public:

		/** Advances the iterator to the next element. */
		const ConstIterator &operator++() {
			if (_act == NULL) throw InvalidAccessException();
			_act = _act->_sig;
			return *this;
		}

		/** Moves the iterator to the previous element. */
		const ConstIterator &operator--() {
			if (_act == NULL) throw InvalidAccessException();
			_act = _act->_ant;
			return *this;
		}

		/** Comparison operator. */
		bool operator==(const ConstIterator &rhs) const {
			return _act == rhs._act;
		}

		/** Comparison operator. */
		bool operator!=(const ConstIterator &rhs) const {
			return _act != rhs._act;
		}

		/** Constant dereferencing operator. */
		const T& operator*() const {
			// Code identical to elem() because it is const,
			// so it cannot be used from here.
			if (_act == NULL) throw InvalidAccessException();
			return _act->_elem;
		}

	protected:
		// So that it can build objects of the
		// iterator type
		friend class List;

		ConstIterator() : _act(NULL) {}
		ConstIterator(Nodo *act) : _act(act) {}

		// Pointer to the current node of the traversal
		Nodo *_act;
	};

	/**
	 Internal class that implements an iterator over
	 the list that allows traversing the list and even
	 altering the value of its elements.
	 */
	class Iterator : public ConstIterator {
	public:

		/** Advances the iterator to the next element. */
		const Iterator &operator++() {
			if (_act == NULL) throw InvalidAccessException();
			_act = _act->_sig;
			return *this;
		}

		/** Moves the iterator to the previous element. */
		const Iterator &operator--() {
			if (_act == NULL) throw InvalidAccessException();
			_act = _act->_ant;
			return *this;
		}

		/** Comparison operator. */
		bool operator==(const Iterator &rhs) const {
			return _act == rhs._act;
		}

		/** Comparison operator. */
		bool operator!=(const Iterator &rhs) const {
			return _act != rhs._act;
		}

		/** Non-constant dereferencing operator. */
		T& operator*() {
			// Code identical to elem() because it is const,
			// so it cannot be used from here.
			if (_act == NULL) throw InvalidAccessException();
			return _act->_elem;
		}

	protected:
		// So that it can build objects of the
		// iterator type
		friend class List;

		Iterator() : _act(NULL) {}
		Iterator(Nodo *act) : _act(act) {}

		// Pointer to the current node of the traversal
		Nodo *_act;
	};

	/**
	 Returns the constant iterator to the beginning of the list.
	 @return iterator to the beginning of the list;
	 will coincide with cend() if the list is empty.
	 */
	ConstIterator cbegin() const {
		return ConstIterator(_prim);
	}

	/**
	 @return Returns a constant iterator to the end of the traversal
	 (outside of it).
	 */
	ConstIterator cend() const {
		return ConstIterator(NULL);
	}

	/**
	 Returns the non-constant iterator to the beginning of the list.
	 @return iterator to the beginning of the list;
	 will coincide with end() if the list is empty.
	 */
	Iterator begin() {
		return Iterator(_prim);
	}

	/**
	 @return Returns a non-constant iterator to the end of the traversal
	 (outside of it).
	 */
	Iterator end() const {
		return Iterator(NULL);
	}


	/**
	 Allows removing the element pointed to by the
	 iterator passed as a parameter from the list.
	 The received iterator BECOMES INVALID. Instead,
	 the returned iterator should be used, which will
	 point to the element following the deleted one.
	 @param it Iterator positioned at the element to be
	 deleted.
	 @return New iterator positioned at the element following
	 the deleted one (could coincide with final() if the
	 deleted element was the last in the list).
	 */
	Iterator erase(const Iterator &it) {
		if (it._act == NULL)
			throw InvalidAccessException("Cannot erase specified element. Iterator pointing to NULL");

		// Cover special cases where
		// we delete one of the ends
		if (it._act == _prim) {
			pop_front();
			return Iterator(_prim);
		} else if (it._act == _ult) {
			pop_back();
			return Iterator(NULL);
		} else {
			// The element to be deleted is internal to the list.
			Nodo *sig = it._act->_sig;
			borraElem(it._act);
			return Iterator(sig);
		}
	}

	/**
	 Method to insert an element into the list
	 at the point marked by the iterator. Specifically,
	 it is added _just before_ the current element. That
	 is, if it==l.primero(), the inserted element
	 becomes the first element (and the iterator
	 will point to the second). If it==l.final(), the inserted
	 element will be the last (and it will still point
	 outside the traversal).
	 @param elem Value of the element to insert.
	 @param it Point at which to insert the element.
	 */
	void insert(const T &elem, const Iterator &it) {

		// Special case: add at the beginning?
		if (_prim == it._act) {
			push_front(elem);
		} else
		// Special case: add at the end?
		if (it._act == NULL) {
			push_back(elem);
		}
		// Normal case
		else {
			insertaElem(elem, it._act->_ant, it._act);
		}
	}

	// //
	// C++ "PLUMBING" METHODS THAT MAKE THE CLASS
	// VERSATILE
	// //

	/** Copy constructor */
	List(const List<T> &other) : _prim(NULL), _ult(NULL) {
		copia(other);
	}

	/** Assignment operator */
	List<T> &operator=(const List<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Comparison operator. */
	bool operator==(const List<T> &rhs) const {
		if (_numElems != rhs._numElems) return false;
		Nodo *p1 = _prim, *p2 = rhs._prim;
		while (p1 != NULL) {
			if (p1->_elem != p2->_elem) return false;
			p1 = p1->_sig;
			p2 = p2->_sig;
		}
		return true;
	}

protected:

	/**
	 Deletes all nodes of the linked list whose
	 first node is passed as a parameter.
	 It is allowed for the node to be NULL (there will be nothing
	 to free). If a valid node is passed,
	 its pointer to the previous node must be NULL (otherwise,
	 it would not be the first in the list!).
	 */
	static void libera(Nodo *prim) {
		while (prim != NULL) {
			Nodo *sig = prim->_sig;
			delete prim;
			prim = sig;
		}
	}

	/**
	 Inserts an element between node1 and node2.
	 Returns the pointer to the created node.
	 General case: both nodes exist.
	    node1->_sig == nodo2
	    node2->_ant == nodo1
	 Special cases: one of the nodes does not exist
	    node1 == NULL and/or node2 == NULL
	*/
	Nodo *insertaElem(const T &e, Nodo *nodo1, Nodo *nodo2) {
		Nodo *nuevo = new Nodo(e, nodo2, nodo1);
		nodo1->_sig = nuevo;
		nodo2->_ant = nuevo;
		_numElems++;
		return nuevo;
	}

	/**
	 Deletes node n. If the node has nodes before
	 or after, updates their previous and next pointers.
	 General case: there are previous and next nodes.
	 Special cases: some of the nodes (previous or next
	 to n) do not exist.
	*/
	void borraElem(Nodo *n) {
		if (n == _prim) pop_front();
		else if (n == _ult) pop_back();
		else {
			n->_ant->_sig = n->_sig;
			n->_sig->_ant = n->_ant;
			delete n;
			_numElems--;
		}
	}

	/**
	 Copies the content of the other list into this one.
	 @param other List to copy.
	 */
	void copia(const List<T> &other) {
		// Instead of working with pointers during insertion,
		// we use ponDr
		_prim = 0;
		_numElems = 0;

		Nodo *act = other._prim;
		while (act != NULL) {
			push_back(act->_elem);
			act = act->_sig;
		}
	}

private:


	// Pointer to the first and last element
	Nodo *_prim, *_ult;

	// Number of elements (number of nodes between _prim and _ult)
	unsigned int _numElems;
};