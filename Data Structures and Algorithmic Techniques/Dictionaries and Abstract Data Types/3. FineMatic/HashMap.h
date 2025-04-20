/**
  @file HashMap.h

  Dynamic implementation of the Dictionary ADT using
  search tables

  Data Structures and Algorithms
  Faculty of Informatics
  Complutense University of Madrid

 (c) Antonio Sánchez Ruiz-Granados, 2012
 */
#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "Exceptions.h"

// funciones de hash a usar
#include "Hash.h"

/**
 * Dynamic implementation of the Dictionary ADT using 
 * an open hash table
 * 
 * Operations are:
 * 
 * - HashMapVacio: generator operation that builds
 * an empty hash table
 * 
 * - Insert(key, value): generator that adds a 
 * new pair (key, value) to the table. If the
 * key already existed, the value is replaced.
 * 
 * - erase(key): modifier operation. Removes the
 * key from the table. If the key is not present,
 * the operation has no effect.
 * 
 * - at(key): observer operation that returns
 * the value associated with a key. It is an error to ask
 * for a key that does not exist.
 * 
 * - contains(key): observer operation. Used to
 * find out if a key is present in the table.
 * 
 * - empty(): observer operation that indicates if
 * the table has any keys inserted.
 * 
 * @author Antonio Sánchez Ruiz-Granados
 */
template <class Clave, class Valor>
class HashMap {
private:
	/**
	 The table contains an array of pointers to nodes. Each node contains a 
	 key, a value, and a pointer to the next node.
	 */
	class Nodo {
	public:
		/* Constructors. */
		Nodo(const Clave &clave, const Valor &valor) : 
		_clave(clave), _valor(valor), _sig(NULL) {};
		
		Nodo(const Clave &clave, const Valor &valor, Nodo *sig) : 
		_clave(clave), _valor(valor), _sig(sig) {};
		
		/* Public attributes. */
		Clave _clave;    
		Valor _valor;   
		Nodo *_sig;  // Pointer to the next node.
	};  
	
public:
	
	/**
	 Initial size of the table.
	 */
	static const int TAM_INICIAL = 8;    
	
	/** Default constructor that implements HashMapVacio */
	HashMap() : _v(new Nodo*[TAM_INICIAL]), _tam(TAM_INICIAL), _numElems(0) {
		for (unsigned int i=0; i<_tam; ++i) {
			_v[i] = NULL;
		}
	}
	
	/** Destructor; removes the linked lists */
	~HashMap() {
		libera();
	}
	
	/**
	 Generator operation that adds a new key/value
	 to this table
	 @param clave New key.
	 @param valor Value associated with that key. If the key
	 had already been inserted previously, we replace the
	 old value with the new one.
	 */
	void insert(const Clave &clave, const Valor &valor) {        
		// If the occupancy is very high, expand the table
		float ocupacion = 100 * ((float) _numElems) / _tam; 
		if (ocupacion > MAX_OCUPACION)
			amplia();
		
		// Get the index associated with the key.
		unsigned int ind = ::hash(clave) % _tam;
		
		// If the key already existed, update its value
		Nodo *nodo = buscaNodo(clave, _v[ind]);
		if (nodo != NULL) {
			nodo->_valor = valor;
		} else {            
			// If the key did not exist, create a new node and insert it
			// at the beginning
			_v[ind] = new Nodo(clave, valor, _v[ind]);
			_numElems++;
		}
	}
	
	/**
	 Modifier operation that removes a key from the table.
	 If the key did not exist, the operation has no effect.
	 * 
	 *	   erase(elem, EmptyHashMap) = HashMapVacio
	 *	   erase(e, insert(c, v, arbol)) = 
	 *	                     inserta(c, v, erase(e, arbol)) if c != e
	 *	   erase(e, insert(c, v, arbol)) = erase(e, arbol) if c == e
	 * 
	 *	 @param clave Key to remove.
	 */
	void erase(const Clave &clave) {
		// Get the index associated with the key.
		unsigned int ind = ::hash(clave) % _tam;
		
		// Search for the node containing that key and the previous node.
		Nodo *act = _v[ind];
		Nodo *ant = NULL;
		buscaNodo(clave, act, ant);
		
		if (act != NULL) {
			
			// Remove the node from the sequence of nodes.
			if (ant != NULL) {
				ant->_sig = act->_sig;
			} else {
				_v[ind] = act->_sig;
			}
			
			// Delete the extracted node.
			delete act;
			_numElems--;
		}        
	}
	
	/**
	 Observer operation that returns the value associated
	 with a given key.
	 * 
	 *	 at(e, insert(c, v, tabla)) = v if e == c
	 *	 at(e, insert(c, v, tabla)) = at(e, tabla) if e != c
	 *	 error at(EmptyHashMap)
	 * 
	 *	 @param clave Key being queried.
	 */
	const Valor &at(const Clave &clave) const {
		// Get the index associated with the key.
		unsigned int ind = ::hash(clave) % _tam;
		
		// Search for a node containing that key.
		Nodo *nodo = buscaNodo(clave, _v[ind]);
		if (nodo == NULL)
			throw EClaveErronea();
		
		return nodo->_valor;
	}
	
