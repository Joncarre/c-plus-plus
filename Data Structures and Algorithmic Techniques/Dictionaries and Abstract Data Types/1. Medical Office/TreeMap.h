/**
  @file TreeMap.h

  Dynamic implementation of the Dictionary ADT using
  search trees.

  Data Structures and Algorithms
  Faculty of Informatics
  Complutense University of Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/
#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "Exceptions.h"

#include "Stack.h" // Usado internamente por los iteradores

/**
 Dynamic implementation of the Dictionary ADT using 
 search trees (not self-balancing).

 Operations are:

 - TreeMapVacio: generator operation that builds
 an empty search tree.

 - Insert(key, value): generator that adds a 
 new pair (key, value) to the tree. If the
 key already existed, the value is replaced.

 - erase(key): modifier operation. Removes the
 key from the search tree. If the key is not present,
 the operation has no effect.

 - at(key): observer operation that returns
 the value associated with a key. It is an error to ask
 for a key that does not exist.

 - contains(key): observer operation. Used to
 find out if a key has been inserted into the
 tree.

 - empty(): observer operation that indicates if
 the search tree has any keys inserted.

 @author Marco Antonio Gómez Martín
 */
template <class Clave, class Valor>
class TreeMap {
private:
	/**
	 Node class that internally stores the pair (key, value)
	 and pointers to the left and right children.
	 */
	class Nodo {
	public:
		Nodo() : _iz(NULL), _dr(NULL) {}
		Nodo(const Clave &clave, const Valor &valor) 
			: _clave(clave), _valor(valor), _iz(NULL), _dr(NULL) {}
		Nodo(Nodo *iz, const Clave &clave, const Valor &valor, Nodo *dr)
			: _clave(clave), _valor(valor), _iz(iz), _dr(dr) {}

		Clave _clave;
		Valor _valor;
		Nodo *_iz;
		Nodo *_dr;
	};

public:

	/** Constructor; EmptyTreeMap operation */
	TreeMap() : _ra(NULL) {
	}

	/** Destructor; removes the hierarchical node structure. */
	~TreeMap() {
		libera();
		_ra = NULL;
	}

	/**
	 Generator operation that adds a new key/value
	 to a search tree.
	 @param clave New key.
	 @param valor Value associated with that key. If the key
	 had already been inserted previously, we replace the
	 old value with the new one.
	 */
	void insert(const Clave &clave, const Valor &valor) {
		_ra = insertaAux(clave, valor, _ra);
	}

	/**
	 Modifier operation that removes a key from the tree.
	 If the key did not exist, the operation has no effect.

	   erase(elem, EmptyTreeMap) = TreeMapVacio
	   erase(e, insert(c, v, arbol)) = 
	                     inserta(c, v, erase(e, arbol)) if c != e
	   erase(e, insert(c, v, arbol)) = erase(e, arbol) if c == e

	 @param clave Key to remove.
	 */
	void erase(const Clave &clave) {
		_ra = borraAux(_ra, clave);
	}

	/**
	 Observer operation that returns the value associated
	 with a given key.

	 at(e, insert(c, v, arbol)) = v if e == c
	 at(e, insert(c, v, arbol)) = at(e, arbol) if e != c
	 error at(EmptyTreeMap)

	 @param clave Key being queried.
	 */
	const Valor &at(const Clave &clave) const {
		Nodo *p = buscaAux(_ra, clave);
		if (p == NULL)
			throw EClaveErronea();

		return p->_valor;
	}

	/**
	 Observer operation that allows finding out if a specific
	 key is present in the search tree.

	 contains(e, EmptyTreeMap) = false
	 contains(e, insert(c, v, arbol)) = true if e == c
	 contains(e, insert(c, v, arbol)) = contains(e, arbol) if e != c

	 @param clave Key being queried.
	 @return true if the dictionary contains a value associated
	 with that key.
	 */
	bool contains(const Clave &clave) const {
		return (buscaAux(_ra, clave) != NULL) ? true : false;
	}

	/**
	 Observer operation that returns whether the tree
	 is empty (contains no elements) or not.

	 empty(EmptyTreeMap) = true
	 empty(insert(c, v, arbol)) = false
	 */
	bool empty() const {
		return _ra == NULL;
	}

