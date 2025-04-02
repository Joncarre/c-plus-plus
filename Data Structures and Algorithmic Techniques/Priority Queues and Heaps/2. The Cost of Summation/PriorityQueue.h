//
//  PriorityQueue.h
//
//  Implementation of priority queues using heaps
//
//  Algorithmic Techniques in Software Engineering / Algorithm Design
//  Faculty of Computer Science
//  Complutense University of Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

const size_t TAM_INICIAL = 100;

// Comparator specifies when a value of type T has higher priority than another
template <typename T = int, typename Comparator = std::less<T>>
class PriorityQueue {
public:

	PriorityQueue(size_t t = TAM_INICIAL, Comparator c = Comparator());

	/** Constructor from a vector of elements */
	PriorityQueue(std::vector<T> const& v_ini, Comparator c = Comparator());

	PriorityQueue(PriorityQueue<T, Comparator> const&) = default;

//	PriorityQueue(PriorityQueue<T, Comparator> &&) = default;

	PriorityQueue<T, Comparator> & operator=(PriorityQueue<T, Comparator> const&) = default;

//	PriorityQueue<T, Comparator> & operator=(PriorityQueue<T, Comparator> &&) = default;

	~PriorityQueue() = default;


	/** Insert the element x (which includes its priority).
	If there is no space, the array is expanded. */
	void push(T const& x);
	void push(T && x);

	/** Returns the number of elements in the queue. */
	size_t size() const { return numElems; }

	bool empty() const { return (numElems == 0); }

	/* If the queue is not empty, returns the highest priority element. */
	T const& top() const;

	/* If the queue is not empty, removes the highest priority element. */
	void pop();

	/* If the queue is not empty, removes and returns the highest priority element. */
	void pop(T & prim);

	/* Displays the heap through the output o */
	void print(std::ostream& o = std::cout) const;


private:

	/** Vector containing the data */
	std::vector<T> array;     // first element at position 1

	/** Number of elements in the heap */
	size_t numElems;

	/** Function object that knows how to compare elements.
	* antes(a,b) is true if a has higher priority than b (a should come out before b)
	*/
	Comparator antes;

	/* Floats the element located at position n of the heap. */
	void flotar(size_t n);

	/* Sinks the element located at position n of the heap. */
	void hundir(size_t n);

	/* converts an array into a heap */
	void monticulizar();
};

template <typename T, typename Comparator>
inline std::ostream& operator<<(std::ostream & o, PriorityQueue<T, Comparator> const& a){
	a.print(o);
	return o;
}

/** Function to build a priority queue whose Comparator is a lambda. */
template<typename T, typename Comparator> // the Comparator type is deduced from c
inline PriorityQueue<T, Comparator> make_priorityqueue(Comparator c, size_t tam = TAM_INICIAL)
{
	return PriorityQueue<T, Comparator>(tam, c);
}


template <typename T, typename Comparator>
PriorityQueue<T, Comparator>::PriorityQueue(size_t t, Comparator c) :
array(t + 1), numElems(0), antes(c) {};

template <typename T, typename Comparator>
PriorityQueue<T, Comparator>::PriorityQueue(std::vector<T> const& v_ini, Comparator c) :
array(2 * v_ini.size()), numElems(v_ini.size()), antes(c) {
	for (auto i = 0; i < v_ini.size(); ++i)
		array[i + 1] = v_ini[i];
	monticulizar();
};


template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::push(T const& x) {
	if (numElems == array.size() - 1)  // if the array is full, increase its size
		array.resize(array.size() * 2);
	++numElems;
	array[numElems] = x;
	flotar(numElems);
}
template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::push(T && x) {
	if (numElems == array.size() - 1)  // if the array is full, increase its size
		array.resize(array.size() * 2);
	++numElems;
	array[numElems] = std::move(x);
	flotar(numElems);
}

template <typename T, typename Comparator>
T const& PriorityQueue<T, Comparator>::top() const {
	if (empty()) throw std::domain_error("Cannot access the top element of an empty queue.");
	else return array[1];
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::pop() {
	if (empty()) throw std::domain_error("Cannot remove the top element from an empty queue");
	else {
		array[1] = std::move(array[numElems]);
		--numElems;
		hundir(1);
	}
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::pop(T & prim) {
	if (empty()) throw std::domain_error("Cannot remove the top element from an empty queue");
	else {
		prim = std::move(array[1]);
		array[1] = std::move(array[numElems]);
		--numElems;
		hundir(1);
	}
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::print(std::ostream & o) const {
	for (auto i = 1; i <= numElems; ++i)
		o << array[i] << " ";
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::flotar(size_t n) {
	T elem = std::move(array[n]);
	size_t hueco = n;
	while (hueco != 1 && antes(elem, array[hueco / 2])) {
		array[hueco] = std::move(array[hueco / 2]);
		hueco /= 2;
	}
	array[hueco] = std::move(elem);
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::hundir(size_t n) {
	T elem = std::move(array[n]);
	size_t hueco = n;
	size_t hijo = 2 * hueco; // left child, if it exists
	while (hijo <= numElems)  {
		// switch to right child if it exists and has higher priority than the left one
		if (hijo < numElems && antes(array[hijo + 1], array[hijo]))
			++hijo;
		// float the child if it has higher priority than the sinking element
		if (antes(array[hijo], elem)) {
			array[hueco] = std::move(array[hijo]);
			hueco = hijo; hijo = 2 * hueco;
		}
		else break;
	}
	array[hueco] = std::move(elem);
}

template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::monticulizar() {
	for (auto i = numElems / 2; i > 0; --i)
		hundir(i);
}


#endif /* PRIORITYQUEUE_H_ */