	/**
	 Observer operation that allows finding out if a specific
	 key is present in the hash table.
	 * 
	 *	 contains(e, EmptyHashMap) = false
	 *	 contains(e, insert(c, v, arbol)) = true if e == c
	 *	 contains(e, insert(c, v, arbol)) = contains(e, arbol) if e != c
	 * 
	 *	 @param clave Key being queried.
	 *	 @return true if the dictionary contains a value associated
	 *	 with that key.
	 */
	bool contains(const Clave &clave) const {
		// Get the index associated with the key.
		unsigned int ind = ::hash(clave) % _tam;
		
		// Search for a node containing that key.
		Nodo *nodo = buscaNodo(clave, _v[ind]);
		return nodo != NULL;
	}
	
	/**
	 Observer operation that returns whether the tree
	 is empty (contains no elements) or not.
	 * 
	 *	 empty(EmptyHashMap) = true
	 *	 empty(insert(c, v, arbol)) = false
	 */
	bool empty() const {
		return _numElems == 0;
	}
	
	/**
	 Overload of the [] operator that allows accessing
	 the value associated with a key and modifying it.
	 If the searched element was not present, one is inserted
	 with the default value of the Valor type.
	 */
	Valor &operator[](const Clave &clave) {
		// Get the index associated with the key.
		unsigned int ind = ::hash(clave) % _tam;
		
		// Search for a node containing that key.
		Nodo *nodo = buscaNodo(clave, _v[ind]);
		if (nodo == NULL) {
			// Not present, add it and see where it ended up. 
			insert(clave, Valor());
			// ind might change if insertion caused expansion!
			ind = ::hash(clave) % _tam;
			nodo = buscaNodo(clave, _v[ind]);
		}        
		return nodo->_valor;
	}
	
	// //
	// CONSTANT ITERATOR AND RELATED FUNCTIONS
	// //
	