	/**
	 Overload of the [] operator that allows accessing
	 the value associated with a key and modifying it.
	 If the searched element was not present, one is inserted
	 with the default value of the Valor type.
	 */
	Valor &operator[](const Clave &clave) {
		// Search. It would be better to do it in-line; thus
		// if not found, there is no need to search again
		// where to insert the key.
		Nodo * ret = buscaAux(_ra, clave);
		if (ret == NULL) {
			// Not present, add it and see where
			// it ended up. There are more efficient ways to avoid
			// tree traversals.
			insert(clave, Valor());
			ret = buscaAux(_ra, clave);
		}

		return ret->_valor;
	}

	// //
	// CONSTANT ITERATOR AND RELATED FUNCTIONS
	// //

	/**
	 Internal class that implements an iterator over
	 the list that allows traversing the tree but does not
	 allow modifying it.
	 */
	class ConstIterator {
	public:
		void next() {
			if (_act == NULL) throw InvalidAccessException();

			// If there is a right child, jump to the first
			// in-order element of the right child
			if (_act->_dr!=NULL)
				_act = primeroInOrden(_act->_dr);
			else {
				// Otherwise, go to the first unvisited
				// ancestor. For this, consult
				// the stack; if it is already empty, there are no
				// ancestors left to visit
				if (_ascendientes.empty())
					_act = NULL;
				else {
					_act = _ascendientes.top();
					_ascendientes.pop();
				}
			}
		}

		const Clave &key() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_clave;
		}

