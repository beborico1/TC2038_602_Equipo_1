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

std::vector<std::vector<int>> test_arr = {
    {0, 10, 15, 20, 25},
    {10, 0, 35, 25, 30},
    {15, 35, 0, 30, 20},
    {20, 25, 30, 0, 10},
    {25, 30, 20, 10, 0}
};

int test_arr_indexes[10] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 0};

// template <int columns, int rows, int index>
// int get_sum_of_indexes(const int (&arr)[rows][columns], const int (&arr_indexes)[index]){
//     int sum = 0;
//     // rows, columns y index deberian de tener el mismo valor
//     for(int i = 0; i < index; i += 2){
//         sum += arr[arr_indexes[i]][arr_indexes[i+1]];
//     }
//     return sum;
// }

int get_relaxed_weight(const std::vector<std::vector<int>>& matrix){
    int max_weight = std::numeric_limits<int>::max();
    int relaxed_weight = 0;

    for(int i = 0; i < matrix.size(); ++i){
        int relaxed_col = max_weight;
        for(int j = 0; j < matrix.size(); ++j){
            if(matrix[i][j] <= relaxed_col && matrix[i][j] != 0)
                relaxed_col = matrix[i][j]; 
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

int get_hamiltonian_cycle(const std::vector<std::vector<int>>& matrix){
    int max_weight = std::numeric_limits<int>::max();
    int result = 0;
    std::vector<int> chosenColumns;

    for(int i = 0; i < matrix.size(); ++i){  
        int weight = max_weight;
        int col = 0;
        for(int j = 0; j < matrix.size(); ++j){
            if(matrix[i][j] <= weight  && matrix[i][j] != 0 && !in_array(j, chosenColumns)){
                col = j;
                weight = matrix[i][j];
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

void print_matrix(const std::vector<std::vector<int>>& matrix){
    for(int i = 0; i < matrix.size(); ++i){
            for(int j = 0; j < matrix.size(); ++j)
                std::cout<<matrix[i][j]<<" ";
            std::cout<<std::endl;
    }
}


int main() {
    // int A[5][5];

    std::cout<< "Matrix: " <<std::endl;
    print_matrix(test_arr);

    std::cout<< "Relaxed Weight: " <<std::endl;
    std::cout <<  get_relaxed_weight(test_arr) << std::endl; 

    std::cout<< "Hamiltonian Cycle: " <<std::endl;
    std::cout <<  get_hamiltonian_cycle(test_arr) << std::endl; 


    return 0;
}