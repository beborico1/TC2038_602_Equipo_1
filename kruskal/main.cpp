#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// Estructura para representar una arista
struct Edge {
    int src, dest, weight;
};

// Estructura para representar un grafo
struct Graph {
    int V, E;
    std::vector<Edge> edges;
};

// Función para crear un nuevo grafo
Graph* createGraph(int V, int E) {
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edges.resize(E);
    return graph;
}

// Función para encontrar el conjunto de un elemento i
int find(std::vector<int>& parent, int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

// Función para unir dos conjuntos
void Union(std::vector<int>& parent, std::vector<int>& rank, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

// Comparador para ordenar las aristas por peso
bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Función principal para Kruskal
void KruskalMST(Graph* graph) {
    std::vector<Edge> result(graph->V);
    int e = 0;
    int i = 0;

    // Ordenar las aristas por peso
    std::sort(graph->edges.begin(), graph->edges.end(), compareEdges);

    std::vector<int> parent(graph->V);
    std::vector<int> rank(graph->V, 0);

    // Crear V conjuntos con elementos individuales
    for (int v = 0; v < graph->V; ++v) {
        parent[v] = v;
    }

    while (e < graph->V - 1 && i < graph->E) {
        Edge nextEdge = graph->edges[i++];

        int x = find(parent, nextEdge.src);
        int y = find(parent, nextEdge.dest);

        if (x != y) {
            result[e++] = nextEdge;
            Union(parent, rank, x, y);
        }
    }

    int totalWeight = 0;
    for (i = 0; i < e; ++i) {
        std::cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << std::endl;
        totalWeight += result[i].weight;
    }

    std::cout << "Peso total: " << totalWeight << std::endl;
}

int main() {
    std::ifstream file("connections.txt");
    if (!file) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return -1;
    }

    int V, E;
    file >> V >> E;
    Graph* graph = createGraph(V, E);

    for (int i = 0; i < E; i++) {
        file >> graph->edges[i].src >> graph->edges[i].dest >> graph->edges[i].weight;
    }

    KruskalMST(graph);

    delete graph;
    return 0;
}
