/**
  @file Arbin.h

  Dynamic Implementation of the Binary Tree ADT.

  Data Structures and Algorithms
  Faculty of Computer Science
  Complutense University of Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/
#ifndef __ARBIN_H
#define __ARBIN_H

#include "Excepciones.h"

#include "Lista.h" // Type returned by tree traversals

#include "Cola.h" // Auxiliary type for implementing level-order traversal

/**
 Dynamic implementation of the Binary Tree ADT using
 nodes with pointers to left and right children. The
 implementation allows structure sharing, keeping it
 under control through reference counting. However,
 the implementation is quite artisanal, as smart pointers
 that automatically increment and decrement these
 references have not been used to avoid complicating
 the code excessively.

 The operations are:

 - EmptyTree: -> Arbin. Generator implemented in the
   parameterless constructor.
 - Cons: Arbin, Elem, Arbin -> Arbin. Generator implemented
   in a constructor with three parameters.
 - leftChild, rightChild: Arbin -> Arbin. Observers that
   return the left or right child of a tree.
 - isEmpty: Arbin -> Bool. Observer that returns whether
   a binary tree is empty.

 @author Marco Antonio Gómez Martín
 */
template <class T>
class Arbin {
public:

	/** Constructor; EmptyTree operation */
	Arbin() : _ra(NULL) {
	}

	/** Constructor; Cons operation */
	Arbin(const Arbin &iz, const T &elem, const Arbin &dr) :
		_ra(new Nodo(iz._ra, elem, dr._ra)) {
		_ra->addRef();
	}

	/** Destructor; eliminates the hierarchical structure of nodes. */
	~Arbin() {
		libera();
		_ra = NULL;
	}

	/**
	 Returns the element stored at the root

	 root(Cons(left, elem, right)) = elem
	 error root(EmptyTree)
	 @return Element at the root.
	 */
	const T &raiz() const {
		if (esVacio())
			throw EArbolVacio();
		return _ra->_elem;
	}

	/**
	 Returns a copy of the left subtree.
	 It's a partial operation (fails with an empty tree).

	 leftChild(Cons(left, elem, right)) = left
	 error leftChild(EmptyTree)
	*/
	Arbin hijoIz() const {
		if (esVacio())
			throw EArbolVacio();

		return Arbin(_ra->_iz);
	}

	/**
	 Returns a copy of the right subtree.
	 It's a partial operation (fails with an empty tree).

	 rightChild(Cons(left, elem, right)) = right
	 error rightChild(EmptyTree)
	*/
	Arbin hijoDr() const {
		if (esVacio())
			throw EArbolVacio();

		return Arbin(_ra->_dr);
	}

	/**
	 Observer operation that returns whether the tree
	 is empty (contains no elements) or not.

	 isEmpty(EmptyTree) = true
	 isEmpty(Cons(left, elem, right)) = false
	 */
	bool esVacio() const {
		return _ra == NULL;
	}

	// //
	// TRAVERSALS ON THE TREE
	// //

	Lista<T> preorden() const {
		Lista<T> ret;
		preordenAcu(_ra, ret);
		return ret;
	}

	Lista<T> inorden() const {
		Lista<T> ret;
		inordenAcu(_ra, ret);
		return ret;
	}

	Lista<T> postorden() const {
		Lista<T> ret;
		postordenAcu(_ra, ret);
		return ret;
	}

	Lista<T> niveles() const {

		if (esVacio())
			return Lista<T>();

		Lista<T> ret;
		Cola<Nodo*> porProcesar;
		porProcesar.ponDetras(_ra);

		while (!porProcesar.esVacia()) {
			Nodo *visita = porProcesar.primero();
			porProcesar.quitaPrim();
			ret.ponDr(visita->_elem);
			if (visita->_iz)
				porProcesar.ponDetras(visita->_iz);
			if (visita->_dr)
				porProcesar.ponDetras(visita->_dr);
		}

		return ret;
	}

	// //
	// OTHER OBSERVER OPERATIONS
	// //

	/**
	 Returns the number of nodes in a tree.
	 */
	unsigned int numNodos() const {
		return numNodosAux(_ra);
	}

	/**
	 Returns the height of the tree.
	 */
	unsigned int talla() const {
		return tallaAux(_ra);
	}

	/**
	 Returns the number of leaves in a tree.
	 */
	unsigned int numHojas() const {
		return numHojasAux(_ra);
	}

	// //
	// C++ "PLUMBING" METHODS THAT MAKE THE CLASS VERSATILE
	// //

