//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include "HashMap.h"
#include "TreeMap.h"
#include "List.h"
using namespace std;

typedef string idNave;
typedef string idModulo;
typedef int nivel;
typedef int nada;
typedef class Espacio{
public:
	// COMPLEXITIES: m = ships, n = modules
	// ----------------------------------------------------------------
	void EspacioMatic(){

	}
	// ----------------------------------------------------------------
	// Complexity: O(1)
	void nuevaNave(idNave idnave){
		if (naves.contains(idnave))
			throw string("La nave ya existe.");
		else{
			TreeMap<idModulo, nivel> nuevosModulos;
			naves.insert(idnave, nuevosModulos);
		}
	}
	// ----------------------------------------------------------------
	// Complexity: O(logn)
	void equipaNave(idNave idnave, idModulo idmodulo, nivel nivelModulo){
		if (!naves.contains(idnave))
			throw string("La nave no existe.");
		else{
			HashMap<idNave, TreeMap<idModulo, nivel>>::Iterator itNave = naves.find(idnave);
			if (itNave.value().contains(idmodulo)){ // If it has the module...
				if (itNave.value().at(idmodulo) == 0){ // If the module has level 0...
					navesRotas.erase(idnave); // It means that ship was in 'navesRotas'. And if it was in 'navesRotas' we have to remove it because it will be repaired
				}
				else{ // If it doesn't have level 0...
					// Then insert the module (it will be replaced) with the level it had + the new level
					itNave.value().insert(idmodulo, itNave.value().at(idmodulo) + nivelModulo);
				}
			}
			else{ // And if it doesn't have the module...
				itNave.value().insert(idmodulo, nivelModulo);
			}
		}
	}
	// ----------------------------------------------------------------
	// Complexity: O(logn)
	bool estropeaNave(idNave idnave, idModulo idmodulo){
		if (!naves.contains(idnave)){
			throw string("La nave no existe.");
		}
		else{ // If the ship exists...
			HashMap<idNave, TreeMap<idModulo, nivel>>::Iterator itNaves = naves.find(idnave);
			if (!itNaves.value().contains(idmodulo)){
				throw string("El modulo no existe");
				return false;
			}
			else{ // if the module exists...
				if (itNaves.value().at(idmodulo) == 0){
					return false;
				}
				else{ // If the module level is not 0...
					itNaves.value().insert(idmodulo, itNaves.value().at(idmodulo) - 1); // Insert the module but subtract 1 from its level
					if (itNaves.value().at(idmodulo) == 0){ // If subtracting 1 made it reach 0 (it broke)...
						if (!navesRotas.contains(idnave)){ // If the ship did NOT have any broken module...
							navesRotas.insert(idnave, 0); // Add it to the broken ships map
						}
					}
					return true;
				}
			}
		}
	}
	// ----------------------------------------------------------------
	// Complexity: O(d), where d is the number of broken ships stored in 'navesRotas'
	List<idNave> navesDefectuosas(){
		List<idNave> lista;
		HashMap<idNave, nada>::ConstIterator itNavesRotas = navesRotas.cbegin();
		while (itNavesRotas != navesRotas.cend()){
			lista.push_back(itNavesRotas.key());
			itNavesRotas.next();
		}
		return lista;
	}
	// ----------------------------------------------------------------
	// Complexity: O(n)
	List<idModulo> modulosNave(idNave idnave){
		if (!naves.contains(idnave))
			throw string("La nave no existe.");
		else{
			List<idModulo> lista;
			HashMap<idNave, TreeMap<idModulo, nivel>>::Iterator itNaves = naves.find(idnave);
			TreeMap<idModulo, nivel>::ConstIterator itModulos = itNaves.value().cbegin();
			while (itModulos != itNaves.value().cend()){
				lista.push_back(itModulos.key());
				itModulos.next();
			}
			return lista;
		}
	}
private:
	HashMap<idNave, TreeMap<idModulo, nivel>> naves;
	HashMap<idNave, nada> navesRotas;
};
