//
//  GrafoDirigido.h
//
//  Implementación de grafos dirigidos y clases que los exploran
//
//  Técnicas Algoritmicas en Ingeniería del Software / Diseño de Algoritmos
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Created by Alberto Verdejo on 26/6/15.
//  Copyright (c) 2015 Alberto Verdejo. All rights reserved.
//

#ifndef GRAFODIRIGIDO_H_
#define GRAFODIRIGIDO_H_

#include <iostream>
#include <fstream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

using Adys = std::vector<size_t>;  // lista de adyacentes a un vértice
using Path = std::deque<size_t>;   // para representar caminos

class GrafoDirigido {
public:
    
    /**
     * Crea un grafo con V vértices.
     */
    GrafoDirigido(size_t v) : _V{v}, _E{0}, _adj(_V) {}
    
    /**
     * Crea un grafo a partir de un fichero de entrada.
     */
    GrafoDirigido(std::string file);
        
    /**
     * Devuelve el número de vértices del grafo.
     */
    size_t V() const { return _V; }
    
    /**
     * Devuelve el número de aristas del grafo.
     */
    size_t E() const { return _E; }
    
    /**
     * Añade la arista dirigida v-w al grafo.
     * @throws invalid_argument si algún vértice no existe
     */
    void ponArista(size_t v, size_t w);
    
    /**
     * Comprueba si hay arista de u a v.
     */
    bool hayArista(size_t v, size_t w) const;
    
    /**
     * Devuelve la lista de adyacencia de v.
     * @throws invalid_argument si v no existe
     */
    Adys const& adj(size_t v) const;
    
    /**
     * Devuelve el grafo dirigido inverso.
     */
    GrafoDirigido reverse() const;
    
    /**
     * Muestra el grafo en el stream de salida o
     */
    void print(std::ostream& o = std::cout) const;
    
private:
    size_t _V;   // número de vértices
    size_t _E;   // número de aristas
    std::vector<Adys> _adj;   // vector de listas de adyacentes
    
};

/**
 * Para mostrar grafos por la salida estándar.
 */
std::ostream& operator<<(std::ostream& o,GrafoDirigido const& g);


/**
 * Recorrido en profundidad de un grafo a partir de un vértice origen.
 * Permite recuperar los caminos desde el origen a todos los vértices alcanzables.
 */
class DepthFirstDirectedPaths {
public:
    DepthFirstDirectedPaths(GrafoDirigido const& G, size_t s);
    
    // Hay camino del origen a v?
    bool hasPathTo(size_t v) const { return marked[v]; }
    
    // Devuelve un camino desde el origen a v (vacío si no están conectados).
    Path pathTo(size_t v) const;
    
private:
    std::vector<bool> marked;     // marked[v] = hay camino s-v?
    std::vector<size_t> edgeTo;   // edgeTo[v] = último vértice antes de llegar a v
    size_t s;                     // vértice origen
    
    // recorrido en profundidad desde v
    void dfs(GrafoDirigido const& G, size_t v);
};


/**
 * Recorrido en anchura de un grafo a partir de un vértice origen.
 * Permite recuperar los caminos más cortos desde el origen a todos los vértices alcanzables.
 */
class BreadthFirstDirectedPaths {
public:
    // BFS desde un único origen
    BreadthFirstDirectedPaths(GrafoDirigido const& G, size_t s);
    
    // BFS desde múltiples origenes
    BreadthFirstDirectedPaths(GrafoDirigido const& G, std::vector<size_t> const& ss);
    
    // Hay camino del origen a v?
    bool hasPathTo(size_t v) const { return marked[v]; }
    
    // Devuelve el camino más corto desde el origen a v (vacío si no están conectados).
    Path pathTo(size_t v) const;
    
    // Devuelve el número de aristas en el camino más corto a v
    size_t distance(size_t v) const {
        return distTo[v];
    }
    
private:
    std::vector<bool> marked;     // marked[v] = hay camino s-v?
    std::vector<size_t> edgeTo;   // edgeTo[v] = último vértice antes de llegar a v
    std::vector<size_t> distTo;   // distTo[v] = número de aristas en el camino s-v más corto
    
    void bfs(GrafoDirigido const& G, std::vector<size_t> const& ss);
};


/**
 * Recorridos en preorden y postorden de un grafo dirigido.
 */
class DepthFirstOrder {
public:
    DepthFirstOrder(GrafoDirigido const& G);
    
    size_t prenum(size_t v) const { return pre[v]; }
    
    size_t postnum(size_t v) const { return post[v]; }
    
    // devuelve los vértices en postorden
    std::deque<size_t> const& postOrder() const { return postorder; }
    
    // devuelve los vértices en preorden
    std::deque<size_t> const& preOrder() const { return preorder; }
    
    // devuelve los vértices en postorden inverso
    std::deque<size_t> const& reversePost() const { return revPost; }
    
private:
    std::vector<bool> marked;       // marked[v] = se ha alcanzado a v en el dfs?
    std::vector<size_t> pre;        // pre[v]    = número en preorden de v
    std::vector<size_t> post;       // post[v]   = número en postorden de v
    std::deque<size_t> preorder;    // vértices en preorden
    std::deque<size_t> postorder;   // vértices en postorden
    std::deque<size_t> revPost;     // vértices en postorden inverso
    size_t preCounter;              // contador para numerar en preorden
    size_t postCounter;             // contador para numerar en postorden
    
    void dfs(GrafoDirigido const& G, size_t v);
};


/**
 * Detecta si un grafo dirigido tiene ciclos.
 */
class DirectedCycle {
public:
    DirectedCycle(GrafoDirigido const& G);
    bool hasCycle() const { return hayciclo; }
    Path const& cycle() const { return ciclo; }
private:
    std::vector<bool> marked;        // marked[v] = se ha alcanzado a v en el dfs?
    std::vector<size_t> edgeTo;      // edgeTo[v] = vértice anterior en el camino a v
    std::vector<bool> onStack;       // onStack[v] = está el vértice v en la pila?
    Path ciclo;           // ciclo dirigido (vacío si no existe)
    bool hayciclo;
    
    void dfs(GrafoDirigido const& G, size_t v);
    
};


/**
 * Halla una ordenación topológica de un grafo dirigido (si existe).
 * La ordenación topológica existe si el grafo es acíclico.
 */
class Topological {
public:
    Topological(GrafoDirigido const& G);
    
    // devuelve la ordenación topológica si existe
    std::deque<size_t> const& order() const { return _order; }
    
    // existe la ordenación topológica?
    bool hasOrder() const { return hayOrden; }
private:
    std::deque<size_t> _order;    // ordenación topológica
    bool hayOrden;
};


/**
 * Detecta las componentes fuertemente conexas de un grafo dirigido.
 */
class KosarajuSharirSCC {
public:
    KosarajuSharirSCC(GrafoDirigido const& G);
    
    // devuelve el número de componentes fuertemente conexas del grafo
    size_t count() const { return _count; }
    
    // pertenecen v y w a la misma componente?
    bool stronglyConnected(size_t v, size_t w) const { return _id[v] == _id[w]; }
    
    // devuelve el id de la componente fuerte de v
    size_t id(size_t v) const { return _id[v]; }
private:
    std::vector<bool> marked;  // marked[v] = se ha visitado el vértice v?
    std::vector<size_t> _id;   // id[v] = id de la componente que contiene a v
    size_t _count;             // número de componentes
    
    void dfs(GrafoDirigido const& G, size_t v);
};

#endif /* GRAFODIRIGIDO_H_ */
