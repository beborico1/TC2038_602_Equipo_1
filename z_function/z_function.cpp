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

void print_vec(std::vector <int> mi_vec){
    std::cout<< " After: ";
    for(short i = 0; i < mi_vec.size(); ++i){
        std::cout<< mi_vec[i];
    }
    std::cout<<std::endl;
}

void getPattern(std::string pattern, std::string main_str){
    std::string concatenated_str = pattern + "$" + main_str;
    std::vector <int> tabla_z = getZ(concatenated_str);
    print_vec(tabla_z);
}

int main(){
    std::cout<<"Before: ABABD"<<"$"<<"ABABCABCABABABD"<<std::endl;
    getPattern("ABABD", "ABABCABCABABABD");
    return 0;
}