//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <math.h>
#include <algorithm>
#include "BinTree.h"
using namespace std;

void resuelve();
BinTree<int> leerArbol();
bool esOrdenado(BinTree<int> arbol, int padre); // 'esOrdenado' means that it satisfies the min-heap property
int altura(BinTree<int> arbol); // Function that returns the height of a tree
bool esCompleto(BinTree<int> arbol); // Function that tells us if a tree is complete
bool esSemiCompleto(BinTree<int> arbol); // Function that tells us if a tree is semi-complete
bool esMonticulo(BinTree<int> arbol); // Function that tells us if it's a heap
// ------------------------------------------------------------------------------------------------------
// Complexity: O(logN + 1), where N is the height of the semi-complete tree
int altura(BinTree<int> arbol){
	if (arbol.empty())
		return 0;
	else
		return 1 + max(altura(arbol.left()) , altura(arbol.right()));
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N), where N is the number of elements read from the input
BinTree<int> leerArbol(){
	BinTree<int> arbol;
	int elemento;
	cin >> elemento;

	if (elemento == -1)
		return BinTree<int>();
	else{
		const BinTree<int> &dr = leerArbol();
		const BinTree<int> &iz = leerArbol();
		return BinTree<int>(dr, elemento, iz);
	}
	return arbol;
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N), has the same complexity as 'esCompleto'
bool esSemiCompleto(BinTree<int> arbol){
	if (arbol.empty())
		return true;
	else if (esCompleto(arbol))
		return true;
	else return (
		((altura(arbol.left()) == altura(arbol.right())) && esCompleto(arbol.left()) && esSemiCompleto(arbol.right())) ||
		((altura(arbol.left()) == altura(arbol.right()) + 1) && esCompleto(arbol.right()) && esSemiCompleto(arbol.left()))
		);
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N), where N is the number of nodes in the tree
bool esCompleto(BinTree<int> arbol){
	if (arbol.empty())
		return true;
	else 
		return (
		esCompleto(arbol.left()) &&
		esCompleto(arbol.right()) &&
		altura(arbol.left()) == altura(arbol.right())
		);
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N), where N is the number of nodes in the tree
bool esOrdenado(BinTree<int> arbol, int padre){
	if (arbol.empty())
		return true;
	else{
		if (esOrdenado(arbol.left(), arbol.root()) &&
			esOrdenado(arbol.right(), arbol.root()) &&
			padre <= arbol.root())
			return true;
		else 
			return false;
	}
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N), the highest complexity of the functions it calls is O(N), where N is the number of nodes
bool esMonticulo(BinTree<int> arbol){
	if (arbol.empty())
		return true;
	else
	if (esSemiCompleto(arbol) &&
		esOrdenado(arbol.left(), arbol.root()) &&
		esOrdenado(arbol.right(), arbol.root()) &&
		esMonticulo(arbol.left()) &&
		esMonticulo(arbol.right()))
		return true;
	else return false;
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N)
void resuelve(){
	BinTree<int> arbol;
	arbol = leerArbol();

	if (esMonticulo(arbol))
		cout << "SI" << endl;
	else
		cout << "NO" << endl;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; i++){
		resuelve();
	}
	//system("PAUSE");
	return 0;
}
