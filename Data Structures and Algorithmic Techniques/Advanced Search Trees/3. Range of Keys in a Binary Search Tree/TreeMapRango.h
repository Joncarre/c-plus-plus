//
//  TreeMapRango.h
//
//  Extension of <key, value> tables as AVL search trees
//  with an operation to query keys in a range
//

#ifndef TREEMAPRANGO_H_
#define TREEMAPRANGO_H_

#include <vector>

#include "TreeMap_AVL.h"

template <typename Clave, typename Valor, typename Comparador = std::less<Clave>>
class TreeMapRango : public TreeMap<Clave, Valor, Comparador> {
public:
    
    TreeMapRango(Comparador c = Comparador()) : TreeMap<Clave, Valor, Comparador>(c) {};

	std::vector<Clave> rango(Clave const& k1, Clave const& k2) const {

		// Empty list.
		std::vector<Clave> lista;

		// Range.
		rango(k1, k2,  this->raiz, lista);

		return lista;

	}
protected:
    using TreeNode = typename TreeMap<Clave, Valor, Comparador>::TreeNode;
    using Link = TreeNode *;

	/*
	*	Function that performs the necessary pruning to find elements that are
	*	within the interval established with k1 and k2. Additionally, if the element is
	*	in that interval, it adds it to the vector (list). Its complexity is given by the size
	*	of the tree but won't be linear since pruning allows reducing that complexity.
	*
	*	Complexity: O(log n)
	*/
    void rango(Clave const& k1, Clave const& k2, Link a, std::vector<Clave> & lista) const {
		
		// Root is not empty.
		if (a!=nullptr){
			// If key < k1 then prune left child.
			if (this->menor(a->cv.clave, k1)){
					
					rango(k1, k2, a->dr, lista);
			}// If Key > k2 then prune right child.
			else if (this->menor(k2, a->cv.clave)){
					
					rango(k1, k2, a->iz, lista);			
			}
			else {
				// If it's in the Range.
				rango(k1, k2, a->iz, lista);
				lista.push_back(a->cv.clave);
				rango(k1, k2, a->dr, lista);
			}
		}
    }
};

#endif /* TREEMAPRANGO_H_ */