		const Valor &value() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_valor;
		}

		bool operator==(const ConstIterator &other) const {
			return _act == other._act;
		}

		bool operator!=(const ConstIterator &other) const {
			return !(this->operator==(other));
		}

		ConstIterator &operator++() {
			next();
			return *this;
		}

		ConstIterator operator++(int) {
			ConstIterator ret(*this);
			operator++();
			return ret;
		}

	protected:
		// So that it can build objects of the
		// iterator type
		friend class TreeMap;

		ConstIterator() : _act(NULL) {}
		ConstIterator(Nodo *act) {
			_act = primeroInOrden(act);
		}

		/**
		 Finds the first in-order element of
		 the hierarchical node structure passed
		 as a parameter; it stacks its ancestors
		 to be able to "go back" when necessary.
		 @param p Pointer to the root of the substructure.
		 */
		Nodo *primeroInOrden(Nodo *p) {
			if (p == NULL)
				return NULL;

			while (p->_iz != NULL) {
				_ascendientes.push(p);
				p = p->_iz;
			}
			return p;
		}

		// Pointer to the current node of the traversal
		// NULL if we have reached the end.
		Nodo *_act;

		// Ancestors of the current node
		// yet to be visited
		Stack<Nodo*> _ascendientes;
	};
	
	/**
	 Returns the constant iterator to the beginning of the
	 dictionary (smallest key).
	 @return iterator to the beginning of the traversal;
	 will coincide with cend() if the dictionary is empty.
	 */
	ConstIterator cbegin() const {
		return ConstIterator(_ra);
	}

	/**
	 @return Returns an iterator to the end of the traversal
	 (outside of it).
	 */
	ConstIterator cend() const {
		return ConstIterator(NULL);
	}

	ConstIterator find(const Clave &c) const {
		Stack<Nodo*> ascendientes;
		Nodo *p = _ra;
		while ((p != NULL) && (p->_clave != c)) {
			if (p->_clave > c) {
				ascendientes.push(p);
				p = p->_iz;
			} else
				p = p->_dr;
		}
		ConstIterator ret;
		ret._act = p;
		if (p != NULL)
			ret._ascendientes = ascendientes;
		return ret;
	}

	// //
	// NON-CONSTANT ITERATOR AND RELATED FUNCTIONS
	// //

	/**
	 Internal class that implements an iterator over
	 the search tree that allows traversing the list and even
	 altering the value of its elements.
	 */
	class Iterator {
	public:
		void next() {
			if (_act == NULL) throw InvalidAccessException();

			// If there is a right child, jump to the first
			// in-order element of the right child
			if (_act->_dr!=NULL)
				_act = primeroInOrden(_act->_dr);
			else {
				// Otherwise, go to the first unvisited
				// ancestor. For this, consult
				// the stack; if it is already empty, there are no
				// ancestors left to visit
				if (_ascendientes.empty())
					_act = NULL;
				else {
					_act = _ascendientes.top();
					_ascendientes.pop();
				}
			}
		}

		const Clave &key() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_clave;
		}

		Valor &value() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_valor;
		}

		bool operator==(const Iterator &other) const {
			return _act == other._act;
		}

		bool operator!=(const Iterator &other) const {
			return !(this->operator==(other));
		}

		Iterator &operator++() {
			next();
			return *this;
		}

		Iterator operator++(int) {
			Iterator ret(*this);
			operator++();
			return ret;
		}

	protected:
		// So that it can build objects of the
		// iterator type
		friend class TreeMap;

		Iterator() : _act(NULL) {}
		Iterator(Nodo *act) {
			_act = primeroInOrden(act);
		}

		/**
		 Finds the first in-order element of
		 the hierarchical node structure passed
		 as a parameter; it stacks its ancestors
		 to be able to "go back" when necessary.
		 @param p Pointer to the root of the substructure.
		 */
		Nodo *primeroInOrden(Nodo *p) {
			if (p == NULL)
				return NULL;

			while (p->_iz != NULL) {
				_ascendientes.push(p);
				p = p->_iz;
			}
			return p;
		}

		// Pointer to the current node of the traversal
		// NULL if we have reached the end.
		Nodo *_act;

		// Ancestors of the current node
		// yet to be visited
		Stack<Nodo*> _ascendientes;
	};
	
	/**
	 Returns the iterator to the beginning of the list.
	 @return iterator to the beginning of the list;
	 will coincide with end() if the list is empty.
	 */
	Iterator begin() {
		return Iterator(_ra);
	}

	/**
	 @return Returns an iterator to the end of the traversal
	 (outside of it).
	 */
	Iterator end() const {
		return Iterator(NULL);
	}

	Iterator find(const Clave &c) {
		Stack<Nodo*> ascendientes;
		Nodo *p = _ra;
		while ((p != NULL) && (p->_clave != c)) {
			if (p->_clave > c) {
				ascendientes.push(p);
				p = p->_iz;
			} else
				p = p->_dr;
		}
		Iterator ret;
		ret._act = p;
		if (p != NULL)
			ret._ascendientes = ascendientes;
		return ret;
	}


	// //
	// C++ "PLUMBING" METHODS THAT MAKE THE CLASS
	// VERSATILE
	// //

	/** Copy constructor */
	TreeMap(const TreeMap<Clave, Valor> &other) : _ra(NULL) {
		copia(other);
	}

	/** Assignment operator */
	TreeMap<Clave, Valor> &operator=(const TreeMap<Clave, Valor> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

protected:

	/**
	 Protected constructor that creates a tree
	 from a previously created hierarchical node
	 structure.
	 Used in hijoIz and hijoDr.
	 */
	TreeMap(Nodo *raiz) : _ra(raiz) {
	}

	void libera() {
		libera(_ra);
	}

	void copia(const TreeMap &other) {
		_ra = copiaAux(other._ra);
	}

private:

	/**
	 Removes all nodes of a tree structure
	 starting with the pointer ra.
	 It is allowed for the node to be NULL (there will be nothing
	 to free).
	 */
	static void libera(Nodo *ra) {
		if (ra != NULL) {
			libera(ra->_iz);
			libera(ra->_dr);
			delete ra;
		}
	}

	/**
	 Copies the hierarchical node structure passed
	 as a parameter (pointer to its root) and returns a
	 pointer to a new hierarchical structure, a copy
	 of the previous one (and which, therefore, must be freed).
	 */
	static Nodo *copiaAux(Nodo *ra) {
		if (ra == NULL)
			return NULL;

		return new Nodo(copiaAux(ra->_iz),
						ra->_clave, ra->_valor,
						copiaAux(ra->_dr));
	}

	/**
	 Inserts a pair (key, value) into the hierarchical
	 structure starting at the pointer passed as a parameter.
	 This pointer is allowed to be NULL, in which case a
	 new node will be created which will become the new root of that
	 hierarchical structure. The method returns a pointer to the
	 root of the modified structure. Under normal conditions
	 it will coincide with the received parameter; it will only change if
	 the structure was empty.
	 @param clave Key to insert. If it already appeared in the
	 node structure, the value is overwritten.
	 @param valor Value to insert.
	 @param p Pointer to the root node where to insert the pair.
	 @return New root (or p if it doesn't change).
	 */
	static Nodo *insertaAux(const Clave &clave, const Valor &valor, Nodo *p) {

		if (p == NULL) {
			return new Nodo(clave, valor);
		} else if (p->_clave == clave) {
			p->_valor = valor;
			return p;
		} else if (clave < p->_clave) {
			p->_iz = insertaAux(clave, valor, p->_iz);
			return p;
		} else { // (clave > p->_clave)
			p->_dr = insertaAux(clave, valor, p->_dr);
			return p;
		}
	}

	/**
	 Searches for a key in the hierarchical node
	 structure whose root is passed as a parameter, and returns
	 the node where it is found (or NULL if not present).
	 @param p Pointer to the root of the node structure
	 @param clave Key to search for
	 */
	static Nodo *buscaAux(Nodo *p, const Clave &clave) {
		if (p == NULL)
			return NULL;

		if (p->_clave == clave)
			return p;

		if (clave < p->_clave)
			return buscaAux(p->_iz, clave);
		else
			return buscaAux(p->_dr, clave);
	}

	/**
	 Removes (if it exists) the key/value from the hierarchical
	 node structure pointed to by p. If the key appeared at the root itself,
	 it will change, so the new root is returned. If it doesn't change,
	 p itself is returned.

	 @param p Root of the hierarchical structure where to delete the key.
	 @param clave Key to delete.
	 @return New root of the structure, after deletion. If the root
	 does not change, p itself is returned.
	 */
	static Nodo *borraAux(Nodo *p, const Clave &clave) {

		if (p == NULL)
			return NULL;

		if (clave == p->_clave) {
			return borraRaiz(p);
		} else if (clave < p->_clave) {
			p->_iz = borraAux(p->_iz, clave);
			return p;
		} else { // clave > p->_clave
			p->_dr = borraAux(p->_dr, clave);
			return p;
		}
	}

	/**
	 Deletes the root of the hierarchical node structure
	 and returns the pointer to the new root that guarantees
	 that the structure remains valid for a search tree
	 (ordered keys).
	 */
	static Nodo *borraRaiz(Nodo *p) {

		Nodo *aux;

		// If there is no left child, the root becomes
		// the right child
		if (p->_iz == NULL) {
			aux = p->_dr;
			delete p;
			return aux;
		} else
		// If there is no right child, the root becomes
		// the left child
		if (p->_dr == NULL) {
			aux = p->_iz;
			delete p;
			return aux;
		} else {
		// Convert the smallest element of the right child
		// into the root.
			return mueveMinYBorra(p);
		}
	}

	/**
	 Auxiliary method for deletion; receives a pointer to the
	 root to be deleted. Searches for the smallest element of the right child
	 which will become the root (which it will return), deletes the old
	 root (p) and "stitches" all the pointers, so that now:

	   - The minimum becomes the root, whose left and
	     right children were the left and right children of the old
	     root.
	   - The left child of the parent of the smallest element
	     becomes the old right child of that minimum.
	 */
	static Nodo *mueveMinYBorra(Nodo *p) {

		// Go down until we find the smallest element
		// (the one with no left child).
		// Also keep track of the parent (which will be null
		// if the right child is directly the smallest
		// element).
		Nodo *padre = NULL;
		Nodo *aux = p->_dr;
		while (aux->_iz != NULL) {
			padre = aux;
			aux = aux->_iz;
		}

		// aux points to the smallest element.
		// padre points to its parent (if the node is a left child)

		// Two cases depending on whether the parent of the node with
		// the minimum is or is not the root to be deleted
		// (=> padre != NULL)
		if (padre != NULL) {
			padre->_iz = aux->_dr;
			aux->_iz = p->_iz;
			aux->_dr = p->_dr;
		} else {
			aux->_iz = p->_iz;
		}

		delete p;
		return aux;
	}

	/** 
	 Pointer to the root of the hierarchical node
	 structure.
	 */
	Nodo *_ra;
};

#endif // __TREEMAP_H
