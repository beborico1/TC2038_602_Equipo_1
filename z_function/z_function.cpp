/*
    Authors> 
        David Medina Domínguez (A01783155)
        Luis Rico Almada (A01252831)
        Arantza Parra Matrínez (A01782023) 
    Date> 21/09/2023
    Abstract>
        in this work we implement the z function to find patterns on a string :)
*/


#include <iostream>
#include <vector>
#include <string>

// Función para construir la tabla 'Z' para el algoritmo z function.
std::vector <int> getZ (std::string str) {
    std::vector<int> z_vec(str.length(), 0); // Inicializar el vector 'z_vec' con ceros.
    int x = 0; // indice de inicio de busqueda
    int y = 1; // indice de fin de busqueda

    for(short i = 1; i < str.length(); ++i){
        short contador = 0;
        y = i;
        x = 0;

        // std::cout<<str[x]<<"---"<<str[y]<<std::endl;
        while(str[x] == str[y] && y <= str.length()){
            // std::cout<<"__"<<str[x]<<"---"<<str[y]<<std::endl;
            ++contador;++x;++y;
        }
        if(str[x] == str[y] && y == i){
            ++contador;
            z_vec[i] = contador;
            return z_vec;
        }
        z_vec[i] = contador;
    }
    return z_vec;
}

std::vector <int> getIndexes(std::vector <int> mi_vec, std::string pattern){
    std::vector <int> indexes;
    for(short i = 0; i < mi_vec.size(); ++i){
        if(mi_vec[i] == pattern.length()){
            indexes.push_back(i-pattern.length()-1);
        }
    }
    return indexes;
}

void print_vec(std::vector <int> mi_vec){
    for(short i = 0; i < mi_vec.size(); ++i){
        std::cout<< mi_vec[i];
        if(i != mi_vec.size()-1){
            std::cout<<",";
        }
    }
    std::cout<<std::endl;
}

std::vector <int> getPattern(std::string pattern, std::string main_str){
    std::string concatenated_str = pattern + "$" + main_str;
    std::vector <int> tabla_z = getZ(concatenated_str);
    print_vec(tabla_z);
    return tabla_z;
}

int main(){
    std::string pattern = "ABABD";
    std::string main_str = "ABABCABCABABABD";
    std::cout<<"Pattern: "<< pattern<<std::endl;
    std::cout<<"main_str: "<< main_str<<std::endl;
    std::cout<<"Concatenated string: "<< pattern + "$" + main_str<<std::endl;
    std::cout<<"Z table: ";
    std::vector <int> final_vector = getPattern(pattern, main_str);
    std::vector <int> indexes = getIndexes(final_vector, pattern);
    std::cout<<"Index where we can find the pattern: ";
    print_vec(indexes);


    return 0;
}
