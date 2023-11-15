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
#include <vector>
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
int get_relaxed_weight(const int (&arr)[rows][columns]){
    std::array <int, columns> chosen_indexes;
    int max_weight = std::numeric_limits<int>::max();
    int relaxed_weight = 0;

    for(int i = 0; i < columns; ++i){
        int relaxed_col = max_weight;
        for(int j = 0; j < rows; ++j){
            if(arr[i][j] <= relaxed_col && arr[i][j] != 0)
                relaxed_col = arr[i][j]; 
        }
        relaxed_weight += relaxed_col; 
    }
    
    return relaxed_weight;
}

bool in_array(int value, const std::vector<int>& arr){
    for(int i = 0; i < arr.size(); ++i){
        if(arr[i] == value)
            return true;
    }
    return false;
}

// std::array <int, rows> get_hamiltonian_cycle(const int (&arr)[rows][columns]){
template <int columns, int rows>
int get_hamiltonian_cycle(const int (&arr)[rows][columns]){
    int max_weight = std::numeric_limits<int>::max();
    int result = 0;
    std::vector<int> chosenColumns;

    for(int i = 0; i < rows; ++i){  
        int weight = max_weight;
        int col = 0;
        for(int j = 0; j < columns; ++j){
            if(arr[i][j] <= weight  && arr[i][j] != 0 && !in_array(j, chosenColumns)){
                col = j;
                weight = arr[i][j];
            }
        }
        chosenColumns.push_back(col);
        result += weight;
    }
    for(int column : chosenColumns){
        std::cout << column << "->";
    }
        std::cout << chosenColumns[0] << std::endl;
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

    std::cout<< "Matrix: " <<std::endl;
    print_2D_array(test_arr);

    std::cout<< "Relaxed Weight: " <<std::endl;
    std::cout <<  get_relaxed_weight(test_arr) << std::endl; 

    std::cout<< "Hamiltonian Cycle: " <<std::endl;
    std::cout <<  get_hamiltonian_cycle(test_arr) << std::endl; 


    return 0;
}