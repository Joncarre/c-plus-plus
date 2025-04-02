//
//  TreeMap_Modificado_Modificado.h
//
//  Extension of <key, value> tables as AVL search trees
//  with an operation to query the Kth element
//
#ifndef TreeMap_Modificado_MODOFOCADO_H_
#define TreeMap_Modificado_MODOFOCADO_H_

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <utility>
#include "Exceptions.h"

template <typename Clave, typename Valor, typename Comparador = std::less<Clave>>
class TreeMap_Modificado {
protected:
	using AVLT = TreeMap_Modificado<Clave, Valor, Comparador>;
public:
    struct ClaveValor {
        const Clave clave;
        Valor valor;
        ClaveValor(Clave const& c, Valor const& v = Valor()) : clave(c), valor(v) {};
    };

	TreeMap_Modificado(Comparador c = Comparador()) : raiz(nullptr), menor(c) {};

	TreeMap_Modificado(AVLT const& other);

	TreeMap_Modificado(AVLT && other);

	AVLT & operator=(AVLT const& other);

	AVLT & operator=(AVLT && other);

	~TreeMap_Modificado();

	void insert(Clave const& clave, Valor const& valor);

	int mostrar_Tam_i() {
		return raiz->tam_i;
	}


	bool empty() const;

	bool contains(Clave const& c) const;

	Valor const& at(Clave const& clave) const;

	void erase(Clave const& c);

	void print(std::ostream& o = std::cout) const;

	Clave const& k_esimo(int k);

	
protected:
	
	/**
	Node class that internally stores the (key, value) pair,
	pointers to the left and right children, and the height.
	*/
	class TreeNode;
	using Link = TreeNode *;

	/** Pointer to the root of the hierarchical node structure. */
	Link raiz;

	/** Function object that compares elements. */
	Comparador menor;

public:
	// iterator that traverses the <key, value> pairs of the tree in inorder
	class Iterator {
	public:
		ClaveValor const& operator*() const;

		Iterator & operator++();
		Iterator operator++(int);

		bool operator==(const Iterator &other) const;

		bool operator!=(const Iterator &other) const;

	protected:
		friend class TreeMap_Modificado;

		Iterator() : act_(nullptr) {}
		Iterator(Link p) { act_ = first(p); }

		Link first(Link p);
		void next();

		Link act_;
		std::stack<Link> ancestors;
	};

	Iterator begin() {
		return Iterator(raiz);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}


protected:

	static void liberar(Link a);

	static Link copiar(Link b);

	Link buscar(Clave const& clave, Link a) const;

	static int altura(Link a);

	virtual void insertar(ClaveValor const& cv, Link & a, bool& ok);

	void erase(Clave const& clave, Link & a);

	static void subirMenor(Link & a, Link b, Link padre);

	static void rotaDer(Link & k2);
	static void rotaIzq(Link & k1);
	static void rotaIzqDer(Link & k3);
	static void rotaDerIzq(Link & k1);
	static void reequilibraIzq(Link & a);
	static void reequilibraDer(Link & a);

	static void print(std::ostream & o, int indent, Link r);
	/*
		Auxiliary function that adds up the tam_i of the right child of a tree
		O(log N)
	*/
	static int suma_der_tam_i(Link a);
	/*
		Function that searches for the k-th element, uses the suma_der_tam_i function to compare with root.tam_i
		O(log N)
	*/
	Clave const& Busca_k_esimo( int k, Link a);
};


template <typename Clave, typename Valor, typename Comparador>
inline std::ostream& operator<<(std::ostream & o, TreeMap_Modificado<Clave, Valor, Comparador> const& a) {
	a.print(o);
	return o;
}

template <typename Clave, typename Valor, typename Comparador>
TreeMap_Modificado<Clave, Valor, Comparador>::TreeMap_Modificado(AVLT const& other) {
	raiz = copiar(other.raiz);
}

template <typename Clave, typename Valor, typename Comparador>
TreeMap_Modificado<Clave, Valor, Comparador>::TreeMap_Modificado(AVLT && other) : raiz(other.raiz) {
	other.raiz = nullptr;
}


template <typename Clave, typename Valor, typename Comparador>
TreeMap_Modificado<Clave, Valor, Comparador> & TreeMap_Modificado<Clave, Valor, Comparador>::operator=(AVLT const& other) {
	if (this != &other) {
		AVLT copia = other;
		std::swap(*this, copia);
	}
	return *this;
}

template <typename Clave, typename Valor, typename Comparador>
TreeMap_Modificado<Clave, Valor, Comparador> & TreeMap_Modificado<Clave, Valor, Comparador>::operator=(AVLT && other) {
	std::swap(raiz, other.raiz);
	return *this;
}

template <typename Clave, typename Valor, typename Comparador>
TreeMap_Modificado<Clave, Valor, Comparador>::~TreeMap_Modificado(){
	liberar(raiz);
	raiz = nullptr;
};

template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::insert(Clave const& clave, Valor const& valor) {
	bool ok = false;
	insertar({ clave, valor }, raiz, ok);
}