	/**
	 Internal class that implements an iterator over
	 the list that allows traversing the table but does not
	 allow modifying it.
	 */
	class ConstIterator {
	public:
		void next() {
			if (_act == NULL) throw InvalidAccessException();
			
			// Search for the next node in the list of nodes.
			_act = _act->_sig;
			
			// If we have reached the end of the list of nodes, continue
			// searching through the vector _v.
			while ((_act == NULL) && (_ind < _tabla->_tam - 1)) {
				++_ind;
				_act = _tabla->_v[_ind];
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
		// So that it can build objects of the iterator type
		friend class HashMap;
		
		ConstIterator(const HashMap* tabla, Nodo* act, unsigned int ind) 
			: _tabla(tabla), _act(act), _ind(ind) { }
		
		const HashMap *_tabla;  ///< Table being traversed
		Nodo* _act;             ///< Pointer to the current node of the traversal
		unsigned int _ind;      ///< Current index in the vector _v
	};
	
	/**
	 Returns the constant iterator to the beginning of the
	 dictionary (smallest key).
	 @return iterator to the beginning of the traversal;
	 will coincide with cend() if the dictionary is empty.
	 */
	ConstIterator cbegin() const {
		unsigned int ind = 0;
		Nodo *act = _v[0];
		while (ind < _tam-1 && act == NULL) {
			ind++;
			act = _v[ind];
		}
		return ConstIterator(this, act, ind);
	}
	
	/**
	 @return Returns an iterator to the end of the traversal
	 (outside of it).
	 */
	ConstIterator cend() const {
		return ConstIterator(this, NULL, 0);
	}
	
	/**
	 @return Returns an iterator to the position of 
	 key, or to the end of the traversal if key not found
	 */
	ConstIterator find(const Clave &clave) const {
		// Get the index associated with the key.
		unsigned int ind = ::hash(clave) % _tam;
		
		// Search for a node containing that key.
		Nodo *nodo = buscaNodo(clave, _v[ind]);
		
		// if nodo == NULL, actually returns cend()
		return ConstIterator(this, nodo, ind);
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
			
			// Search for the next node in the list of nodes.
			_act = _act->_sig;
			
			// If we have reached the end of the list of nodes, continue
			// searching through the vector _v.
			while ((_act == NULL) && (_ind < _tabla->_tam - 1)) {
				++_ind;
				_act = _tabla->_v[_ind];
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
		// So that it can build objects of the iterator type
		friend class HashMap;
		
		Iterator(const HashMap* tabla, Nodo* act, unsigned int ind) 
		: _tabla(tabla), _act(act), _ind(ind) { }
		
		const HashMap *_tabla;  ///< Table being traversed
		Nodo* _act;             ///< Pointer to the current node of the traversal
		unsigned int _ind;      ///< Current index in the vector _v
	};
	
	/**
	 Returns the iterator to the beginning of the list.
	 @return iterator to the beginning of the list;
	 will coincide with end() if the list is empty.
	 */
	Iterator begin() {
		unsigned int ind = 0;
		Nodo *act = _v[0];
		while (ind < _tam-1 && act == NULL) {
			ind++;
			act = _v[ind];
		}
		return Iterator(this, act, ind);        
	}
	
	/**
	 @return Returns an iterator to the end of the traversal
	 (outside of it).
	 */
	Iterator end() const {
		return Iterator(this, NULL, 0);
	}
	
	/**
	 @return Returns an iterator to the position of 
	 key, or to the end of the traversal if key not found
	 */
	Iterator find(const Clave &clave) {
		// Get the index associated with the key.
		unsigned int ind = ::hash(clave) % _tam;
		
		// Search for a node containing that key.
		Nodo *nodo = buscaNodo(clave, _v[ind]);
		
		// if nodo == NULL, actually returns cend()
		return Iterator(this, nodo, ind);
	}
	
	
	// //
	// C++ "PLUMBING" METHODS THAT MAKE THE CLASS
	// VERSATILE
	// //
	
	/** Copy constructor */
	HashMap(const HashMap<Clave, Valor> &other) {
		copia(other);
	}
	
	/** Assignment operator */
	HashMap<Clave, Valor> &operator=(const HashMap<Clave, Valor> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}
	
private:
	
	// So that the iterator can access the private part
	friend class Iterador;    
	
	/**
	 Frees all dynamic memory reserved for the table.
	 */
	void libera() {
		
		// Free the lists of nodes.
		for (unsigned int i=0; i<_tam; i++) {
			liberaNodos(_v[i]);
		}
		
		// Free the array of pointers to nodes.
		if (_v != NULL) {
			delete[] _v;
			_v = NULL;
		}
	}
	
	/**
	 Frees a node and all subsequent ones.
	
	 @param prim pointer to the first node of the list to be freed.
	 */
	static void liberaNodos(Nodo *prim) {
		
		while (prim != NULL) {
			Nodo *aux = prim;
			prim = prim->_sig;
			delete aux;
		}       
	}
	
	/**
	 Makes a copy of the table received as a parameter. Before calling
	 this method, the "libera" method must be invoked.
	
	 @param other table to be copied.
	 */
	void copia(const HashMap<Clave,Valor> &other) {
		_tam = other._tam;
		_numElems = other._numElems;
		
		// Reserve memory for the array of pointers to nodes.
		_v = new Nodo*[_tam];
		for (unsigned int i=0; i<_tam; ++i) { 
			_v[i] = NULL;
			
			// Copy the list of nodes from other._v[i] to _v[i]
			Nodo *act = other._v[i];
			while (act != NULL) {
				_v[i] = new Nodo(act->_clave, act->_valor, _v[i]); 
				act = act->_sig;
			}
		}
	}
	
	/**
	 Searches for a node containing the given key. If found,
	 returns a pointer to it; otherwise, returns NULL.
	
	 @param clave Key to search for.
	 @param prim Pointer to the first node of the list where to search.
	 @return Pointer to the node found, or NULL.
	 */
	static Nodo* buscaNodo(const Clave &clave, Nodo *prim) {
		Nodo *act = prim;
		while ((act != NULL) && (act->_clave != clave)) {
			act = act->_sig;
		}
		return act;
	}
	
	/**
	 Searches for a node containing the given key. If found,
	 sets 'act' to point to it and 'ant' to the previous node.
	 If not found, sets 'act' to NULL.
	
	 @param clave Key to search for.
	 @param act [in/out] Initially points to the first node; upon return,
	 points to the found node or NULL.
	 @param ant [out] Upon return, points to the node before 'act', or NULL
	 if 'act' is the first node or was not found.
	 */
	static void buscaNodo(const Clave &clave, Nodo* &act, Nodo* &ant) {
		ant = NULL;
		while ((act != NULL) && (act->_clave != clave)) {
			ant = act;
			act = act->_sig;
		}
	}
	
	/**
	 Expands the hash table to double its size.
	 */
	void amplia() {
		// Create a new table with double the size.
		Nodo **vAnt = _v;
		unsigned int tamAnt = _tam;
		_tam *= 2;
		_v = new Nodo*[_tam];
		for (unsigned int i=0; i<_tam; ++i)
			_v[i] = NULL;
		
		// Rehash the elements from the old table to the new one.
		for (unsigned int i=0; i<tamAnt; ++i) {
			
			// We traverse the list of nodes in the old table.
			Nodo *nodo = vAnt[i];
			while (nodo != NULL) {
				
				// Get the index in the new table.
				unsigned int ind = ::hash(nodo->_clave) % _tam;
				
				// We take the node from the old list.
				Nodo *aux = nodo;
				nodo = nodo->_sig;
				
				// Insert the node at the beginning of the corresponding list in the new table.
				aux->_sig = _v[ind];
				_v[ind] = aux;
			}
		}
		
		// Delete the old table (the nodes are reused).
		delete[] vAnt;
	}
	
	/**
	 Maximum occupancy allowed before expanding the table.
	 */
	static const int MAX_OCUPACION = 80;
	
	Nodo **_v;               ///< Array of pointers to node lists.
	unsigned int _tam;       ///< Size of the array _v.
	unsigned int _numElems;  ///< Number of elements stored.      
};

#endif // __HASHMAP_H
