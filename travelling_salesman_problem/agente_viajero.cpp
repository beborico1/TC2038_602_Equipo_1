/*
    Autores> 
        David Medina Domínguez (A01783155)
        Luis Rico Almada (A01252831)
        Arantza Parra Matrínez (A01782023) 
    Fecha> 14/11/2023
    Abstract>

    Instrucciones>
        Por equipo, implementen un programa en C++ que pueda resolver el problema del agente viajero usando Branch and Bound.

        Entrada: Matriz de adyacencia de tamaño N x N, donde N son el número de ciudades a visitar.
        Salida: Recorrido que se debe realizar y el costo total de éste.        
*/

#include <iostream>
#include <array>
#include <limits> //Solo para encontrar el numero mas grande de un tipo de dato

int test_arr[5][5] = {
    {0, 10, 15, 20, 25},
    {10, 0, 35, 25, 30},
    {15, 35, 0, 30, 20},
    {20, 25, 30, 0, 10},
    {25, 30, 20, 10, 0}
};

int test_arr_indexes[10] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 0};
// void get_relaxed_weight(const std::array<std::array<int, colums>, rows>& arr){ //Por si queremos crear nuestro array desde un txt, mabe

template <int columns, int rows, int index> // Otra opcion es: size_t, y asi no definirlo, dejarselo al compilador
int get_sum_of_indexes(const int (&arr)[rows][columns], const int (&arr_indexes)[index]){
    int sum = 0;
    // rows, columns y index deberian de tener el mismo valor
    for(int i = 0; i < index; i += 2){
        sum += arr[arr_indexes[i]][arr_indexes[i+1]];
    }
    return sum;
}

template <int columns, int rows> // Estos son un template que seran remplazados por el correcto type cuando sean instanceadas :o
int get_relaxed_weight(const int (&arr)[rows][columns]){ //Esto es basicamente un BFS
    std::array <int, columns> chosen_indexes;
    int relaxed_weight = std::numeric_limits<int>::max();

    //Aqui hacer una función recursiva que haga un BFS y que regrese el peso relajado
    auto BFS = [](int a, int b) -> int {
        if()
        return BFS();
    };
    
    return relaxed_weight;
}

template <int columns, int rows>
std::array <int, rows> get_hamiltonian_cycle(const int (&arr)[rows][columns], int relaxed_weight){
    std::array<int, rows> result;
    int relaxed_weight = get_relaxed_weight(arr);   
    //Aqui si se tiene que hacer el hamiltonian cycle (la que esta en "Travelling Salesman Problem.pdf")

    return result;
}

template <int columns, int rows>
void print_2D_array(const int (&arr)[rows][columns]){
    for(int i = 0; i < rows; ++i){
            for(int j = 0; j < columns; ++j)
                std::cout<<arr[i][j]<<" ";
            std::cout<<std::endl;
    }
}


int main() {
    int A[5][5];
    std::cout << std::max(1, 2) << std::endl; 

    get_relaxed_weight(test_arr);

    std::cout << get_sum_of_indexes(test_arr, test_arr_indexes) << std::endl;

    print_2D_array(test_arr);

    return 0;
}