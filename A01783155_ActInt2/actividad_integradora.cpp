/*
    Autores>
        David Medina Domínguez (A01783155)
        Luis Rico Almada (A01252831)
        Arantza Parra Matrínez (A01782023)
    Fecha> 26/11/2023
    Abstract>

    Instrucciones>
            Escribe en C++ un programa que ayude a una empresa que quiere incursionar en los servicios de Internet respondiendo a la situación
            problema 2.
    Parte #1:
        El programa debe leer un archivo de entrada que contiene la información de un grafo representado en forma de una matriz de adyacencias
        con grafos ponderados. El peso de cada arista es la distancia en kilómetros entre colonia y colonia, por donde es factible meter 
        cableado.
        El programa debe desplegar cuál es la forma óptima de cablear con fibra óptica conectando colonias de tal forma que se pueda compartir
        información entre cuales quiera dos colonias.
    Parte #2:
        Debido a que las ciudades apenas están entrando al mundo tecnológico, se requiere que alguien visite cada colonia para ir a dejar estados 
        de cuenta físicos, publicidad,avisos y notificaciones impresos. por eso se quiere saber ¿cuál es la ruta más corta posible que visita
        cada colonia exactamente una vez y al finalizar regresa a la colonia origen?
        El programa debe desplegar la ruta a considerar, tomando en cuenta que la primera ciudad se le llamará A, a la segunda B, y así 
        sucesivamente.

    Parte #3:
         Teniendo en cuenta la ubicación geográfica de varias "centrales" a las que se pueden conectar nuevas casas, la empresa quiere contar 
         con una forma de decidir, dada una nueva contratación del servicio, cuál es la central más cercana geográficamente a esa nueva 
         contratación. No necesariamente hay una central por cada colonia. Se pueden tener colonias sin central, y colonias con más de una 
         central.

*/


#include <iostream>
#include <fstream> //Library to read what is on a file (in/out)
#include <sstream> //Stringstream library
#include <string>
#include <vector>
#include <limits>


// Parte #1: Cableado de fibra óptica (Kruskal)

// Define the structure representing each link
struct links
{
    short weight;
    short source;
    short destination;
    struct links *next;
    struct links *previous;
};
// Head of the linked list
struct links *indice = NULL; 
const int MAX_NODOS = 100;
//Array that stores the parent of each node
int rank[MAX_NODOS];
int adj_matrix[MAX_NODOS][MAX_NODOS];

//Function to add a link to the linked list in a sorted way (by weight)
void add_sort(short weight_, short source_, short destination_)
{
    links *link_;
    link_ = new links;
    if (link_ == NULL)
    { // Check if the new "link" memory space did in fact was created
        std::cout << "Couldn't create new link" << std::endl;
        return;
    }

    // Give the corresponding values to the new link
    link_->weight = weight_;
    link_->source = source_;
    link_->destination = destination_;

    // Create an auxiliary index (leading) to iterate through the double linked list
    struct links *indice_ = indice; 
     // Create another auxiliary index (following)
    struct links *_indice = NULL;  

    // If it is going to be the first link to be added
    if (indice == NULL)
    {
        link_->next = NULL;
        link_->previous = NULL;
        indice = link_;
        return;
    }

    while (indice_ != NULL)
    {
        if (indice_->weight >= link_->weight)
        {
            // Set up right order between links
            link_->previous = _indice;
            link_->next = indice_;
            indice_->previous = link_;

            // In case that it is has the lowest weight of the existing linked list
            if (_indice == NULL)
            {
                indice = link_;
                return;
            }
            // In case that it is not the lowest weight on the list
            _indice->next = link_;
            return;
        }
        // Iterate over
        _indice = indice_;
        indice_ = indice_->next;
    }

    // If it is the link with the heaviest weight (last)
    link_->next = NULL;
    link_->previous = _indice;
    _indice->next = link_;
    return;
    
}

// Lee archivo de texto con la matriz de adyacencias
void readTXT(std::string filename, int& N)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Unable to open file";
        return;
    }

    file >> N; // Leer el número de colonias

    int weight;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            file >> weight;
            adj_matrix[i][j] = weight;
        }
    }
}

//Function to delete the linked list
void delete_links(links *index = indice)
{
    if (index != NULL)
    {
        // std::cout<<index->weight<<std::endl;
        delete_links(index->next);
        delete index;
    }
}