template <typename Clave, typename Valor, typename Comparador>
bool TreeMap_Modificado<Clave, Valor, Comparador>::empty() const {
	return raiz == nullptr;
}

template <typename Clave, typename Valor, typename Comparador>
bool TreeMap_Modificado<Clave, Valor, Comparador>::contains(Clave const& c) const {
	return buscar(c, raiz) != nullptr;
}

template <typename Clave, typename Valor, typename Comparador>
Valor const& TreeMap_Modificado<Clave, Valor, Comparador>::at(Clave const& clave) const {
	Link p = buscar(clave, raiz);
	if (p == nullptr)
		throw std::out_of_range("La clave no se puede consultar");
	return p->cv.valor;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::erase(Clave const& c){
	erase(c, raiz);
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::print(std::ostream& o) const {
	if (raiz != nullptr) {
		print(o, 0, raiz);
	}
	else
		o << "vacio\n";
}
/*
	Function that receives an integer k as parameter,
	and is responsible for finding the k-th smallest element in the search tree
	
	Complexity: log(N)
*/
template <typename Clave, typename Valor, typename Comparador>
Clave const& TreeMap_Modificado<Clave, Valor, Comparador>::  k_esimo(int k) {
	try
	{
		if (raiz !=nullptr) {

			return  Busca_k_esimo(k, raiz);
		}
		else throw NotExistException("null root");
	}
	catch (NotExistException)
	{
		throw NotExistException("k-th element does not exist");
	}
}



template <typename Clave, typename Valor, typename Comparador>
Clave const& TreeMap_Modificado<Clave, Valor, Comparador>:: Busca_k_esimo( int k , Link a) {

	if (a != nullptr) {

		if (menor(a->tam_i, k)) { 

				k -= a->tam_i;
				return Busca_k_esimo(k, a->dr);

		}
		else if (menor(k, a->tam_i)) {

				return Busca_k_esimo(k, a->iz);
			
		}
		else 
			return a->cv.clave;
	}
	else  throw NotExistException();
}


template <typename Clave, typename Valor, typename Comparador>
int TreeMap_Modificado<Clave, Valor, Comparador>:: suma_der_tam_i(Link a) {

	if (a == nullptr) {
		return 0;
	}
	else {

		if (a -> iz != nullptr) {

			return suma_der_tam_i(a->iz->dr) + suma_der_tam_i(a->dr) + a->tam_i;
		}
		else{

			return suma_der_tam_i(a->dr) + a->tam_i;
		}
			
	
	}
}
template <typename Clave, typename Valor, typename Comparador>
class TreeMap_Modificado<Clave, Valor, Comparador>::TreeNode { 
public:
	ClaveValor cv;
	Link iz;
	Link dr;
	int altura;
	int tam_i;
	TreeNode(ClaveValor e, Link i = nullptr, Link d = nullptr, int alt = 1,int tam_i = 1)
		: cv(e), iz(i), dr(d), altura(alt),tam_i(tam_i) {}

};

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap_Modificado<Clave, Valor, Comparador>::ClaveValor const& TreeMap_Modificado<Clave, Valor, Comparador>::Iterator::operator*() const {
	if (act_ == nullptr) throw std::out_of_range("No hay elemento a consultar");
	return act_->cv;
}


template <typename Clave, typename Valor, typename Comparador>
typename TreeMap_Modificado<Clave, Valor, Comparador>::Iterator & TreeMap_Modificado<Clave, Valor, Comparador>::Iterator::operator++() {
	next();
	return *this;
}

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap_Modificado<Clave, Valor, Comparador>::Iterator TreeMap_Modificado<Clave, Valor, Comparador>::Iterator::operator++(int) {
	Iterator ret(*this);
	operator++();
	return ret;
}

template <typename Clave, typename Valor, typename Comparador>
bool TreeMap_Modificado<Clave, Valor, Comparador>::Iterator::operator==(const Iterator &other) const {
	return act_ == other.act_;
}

template <typename Clave, typename Valor, typename Comparador>
bool TreeMap_Modificado<Clave, Valor, Comparador>::Iterator::operator!=(const Iterator &other) const {
	return !(this->operator==(other));
}

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap_Modificado<Clave, Valor, Comparador>::Link TreeMap_Modificado<Clave, Valor, Comparador>::Iterator::first(Link p) {
	if (p == nullptr)
		return nullptr;

	while (p->iz != nullptr) {
		ancestors.push(p);
		p = p->iz;
	}
	return p;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::Iterator::next() {
	if (act_ == nullptr) throw std::out_of_range("The iterator cannot be advanced");

	// If there is a right child, jump to the first
	// in-order element of the right child
	if (act_->dr)
		act_ = first(act_->dr);
	else {
		// If not, go to the first unvisited
		// ancestor. For that we check the
		// stack; if it's already empty, there are no
		// ancestors left to visit
		if (ancestors.empty())
			act_ = nullptr;
		else {
			act_ = ancestors.top();
			ancestors.pop();
		}
	}
}


template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::liberar(Link a){
	if (a != nullptr){
		liberar(a->iz);
		liberar(a->dr);
		delete a;
	}
}

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap_Modificado<Clave, Valor, Comparador>::Link
TreeMap_Modificado<Clave, Valor, Comparador>::copiar(Link b) {
	if (b == nullptr) return nullptr;
	else return new TreeNode(b->cv,
		copiar(b->iz),
		copiar(b->dr),
		b->altura);
}

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap_Modificado<Clave, Valor, Comparador>::Link
TreeMap_Modificado<Clave, Valor, Comparador>::buscar(Clave const& clave, Link a) const {
	if (a == nullptr)
		return nullptr;
	else if (menor(clave, a->cv.clave))
		return buscar(clave, a->iz);
	else if (menor(a->cv.clave, clave))
		return buscar(clave, a->dr);
	else // clave == a->cv.clave
		return a;
}

template <typename Clave, typename Valor, typename Comparador>
int TreeMap_Modificado<Clave, Valor, Comparador>::altura(Link a) {
	if (a == nullptr) return 0;
	else return a->altura;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::insertar(ClaveValor const& cv, Link & a, bool& ok) {
	
	if (a == nullptr) {		
		a = new TreeNode(cv);
		ok = true;
	}//  LLAMADA IZQUIERDO
	else if (menor(cv.clave, a->cv.clave)) { // clave < raiz_clave
		
				//Tam_i + 1 
					
		// si Hiji_IZ.clave == Padre.clave -> quitamos uno a padre tam_i
			/*if (a->iz != nullptr){
				if (a->iz->cv.clave == cv.clave){
					a->tam_i -= 1;
					
				}
			}
			*/
					
					insertar(cv, a->iz, ok);
					if (ok == true)
						a->tam_i += 1;

					reequilibraDer(a);
		
	}
	else if (menor(a->cv.clave, cv.clave)) {
		
		insertar(cv, a->dr,ok);

		reequilibraIzq(a);
	}
	else { // la clave ya está, se actualiza el valor asociado
		a->cv.valor = cv.valor;
		ok = false;
	}

}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::erase(Clave const& clave, Link & a) {
	if (a != nullptr) {
		if (menor(clave, a->cv.clave)) {
			erase(clave, a->iz);
			reequilibraIzq(a);
		}
		else if (menor(a->cv.clave, clave)) {
			erase(clave, a->dr);
			reequilibraDer(a);
		}
		else // a->cv.clave == clave
			if (a->iz == nullptr || a->dr == nullptr) {
				Link aux = a;
				a = a->iz == nullptr ? a->dr : a->iz;
				delete aux;
			}
			else { // tiene dos hijos
				subirMenor(a, a->dr, nullptr);
				// reequilibraDer(a);
			}
	}
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::subirMenor(Link & a, Link b, Link padre) {
	if (b->iz != nullptr){
		subirMenor(a, b->iz, b);
		reequilibraIzq(b);
	}
	else {
		if (padre != nullptr) {
			padre->iz = b->dr;
			b->dr = a->dr;
		}
		b->iz = a->iz;
		delete a;
		a = b;
		a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
	}
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::rotaDer(Link & k2) {

	Link k1 = k2->iz;	 //k1 HIJO IZ
	k2->iz = k1->dr;

	//if(k1->dr != nullptr)
//	//	k2->tam_i = k1->dr->tam_i;
//	else k2->tam_i = 1;
	k2->tam_i -= k1->tam_i;


	k1->dr = k2;
	k2->altura = std::max(altura(k2->iz), altura(k2->dr)) + 1;
	k1->altura = std::max(altura(k1->iz), altura(k1->dr)) + 1;
	k2 = k1;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::rotaIzq(Link & k1) {

	Link k2 = k1->dr;   //k2 hijo DR
	k1->dr = k2->iz;

	// sumamos a k2 el hijo izq k1
	k2->tam_i = k1->tam_i + k2->tam_i;

	k2->iz = k1;
	k1->altura = std::max(altura(k1->iz), altura(k1->dr)) + 1;
	k2->altura = std::max(altura(k2->iz), altura(k2->dr)) + 1;
	k1 = k2;

}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::rotaIzqDer(Link & k3) {
	rotaIzq(k3->iz);
	rotaDer(k3);
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::rotaDerIzq(Link & k1) {
	rotaDer(k1->dr);
	rotaIzq(k1);
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::reequilibraIzq(Link & a) {
	if (altura(a->dr) - altura(a->iz) > 1) {
		if (altura(a->dr->iz) > altura(a->dr->dr))
			rotaDerIzq(a);
		else rotaIzq(a);
	}
	else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::reequilibraDer(Link & a) {
	if (altura(a->iz) - altura(a->dr) > 1) {
		if (altura(a->iz->dr) > altura(a->iz->iz))
			rotaIzqDer(a);
		else rotaDer(a);
	}
	else
		a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap_Modificado<Clave, Valor, Comparador>::print(std::ostream & o, int indent, Link r) {
	if (r != nullptr){
		print(o, indent + 2, r->dr);
		for (auto i = 0; i < indent; ++i) o << " ";
		o << "(" << r->cv.clave << "," << r->cv.valor << ")\n";
		print(o, indent + 2, r->iz);
	}
}



#endif /* TreeMap_Modificado_AVL_H_ */
