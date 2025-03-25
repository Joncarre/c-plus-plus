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
	// COMPLEJIDADES: m = naves, n = módulos
	// ----------------------------------------------------------------
	void EspacioMatic(){

	}
	// ----------------------------------------------------------------
	// Complejidad: O(1)
	void nuevaNave(idNave idnave){
		if (naves.contains(idnave))
			throw string("La nave ya existe.");
		else{
			TreeMap<idModulo, nivel> nuevosModulos;
			naves.insert(idnave, nuevosModulos);
		}
	}
	// ----------------------------------------------------------------
	// Complejidad: O(logn)
	void equipaNave(idNave idnave, idModulo idmodulo, nivel nivelModulo){
		if (!naves.contains(idnave))
			throw string("La nave no existe.");
		else{
			HashMap<idNave, TreeMap<idModulo, nivel>>::Iterator itNave = naves.find(idnave);
			if (itNave.value().contains(idmodulo)){ // Si tiene el módulo...
				if (itNave.value().at(idmodulo) == 0){ // Si el módulo tiene nivel 0...
					navesRotas.erase(idnave); // Es que esa nave estaba en 'navesRotas'. Y si estaba en 'navesRotas' la tenemos que quitar porque se va a reparar
				}
				else{ // Si no tiene nivel 0...
					// Entonces insertamos el módulo (se sustituirá) con el nivel que tenía + el nuevo nivel
					itNave.value().insert(idmodulo, itNave.value().at(idmodulo) + nivelModulo);
				}
			}
			else{ // Y si no tiene el módulo...
				itNave.value().insert(idmodulo, nivelModulo);
			}
		}
	}
	// ----------------------------------------------------------------
	// Complejidad: O(logn)
	bool estropeaNave(idNave idnave, idModulo idmodulo){
		if (!naves.contains(idnave)){
			throw string("La nave no existe.");
		}
		else{ // Si la nave existe...
			HashMap<idNave, TreeMap<idModulo, nivel>>::Iterator itNaves = naves.find(idnave);
			if (!itNaves.value().contains(idmodulo)){
				throw string("El modulo no existe");
				return false;
			}
			else{ // si el módulo existe...
				if (itNaves.value().at(idmodulo) == 0){
					return false;
				}
				else{ // Si el nivel del módulo no es 0...
					itNaves.value().insert(idmodulo, itNaves.value().at(idmodulo) - 1); // Insertamos el módulo pero restándole 1
					if (itNaves.value().at(idmodulo) == 0){ // Si al restarle 1 ha llegado a 0 (se ha roto)...
						if (!navesRotas.contains(idnave)){ // Si la nave NO tenía algún módulo roto...
							navesRotas.insert(idnave, 0); // Le metemos en las naves rotas
						}
					}
					return true;
				}
			}
		}
	}
	// ----------------------------------------------------------------
	// Complejidad: O(d), donde d es el número de naves rotas almacenadas en 'navesRotas'
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
	// Complejidad: O(n)
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