//Function to find the parent of a node in a disjoint set
int find_set(int i)
{
    // If the node is its own parent, it returns it
    if (i == rank[i])
        return i;
    else
    {
        // Looks for the parent of the node
        int result = find_set(rank[i]);
        rank[i] = result;
        return result;
    }
}
//Function to unite two disjoint sets
void union_sets(int source, int destination)
{
    int source_parent = find_set(source);
    int destination_parent = find_set(destination);


    //If the nodes are not in the same set, it unites them
    if (source_parent != destination_parent)
    {
        rank[destination_parent] = source_parent;
    }
}
//Function to add a link to the linked list
void add_link_to_list(links *&list, short weight, short source, short destination)
{
    links *link_ = new links;
    if (link_ == NULL)
    {
        std::cout << "Couldn't create new link" << std::endl;
        return;
    }

    link_->weight = weight;
    link_->source = source;
    link_->destination = destination;
    link_->next = list;
    link_->previous = NULL;
    if (list != NULL)
    {
        list->previous = link_;
    }
    list = link_;
}

links *kruskal_algorithm(links *indice)
{
    // Initialize the result list
    links *kruskal_list = NULL;

    // Iterate over the original list
    while (indice != NULL)
    {
        // If the source and destination are not in the same set, add the link to the result list
        if (find_set(indice->source) != find_set(indice->destination))
        {
            union_sets(indice->source, indice->destination);
            // Add to the MST list instead of the original list
            add_link_to_list(kruskal_list, indice->weight, indice->source, indice->destination);
        }
        indice = indice->next;
    }

    // Return the result list
    return kruskal_list;
}
//Function to initialize the rank array so that each node is its own parent
void initialize_parent()
{
    for (int i = 0; i < MAX_NODOS; i++)
    {
        rank[i] = i;
    }
}
void print_links(links *index)
{
    std::cout << "Conexiones utilizadas:" << std::endl;
    // Create an auxiliary index to print element on list
    links *indice_ = index;
    short count = 1; // Initialize counter for the links

    while (indice_ != NULL)
    {
        std::cout << "[" << count << "] Peso: " << indice_->weight
                  << ", Origen: " << indice_->source
                  << ", Destino: " << indice_->destination << std::endl;
        indice_ = indice_->next;
        ++count; // Increment the counter for each link
    }

    // Removed the total weight calculation and output
    return;
}

void print_mst(links *mst)
{
    std::cout << "Forma de cablear las colonias con fibra:" << std::endl;
    while (mst != NULL)
    {
        std::cout << "(" << mst->source << ", " << mst->destination << ")" << std::endl;
        mst = mst->next;
    }
}
//  Parte #2: Visita de colonias (TSP)
bool in_array(int value, const std::vector<int>& arr){
    for(int i = 0; i < arr.size(); ++i){
        if(arr[i] == value)
            return true;
    }
    return false;
}

void get_hamiltonian_cycle(int N) {
    int min_weight = std::numeric_limits<int>::max();
    std::vector<int> path(N, -1);
    std::vector<bool> visited(N, false);
    path[0] = 0; // Empezando por el nodo 0
    visited[0] = true;
    int total_weight = 0;

    for (int i = 0; i < N - 1; ++i) {
        int closest = -1;
        int closest_dist = min_weight;
        for (int j = 0; j < N; ++j) {
            if (!visited[j] && adj_matrix[path[i]][j] && adj_matrix[path[i]][j] < closest_dist) {
                closest_dist = adj_matrix[path[i]][j];
                closest = j;
            }
        }
        if (closest != -1) {
            path[i + 1] = closest;
            total_weight += closest_dist;
            visited[closest] = true;
        }
    }

    // Agrega el peso para volver al punto de partida
    if (path[N - 1] != -1 && adj_matrix[path[N - 1]][path[0]] != 0) {
        total_weight += adj_matrix[path[N - 1]][path[0]];
    }

    // Imprimir la ruta y el peso total
    std::cout << "La ruta más corta que visita cada nodo exactamente una vez y regresa al origen es: ";
    for (int i = 0; i < N; ++i) {
        if (path[i] != -1) {
            std::cout << static_cast<char>('A' + path[i]) << " -> ";
        }
    }
    std::cout << static_cast<char>('A' + path[0]) << std::endl;
    std::cout << "Costo total del recorrido: " << total_weight << std::endl;
}



//  Parte #3: Centrales de servicio (Euclidean)
int main(int argc, char *argv[])
{

    //Lectura de archivos
    initialize_parent();
     int N=0; 

    readTXT("test1.txt", N);
    
    
     //Pruebas parte #1
    links *mst = kruskal_algorithm(indice);
    std::cout << "----- Parte #1: Cableado de colonias -----" << std::endl;
    print_mst(mst);
    print_links(mst);
    //Free memory
    delete_links(indice);
    delete_links(mst);

    //Pruebas parte #2
    std::cout << "----- Parte #2: Visita de colonias -----" << std::endl;
    if (N > 0) { 
        get_hamiltonian_cycle(N);
    }

    return 0;
}
