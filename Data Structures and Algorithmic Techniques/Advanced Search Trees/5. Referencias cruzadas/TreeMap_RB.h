//
//  TreeMap_RB.h
//
//  Implementación de tablas <clave, valor> como ABB rojinegros inclinados a la izquierda
//
//  Técnicas Algoritmicas en Ingeniería del Software / Diseño de Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 30/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef TREEMAP_RB_H_
#define TREEMAP_RB_H_

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <utility>

const bool RED = true;
const bool BLACK = false;

template <typename Clave, typename Valor, typename Comparador = std::less<Clave>>
class TreeMap {
protected:
	using ABBRB = TreeMap<Clave, Valor, Comparador>;
public:

	TreeMap(Comparador c = Comparador()) : raiz(nullptr), menor(c) {};

	TreeMap(ABBRB const& other);

	TreeMap(ABBRB && other);

	ABBRB & operator=(ABBRB const& other);

	ABBRB & operator=(ABBRB && other);

	~TreeMap();

	void insert(Clave const& clave, Valor const& valor);

	bool empty() const;

	bool contains(Clave const& c) const;

	Valor const& at(Clave const& clave);

	void print(std::ostream& o = std::cout) const;

protected:
	/**
	Clase nodo que almacena internamente la pareja (clave, valor),
	los punteros al hijo izquierdo y al hijo derecho, y la altura.
	*/
	class TreeNode;
	using Link = TreeNode *;

	/** Puntero a la raíz de la estructura jerárquica de nodos. */
	Link raiz;

	/** Objeto función que compara elementos. */
	Comparador menor;

public:
	class Iterator {
	public:
		Clave const& clave() const;

		Valor const& valor() const;

		Iterator & operator++();
		Iterator operator++(int);

		bool operator==(const Iterator &other) const;

		bool operator!=(const Iterator &other) const;

	protected:
		friend class TreeMap;

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

	virtual void insertar(Clave const& clave, Valor const& valor, Link & a);

	static bool isRed(Link x);

	// make a left-leaning link lean to the right
	static void rotateRight(Link & h);

	// make a right-leaning link lean to the left
	static void rotateLeft(Link & h);

	// flip the colors of a node and its two children
	static void flipColors(Link h);


