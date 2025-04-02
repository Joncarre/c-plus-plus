
#include "GrafoDirigido.h"

GrafoDirigido::GrafoDirigido(std::string file) {
    std::ifstream entrada(file);
    if (entrada.fail())
        throw std::runtime_error("Error en fichero");
    entrada >> _V;
    _E = 0;
    _adj.resize(_V);
    size_t e;
    entrada >> e;
    size_t v, w;
    for (auto i = 0; i < e; ++i) {
        entrada >> v;
        entrada >> w;
        ponArista(v, w);
    }
    entrada.close();
}

void GrafoDirigido::ponArista(size_t v, size_t w) {
    if (v >= _V || w >= _V) throw std::invalid_argument("Vértice inexistente");
    ++_E;
    _adj[v].push_back(w);
}

bool GrafoDirigido::hayArista(size_t v, size_t w) const {
    for (auto u : _adj[v])
        if (u == w) return true;
    return false;
}

Adys const& GrafoDirigido::adj(size_t v) const {
    if (v >= _V) throw std::invalid_argument("Vértice inexistente");
    return _adj[v];
}

/**
 * Devuelve el grafo dirigido inverso.
 */
GrafoDirigido GrafoDirigido::reverse() const {
    GrafoDirigido R(_V);
    for (auto v = 0; v < _V; ++v) {
        for (auto w : _adj[v]) {
            R.ponArista(w, v);
        }
    }
    return R;
}

/**
 * Muestra el grafo en el stream de salida o
 */
void GrafoDirigido::print(std::ostream& o) const {
    o << _V << " vértices, " << _E << " aristas\n";
    for (auto v = 0; v < _V; ++v) {
        o << v << ": ";
        for(auto w : _adj[v]) {
            o << w << " ";
        }
        o << "\n";
    }
}

std::ostream& operator<<(std::ostream& o,GrafoDirigido const& g){
    g.print(o);
    return o;
}

/**
 * Recorrido en profundidad de un grafo a partir de un vértice origen.
 * Permite recuperar los caminos desde el origen a todos los vértices alcanzables.
 */

DepthFirstDirectedPaths::DepthFirstDirectedPaths(GrafoDirigido const& G, size_t s) : marked(G.V(), false),
edgeTo(G.V()), s(s) {
    dfs(G, s);
}

// Devuelve un camino desde el origen a v (vacío si no están conectados).
Path DepthFirstDirectedPaths::pathTo(size_t v) const {
    Path path;
    if (!hasPathTo(v)) return path;
    for (auto x = v; x != s; x = edgeTo[x])
        path.push_front(x);
    path.push_front(s);
    return path;
}


// recorrido en profundidad desde v
void DepthFirstDirectedPaths::dfs(GrafoDirigido const& G, size_t v) {
    marked[v] = true;
    for (size_t w : G.adj(v)) {
        if (!marked[w]) {
            edgeTo[w] = v;
            dfs(G, w);
        }
    }
}


/**
 * Recorrido en anchura de un grafo a partir de un vértice origen.
 * Permite recuperar los caminos más cortos desde el origen a todos los vértices alcanzables.
 */
// BFS desde un único origen
BreadthFirstDirectedPaths::BreadthFirstDirectedPaths(GrafoDirigido const& G, size_t s) : marked(G.V(), false),
edgeTo(G.V()), distTo(G.V()) {
    bfs(G, { s } );
}

// BFS desde múltiples origenes
BreadthFirstDirectedPaths::BreadthFirstDirectedPaths(GrafoDirigido const& G, std::vector<size_t> const& ss) :
marked(G.V(), false), edgeTo(G.V()), distTo(G.V()) {
    bfs(G, ss);
}

// Devuelve el camino más corto desde el origen a v (vacío si no están conectados).
Path BreadthFirstDirectedPaths::pathTo(size_t v) const {
    Path path;
    if (!hasPathTo(v)) return path;
    size_t x;
    for (x = v; distTo[x] != 0; x = edgeTo[x])
        path.push_front(x);
    path.push_front(x);
    return path;
}

void BreadthFirstDirectedPaths::bfs(GrafoDirigido const& G, std::vector<size_t> const& ss) {
    std::queue<size_t> q;
    for(auto s : ss) {
        distTo[s] = 0;
        marked[s] = true;
        q.push(s);
    }
    while (!q.empty()) {
        size_t v = q.front(); q.pop();
        for (size_t w : G.adj(v)) {
            if (!marked[w]) {
                edgeTo[w] = v;
                distTo[w] = distTo[v] + 1;
                marked[w] = true;
                q.push(w);
            }
        }
    }
}


// depth-first search preorder and postorder in a digraph
DepthFirstOrder::DepthFirstOrder(GrafoDirigido const& G) :
marked(G.V(), false), pre(G.V()), post(G.V()), preCounter(0), postCounter(0) {
    for (auto v = 0; v < G.V(); ++v)
        if (!marked[v]) dfs(G, v);
}

// run DFS in digraph G from vertex v and compute preorder/postorder
void DepthFirstOrder::dfs(GrafoDirigido const& G, size_t v) {
    marked[v] = true;
    pre[v] = preCounter++;
    preorder.push_back(v);
    for (auto w : G.adj(v)) {
        if (!marked[w]) {
            dfs(G, w);
        }
    }
    postorder.push_back(v);
    post[v] = postCounter++;
    revPost.push_front(v);
}


DirectedCycle::DirectedCycle(GrafoDirigido const& G) :
marked(G.V(),false), edgeTo(G.V()), onStack(G.V(), false), hayciclo(false) {
    for (auto v = 0; v < G.V(); v++)
        if (!marked[v])
            dfs(G, v);
}


// check that algorithm computes either the topological order or finds a directed cycle
void DirectedCycle::dfs(GrafoDirigido const& G, size_t v) {
    onStack[v] = true;
    marked[v] = true;
    for (auto w : G.adj(v)) {
        // short circuit if directed cycle found
        if (hayciclo) return;
        //found new vertex, so recur
        else if (!marked[w]) {
            edgeTo[w] = v;
            dfs(G, w);
        }
        // trace back directed cycle
        else if (onStack[w]) {
            hayciclo = true;
            for (auto x = v; x != w; x = edgeTo[x]) {
                ciclo.push_front(x);
            }
            ciclo.push_front(w);
            ciclo.push_front(v);
        }
    }
    onStack[v] = false;
}


// topological sort in a digraph
Topological::Topological(GrafoDirigido const& G) {
    DirectedCycle finder{G};
    if (!finder.hasCycle()) {
        hayOrden = true;
        DepthFirstOrder dfs{G};
        _order = dfs.reversePost();
    } else hayOrden = false;
}


KosarajuSharirSCC::KosarajuSharirSCC(GrafoDirigido const& G) : marked(G.V(), false), _id(G.V()), _count(0) {
    
    // compute reverse postorder of reverse graph
    DepthFirstOrder dfsrev(G.reverse());
    
    // run DFS on G, using reverse postorder to guide calculation
    for (auto v : dfsrev.reversePost()) {
        if (!marked[v]) {
            dfs(G, v);
            _count++;
        }
    }
}

// DFS on graph G
void KosarajuSharirSCC::dfs(GrafoDirigido const& G, size_t v) {
    marked[v] = true;
    _id[v] = _count;
    for (auto w : G.adj(v)) {
        if (!marked[w]) dfs(G, w);
    }
}