	/** Copy constructor */
	Arbin(const Arbin<T> &other) : _ra(NULL) {
		copia(other);
	}

	/** Assignment operator */
	Arbin<T> &operator=(const Arbin<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Comparison operator. */
	bool operator==(const Arbin<T> &rhs) const {
		return comparaAux(_ra, rhs._ra);
	}

	bool operator!=(const Arbin<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	/**
	 Node class that internally stores the element (of type T),
	 pointers to the left and right children, as well as
	 the number of references.
	 */
	class Nodo {
	public:
		Nodo() : _iz(NULL), _dr(NULL), _numRefs(0) {}
		Nodo(Nodo *iz, const T &elem, Nodo *dr) : 
			_elem(elem), _iz(iz), _dr(dr), _numRefs(0) {
			if (_iz != NULL)
				_iz->addRef();
			if (_dr != NULL)
				_dr->addRef();
		}

		void addRef() { assert(_numRefs >= 0); _numRefs++; }
		void remRef() { assert(_numRefs > 0); _numRefs--; }

		T _elem;
		Nodo *_iz;
		Nodo *_dr;

		int _numRefs;
	};

	/**
	 Protected constructor that creates a tree
	 from an existing hierarchical structure.
	 That hierarchical structure is SHARED, so
	 the reference is added.
	 It is used in leftChild and rightChild.
	 */
	Arbin(Nodo *raiz) : _ra(raiz) {
		if (_ra != NULL)
			_ra->addRef();
	}

	void libera() {
		libera(_ra);
	}

	void copia(const Arbin &other) {
		assert(this != &other);
		_ra = other._ra;
		if (_ra != NULL)
			_ra->addRef();
	}

	// //
	// AUXILIARY METHODS FOR TRAVERSALS
	// //
	
	static void preordenAcu(Nodo *ra, Lista<T> &acu) {
		if (ra == NULL)
			return;

		acu.ponDr(ra->_elem);
		preordenAcu(ra->_iz, acu);
		preordenAcu(ra->_dr, acu);
	}

	static void inordenAcu(Nodo *ra, Lista<T> &acu) {
		if (ra == NULL)
			return;

		inordenAcu(ra->_iz, acu);
		acu.ponDr(ra->_elem);
		inordenAcu(ra->_dr, acu);
	}

	static void postordenAcu(Nodo *ra, Lista<T> &acu) {
		if (ra == NULL)
			return;

		postordenAcu(ra->_iz, acu);
		postordenAcu(ra->_dr, acu);
		acu.ponDr(ra->_elem);
	}

	// //
	// AUXILIARY (RECURSIVE) METHODS FOR OTHER OBSERVER OPERATIONS
	// //

	static unsigned int numNodosAux(Nodo *ra) {
		if (ra == NULL)
			return 0;
		return 1 + numNodosAux(ra->_iz) + numNodosAux(ra->_dr);
	}

	static unsigned int tallaAux(Nodo *ra) {
		if (ra == NULL)
			return 0;

		int tallaiz = tallaAux(ra->_iz);
		int talladr = tallaAux(ra->_dr);
		if (tallaiz > talladr)
			return 1 + tallaiz;
		else
			return 1 + talladr;
	}

	static unsigned int numHojasAux(Nodo *ra) {
		if (ra == NULL)
			return 0;

		if ((ra->_iz == NULL) && (ra->_dr == NULL))
			return 1;

		return numHojasAux(ra->_iz) + numHojasAux(ra->_dr);
	}

private:

	/**
	 Deletes all nodes of a tree structure
	 that begins with the pointer ra.
	 The node can be NULL (there will be nothing to free).
	 */
	static void libera(Nodo *ra) {
		if (ra != NULL) {
			ra->remRef();
			if (ra->_numRefs == 0) {
				libera(ra->_iz);
				libera(ra->_dr);
				delete ra;
			}
		}
	}

	/**
	 Compares two hierarchical node structures,
	 given their roots (which can be NULL).
	 */
	static bool comparaAux(Nodo *r1, Nodo *r2) {
		if (r1 == r2)
			return true;
		else if ((r1 == NULL) || (r2 == NULL))
			// In the previous if we ensure that
			// r1 != r2. If one is NULL, the
			// other will not be, so they are different.
			return false;
		else {
			return (r1->_elem == r2->_elem) &&
				comparaAux(r1->_iz, r2->_iz) &&
				comparaAux(r1->_dr, r2->_dr);
		}
	}

protected:
	/** 
	 Pointer to the root of the hierarchical structure
	 of nodes.
	 */
	Nodo *_ra;
};

#endif // __ARBIN_H