	static void print(std::ostream & o, int indent, Link r);

};


template <typename Clave, typename Valor, typename Comparador>
inline std::ostream& operator<<(std::ostream & o, TreeMap<Clave, Valor, Comparador> const& a) {
	a.print(o);
	return o;
}


template <typename Clave, typename Valor, typename Comparador>
TreeMap<Clave, Valor, Comparador>::TreeMap(ABBRB const& other) {
	raiz = copiar(other.raiz);
}

template <typename Clave, typename Valor, typename Comparador>
TreeMap<Clave, Valor, Comparador>::TreeMap(ABBRB && other) : raiz(other.raiz) {
	other.raiz = nullptr;
}


template <typename Clave, typename Valor, typename Comparador>
TreeMap<Clave, Valor, Comparador> & TreeMap<Clave, Valor, Comparador>::operator=(ABBRB const& other) {
	if (this != &other) {
		ABBRB copia = other;
		std::swap(*this, copia);
	}
	return *this;
}

template <typename Clave, typename Valor, typename Comparador>
TreeMap<Clave, Valor, Comparador> & TreeMap<Clave, Valor, Comparador>::operator=(ABBRB && other) {
	std::swap(raiz, other.raiz);
	return *this;
}

template <typename Clave, typename Valor, typename Comparador>
TreeMap<Clave, Valor, Comparador>::~TreeMap(){
	liberar(raiz);
	raiz = nullptr;
};

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::insert(Clave const& clave, Valor const& valor) {
	insertar(clave, valor, raiz);
	raiz->color = BLACK;
}

template <typename Clave, typename Valor, typename Comparador>
bool TreeMap<Clave, Valor, Comparador>::empty() const {
	return raiz == nullptr;
}

template <typename Clave, typename Valor, typename Comparador>
bool TreeMap<Clave, Valor, Comparador>::contains(Clave const& c) const {
	return buscar(c, raiz) != nullptr;
}

template <typename Clave, typename Valor, typename Comparador>
Valor const& TreeMap<Clave, Valor, Comparador>::at(Clave const& clave) {
	Link p = buscar(clave, raiz);
	if (p == nullptr)
		throw std::out_of_range("La clave no se puede consultar");
	return p->valor;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::print(std::ostream& o) const {
	if (raiz != nullptr) {
		print(o, 0, raiz);
	}
	else
		o << "vacio\n";
}

template <typename Clave, typename Valor, typename Comparador>
class TreeMap<Clave, Valor, Comparador>::TreeNode {
public:
	const Clave clave;
	Valor valor;
	Link iz;
	Link dr;
	bool color;
	TreeNode(Clave const& c, Valor const& v, Link i = nullptr, Link d = nullptr, bool col = RED)
		: clave(c), valor(v), iz(i), dr(d), color(col) {}
};


template <typename Clave, typename Valor, typename Comparador>
Clave const& TreeMap<Clave, Valor, Comparador>::Iterator::clave() const {
	if (act_ == nullptr) throw std::out_of_range("La clave no se puede consultar");
	return act_->clave;
}

template <typename Clave, typename Valor, typename Comparador>
Valor const& TreeMap<Clave, Valor, Comparador>::Iterator::valor() const {
	if (act_ == nullptr) throw std::out_of_range("El valor no se puede consultar");
	return act_->valor;
}

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap<Clave, Valor, Comparador>::Iterator & TreeMap<Clave, Valor, Comparador>::Iterator::operator++() {
	next();
	return *this;
}

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap<Clave, Valor, Comparador>::Iterator TreeMap<Clave, Valor, Comparador>::Iterator::operator++(int) {
	Iterator ret(*this);
	operator++();
	return ret;
}

template <typename Clave, typename Valor, typename Comparador>
bool TreeMap<Clave, Valor, Comparador>::Iterator::operator==(const Iterator &other) const {
	return act_ == other.act_;
}

template <typename Clave, typename Valor, typename Comparador>
bool TreeMap<Clave, Valor, Comparador>::Iterator::operator!=(const Iterator &other) const {
	return !(this->operator==(other));
}

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap<Clave, Valor, Comparador>::Link TreeMap<Clave, Valor, Comparador>::Iterator::first(Link p) {
	if (p == nullptr)
		return nullptr;

	while (p->iz != nullptr) {
		ancestors.push(p);
		p = p->iz;
	}
	return p;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::Iterator::next() {
	if (act_ == nullptr) throw std::out_of_range("El iterador no se puede avanzar");

	// Si hay hijo derecho, saltamos al primero
	// en inorden del hijo derecho
	if (act_->dr)
		act_ = first(act_->dr);
	else {
		// Si no, vamos al primer ascendiente
		// no visitado. Para eso consultamos
		// la pila; si ya est· vacÌa, no quedan
		// ascendientes por visitar
		if (ancestors.empty())
			act_ = nullptr;
		else {
			act_ = ancestors.top();
			ancestors.pop();
		}
	}
}


template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::liberar(Link a){
	if (a != nullptr){
		liberar(a->iz);
		liberar(a->dr);
		delete a;
	}
}

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap<Clave, Valor, Comparador>::Link
TreeMap<Clave, Valor, Comparador>::copiar(Link b) {
	if (b == nullptr) return nullptr;
	else return new TreeNode(b->clave, b->valor,
		copiar(b->iz),
		copiar(b->dr),
		b->color);
}

template <typename Clave, typename Valor, typename Comparador>
typename TreeMap<Clave, Valor, Comparador>::Link
TreeMap<Clave, Valor, Comparador>::buscar(Clave const& clave, Link a) const {
	if (a == nullptr)
		return nullptr;
	else if (menor(clave, a->clave))
		return buscar(clave, a->iz);
	else if (menor(a->clave, clave))
		return buscar(clave, a->dr);
	else // clave == a->clave
		return a;
}


template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::insertar(Clave const& clave, Valor const& valor, Link & a) {
	if (a == nullptr) {
		a = new TreeNode(clave, valor);
	}
	else {
		if (menor(clave, a->clave)) {
			insertar(clave, valor, a->iz);
		}
		else if (menor(a->clave, clave)) {
			insertar(clave, valor, a->dr);
		}
		else { // la clave ya está, se modifica el valor asociado
			a->valor = valor;
		}
		// fix right-leaning reds
		if (isRed(a->dr) && !isRed(a->iz))     rotateLeft(a);
		// fix two reds in a row
		if (isRed(a->iz) && isRed(a->iz->iz)) rotateRight(a);
		// split 4-nodes
		if (isRed(a->iz) && isRed(a->dr))     flipColors(a);
	}
}

template <typename Clave, typename Valor, typename Comparador>
bool TreeMap<Clave, Valor, Comparador>::isRed(Link x) {
	if (x == nullptr) return false;
	return (x->color == RED);
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::rotateRight(Link & h) {
	Link x = h->iz;
	h->iz = x->dr;
	x->dr = h;
	x->color = h->color;
	h->color = RED;
	h = x;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::rotateLeft(Link & h) {
	Link x = h->dr;
	h->dr = x->iz;
	x->iz = h;
	x->color = h->color;
	h->color = RED;
	h = x;
}

template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::flipColors(Link h) {
	h->color = RED;
	h->iz->color = BLACK;
	h->dr->color = BLACK;
}


template <typename Clave, typename Valor, typename Comparador>
void TreeMap<Clave, Valor, Comparador>::print(std::ostream & o, int indent, Link r) {
	if (r != nullptr){
		print(o, indent + 2, r->dr);
		for (auto i = 0; i < indent; ++i) o << " ";
		o << "(" << r->clave << "," << r->valor << ")\n";
		print(o, indent + 2, r->iz);

		//            print(o, indent, r->iz);
		//            o << r-> clave << " ";
		//            print(o, indent, r->dr);
	}
}



#endif /* TREEMAP_RB_H_ */
