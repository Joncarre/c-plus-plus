//
//  TreeMapRango.h
//
//  Extensión de tablas <clave, valor> como árboles de búsqueda AVL
//  con una operación para consultar las claves en un rango
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

		// Lista vacía.
		std::vector<Clave> lista;

		// Rango.
		rango(k1, k2,  this->raiz, lista);

		return lista;

	}
protected:
    using TreeNode = typename TreeMap<Clave, Valor, Comparador>::TreeNode;
    using Link = TreeNode *;

	/*
	*	Función que realiza las podas necesarias para ir encontrando los elementos que estén
	*	dentro del intervalo que hayamos establecido con k1 y k2. Además, si el elemento está 
	*	en ese intervalo, lo introduce en el vector (lista). Su complejidad viene dada por el tamaño
	*	del árbol pero no será lineal ya que la poda permite reducir esa complejidad.
	*
	*	Complejidad: O(log n)
	*/
    void rango(Clave const& k1, Clave const& k2, Link a, std::vector<Clave> & lista) const {
		
		// Raíz no es vacío.
		if (a!=nullptr){
			// Si clave < k1 entonces podamos hijo_Iz.
			if (this->menor(a->cv.clave, k1)){
					
					rango(k1, k2, a->dr, lista);
			}// Si Clave > k2 entonces podamos hijo_Dr.
			else if (this->menor(k2, a->cv.clave)){
					
					rango(k1, k2, a->iz, lista);			
			}
			else {
				// Si esta en el Rango.
				rango(k1, k2, a->iz, lista);
				lista.push_back(a->cv.clave);
				rango(k1, k2, a->dr, lista);
			}
		}
    }
};

#endif /* TREEMAPRANGO_H_ */
