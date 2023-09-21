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

void print_ztable(std::vector <int> mi_vec){
    std::cout<< "Z Table: ";
    for(short i = 0; i < mi_vec.size(); ++i){
        if (i == mi_vec.size() - 1){
            std::cout<< mi_vec[i];
        } else {
            std::cout<< mi_vec[i] << ",";
        }
    }
    std::cout<<std::endl;
}

void getPattern(std::string pattern, std::string main_str){
    std::string concatenated_str = pattern + "$" + main_str;
    std::vector <int> tabla_z = getZ(concatenated_str);
    print_ztable(tabla_z);
    for (short i = 0; i < tabla_z.size(); ++i){
        if(tabla_z[i] == pattern.length()){
            // Quitamos al indice el tamaño del patron y el caracter '$'
            std::cout<<"Pattern found at index: "<< i - pattern.length() - 1 <<std::endl;
        }
    }
}

int main(){
    std::string main_str = "ABABD";
    std::string pattern = "ABABCABCABABABD";
    std::cout<<"Pattern: " << pattern << std::endl;
    std::cout<<"Main String: " << main_str << std::endl;
    std::cout<<"Concatenated String: " << pattern << "$" << main_str << std::endl;
    getPattern(pattern, main_str);
    return 0;
}